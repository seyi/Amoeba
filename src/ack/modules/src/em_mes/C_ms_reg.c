/*	@(#)C_ms_reg.c	1.1	91/04/11 11:57:39 */
/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
#include <em.h>
#include <em_mes.h>

C_ms_reg(offs, siz, class, prior)
	arith offs, siz;
	int class, prior;
{
	C_mes_begin(ms_reg);
	C_cst(offs);
	C_cst(siz);
	C_cst((arith)class);
	C_cst((arith)prior);
	C_mes_end();
}
