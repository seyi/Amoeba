/*	@(#)btscpy.c	1.1	91/04/11 13:47:01 */
/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
/* btscpy()
*/

char *
btscpy(b1, b2, n)
	register char *b1, *b2;
	register int n;
{
	char *b1s = b1;

	while (n-- > 0)
		*b1++ = *b2++;
	return b1s;
}
