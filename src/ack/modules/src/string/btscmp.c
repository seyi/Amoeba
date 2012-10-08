/*	@(#)btscmp.c	1.1	91/04/11 13:46:50 */
/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
/* btscmp()
*/

int
btscmp(b1, n1, b2, n2)
	register char *b1, *b2;
	int n1, n2;
{
	register n = (n1 <= n2) ? n1 : n2;

	while (n-- > 0) {
		if (*b1++ != *b2++)
			return *--b1 - *--b2;
	}
	return n2 - n1;
}
