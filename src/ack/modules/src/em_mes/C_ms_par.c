/*	@(#)C_ms_par.c	1.1	91/04/11 11:57:29 */
/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
#include <em.h>
#include <em_mes.h>

C_ms_par(nparams)
	arith nparams;
{
	C_mes_begin(ms_par);
	C_cst(nparams);
	C_mes_end();
}
