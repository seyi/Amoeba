/*	@(#)ctype.h	1.2	94/04/06 16:52:46 */
/*
 * Copyright 1994 Vrije Universiteit, The Netherlands.
 * For full copyright and restrictions on use see the file COPYRIGHT in the
 * top level of the Amoeba distribution.
 */

/*
 * ctype.h - character handling
 */

#if	!defined(_CTYPE_H)
#define	_CTYPE_H

extern char	__ctype[];	/* located in chartab.c */

#define _U		0x01	/* this bit is for upper-case letters [A-Z] */
#define _L		0x02	/* this bit is for lower-case letters [a-z] */
#define _N		0x04	/* this bit is for numbers [0-9] */
#define _S		0x08	/* this bit is for white space \t \n \f etc */
#define _P		0x10	/* this bit is for punctuation characters */
#define _C		0x20	/* this bit is for control characters */
#define _X		0x40	/* this bit is for hex digits [a-f] and [A-F]*/

#ifdef __STDC__
int isalnum(int _c);		/* alphanumeric [a-z], [A-Z], [0-9] */
int isalpha(int _c);		/* alphabetic */
int iscntrl(int _c);		/* control characters */
int isdigit(int _c);		/* digit [0-9] */
int isgraph(int _c);		/* graphic character */
int islower(int _c);		/* lower-case letter [a-z] */
int isprint(int _c);		/* printable character */
int ispunct(int _c);		/* punctuation mark */
int isspace(int _c);		/* white space sp, \f, \n, \r, \t, \v */
int isupper(int _c);		/* upper-case letter [A-Z] */
int isxdigit(int _c);		/* hex digit [0-9], [a-f], [A-F] */
int tolower(int _c);		/* convert to lower case character */
int toupper(int _c);		/* convert to upper case character */
#else
int tolower();			/* convert to lower case character */
int toupper();			/* convert to upper case character */
#endif

#define isalpha(c)	((__ctype+1)[c]&(_U|_L))
#define isspace(c)	((__ctype+1)[c]&_S)
#define	iscntrl(c)	((__ctype+1)[c]&_C)
#define isxdigit(c)	((__ctype+1)[c]&(_N|_X))
#define isalnum(c)	((__ctype+1)[c]&(_U|_L|_N))
#define isgraph(c)	((__ctype+1)[c]&(_P|_U|_L|_N))
#define ispunct(c)	((__ctype+1)[c]&_P)

#define isdigit(c)	((unsigned) ((c)-'0') < 10)
#define islower(c)	((unsigned) ((c)-'a') < 26)
#define isupper(c)	((unsigned) ((c)-'A') < 26)
#define	isprint(c)	((unsigned) ((c)-' ') < 95)
#define	isascii(c)	((unsigned) (c) < 128)

#endif	/* _CTYPE_H */
