/*	@(#)access.c	1.1	91/04/11 13:48:07 */
/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */

#include <system.h>

int
sys_access(path, mode)
	char *path;
	int mode;
{
	return access(path, mode) == 0;
}
