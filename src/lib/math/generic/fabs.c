/*	@(#)fabs.c	1.1	91/04/09 09:22:08 */
/*
 * (c) copyright 1988 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 *
 * Author: Ceriel J.H. Jacobs
 */

double
fabs(x)
double x;
{
	return  x < 0 ? -x : x;
}
