/*	@(#)C_ms_std.c	1.1	91/04/11 11:58:12 */
/*
 * (c) copyright 1990 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
#include <em.h>
#include <em_mes.h>

C_ms_std(s, e1, l)
	char *s;
	int e1;
	int l;
{
	C_mes_begin(ms_std);
	if (s) C_scon(s, (arith) (strlen(s)+1));
	C_cst((arith) e1);
	C_cst((arith) l);
	C_mes_end();
}
