/*	@(#)rd_long.c	1.1	91/04/11 13:03:09 */
/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
#include "object.h"

long
rd_long(fd)
{
	char buf[4];

	rd_bytes(fd, buf, 4L);
	return get4(buf);
}
