/*	@(#)bhucon.c	1.2	94/04/06 11:14:16 */
/*
 * Copyright 1994 Vrije Universiteit, The Netherlands.
 * For full copyright and restrictions on use see the file COPYRIGHT in the
 * top level of the Amoeba distribution.
 */

#include "em_private.h"


CC_bhucon(op, n, s, sz, i)
	arith n;
	char *s;
	arith sz;
	int i;
{
	/*	BSS or HOL with size n, initial value an UCON (s, sz),
		and flag i
	*/
	PS(op);
	CST(n);
	COMMA();
	WCON(sp_ucon, s, sz);
	COMMA();
	CST((arith) i);
	NL();
}
