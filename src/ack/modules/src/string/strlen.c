/*	@(#)strlen.c	1.1	91/04/11 13:48:35 */
/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
/* return length of s
*/
int
strlen(s)
	char *s;
{
	register char *b = s;

	while (*b++)
		;
	return b - s - 1;
}
