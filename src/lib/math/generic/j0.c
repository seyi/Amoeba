/*	@(#)j0.c	1.1	91/04/09 09:23:25 */
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
P0(x)
	double x;
{
	/*	P0(x) = P(z*z)/Q(z*z) where z = 8/x, with x >= 8 */
	/*	Hart & Cheney # 6554 */

	static double p[9] = {
		 0.9999999999999999999999995647e+00,
		 0.5638253933310769952531889297e+01,
		 0.1124846237418285392887270013e+02,
		 0.1009280644639441488899111404e+02,
		 0.4290591487686900980651458361e+01,
		 0.8374209971661497198619102718e+00,
		 0.6702347074465611456598882534e-01,
		 0.1696260729396856143084502774e-02,
		 0.6463970103128382090713889584e-05
	};

	static double q[9] = {
		 0.9999999999999999999999999999e+00,
		 0.5639352566123269952531467562e+01,
		 0.1125463057106955935416066535e+02,
		 0.1010501892629524191262518048e+02,
		 0.4301396985171094350444425443e+01,
		 0.8418926086780046799127094223e+00,
		 0.6784915305473610998681570734e-01,
		 0.1754416614608056207958880988e-02,
		 0.7482977995134121064747276923e-05
	};

	double zsq = 64.0/(x*x);

	return POLYNOM8(zsq, p) / POLYNOM8(zsq, q);
}

static double
Q0(x)
	double x;
{
	/*	Q0(x) = z*P(z*z)/Q(z*z) where z = 8/x, x >= 8 */
	/*	Hart & Cheney # 6955 */
	/*	Probably typerror in Hart & Cheney; it sais:
		Q0(x) = x*P(z*z)/Q(z*z)
	*/

	static double p[9] = {
		-0.1562499999999999999999995808e-01,
		-0.1111285583113679178917024959e+00,
		-0.2877685516355036842789761274e+00,
		-0.3477683453166454475665803194e+00,
		-0.2093031978191084473537206358e+00,
		-0.6209520943730206312601003832e-01,
		-0.8434508346572023650653353729e-02,
		-0.4414848186188819989871882393e-03,
		-0.5768946278415631134804064871e-05
	};

	static double q[10] = {
		 0.9999999999999999999999999999e+00,
		 0.7121383005365046745065850254e+01,
		 0.1848194194302368046679068851e+02,
		 0.2242327522435983712994071530e+02,
		 0.1359286169255959339963319677e+02,
		 0.4089489268101204780080944780e+01,
		 0.5722140925672174525430730669e+00,
		 0.3219814230905924725810683346e-01,
		 0.5299687475496044642364124073e-03,
		 0.9423249021001925212258428217e-06
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
smallj0(x)
	double x;
{
	/*	J0(x) = P(x*x)/Q(x*x) for x in [0,8] */
	/*	Hart & Cheney # 5852 */

	static double p[10] = {
		 0.1641556014884554385346147435e+25,
		-0.3943559664767296636012616471e+24,
		 0.2172018385924539313982287997e+23,
		-0.4814859952069817648285245941e+21,
		 0.5345457598841972345381674607e+19,
		-0.3301538925689637686465426220e+17,
		 0.1187390681211042949874031474e+15,
		-0.2479851167896144439689877514e+12,
		 0.2803148940831953934479400118e+09,
		-0.1336625500481224741885945416e+06
	};

	static double q[10] = {
		 0.1641556014884554385346137617e+25,
		 0.1603303724440893273539045602e+23,
		 0.7913043777646405204323616203e+20,
		 0.2613165313325153278086066185e+18,
		 0.6429607918826017759289213100e+15,
		 0.1237672982083407903483177730e+13,
		 0.1893012093677918995179541438e+10,
		 0.2263381356781110003609399116e+07,
		 0.1974019272727281783930443513e+04,
		 0.1000000000000000000000000000e+01
	};

	double xsq = x*x;

#ifdef ORIGINAL
	return POLYNOM9(xsq, p) / POLYNOM9(xsq, q);
#else
	/* Ultrix 2.2 compiler complains this is too complicated */
	double result;
	
	result = POLYNOM9(xsq, p);
	return result / POLYNOM9(xsq, q);
#endif
}

double
j0(x)
	double x;
{
	/*	Use J0(x) = sqrt(2/(pi*x))*(P0(x)*cos(X0)-Q0(x)*sin(X0))
			where X0 = x - pi/4 for |x| > 8.
		Use J0(-x) = J0(x).
		Use direct approximation of smallj0 for |x| <= 8.
	*/
	extern double sqrt(), sin(), cos();

	if (x < 0) x = -x;
	if (x > 8.0) {
		double X0 = x - M_PI_4;
		return sqrt(M_2_PI/x)*(P0(x)*cos(X0) - Q0(x)*sin(X0));
	}
	return smallj0(x);
}

static double
smally0_bar(x)
	double x;
{
	/*	Y0(x) = Y0BAR(x)+(2/pi)*J0(x)ln(x)
		Approximation of Y0BAR for 0 <= x <= 8:
			Y0BAR(x) = P(x*x)/Q(x*x)
		Hart & Cheney #6250
	*/

	static double p[14] = {
		-0.2692670958801060448840356941e+14,
		 0.6467231173109037044444917683e+14,
		-0.5563036156275660297303897296e+13,
		 0.1698403391975239335187832821e+12,
		-0.2606282788256139370857687880e+10,
		 0.2352841334491277505699488812e+08,
		-0.1365184412186963659690851354e+06,
		 0.5371538422626582142170627457e+03,
		-0.1478903875146718839145348490e+01,
		 0.2887840299886172125955719069e-02,
		-0.3977426824263991024666116123e-05,
		 0.3738169731655229006655176866e-08,
		-0.2194460874896856106887900645e-11,
		 0.6208996973821484304384239393e-15
	};

	static double q[6] = {
		 0.3648393301278364629844168660e+15,
		 0.1698390180526960997295118328e+13,
		 0.3587111679107612117789088586e+10,
		 0.4337760840406994515845890005e+07,
		 0.3037977771964348276793136205e+04,
		 0.1000000000000000000000000000e+01
	};

	double xsq = x*x;

#ifdef ORIGINAL
	return POLYNOM13(xsq, p) / POLYNOM5(xsq, q);
#else
	/* Ultrix 2.2 compiler complains this is too complicated */
	double result;
	
	result = POLYNOM13(xsq, p);
	return result / POLYNOM5(xsq, q);
#endif
}

double
y0(x)
	double x;
{
	extern double sqrt(), sin(), cos(), log();

	if (x <= 0.0) {
		errno = EDOM;
		return -HUGE_VAL;
	}
	if (x > 8.0) {
		double X0 = x - M_PI_4;
		return sqrt(M_2_PI/x) * (P0(x)*sin(X0)+Q0(x)*cos(X0));
	}
	return smally0_bar(x) + M_2_PI*j0(x)*log(x);
}
