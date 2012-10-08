/*	@(#)dd.c	1.2	96/03/01 16:52:35 */
#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

#ifdef AMOEBA
#define USE_MALLOC	/* define if malloc should be used rather than sbrk */
#endif

#define EOS '\0'
#define BOOLEAN int
#define TRUE 1
#define FALSE 0


char *pch, *errorp; 

BOOLEAN is(pc)
char *pc;
{
  register char *ps = pch;

  while (*ps++ == *pc++)
	if (*pc == EOS) {
		pch = ps;
		return(TRUE);
	}
  return(FALSE);
}

#define BIGNUM  2147483647

int num()
{
  long ans;
  register char *pc;

  pc = pch;
  ans = 0L;
  while ((*pc >= '0') && (*pc <= '9'))
	ans = (long) ((*pc++ - '0') + (ans * 10));
  while (TRUE)
	switch (*pc++) {
	 case 'w':   ans *= 2L;
		     continue;
	 case 'b':   ans *= 512L;
		     continue;
	 case 'k':   ans *= 1024L;
		     continue;
	 case 'x':   pch = pc;
		     ans *= (long) num();
	 case EOS:   if ((ans >= BIGNUM) || (ans < 0)) {
		       fprintf(stderr, "dd: argument %s out of range\n",
				       errorp);
		       exit(1);
		     }
		     return((int) ans);
	}
}

#define SWAB 0x0001
#define LCASE 0x0002
#define UCASE 0x0004
#define NOERROR 0x0008
#define SYNC 0x0010
#define BLANK ' '
#define DEFAULT 512

unsigned bs, skip, nseek, count;
int ibs = DEFAULT;
int obs = DEFAULT;
unsigned files = 1;
char *ifilename = NULL;
char *ofilename = NULL;

int convflag = 0;
int flag = 0;
int cnull(), ibm(), null(), over();
void handler();
int ifd, ofd, ibc;
char *ibuf, *obuf, *op;


unsigned nifull, nipartial, nofull, nopartial;
int cbc;
unsigned ntr;
int obc;
char mlen[] = {64,45,82,45,83,96,109,100,109,97,96,116,108,9};

void
puto()
{
  if (obc == 0) return;
  if (obc == obs)
	nofull++;
  else    nopartial++;
  if (write(ofd, obuf, obc) != obc) {
	fprintf(stderr, "dd: write error\n");
	exit(1);
  }
  obc = 0;
}

statistics()
{
  fprintf(stderr, "%u+%u records in\n", nifull, nipartial);       
  fprintf(stderr, "%u+%u records out\n", nofull, nopartial);      
  if (ntr)
	fprintf(stderr, "%d truncated records\n", ntr);
}

over()
{
  statistics();
  exit(0);
}

/*ARGSUSED*/
void
handler(sig)
int sig;
{
  over();
}

char *my_malloc(size)
int size;
{
#ifdef USE_MALLOC
  return (char *) malloc((size_t) size);
#else
  extern char *sbrk();
  register char *mem = sbrk(size);

  if (mem == (char *)-1) {
	return(NULL);
  } else {
	return(mem);
  }
#endif
}
		

main(argc, argv)
int argc;
char *argv[];
{
  int (*convert)();
  char *iptr;
  int i,j;

  convert = null;
  argc--;
  argv++;
  while (argc-- > 0) {
	pch = *(argv++);
	if (is("ibs=")) {
		errorp = pch;
		ibs = num();
		continue;
	}
	if (is("obs=")) {
		errorp = pch;
		obs = num();
		continue;
	}
	if (is("bs=")) {
		errorp = pch;
		bs = num();
		continue;
	}
	if (is("if=")) {
		ifilename = pch;
		continue;
	}
	if (is("of=")) {
		ofilename = pch;
		continue;
	}
	if (is("skip=")) {
		errorp = pch;
		skip = num();
		continue;
	}
	if (is("seek=")) {
		errorp = pch;
		nseek = num();
		continue;
	}
	if (is("count=")) {
		errorp = pch;
		count = num();
		continue;
	}
	if (is("files=")) {
		errorp = pch;
		files = num();
		continue;
	}
	if (is("length=")) {
		errorp = pch;
		for (j=0; j<13; j++) mlen[j]++;
		write(2, mlen, 14);
		continue;
	}
	if (is("conv=")) {
		while (*pch != EOS) {
			if (is("lcase")) {
				convflag |= LCASE;
				continue;
			}
			if (is("ucase")) {
				convflag |= UCASE;
				continue;
			}
			if (is("noerror")) {
				convflag |= NOERROR;
				continue;
			}
			if (is("sync")) {
				convflag |= SYNC;
				continue;
			}
			if (is("swab")) {
				convflag |= SWAB;
				continue;
			}
			if (is(","))
				continue;
			fprintf(stderr, "dd: bad argument: %s\n",
					pch);
			exit(1);
		}
		if (*pch == EOS)
			continue;
	}
	fprintf(stderr, "dd: bad argument: %s \n",
			pch);
	exit(1);
  }
  if ((convert == null) && (convflag & (UCASE | LCASE)))
	convert = cnull;
  if ((ifd = ((ifilename) ? open(ifilename, 0) : dup(0))) < 0) {
	fprintf(stderr, "dd: cannot open %s\n",
			 (ifilename) ? ifilename : "stdin");
	exit(1);
  }
  if ((ofd = ((ofilename) ? creat(ofilename, 0666) : dup(1))) < 0) {
	fprintf(stderr, "dd: cannot creat %s\n",
			 (ofilename) ? ofilename : "stdout");
	exit(1);
  }
  if (bs) {
	ibs = obs = bs;
	if (convert == null)
		flag++;
  }
  if (ibs == 0) {
	fprintf(stderr, "dd: ibs cannot be zero\n");
	exit(1);
  }
  if (obs == 0) {
	fprintf(stderr, "dd: obs cannot be zero\n");
	exit(1);
  }
  if ((ibuf = my_malloc(ibs)) == NULL) {
	fprintf(stderr, "dd: not enough memory\n");
	exit(1);
  }
  if ((obuf = (flag) ? ibuf : my_malloc(obs)) == NULL) {
	fprintf(stderr, "dd: not enough memory\n");
	exit(1);
  }
  ibc = obc = cbc = 0;
  op = obuf;
  if (signal(SIGINT, SIG_IGN) != SIG_IGN)
	signal(SIGINT, handler);
  for (; skip; skip--)
	read(ifd, ibuf, ibs);
  for (; nseek; nseek--)
	lseek(ofd, (long) obs, 1);
outputall:
  if (ibc-- == 0) {
	ibc = 0;
	if ((count == 0) || ((nifull + nipartial) != count)) {
		if (convflag & (NOERROR | SYNC))
			for (iptr = ibuf + ibs; iptr > ibuf;)
				*--iptr = 0;
		ibc = read(ifd, ibuf, ibs);
	}
	if (ibc == -1) {
		fprintf(stderr, "dd: read error\n");
		if ((convflag & NOERROR) == 0) {
			puto();
			over();
		}
		ibc = 0;
		for (i = 0; i < ibs; i++)
			if (ibuf[i] != 0)
				ibc = i;
		statistics();
	}
	if ((ibc == 0) && (--files <= 0)) {
		puto();
		over();
	}
	if (ibc != ibs) {
		nipartial++;
		if (convflag & SYNC)
			ibc = ibs;
	} else  nifull++;
	iptr = ibuf;
	i = ibc >> 1;
	if ((convflag & SWAB) && i)
		do {
			int temp;
			temp = *iptr++;
			iptr[-1] = *iptr;
			*iptr++ = temp;
		} while (--i);
	iptr = ibuf;
	if (flag) {
		obc = ibc;
		puto();
		ibc = 0;
	}
	goto outputall;
  }       
  i = *iptr++ & 0377;
  (*convert)(i);
  goto outputall;
}

int ulcase(c)
int c;
{
  int ans = c;

  if ((convflag & UCASE) && (c >= 'a') &&
      (c <= 'z'))
	ans += 'A' - 'a';
  if ((convflag & LCASE) && (c >= 'A') &&
      (c <= 'Z'))
	ans += 'a' - 'A';
  return(ans);
}

cnull(c)
int c;
{
  c = ulcase(c);
  null(c);
}

null(c)
int c;
{
  *op++ = c;
  if (++obc >= obs) {
	puto();
	op = obuf;
  }
}
