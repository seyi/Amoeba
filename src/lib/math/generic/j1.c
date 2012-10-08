/*	@(#)j1.c	1.1	91/04/09 09:23:34 */
/*
 * (c) copyright 1988 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 *
 * Author: Ceriel J.H. Jacobs
 */


#include "math.h"
#include <float.h>
#include "localmath.h"
#include <errno.h>

extern int errno;

static double
P1(x)
	double x;
{
	/*	P1(x) = P(z*z)/Q(z*z) where z = 8/x, with x >= 8 */
	/*	Hart & Cheney # 6755 */

	static double p[9] = {
		 0.1000000000000000000000000489e+01,
		 0.5581663300347182292169450071e+01,
		 0.1100186625131173123750501118e+02,
		 0.9727139359130463694593683431e+01,
		 0.4060011483142278994462590992e+01,
		 0.7742832212665311906917358099e+00,
		 0.6021617752811098752098248630e-01,
		 0.1482350677236405118074646993e-02,
		 0.6094215148131061431667573909e-05
	};

	static double q[9] = {
		 0.9999999999999999999999999999e+00,
		 0.5579832245659682292169922224e+01,
		 0.1099168447731617288972771040e+02,
		 0.9707206835125961446797916892e+01,
		 0.4042610016540342097334497865e+01,
		 0.7671965204303836019508430169e+00,
		 0.5893258668794493100786371406e-01,
		 0.1393993644981256852404222530e-02,
		 0.4585597769784750669754696825e-05
	};

	double zsq = 64.0/(x*x);

	return POLYNOM8(zsq, p) / POLYNOM8(zsq, q);
}

static double
Q1(x)
	double x;
{
	/*	Q1(x) = z*P(z*z)/Q(z*z) where z = 8/x, x >= 8 */
	/*	Hart & Cheney # 7157 */
	/*	Probably typerror in Hart & Cheney; it sais:
		Q1(x) = x*P(z*z)/Q(z*z)
	*/

	static double p[9] = {
		0.4687499999999999999999995275e-01,
		0.3302394516691663879252493748e+00,
		0.8456888491208195767613862428e+00,
		0.1008551084218946085420665147e+01,
		0.5973407972399900690521296181e+00,
		0.1737697433393258207540273097e+00,
		0.2303862814819568573893610740e-01,
		0.1171224207976250587945594946e-02,
		0.1486418220337492918307904804e-04
	};

	static double q[10] = {
		0.9999999999999999999999999999e+00,
		0.7049380763213049609070823421e+01,
		0.1807129960468949760845562209e+02,
		0.2159171174362827330505421695e+02,
		0.1283239297740546866114600499e+02,
		0.3758349275324260869598403931e+01,
		0.5055985453754739528620657666e+00,
		0.2665604326323907148063400439e-01,
		0.3821140353404633025596424652e-03,
		0.3206696590241261037875154062e-06
	};

	double zsq = 64.0/(x*x);

#ifdef ORIGINAL
	return (8.0/x) * POLYNOM8(zsq, p) / POLYNOM9(zsq, q);
#else
	/* Ultrix 2.2 compiler complains this is too complicated */
	double result;
	
	result = (8.0/x) * POLYNOM8(zsq, p);
	return result / POLYNOM9(zsq, q);
#endif
}

static double
smallj1(x)
	double x;
{
	/*	J1(x) = x*P(x*x)/Q(x*x) for x in [0,8] */
	/*	Hart & Cheney # 6054 */

	static double p[10] = {
		 0.1921176307760798128049021316e+25,
		-0.2226092031387396254771375773e+24,
		 0.7894463902082476734673226741e+22,
		-0.1269424373753606065436561036e+21,
		 0.1092152214043184787101134641e+19,
		-0.5454629264396819144157448868e+16,
		 0.1634659487571284628830445048e+14,
		-0.2909662785381647825756152444e+11,
		 0.2853433451054763915026471449e+08,
		-0.1197705712815379389149134705e+05
	};

	static double q[10] = {
		 0.3842352615521596256098041912e+25,
		 0.3507567066272028105798868716e+23,
		 0.1611334311633414344007062889e+21,
		 0.4929612313959850319632645381e+18,
		 0.1117536965288162684489793105e+16,
		 0.1969278625584719037168592923e+13,
		 0.2735606122949877990248154504e+10,
		 0.2940957355049651347475558106e+07,
		 0.2274736606126590905134610965e+04,
		 0.1000000000000000000000000000e+01
	};

	double xsq = x*x;

#ifdef ORIGINAL
	return x * POLYNOM9(xsq, p) / POLYNOM9(xsq, q);
#else
	/* Ultrix 2.2 compiler complains this is too complicated */
	double result;
	
	result = x * POLYNOM9(xsq, p);
	return result / POLYNOM9(xsq, q);
#endif
}

double
j1(x)
	double x;
{
	/*	Use J1(x) = sqrt(2/(pi*x))*(P1(x)*cos(X1)-Q1(x)*sin(X1))
			where X1 = x - 3*pi/4 for |x| > 8.
		Use J1(-x) = -J1(x).
		Use direct approximation of smallj1 for |x| <= 8.
	*/
	extern double sqrt(), sin(), cos();
	int negative = x < 0.0;

	if (negative) x = -x;
	if (x > 8.0) {
		double X1 = x - (M_PI - M_PI_4);
		x = sqrt(M_2_PI/x)*(P1(x)*cos(X1) - Q1(x)*sin(X1));
	}
	else x = smallj1(x);
	if (negative) return -x;
	return x;
}

static double
smally1_bar(x)
	double x;
{
	/*	Y1(x) = Y1BAR(x)+(2/pi)*(J1(x)ln(x) - 1/x)
		Approximation of Y1BAR for 0 <= x <= 8:
			Y1BAR(x) = x*P(x*x)/Q(x*x)
		Hart & Cheney # 6449
	*/

	static double p[10] = {
		-0.5862655424363443992938931700e+24,
		 0.1570668341992328458208364904e+24,
		-0.7351681299005467428400402479e+22,
		 0.1390658785759080111485190942e+21,
		-0.1339544201526785345938109179e+19,
		 0.7290257386242270629526344379e+16,
		-0.2340575603057015935501295099e+14,
		 0.4411516199185230690878878903e+11,
		-0.4542128738770213026987060358e+08,
		 0.1988612563465350530472715888e+05
	};

	static double q[10] = {
		 0.2990279721605116022908679994e+25,
		 0.2780285010357803058127175655e+23,
		 0.1302687474507355553192845146e+21,
		 0.4071330372239164349602952937e+18,
		 0.9446611865086570116528399283e+15,
		 0.1707657951197456205887347694e+13,
		 0.2440358986882941823431612517e+10,
		 0.2708852767034077697963790196e+07,
		 0.2174361138333330803617969305e+04,
		 0.1000000000000000000000000000e+01
	};

	double xsq = x*x;

#ifdef ORIGINAL
	return x * POLYNOM9(xsq, p) / POLYNOM9(xsq, q);
#else
	/* Ultrix 2.2 compiler complains this is too complicated */
	double result;
	
	result = x * POLYNOM9(xsq, p);
	return result / POLYNOM9(xsq, q);
#endif
}

double
y1(x)
	double x;
{
	extern double sqrt(), sin(), cos(), log();

	if (x <= 0.0) {
		errno = EDOM;
		return -HUGE_VAL;
	}
	if (x > 8.0) {
		double X1 = x - (M_PI - M_PI_4);
		return sqrt(M_2_PI/x) * (P1(x)*sin(X1)+Q1(x)*cos(X1));
	}
	return smally1_bar(x) + M_2_PI*(j1(x)*log(x) - 1/x);
}
