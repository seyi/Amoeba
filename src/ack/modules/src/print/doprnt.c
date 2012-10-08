/*	@(#)doprnt.c	1.2	93/01/15 17:14:22 */
/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */

#include <system.h>
#ifdef __STDC__
#include <stdarg.h>
#else
#include <varargs.h>
#endif
#include "param.h"

/*FORMAT1 $
	%s = char *
	%l = long
	%c = int
	%[uxbo] = unsigned int
	%d = int
$ */
doprnt(fp, fmt, argp)
	File *fp;
	char *fmt;
	va_list argp;
{
	char buf[SSIZE];

	sys_write(fp, buf, _format(buf, fmt, argp));
}
