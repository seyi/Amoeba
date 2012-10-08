/*	@(#)strncmp.c	1.1	91/04/11 13:48:59 */
/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
/*	return negative, zero or positive value if
	resp. s < t, s == t or s > t; compare at most n characters
*/
int
strncmp(s, t, n)
	register char *s, *t;
	register int n;
{
	while (n-- > 0) {
		if (*s == *t++) {
			if (*s++ == '\0')
				return 0;
		}
		else
			return *s - *--t;
	}
	return 0;
}
