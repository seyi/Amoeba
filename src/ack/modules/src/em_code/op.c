/*	@(#)op.c	1.2	94/04/06 11:19:34 */
/*
 * Copyright 1994 Vrije Universiteit, The Netherlands.
 * For full copyright and restrictions on use see the file COPYRIGHT in the
 * top level of the Amoeba distribution.
 */

#include "em_private.h"


CC_op(opcode)
{
	/*	Instruction that never has an argument
		Argument types: -
	*/
	OP(opcode);
	NL();
}
