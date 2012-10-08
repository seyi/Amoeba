/*	@(#)break.c	1.1	91/04/11 13:48:16 */
/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */

#include <system.h>

char *sbrk();

char *
sys_break(incr)
	int incr;
{
	char *sbrk();
	register char *brk = sbrk(incr);

	if (brk == (char *) 0 || brk == (char *)-1)
		return ILL_BREAK;
	return brk;
}
