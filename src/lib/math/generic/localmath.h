/*	@(#)localmath.h	1.2	94/04/07 10:57:21 */
/*
 * Copyright 1994 Vrije Universiteit, The Netherlands.
 * For full copyright and restrictions on use see the file COPYRIGHT in the
 * top level of the Amoeba distribution.
 */

/*
 * localmath.h - This header is used by the mathematical library.
 */

/* some constants (Hart & Cheney) */
#define	M_PI		3.14159265358979323846264338327950288
#define	M_2PI		6.28318530717958647692528676655900576
#define	M_3PI_4		2.35619449019234492884698253745962716
#define	M_PI_2		1.57079632679489661923132169163975144
#define	M_3PI_8		1.17809724509617246442349126872981358
#define	M_PI_4		0.78539816339744830961566084581987572
#define	M_PI_8		0.39269908169872415480783042290993786
#define	M_1_PI		0.31830988618379067153776752674502872
#define	M_2_PI		0.63661977236758134307553505349005744
#define	M_4_PI		1.27323954473516268615107010698011488
#define	M_E		2.71828182845904523536028747135266250
#define	M_LOG2E		1.44269504088896340735992468100189213
#define	M_LOG10E	0.43429448190325182765112891891660508
#define	M_LN2		0.69314718055994530941723212145817657
#define	M_LN10		2.30258509299404568401799145468436421
#define	M_SQRT2		1.41421356237309504880168872420969808
#define	M_1_SQRT2	0.70710678118654752440084436210484904
#define	M_EULER		0.57721566490153286060651209008240243

/* macros for constructing polynomials */
#define	POLYNOM1(x, a)	((a)[1]*(x)+(a)[0])
#define	POLYNOM2(x, a)	(POLYNOM1((x),(a)+1)*(x)+(a)[0])
#define	POLYNOM3(x, a)	(POLYNOM2((x),(a)+1)*(x)+(a)[0])
#define	POLYNOM4(x, a)	(POLYNOM3((x),(a)+1)*(x)+(a)[0])
#define	POLYNOM5(x, a)	(POLYNOM4((x),(a)+1)*(x)+(a)[0])
#define	POLYNOM6(x, a)	(POLYNOM5((x),(a)+1)*(x)+(a)[0])
#define	POLYNOM7(x, a)	(POLYNOM6((x),(a)+1)*(x)+(a)[0])
#define	POLYNOM8(x, a)	(POLYNOM7((x),(a)+1)*(x)+(a)[0])
#define	POLYNOM9(x, a)	(POLYNOM8((x),(a)+1)*(x)+(a)[0])
#define	POLYNOM10(x, a)	(POLYNOM9((x),(a)+1)*(x)+(a)[0])
#define	POLYNOM11(x, a)	(POLYNOM10((x),(a)+1)*(x)+(a)[0])
#define	POLYNOM12(x, a)	(POLYNOM11((x),(a)+1)*(x)+(a)[0])
#define	POLYNOM13(x, a)	(POLYNOM12((x),(a)+1)*(x)+(a)[0])

#define	M_LN_MAX_D	(M_LN2 * DBL_MAX_EXP)
#define	M_LN_MIN_D	(M_LN2 * (DBL_MIN_EXP - 1))
