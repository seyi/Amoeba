/*	@(#)ctermid.c	1.3	94/04/07 09:42:46 */
/*
 * Copyright 1994 Vrije Universiteit and Stichting Mathematisch Centrum,
 * The Netherlands.
 * For full copyright and restrictions on use see the file COPYRIGHT in
 * the top level of the Amoeba distribution.
 */

/* ctermid() POSIX 4.7.1 
 * last modified apr 22 93 Ron Visser 
 */

#include "ajax.h"

char *
ctermid(s)
char *s;
{
    static char *termid = "/dev/tty";

    if (s == NULL)
	return termid;
    else
	return strcpy(s, termid);
}
