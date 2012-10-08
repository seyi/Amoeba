/*	@(#)getpw.c	1.2	94/04/07 09:46:25 */
/*
 * Copyright 1994 Vrije Universiteit and Stichting Mathematisch Centrum,
 * The Netherlands.
 * For full copyright and restrictions on use see the file COPYRIGHT in
 * the top level of the Amoeba distribution.
 */

#include	<stdio.h>

getpw(uid, buf)
	int uid;
	char buf[];
{
	register FILE *pwf;
	register int ch, i;
	register char *bp;

	pwf = fopen("/etc/passwd", "r");
	if (pwf == NULL) return(1);

	for (;;) {
		bp = buf;
		while ((ch = getc(pwf)) != '\n') {
			if (ch == EOF) return 1;
			*bp++ = ch;
		}
		*bp++ = '\0';
		bp = buf;
		for (i = 2; i; i--) {
			while ((ch = *bp++) != ':') {
				if(ch = '\0') return 1;
			}
		}
		i = 0;
		while ((ch = *bp++) != ':') {
			if (ch < '0' || ch > '9') return 1;
			i = i * 10 + (ch - '0');
		}
		if (i == uid) return(0);
	}
	/*NOTREACHED*/
}
