/*	@(#)uud.c	1.2	96/03/01 16:53:14 */
/* uud - bulletproof version of uudecode */

/*
 * Uud -- decode a uuencoded file back to binary form.
 *
 * From the Berkeley original, modified by MSD, RDR, JPHD & WLS.
 * The Atari GEMDOS version compiled with MWC 2.x.
 * The MSDOS version with TurboC.
 * The Unix version with cc.
 * this version is made: 25 Nov 1988.
 * Jan 2 1990: Change system definition and change MSDOS to open the output
 *             file for write binary do cr/lf replacement.
 */

#define UNIX  1		/* define one of: UNIX (Minix too!), MSDOS, or GEMDOS */ 

#ifdef GEMDOS
#define SYSNAME "gemdos"
#define SMALL 1
#endif
#ifdef MSDOS
#define SYSNAME "msdos"
#define SMALL 1
#endif
#ifdef UNIX
#define SYSNAME "unix"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef GEMDOS
#include <osbind.h>
#define Error(n)  { Bconin(2); exit(n); }
#else
#define Error(n)  exit(n)
#endif
#ifdef UNIX
#define WRITE	  "w"
#else
#define WRITE	  "wb"		/* for both MSDOS and GEMDOS!	*/
#endif

#define loop	while (1)

char *getnword();

#define NCHARS  256
#define LINELEN 256
#define FILELEN 64
#define NORMLEN 60	/* allows for 80 encoded chars per line */

#define SEQMAX 'z'
#define SEQMIN 'a'
char seqc;
int first, secnd, check, numl;

FILE *in, *out;
char *pos;
char ifname[FILELEN], ofname[FILELEN];
char *source = NULL, *target = NULL;
char blank, part = '\0';
int partn, lens;
int debug = 0, nochk = 0, onedone = 0;
int chtbl[NCHARS], cdlen[NORMLEN + 3];

/* Forward */
void gettable();
void decode();

main(argc, argv) int argc; char *argv[];
{
	int mode;
	register int i, j;
	char *curarg;
	char dest[FILELEN], buf[LINELEN];

	if (argc < 2) {
		format("Usage: uud [-n] [-d] [-s dir] [-t dir] input-file\n");
		Error(1);
	}

	curarg = argv[1];
	
	while (curarg[0] == '-') {
		if (((curarg[1] == 'd') || (curarg[1] == 'D')) &&
		    (curarg[2] == '\0')) {
			debug = 1;
		} else if (((curarg[1] == 'n') || (curarg[1] == 'N')) &&
			   (curarg[2] == '\0')) {
			nochk = 1;
		} else if (((curarg[1] == 't') || (curarg[1] == 'T')) &&
			   (curarg[2] == '\0')) {
			argv++;
			argc--;
			if (argc < 2) {
				format("uud: Missing target directory.\n");
				Error(15);
			}
			target = argv[1];
			if (debug)
				format("Target dir = %s\n",target);
		} else if (((curarg[1] == 's') || (curarg[1] == 'S')) &&
			   (curarg[2] == '\0')) {
			argv++;
			argc--;
			if (argc < 2) {
				format("uud: Missing source directory.\n");
				Error(15);
			}
			source = argv[1];
			if (debug)
				format("Source dir = %s\n",source);
		} else if (curarg[1] != '\0') {
			format("uud: Unknown option <%s>\n", curarg);
			Error(15);
		} else
			break;
		argv++;
		argc--;
		if (argc < 2) {
			format("uud: Missing file name.\n");
			Error(15);
		}
		curarg = argv[1];
	}

	if ((curarg[0] == '-') && (curarg[1] == '\0')) {
		in = stdin;
		strcpy(ifname, "<stdin>");
	} else {
		if (source != NULL) {
			strcpy(ifname, source);
			strcat(ifname, curarg);
		} else
			strcpy(ifname, curarg);
		if ((in = fopen(ifname, "r")) == NULL) {
			format("uud: Can't open %s\n", ifname);
			Error(2);
		}
		numl = 0;
	}

/*
 * Set up the default translation table.
 */
	for (i = 0; i < ' '; i++) chtbl[i] = -1;
	for (i = ' ', j = 0; i < ' ' + 64; i++, j++) chtbl[i] = j;
	for (i = ' ' + 64; i < NCHARS; i++) chtbl[i] = -1;
	chtbl['`'] = chtbl[' '];	/* common mutation */
	chtbl['~'] = chtbl['^'];	/* an other common mutation */
	blank = ' ';
/*
 * set up the line length table, to avoid computing lotsa * and / ...
 */
	cdlen[0] = 1;
	for (i = 1, j = 5; i <= NORMLEN; i += 3, j += 4)
		cdlen[i] = (cdlen[i + 1] = (cdlen[i + 2] = j));
/*
 * search for header or translation table line.
 */
	loop {	/* master loop for multiple decodes in one file */
		partn = 'a';
		loop {
			if (fgets(buf, sizeof buf, in) == NULL) {
				if (onedone) {
					if (debug) format("End of file.\n");
					exit(0);
				} else {
					format("uud: No begin line.\n");
					Error(3);
				}
			}
			numl++;
			if (strncmp(buf, "table", 5) == 0) {
				gettable();
				continue;
			}
			if (strncmp(buf, "begin", 5) == 0) {
				break;
			}
		}
		lens = strlen(buf);
		if (lens) buf[--lens] = '\0';
#ifdef SMALL
		if ((pos = getnword(buf, 3))) {
			strcpy(dest, pos);
		} else
#else
		if(sscanf(buf,"begin%o%s", &mode, dest) != 2)
#endif
		{
			format("uud: Missing filename in begin line.\n");
			Error(10);
		}

		if (target != NULL) {
			strcpy(ofname, target);
			strcat(ofname, dest);
		} else
			strcpy(ofname, dest);

		if((out = fopen(ofname, WRITE)) == NULL) {
			format("uud: Cannot open output file: %s\n", ofname);
			Error(4);
		}
		if (debug) format("Begin uudecoding: %s\n", ofname);
		seqc = SEQMAX;
		check = nochk ? 0 : 1;
		first = 1;
		secnd = 0;
		decode();
		fclose(out);
#ifdef UNIX
		chmod(ofname, mode);
#endif
		onedone = 1;
		if (debug) format("End uudecoding: %s\n", ofname);
	}	/* master loop for multiple decodes in one file */
}

/*
 * Bring back a pointer to the start of the nth word.
 */
char *getnword(str, n) register char *str; register int n;
{
	while((*str == '\t') || (*str == ' ')) str++;
	if (! *str) return NULL;
	while(--n) {
		while ((*str != '\t') && (*str != ' ') && (*str)) str++;
		if (! *str) return NULL;
		while((*str == '\t') || (*str == ' ')) str++;
		if (! *str) return NULL;
	}
	return str;
}

/*
 * Install the table in memory for later use.
 */
void
gettable()
{
	char buf[LINELEN];
	register int c, n = 0;
	register char *cpt;

	for (c = 0; c < NCHARS; c++) chtbl[c] = -1;

again:	if (fgets(buf, sizeof buf, in) == NULL) {
		format("uud: EOF while in translation table.\n");
		Error(5);
	}
	numl++;
	if (strncmp(buf, "begin", 5) == 0) {
		format("uud: Incomplete translation table.\n");
		Error(6);
	}
	cpt = buf + strlen(buf) - 1;
	*cpt = ' ';
	while (*(cpt) == ' ') {
		*cpt = 0;
		cpt--;
	}
	cpt = buf;
	while (c = *cpt) {
		if (chtbl[c] != -1) {
			format("uud: Duplicate char in translation table.\n");
			Error(7);
		}
		if (n == 0) blank = c;
		chtbl[c] = n++;
		if (n >= 64) return;
		cpt++;
	}
	goto again;
}

/*
 * copy from in to out, decoding as you go along.
 */

void
decode()
{
	char buf[LINELEN], outl[LINELEN];
	register char *bp, *ut;
	register int *trtbl = chtbl;
	register int n, c, rlen;
	register unsigned int len;

	loop {
		if (fgets(buf, sizeof buf, in) == NULL) {
			format("uud: EOF before end.\n");
			fclose(out);
			Error(8);
		}
		numl++;
		len = strlen(buf);
		if (len) buf[--len] = '\0';
/*
 * Is it an unprotected empty line before the end line ?
 */
		if (len == 0) continue;
/*
 * Get the binary line length.
 */
		n = trtbl[*buf];
		if (n >= 0) goto decod;
/*
 * end of uuencoded file ?
 */
		if (strncmp(buf, "end", 3) == 0) return;
/*
 * end of current file ? : get next one.
 */
		if (strncmp(buf, "include", 7) == 0) {
			getfile(buf);
			continue;
		}
		format("uud: Bad prefix line %d in file: %s\n",numl, ifname);
		if (debug) format("Bad line =%s\n",buf);
		Error(11);
/*
 * Sequence checking ?
 */
decod:		rlen = cdlen[n];
/*
 * Is it the empty line before the end line ?
 */
		if (n == 0) continue;
/*
 * Pad with blanks.
 */
		for (bp = &buf[c = len];
			c < rlen; c++, bp++) *bp = blank;
/*
 * Verify if asked for.
 */
		if (debug) {
			for (len = 0, bp = buf; len < rlen; len++) {
				if (trtbl[*bp] < 0) {
					format(
	"Non uuencoded char <%c>, line %d in file: %s\n", *bp, numl, ifname);
					format("Bad line =%s\n",buf);
					Error(16);
				}
				bp++;
			}
		}
/*
 * All this just to check for uuencodes that append a 'z' to each line....
 */
		if (secnd && check) {
			secnd = 0;
			if (buf[rlen] == SEQMAX) {
				check = 0;
				if (debug) format("Sequence check turned off (2).\n");
			} else
				if (debug) format("Sequence check on (2).\n");
		} else if (first && check) {
			first = 0;
			secnd = 1;
			if (buf[rlen] != SEQMAX) {
				check = 0;
				if (debug) format("No sequence check (1).\n");
			} else
				if (debug) format("Sequence check on (1).\n");
		}
/*
 * There we check.
 */
		if (check) {
			if (buf[rlen] != seqc) {
				format("uud: Wrong sequence line %d in %s\n",
					numl, ifname);
				if (debug)
					format(
	"Sequence char is <%c> instead of <%c>.\n", buf[rlen], seqc);
				Error(18);
			}
			seqc--;
			if (seqc < SEQMIN) seqc = SEQMAX;
		}
/*
 * output a group of 3 bytes (4 input characters).
 * the input chars are pointed to by p, they are to
 * be output to file f.n is used to tell us not to
 * output all of them at the end of the file.
 */
		ut = outl;
		len = n;
		bp = &buf[1];
		while (n > 0) {
			*(ut++) = trtbl[*bp] << 2 | trtbl[bp[1]] >> 4;
			n--;
			if (n) {
				*(ut++) = (trtbl[bp[1]] << 4) |
					  (trtbl[bp[2]] >> 2);
				n--;
			}
			if (n) {
				*(ut++) = trtbl[bp[2]] << 6 | trtbl[bp[3]];
				n--;
			}
			bp += 4;
		}
		if ((n = fwrite(outl, 1, len, out)) <= 0) {
			format("uud: Error on writing decoded file.\n");
			Error(18);
		}
	}
}

/*
 * Find the next needed file, if existing, otherwise try further
 * on next file.
 */
getfile(buf) register char *buf;
{
	if ((pos = getnword(buf, 2)) == NULL) {
		format("uud: Missing include file name.\n");
		Error(17);
	} else
		if (source != NULL) {
			strcpy(ifname, source);
			strcat(ifname, pos);
		} else
			strcpy(ifname, pos);
#ifdef GEMDOS
	if (Fattrib(ifname, 0, 0) < 0)
#else
	if (access(ifname, 04))
#endif
	{
		if (debug) {
			format("Cant find: %s\n", ifname);
			format("Continuing to read same file.\n");
		}
	}
	else {
		if (freopen(ifname, "r", in) == in) {
			numl = 0;
			if (debug) 
				format("Reading next section from: %s\n", ifname);
		} else {
			format("uud: Freopen abort: %s\n", ifname);
			Error(9);
		}
	}
	loop {
		if (fgets(buf, LINELEN, in) == NULL) {
			format("uud: No begin line after include: %s\n", ifname);
			Error(12);
		}
		numl++;
		if (strncmp(buf, "table", 5) == 0) {
			gettable();
			continue;
		}
		if (strncmp(buf, "begin", 5) == 0) break;
	}
	lens = strlen(buf);
	if (lens) buf[--lens] = '\0';
/*
 * Check the part suffix.
 */
	if ((pos = getnword(buf, 3)) == NULL ) {
		format("uud: Missing part name, in included file: %s\n", ifname);
		Error(13);
	} else {
		part = *pos;
		partn++;
		if (partn > 'z') partn = 'a';
		if (part != partn) {
			format("uud: Part suffix mismatch: <%c> instead of <%c>.\n",
				part, partn);
			Error(14);
		}
		if (debug) format("Reading part %c\n", *pos);
	}
}

/*
 * Printf style formatting. (Borrowed from MicroEmacs by Dave Conroy.) 
 * A lot smaller than the full fledged printf.
 */
/* VARARGS1 */
format(fp, args) char *fp;
{
	doprnt(fp, (char *)&args);
}

doprnt(fp, ap)
register char	*fp;
register char	*ap;
{
	register int	c, k;
	register char	*s;

	while ((c = *fp++) != '\0') {
		if (c != '%')
			outc(c);
		else {
			c = *fp++;
			switch (c) {
			case 'd':
				puti(*(unsigned int *)ap, 10);
				ap += sizeof(int);
				break;

			case 's':
				s = *(char **)ap;
				while ((k = *s++) != '\0')
					outc(k);
				ap += sizeof(char *);
				break;

			case 'c':
				outc(*(int *)ap);
				ap += sizeof(int);
				break;

			default:
				outc(c);
			}
		}
	}
}

/*
 * Put integer, in radix "r".
 */
puti(i, r)
register unsigned int	i;
register unsigned int	r;
{
	register unsigned int	q, s;

	if ((q = i / r) != 0)
		puti(q, r);
	s = i % r;
	if (s <= 9)
		outc((int) (s + '0'));
	else
		outc((int) (s - 10 + 'A'));
}

outc(c)
register int c;
{
#ifdef GEMDOS
	if (c == '\n') Bconout(2, '\r');
	Bconout(2, c);
#else
	putchar(c);
#endif
}
