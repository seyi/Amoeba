/*	@(#)flt_misc.h	1.1	93/01/15 17:12:31 */
/*
 * (c) copyright 1989 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */

#include <flt_arith.h>

/* some short-hands ... */
#define m1 flt_mantissa.flt_h_32
#define m2 flt_mantissa.flt_l_32

/* some constants */
#define EXT_MAX		16384		/* max exponent */
#define EXT_MIN		(-16384)	/* min exponent */

/* hiding of names: */
#define ucmp		_flt_ucmp
#define flt_nrm		_flt_nrm
#define flt_chk		_flt_chk
#define flt_b64_add	_flt_64add
#define flt_split	_flt_split
