/*	@(#)Malloc.c	1.2	93/10/23 10:25:30 */
/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
/*	M E M O R Y  A L L O C A T I O N  R O U T I N E S	*/

/*	The memory allocation routines offered in this file are:

	char *Malloc(n)		: allocate n bytes
*/

#include	"alloc.h"

char *
Malloc(sz)
	unsigned int sz;
{
	register char *res = (char *) malloc(sz);
	
	if (sz && res == 0) No_Mem();
	return res;
}
