/*	@(#)C_ms_emx.c	1.1	91/04/11 11:56:38 */
/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
#include <em.h>
#include <em_mes.h>

C_ms_emx(wsiz, psiz)
	arith wsiz, psiz;
{
	C_mes_begin(ms_emx);
	C_cst(wsiz);
	C_cst(psiz);
	C_mes_end();
}
