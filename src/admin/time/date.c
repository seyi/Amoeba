/*	@(#)date.c	1.2	96/02/27 10:23:46 */
#ifndef lint
#ifndef NOID
static char	elsieid[] = "@ (#)date.c	7.1";
/*
** Modified from the UCB version whose SCCS ID appears below.
*/
#endif /* !defined NOID */
#endif /* !defined lint */

/*
 * Copyright (c) 1985, 1987, 1988 The Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANT[A]BILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 */

#ifndef lint
char copyright[] =
"@ (#) Copyright (c) 1985, 1987, 1988 The Regents of the University of California.\n\
 All rights reserved.\n";
#endif /* not lint */

#ifndef lint
static char sccsid[] = "@ (#)date.c	4.23 (Berkeley) 9/20/88";
#endif /* not lint */

#ifdef AMOEBA
#define USG
#endif

#ifndef USG
#include "sys/time.h"	/* for DST_NONE */
#endif /* !defined USG */
#include "private.h"
#ifndef AMOEBA
#include "utmp.h"	/* for OLD_TIME (or its absence) */
#endif

/*
** The two things date knows about time are. . .
*/

#ifndef TM_YEAR_BASE
#define TM_YEAR_BASE	1900
#endif /* !defined TM_YEAR_BASE */

#ifndef SECSPERMIN
#define SECSPERMIN	60
#endif /* !defined SECSPERMIN */

extern double		atof();
extern char **		environ;
extern char *		getlogin();
extern int		logwtmp();
extern time_t		mktime();
extern char *		optarg;
extern int		optind;
extern char *		strchr();
extern time_t		time();
extern char *		tzname[2];

static int		retval = EXIT_SUCCESS;

static void		checkfinal();
static int		comptm();
static time_t		convert();
static void		display();
static void		dogmt();
static void		errensure();
static void		iffy();
static char *		nondigit();
static void		oops();
static void		reset();
static void		timeout();
static void		usage();
static void		wildinput();

#ifdef AMOEBA

#include <amoeba.h>
#undef timeout		/* We don't want the Amoeba timeout in this file! */
#include <module/tod.h>
#include <module/name.h>
#include <ampolicy.h>
#include <stderr.h>

/*
 * On Amoeba, the '-s server' option is used to specify the TOD server.
 * Adjustments are then made using that server only.
 * The '-g' option causes "date" to use the default time of day server
 * for *getting* the current time.
 * Adjustments to the TOD server specified with "-s" are then made with
 * respect to this default time.
 *
 * So "adate -g -a+0 -s /super/hosts/bullet2/tod" causes the TOD server on
 * bullet2 to be synchronised (modulo a few miliseconds) with the default
 * time of day server.
 */
#define OPTIONS "ungd:t:a:s:"

char *server = DEF_TODSVR;
/* This is not the "super" version.  Let the user specify it explicitly. */

capability servercap;
		
static void
set_tod_server(todsvr)
char *todsvr;
{
    errstat err;

    if ((err = name_lookup(todsvr, &servercap)) != STD_OK) {
	fprintf(stderr, "date: cannot lookup time of day server %s (%s)\n",
		todsvr, err_why(err));
	exit(1);
    }
    tod_setcap(&servercap);
}

#else
#define OPTIONS "und:t:a:"
#endif

int
main(argc, argv)
int	argc;
char *	argv[];
{
	register char *		format;
	register char *		value;
	register char *		cp;
	register int		ch;
	register int		dousg;
	register int		aflag = 0;
	register int		dflag = 0;
	register int		nflag = 0;
	register int		tflag = 0;
#ifdef AMOEBA
	register int		gflag = 0;
#endif
	register int		minuteswest;
	register int		dsttime;
	register float		adjust;
	time_t			now;
	time_t			t;

	format = value = NULL;
	while ((ch = getopt(argc, argv, OPTIONS)) != EOF) {
		switch (ch) {
		default:
			usage();
		case 'u':		/* do it in GMT */
		case 'c':
			dogmt();
			break;
#ifdef AMOEBA
		case 's':
			server = optarg;
			break;
		case 'g':
			gflag = 1;
			break;
#endif
		case 'n':		/* don't set network */
			nflag = 1;
			break;
		case 'd':		/* daylight savings time */
			if (dflag) {
				(void) fprintf(stderr,
					"date: error: multiple -d's used");
				usage();
			}
			dflag = 1;
			cp = optarg;
			dsttime = atoi(cp);
			if (*cp == '\0' || *nondigit(cp) != '\0')
				wildinput("-t value", optarg,
					"must be a non-negative number");
			break;
		case 't':		/* minutes west of GMT */
			if (tflag) {
				(void) fprintf(stderr,
					"date: error: multiple -t's used");
				usage();
			}
			tflag = 1;
			cp = optarg;
			minuteswest = atoi(cp);
			if (*cp == '+' || *cp == '-')
				++cp;
			if (*cp == '\0' || *nondigit(cp) != '\0')
				wildinput("-d value", optarg,
					"must be a number");
			break;
		case 'a':		/* adjustment */
			if (aflag) {
				(void) fprintf(stderr,
					"date: error: multiple -a's used");
				usage();
			}
			aflag = 1;
			cp = optarg;
			adjust = atof(cp);
			if (*cp == '+' || *cp == '-')
				++cp;
			if (*cp == '\0' || strcmp(cp, ".") == 0)
				wildinput("-a value", optarg,
					"must be a number");
			cp = nondigit(cp);
			if (*cp == '.')
				++cp;
			if (*nondigit(cp) != '\0')
				wildinput("-a value", optarg,
					"must be a number");
			break;
		}
	}
	while (optind < argc) {
		cp = argv[optind++];
		if (*cp == '+')
			if (format == NULL)
				format = cp + 1;
			else {
				(void) fprintf(stderr,
"date: error: multiple formats in command line\n");
				usage();
			}
		else	if (value == NULL)
				value = cp;
			else {
				(void) fprintf(stderr,
"date: error: multiple values in command line\n");
				usage();
			}
	}

#ifdef AMOEBA
	/* specify which time of day server we want to be used */
	if (gflag) {
		set_tod_server(DEF_TODSVR);
		(void) time(&now);
		set_tod_server(server);
	} else {
		set_tod_server(server);
		(void) time(&now);
	}
#else
	(void) time(&now);
#endif

	if (value != NULL) {
		/*
		** This order ensures that "reasonable" twelve-digit inputs
		** (such as 120203042006) won't be misinterpreted
		** even if time_t's range all the way back to the thirteenth
		** century.  Do not change the order.
		*/
		t = convert(value, (dousg = TRUE), now);
		if (t == -1)
			t = convert(value, (dousg = FALSE), now);
		if (t == -1) {
			/*
			** Out of range values,
			** or time that falls in a DST transition hole?
			*/
			if ((cp = strchr(value, '.')) != NULL) {
				/*
				** Ensure that the failure of
				**	TZ=US/Eastern date 8712312359.60
				** doesn't get misdiagnosed.  (It was
				**	TZ=US/Eastern date 8712311859.60
				** when the leap second was inserted.)
				** The normal check won't work since
				** the given time is valid in GMT.
				*/
				if (atoi(cp + 1) >= SECSPERMIN)
					wildinput("time", value,
						"out of range seconds given");
			}
			dogmt();
			t = convert(value, FALSE, now);
			if (t == -1)
				t = convert(value, TRUE, now);
			wildinput("time", value,
				(t == -1) ?
				"out of range value given" :
				"time skipped when clock springs forward");
		}
	}
	/*
	** Entire command line has now been checked.
	*/
	if (aflag) {
#ifdef DST_NONE
		struct timeval	tv;

		tv.tv_sec = (int) adjust;
		tv.tv_usec = (int) ((adjust - tv.tv_sec) * 1000000);
		if (adjtime(&tv, (struct timeval *) NULL) != 0)
			oops("date: error: adjtime");
#else /* !defined DST_NONE */
		reset((time_t) (now + adjust), nflag);
#endif /* !defined DST_NONE */
		/*
		** Sun silently ignores everything else; we follow suit.
		*/
		(void) exit(retval);
	}
	if (dflag || tflag) {
#ifdef DST_NONE
		struct timezone	tz;

		if (!dflag || !tflag)
			if (gettimeofday((struct timeval *) NULL, &tz) != 0)
				oops("date: error: gettimeofday");
		if (dflag)
			tz.tz_dsttime = dsttime;
		if (tflag)
			tz.tz_minuteswest = minuteswest;
		if (settimeofday((struct timeval *) NULL, &tz) != 0)
			oops("date: error: settimeofday");
#else /* !defined DST_NONE */
		(void) fprintf(stderr,
"date: warning: kernel doesn't keep -d/-t information, option ignored\n");
#endif /* !defined DST_NONE */
	}

	if (value == NULL)
		display(format);

	reset(t, nflag);

	checkfinal(value, dousg, t, now);

#ifdef EBUG
	{
		struct tm	tm;

		tm = *localtime(&t);
		timeout(stdout, "%c\n", &tm);
		(void) exit(retval);
	}
#endif /* defined EBUG */

	display(format);

	/* gcc -Wall pacifier */
	for ( ; ; )
		;
}

static void
dogmt()
{
	register char **	saveenv;
	static char *		fakeenv[] = { "TZ=GMT0", NULL };

	saveenv = environ;
	environ = fakeenv;
	tzset();
	environ = saveenv;
}

#ifdef AMOEBA

/*
** Amoeba does it different again...
*/

/*ARGSUSED*/
static void
reset(newt, nflag)
time_t	newt;
int	nflag;
{
	errstat err;

	/* time of day server has already been specified; now set the time */
	if ((err = tod_settime(newt, 0)) != STD_OK) {
		fprintf(stderr,	"date: couldn't set time on %s (%s)\n",
			server, err_why(err));
		exit(1);
	}
}

#else /* !defined AMOEBA */
#ifdef OLD_TIME

/*
** We assume we're on a System-V-based system,
** should use stime,
** should write System-V-format utmp entries,
** and don't have network notification to worry about.
*/

#include "fcntl.h"	/* for O_WRONLY, O_APPEND */

/*ARGSUSED*/
static void
reset(newt, nflag)
time_t	newt;
int	nflag;
{
	register int		fid;
	time_t			oldt;
	static struct {
		struct utmp	before;
		struct utmp	after;
	} s;

	/*
	** Wouldn't it be great if stime returned the old time?
	*/
	(void) time(&oldt);
	if (stime(&newt) != 0)
		oops("date: error: stime");
	s.before.ut_type = OLD_TIME;
	s.before.ut_time = oldt;
	(void) strcpy(s.before.ut_line, OTIME_MSG);
	s.after.ut_type = NEW_TIME;
	s.after.ut_time = newt;
	(void) strcpy(s.after.ut_line, NTIME_MSG);
	fid = open(WTMP_FILE, O_WRONLY | O_APPEND);
	if (fid < 0)
		oops("date: error: log file open");
	if (write(fid, (char *) &s, sizeof s) != sizeof s)
		oops("date: error: log file write");
	if (close(fid) != 0)
		oops("date: error: log file close");
	pututline(&s.before);
	pututline(&s.after);
}

#else /* !defined OLD_TIME */

/*
** We assume we're on a BSD-based system,
** should use settimeofday,
** should write BSD-format utmp entries (using logwtmp),
** and may get to worry about network notification.
** The "time name" changes between 4.3-tahoe and 4.4;
** we include sys/param.h to determine which we should use.
*/

#ifndef TIME_NAME
#include "sys/param.h"
#ifdef BSD4_4
#define TIME_NAME	"date"
#else /* !defined BSD4_4 */
#define TIME_NAME	""
#endif /* !defined BSD4_4 */
#endif /* !defined TIME_NAME */

#include "syslog.h"
#include "sys/socket.h"
#include "netinet/in.h"
#include "netdb.h"
#define TSPTYPES
#include "protocols/timed.h"

#ifndef TSP_SETDATE
/*ARGSUSED*/
#endif /* !defined TSP_SETDATE */
static void
reset(newt, nflag)
time_t	newt;
int	nflag;
{
	register char *		username;
	static struct timeval	tv;	/* static so tv_usec is 0 */

#ifdef EBUG
	return;
#endif /* defined EBUG */
	username = getlogin();
	if (username == NULL || *username == '\0') /* single-user or no tty */
		username = "root";
	tv.tv_sec = newt;
#ifdef TSP_SETDATE
	if (nflag || !netsettime(tv))
#endif /* defined TSP_SETDATE */
	{
		/*
		** "old" entry is always written, for compatibility.
		*/
		logwtmp("|", TIME_NAME, "");
		if (settimeofday(&tv, (struct timezone *) NULL) == 0) {
			logwtmp("{", TIME_NAME, "");	/* } */
			syslog(LOG_AUTH | LOG_NOTICE, "date set by %s",
				username);
		} else 	oops("date: error: settimeofday");
	}
}

#endif /* !defined OLD_TIME */
#endif /* !defined AMOEBA */

static void
wildinput(item, value, reason)
char *	item;
char *	value;
char *	reason;
{
	(void) fprintf(stderr, "date: error: bad command line %s \"%s\", %s\n",
		item, value, reason);
	usage();
}

static void
errensure()
{
	if (retval == EXIT_SUCCESS)
		retval = EXIT_FAILURE;
}

static char *
nondigit(cp)
register char *	cp;
{
	while (isdigit(*cp))
		++cp;
	return cp;
}

static void
usage()
{
	(void) fprintf(stderr, "date: usage is date ");
	(void) fprintf(stderr, "[-u] ");
	(void) fprintf(stderr, "[-c] ");
	(void) fprintf(stderr, "[-n] ");
	(void) fprintf(stderr, "[-d dst] ");
	(void) fprintf(stderr, "[-t min-west] ");
	(void) fprintf(stderr, "[-a sss.fff] ");
#ifdef AMOEBA
	(void) fprintf(stderr, "[-s server] ");
	(void) fprintf(stderr, "[-g] ");
#endif
	(void) fprintf(stderr, "[[yyyy]mmddhhmm[yyyy][.ss]] ");
	(void) fprintf(stderr, "[+format]\n");
	errensure();
	(void) exit(retval);
}

static void
oops(string)
char *	string;
{
	(void) perror(string);
	errensure();
	display((char *) NULL);
}

static void
display(format)
char *	format;
{
	struct tm	tm;
	time_t		now;

	(void) time(&now);
	tm = *localtime(&now);
	if (format == NULL) {
		timeout(stdout, "%a %b ", &tm);
		(void) printf("%2d ", tm.tm_mday);
		timeout(stdout, "%X %Z %Y", &tm);
	} else	timeout(stdout, format, &tm);
	(void) putchar('\n');
	(void) fflush(stdout);
	(void) fflush(stderr);
	if (ferror(stdout) || ferror(stderr)) {
		(void) fprintf(stderr, "date: error: couldn't write results\n");
		errensure();
	}
	(void) exit(retval);
}

extern size_t	strftime();

#define INCR	1024

static void
timeout(fp, format, tmp)
FILE *		fp;
char *		format;
struct tm *	tmp;
{
	char *	cp;
	size_t	result, size;

	if (*format == '\0')
		return;
	size = INCR;
	cp = malloc((alloc_size_t) size);
	for ( ; ; ) {
		if (cp == NULL) {
			(void) fprintf(stderr,
				"date: error: can't get memory\n");
			errensure();
			(void) exit(retval);
		}
		result = strftime(cp, size, format, tmp);
		if (result != 0)
			break;
		size += INCR;
		cp = realloc(cp, (alloc_size_t) size);
	}
	(void) fwrite(cp, 1, result, fp);
	free(cp);
}

static int
comptm(atmp, btmp)
register struct tm * atmp;
register struct tm * btmp;
{
	register int	result;

	if ((result = (atmp->tm_year - btmp->tm_year)) == 0 &&
		(result = (atmp->tm_mon - btmp->tm_mon)) == 0 &&
		(result = (atmp->tm_mday - btmp->tm_mday)) == 0 &&
		(result = (atmp->tm_hour - btmp->tm_hour)) == 0 &&
		(result = (atmp->tm_min - btmp->tm_min)) == 0)
			result = atmp->tm_sec - btmp->tm_sec;
	return result;
}

/*
** convert --
**	convert user's input into a time_t.
*/

#define	ATOI2(ar)	(ar[0] - '0') * 10 + (ar[1] - '0'); ar += 2;

static time_t
convert(value, dousg, t)
register char *	value;
int		dousg;
time_t		t;
{
	register char *	cp;
	register char *	dotp;
	register int	cent, year_in_cent, month, hour, day, mins, secs;
	struct tm	tm, outtm;
	time_t		outt;

	tm = *localtime(&t);
	cent = (tm.tm_year + TM_YEAR_BASE) / 100;
	year_in_cent = (tm.tm_year + TM_YEAR_BASE) - cent * 100;
	month = tm.tm_mon + 1;
	day = tm.tm_mday;
	hour = tm.tm_hour;
	mins = tm.tm_min;
	secs = 0;

	dotp = strchr(value, '.');
	for (cp = value; *cp != '\0'; ++cp)
		if (!isdigit(*cp) && cp != dotp)
			wildinput("time", value, "contains a nondigit");

	if (dotp == NULL)
		dotp = strchr(value, '\0');
	else {
		cp = dotp + 1;
		if (strlen(cp) != 2)
			wildinput("time", value,
				"seconds part is not two digits");
		secs = ATOI2(cp);
	}

	cp = value;
	switch (dotp - cp) {
		default:
			wildinput("time", value, "main part is wrong length");
		case 12:
			if (!dousg) {
				cent = ATOI2(cp);
				year_in_cent = ATOI2(cp);
			}
			month = ATOI2(cp);
			day = ATOI2(cp);
			hour = ATOI2(cp);
			mins = ATOI2(cp);
			if (dousg) {
				cent = ATOI2(cp);
				year_in_cent = ATOI2(cp);
			}
			break;
		case 8:	/* mmddhhmm */
			month = ATOI2(cp);
			/* fall through to. . . */
		case 6:	/* ddhhmm */
			day = ATOI2(cp);
			/* fall through to. . . */
		case 4:	/* hhmm */
			hour = ATOI2(cp);
			mins = ATOI2(cp);
			break;
		case 10:
			if (!dousg) {
				year_in_cent = ATOI2(cp);
			}
			month = ATOI2(cp);
			day = ATOI2(cp);
			hour = ATOI2(cp);
			mins = ATOI2(cp);
			if (dousg) {
				year_in_cent = ATOI2(cp);
			}
			break;
	}

	tm.tm_year = cent * 100 + year_in_cent - TM_YEAR_BASE;
	tm.tm_mon = month - 1;
	tm.tm_mday = day;
	tm.tm_hour = hour;
	tm.tm_min = mins;
	tm.tm_sec = secs;
	tm.tm_isdst = -1;
	outtm = tm;
	outt = mktime(&outtm);
	return (comptm(&tm, &outtm) == 0) ? outt : -1;
}

/*
** Code from here on out is either as provided by UCB
** or is only called just before the program exits.
*/

/*
** Check for iffy input.
*/

static void
checkfinal(value, didusg, t, oldnow)
char *	value;
int	didusg;
time_t	t;
time_t	oldnow;
{
	time_t		othert;
	struct tm	tm;
	struct tm	othertm;
	register int	pass;
	register long	offset;

	/*
	** See if there's both a USG and a BSD interpretation.
	*/
	othert = convert(value, !didusg, oldnow);
	if (othert != -1 && othert != t)
		iffy(t, othert, value, "year could be at start or end");
	/*
	** See if there's both a DST and a STD version.
	*/
	tm = *localtime(&t);
	othertm = tm;
	othertm.tm_isdst = !tm.tm_isdst;
	othert = mktime(&othertm);
	if (othert != -1 && othertm.tm_isdst != tm.tm_isdst &&
		comptm(&tm, &othertm) == 0)
			iffy(t, othert, value,
				"both standard and summer time versions exist");
/*
** Final check.
**
** If a jurisdiction shifts time *without* shifting whether time is
** summer or standard (as Hawaii, the United Kingdom, and Saudi Arabia
** have done), routine checks for iffy times may not work.
** So we perform this final check, deferring it until after the time has
** been set--it may take a while, and we don't want to introduce an unnecessary
** lag between the time the user enters their command and the time that
** stime/settimeofday is called.
**
** We just check nearby times to see if any of them have the same representation
** as the time that convert returned.  We work our way out from the center
** for quick response in solar time situations.  We only handle common cases--
** offsets of at most a minute, and offsets of exact numbers of minutes
** and at most an hour.
*/
	for (offset = 1; offset <= 60; ++offset)
		for (pass = 1; pass <= 4; ++pass) {
			if (pass == 1)
				othert = t + offset;
			else if (pass == 2)
				othert = t - offset;
			else if (pass == 3)
				othert = t + 60 * offset;
			else	othert = t - 60 * offset;
			othertm = *localtime(&othert);
			if (comptm(&tm, &othertm) == 0)
				iffy(t, othert, value,
					"multiple matching times exist");
		}
}

static void
iffy(thist, thatt, value, reason)
time_t	thist;
time_t	thatt;
char *	value;
char *	reason;
{
	struct tm	tm;

	(void) fprintf(stderr, "date: warning: ambiguous time \"%s\", %s.\n",
		value, reason);
	tm = *gmtime(&thist);
	(void) fprintf(stderr, "Time was set as if you used\n");
	/*
	** Avoid running afoul of SCCS!
	*/
	timeout(stderr, "\tdate -u ", &tm);
	timeout(stderr, "%m%d%H", &tm);
	timeout(stderr, "%M", &tm);
	timeout(stderr, "%Y.%S\n", &tm);
	tm = *localtime(&thist);
	timeout(stderr, "to get %c", &tm);
	(void) fprintf(stderr, " (%s time)",
		tm.tm_isdst ? "summer" : "standard");
	(void) fprintf(stderr, ".  Use\n");
	tm = *gmtime(&thatt);
	timeout(stderr, "\tdate -u ", &tm);
	timeout(stderr, "%m%d%H", &tm);
	timeout(stderr, "%M", &tm);
	timeout(stderr, "%Y.%S\n", &tm);
	tm = *localtime(&thatt);
	timeout(stderr, "to get %c", &tm);
	(void) fprintf(stderr, " (%s time)",
		tm.tm_isdst ? "summer" : "standard");
	(void) fprintf(stderr, ".\n");
	errensure();
	(void) exit(retval);
}

#ifdef TSP_SETDATE
#define	WAITACK		2	/* seconds */
#define	WAITDATEACK	5	/* seconds */

extern	int errno;
/*
 * Set the date in the machines controlled by timedaemons
 * by communicating the new date to the local timedaemon. 
 * If the timedaemon is in the master state, it performs the
 * correction on all slaves.  If it is in the slave state, it
 * notifies the master that a correction is needed.
 * Returns 1 on success, 0 on failure.
 */
netsettime(ntv)
	struct timeval ntv;
{
	int s, length, port, timed_ack, found, err;
	long waittime;
	fd_set ready;
	char hostname[MAXHOSTNAMELEN];
	struct timeval tout;
	struct servent *sp;
	struct tsp msg;
	struct sockaddr_in sin, dest, from;

	sp = getservbyname("timed", "udp");
	if (sp == 0) {
		fputs("udp/timed: unknown service\n", stderr);
		retval = 2;
		return (0);
	}
	dest.sin_port = sp->s_port;
	dest.sin_family = AF_INET;
	dest.sin_addr.s_addr = htonl((u_long)INADDR_ANY);
	s = socket(AF_INET, SOCK_DGRAM, 0);
	if (s < 0) {
		if (errno != EPROTONOSUPPORT)
			perror("date: socket");
		goto bad;
	}
	bzero((char *)&sin, sizeof (sin));
	sin.sin_family = AF_INET;
	for (port = IPPORT_RESERVED - 1; port > IPPORT_RESERVED / 2; port--) {
		sin.sin_port = htons((u_short)port);
		if (bind(s, (struct sockaddr *)&sin, sizeof (sin)) >= 0)
			break;
		if (errno != EADDRINUSE) {
			if (errno != EADDRNOTAVAIL)
				perror("date: bind");
			goto bad;
		}
	}
	if (port == IPPORT_RESERVED / 2) {
		fputs("date: All ports in use\n", stderr);
		goto bad;
	}
	msg.tsp_type = TSP_SETDATE;
	msg.tsp_vers = TSPVERSION;
	if (gethostname(hostname, sizeof (hostname))) {
		perror("gethostname");
		goto bad;
	}
	(void) strncpy(msg.tsp_name, hostname, sizeof (hostname));
	msg.tsp_seq = htons((u_short)0);
	msg.tsp_time.tv_sec = htonl((u_long)ntv.tv_sec);
	msg.tsp_time.tv_usec = htonl((u_long)ntv.tv_usec);
	length = sizeof (struct sockaddr_in);
	if (connect(s, &dest, length) < 0) {
		perror("date: connect");
		goto bad;
	}
	if (send(s, (char *)&msg, sizeof (struct tsp), 0) < 0) {
		if (errno != ECONNREFUSED)
			perror("date: send");
		goto bad;
	}
	timed_ack = -1;
	waittime = WAITACK;
loop:
	tout.tv_sec = waittime;
	tout.tv_usec = 0;
	FD_ZERO(&ready);
	FD_SET(s, &ready);
	found = select(FD_SETSIZE, &ready, (fd_set *)0, (fd_set *)0, &tout);
	length = sizeof(err);
	if (getsockopt(s, SOL_SOCKET, SO_ERROR, (char *)&err, &length) == 0
	    && err) {
		errno = err;
		if (errno != ECONNREFUSED)
			perror("date: send (delayed error)");
		goto bad;
	}
	if (found > 0 && FD_ISSET(s, &ready)) {
		length = sizeof (struct sockaddr_in);
		if (recvfrom(s, (char *)&msg, sizeof (struct tsp), 0, &from,
		    &length) < 0) {
			if (errno != ECONNREFUSED)
				perror("date: recvfrom");
			goto bad;
		}
		msg.tsp_seq = ntohs(msg.tsp_seq);
		msg.tsp_time.tv_sec = ntohl(msg.tsp_time.tv_sec);
		msg.tsp_time.tv_usec = ntohl(msg.tsp_time.tv_usec);
		switch (msg.tsp_type) {

		case TSP_ACK:
			timed_ack = TSP_ACK;
			waittime = WAITDATEACK;
			goto loop;

		case TSP_DATEACK:
			(void)close(s);
			return (1);

		default:
			fprintf(stderr,
			    "date: Wrong ack received from timed: %s\n", 
			    tsptype[msg.tsp_type]);
			timed_ack = -1;
			break;
		}
	}
	if (timed_ack == -1)
		fputs("date: Can't reach time daemon, time set locally.\n",
		    stderr);
bad:
	(void)close(s);
	retval = 2;
	return (0);
}
#endif /* defined TSP_SETDATE */
