/*	@(#)keys.c	1.1	92/05/13 10:28:02 */
/***************************************************************************
 * This program is Copyright (C) 1986, 1987, 1988 by Jonathan Payne.  JOVE *
 * is provided to you without charge, and with no warranty.  You may give  *
 * away copies of JOVE, including sources, provided that this notice is    *
 * included in all the files.                                              *
 ***************************************************************************/

/* Warning:  You probably shouldn't put ifdefs anywhere *inside* the keymaps
   definitions.	 It'll screw up the stuff in comments (at least), and maybe
   a few other things.	Yes, it *WILL* screw up the comments ... but it's
   not clear that you care ... */

#include "jove.h"

data_obj *MainKeys[NCHARS] = {
	(data_obj *) &commands[161],	/* C-@ */
	(data_obj *) &commands[16],	/* C-A */
	(data_obj *) &commands[7],	/* C-B */
	(data_obj *) 0,                 /* C-C */
	(data_obj *) &commands[43],	/* C-D */
	(data_obj *) &commands[68],	/* C-E */
	(data_obj *) &commands[84],	/* C-F */
	(data_obj *) 0,                 /* C-G */
	(data_obj *) &commands[45],	/* C-H */
	(data_obj *) &commands[96],	/* C-I */
	(data_obj *) &commands[117],	/* C-J */
	(data_obj *) &commands[106],	/* C-K */
	(data_obj *) &commands[143],	/* C-L */
	(data_obj *) &commands[115],	/* C-M */
	(data_obj *) &commands[119],	/* C-N */
	(data_obj *) &commands[116],	/* C-O */
	(data_obj *) &commands[132],	/* C-P */
	(data_obj *) &commands[140],	/* C-Q */
	(data_obj *) &commands[156],	/* C-R */
	(data_obj *) &commands[154],	/* C-S */
	(data_obj *) &commands[177],	/* C-T */
	(data_obj *) &commands[91],	/* C-U */
	(data_obj *) &commands[120],	/* C-V */
	(data_obj *) &commands[102],	/* C-W */
	(data_obj *) 0,                 /* C-X */
	(data_obj *) &commands[190],	/* C-Y */
	(data_obj *) &commands[153],	/* C-Z */
	(data_obj *) 0,                 /* ESC */
	(data_obj *) &commands[154],	/* C-\ */
#ifndef MSDOS
	(data_obj *) 0,                 /* C-] */
#else /* MSDOS */
	(data_obj *) &commands[82],	/* C-] */
#endif /* MSDOS */
	(data_obj *) &commands[140],	/* C-^ */
	(data_obj *) 0,                 /* C-_ */
	(data_obj *) &commands[159],	/*   */
	(data_obj *) &commands[159],	/* ! */
	(data_obj *) &commands[159],	/* " */
	(data_obj *) &commands[159],	/* # */
	(data_obj *) &commands[159],	/* $ */
	(data_obj *) &commands[159],	/* % */
	(data_obj *) &commands[159],	/* & */
	(data_obj *) &commands[159],	/* ' */
	(data_obj *) &commands[159],	/* ( */
	(data_obj *) &commands[125],	/* ) */
	(data_obj *) &commands[159],	/* * */
	(data_obj *) &commands[159],	/* + */
	(data_obj *) &commands[159],	/* , */
	(data_obj *) &commands[159],	/* - */
	(data_obj *) &commands[159],	/* . */
	(data_obj *) &commands[159],	/* / */
	(data_obj *) &commands[159],	/* 0 */
	(data_obj *) &commands[159],	/* 1 */
	(data_obj *) &commands[159],	/* 2 */
	(data_obj *) &commands[159],	/* 3 */
	(data_obj *) &commands[159],	/* 4 */
	(data_obj *) &commands[159],	/* 5 */
	(data_obj *) &commands[159],	/* 6 */
	(data_obj *) &commands[159],	/* 7 */
	(data_obj *) &commands[159],	/* 8 */
	(data_obj *) &commands[159],	/* 9 */
	(data_obj *) &commands[159],	/* : */
	(data_obj *) &commands[159],	/* ; */
	(data_obj *) &commands[159],	/* < */
	(data_obj *) &commands[159],	/* = */
	(data_obj *) &commands[159],	/* > */
	(data_obj *) &commands[159],	/* ? */
	(data_obj *) &commands[159],	/* @ */
	(data_obj *) &commands[159],	/* A */
	(data_obj *) &commands[159],	/* B */
	(data_obj *) &commands[159],	/* C */
	(data_obj *) &commands[159],	/* D */
	(data_obj *) &commands[159],	/* E */
	(data_obj *) &commands[159],	/* F */
	(data_obj *) &commands[159],	/* G */
	(data_obj *) &commands[159],	/* H */
	(data_obj *) &commands[159],	/* I */
	(data_obj *) &commands[159],	/* J */
	(data_obj *) &commands[159],	/* K */
	(data_obj *) &commands[159],	/* L */
	(data_obj *) &commands[159],	/* M */
	(data_obj *) &commands[159],	/* N */
	(data_obj *) &commands[159],	/* O */
	(data_obj *) &commands[159],	/* P */
	(data_obj *) &commands[159],	/* Q */
	(data_obj *) &commands[159],	/* R */
	(data_obj *) &commands[159],	/* S */
	(data_obj *) &commands[159],	/* T */
	(data_obj *) &commands[159],	/* U */
	(data_obj *) &commands[159],	/* V */
	(data_obj *) &commands[159],	/* W */
	(data_obj *) &commands[159],	/* X */
	(data_obj *) &commands[159],	/* Y */
	(data_obj *) &commands[159],	/* Z */
	(data_obj *) &commands[159],	/* [ */
	(data_obj *) &commands[159],	/* \ */
	(data_obj *) &commands[125],	/* ] */
	(data_obj *) &commands[159],	/* ^ */
	(data_obj *) &commands[159],	/* _ */
	(data_obj *) &commands[159],	/* ` */
	(data_obj *) &commands[159],	/* a */
	(data_obj *) &commands[159],	/* b */
	(data_obj *) &commands[159],	/* c */
	(data_obj *) &commands[159],	/* d */
	(data_obj *) &commands[159],	/* e */
	(data_obj *) &commands[159],	/* f */
	(data_obj *) &commands[159],	/* g */
	(data_obj *) &commands[159],	/* h */
	(data_obj *) &commands[159],	/* i */
	(data_obj *) &commands[159],	/* j */
	(data_obj *) &commands[159],	/* k */
	(data_obj *) &commands[159],	/* l */
	(data_obj *) &commands[159],	/* m */
	(data_obj *) &commands[159],	/* n */
	(data_obj *) &commands[159],	/* o */
	(data_obj *) &commands[159],	/* p */
	(data_obj *) &commands[159],	/* q */
	(data_obj *) &commands[159],	/* r */
	(data_obj *) &commands[159],	/* s */
	(data_obj *) &commands[159],	/* t */
	(data_obj *) &commands[159],	/* u */
	(data_obj *) &commands[159],	/* v */
	(data_obj *) &commands[159],	/* w */
	(data_obj *) &commands[159],	/* x */
	(data_obj *) &commands[159],	/* y */
	(data_obj *) &commands[159],	/* z */
	(data_obj *) &commands[159],	/* { */
	(data_obj *) &commands[159],	/* | */
	(data_obj *) &commands[125],	/* } */
	(data_obj *) &commands[159],	/* ~ */
#ifdef ASCII
	(data_obj *) &commands[45],	/* ^? */
#else
	(data_obj *) &commands[45],	/* ^? */
	(data_obj *) &commands[159],	/* M-C-@ */
	(data_obj *) &commands[159],	/* M-C-A */
	(data_obj *) &commands[159],	/* M-C-B */
	(data_obj *) &commands[159],	/* M-C-C */
	(data_obj *) &commands[159],	/* M-C-D */
	(data_obj *) &commands[159],	/* M-C-E */
	(data_obj *) &commands[159],	/* M-C-F */
	(data_obj *) &commands[159],	/* M-C-G */
	(data_obj *) &commands[159],	/* M-C-H */
	(data_obj *) &commands[159],	/* M-C-I */
	(data_obj *) &commands[159],	/* M-C-J */
	(data_obj *) &commands[159],	/* M-C-K */
	(data_obj *) &commands[159],	/* M-C-L */
	(data_obj *) &commands[159],	/* M-C-M */
	(data_obj *) &commands[159],	/* M-C-N */
	(data_obj *) &commands[159],	/* M-C-O */
	(data_obj *) &commands[159],	/* M-C-P */
	(data_obj *) &commands[159],	/* M-C-Q */
	(data_obj *) &commands[159],	/* M-C-R */
	(data_obj *) &commands[159],	/* M-C-S */
	(data_obj *) &commands[159],	/* M-C-T */
	(data_obj *) &commands[159],	/* M-C-U */
	(data_obj *) &commands[159],	/* M-C-V */
	(data_obj *) &commands[159],	/* M-C-W */
	(data_obj *) &commands[159],	/* M-C-X */
	(data_obj *) &commands[159],	/* M-C-Y */
	(data_obj *) &commands[159],	/* M-C-Z */
	(data_obj *) &commands[159],	/* M-ESC */
	(data_obj *) &commands[159],	/* M-C-\ */
	(data_obj *) &commands[159],	/* M-C-] */
	(data_obj *) &commands[159],	/* M-C-^ */
	(data_obj *) &commands[159],	/* M-C-_ */
	(data_obj *) &commands[159],	/* M-  */
	(data_obj *) &commands[159],	/* M-! */
	(data_obj *) &commands[159],	/* M-" */
	(data_obj *) &commands[159],	/* M-# */
	(data_obj *) &commands[159],	/* M-$ */
	(data_obj *) &commands[159],	/* M-% */
	(data_obj *) &commands[159],	/* M-& */
	(data_obj *) &commands[159],	/* M-' */
	(data_obj *) &commands[159],	/* M-( */
	(data_obj *) &commands[159],	/* M-) */
	(data_obj *) &commands[159],	/* M-* */
	(data_obj *) &commands[159],	/* M-+ */
	(data_obj *) &commands[159],	/* M-, */
	(data_obj *) &commands[159],	/* M-- */
	(data_obj *) &commands[159],	/* M-. */
	(data_obj *) &commands[159],	/* M-/ */
	(data_obj *) &commands[159],	/* M-0 */
	(data_obj *) &commands[159],	/* M-1 */
	(data_obj *) &commands[159],	/* M-2 */
	(data_obj *) &commands[159],	/* M-3 */
	(data_obj *) &commands[159],	/* M-4 */
	(data_obj *) &commands[159],	/* M-5 */
	(data_obj *) &commands[159],	/* M-6 */
	(data_obj *) &commands[159],	/* M-7 */
	(data_obj *) &commands[159],	/* M-8 */
	(data_obj *) &commands[159],	/* M-9 */
	(data_obj *) &commands[159],	/* M-: */
	(data_obj *) &commands[159],	/* M-; */
	(data_obj *) &commands[159],	/* M-< */
	(data_obj *) &commands[159],	/* M-= */
	(data_obj *) &commands[159],	/* M-> */
	(data_obj *) &commands[159],	/* M-? */
	(data_obj *) &commands[159],	/* M-@ */
	(data_obj *) &commands[159],	/* M-A */
	(data_obj *) &commands[159],	/* M-B */
	(data_obj *) &commands[159],	/* M-C */
	(data_obj *) &commands[159],	/* M-D */
	(data_obj *) &commands[159],	/* M-E */
	(data_obj *) &commands[159],	/* M-F */
	(data_obj *) &commands[159],	/* M-G */
	(data_obj *) &commands[159],	/* M-H */
	(data_obj *) &commands[159],	/* M-I */
	(data_obj *) &commands[159],	/* M-J */
	(data_obj *) &commands[159],	/* M-K */
	(data_obj *) &commands[159],	/* M-L */
	(data_obj *) &commands[159],	/* M-M */
	(data_obj *) &commands[159],	/* M-N */
	(data_obj *) &commands[159],	/* M-O */
	(data_obj *) &commands[159],	/* M-P */
	(data_obj *) &commands[159],	/* M-Q */
	(data_obj *) &commands[159],	/* M-R */
	(data_obj *) &commands[159],	/* M-S */
	(data_obj *) &commands[159],	/* M-T */
	(data_obj *) &commands[159],	/* M-U */
	(data_obj *) &commands[159],	/* M-V */
	(data_obj *) &commands[159],	/* M-W */
	(data_obj *) &commands[159],	/* M-X */
	(data_obj *) &commands[159],	/* M-Y */
	(data_obj *) &commands[159],	/* M-Z */
	(data_obj *) &commands[159],	/* M-[ */
	(data_obj *) &commands[159],	/* M-\ */
	(data_obj *) &commands[159],	/* M-] */
	(data_obj *) &commands[159],	/* M-^ */
	(data_obj *) &commands[159],	/* M-_ */
	(data_obj *) &commands[159],	/* M-` */
	(data_obj *) &commands[159],	/* M-a */
	(data_obj *) &commands[159],	/* M-b */
	(data_obj *) &commands[159],	/* M-c */
	(data_obj *) &commands[159],	/* M-d */
	(data_obj *) &commands[159],	/* M-e */
	(data_obj *) &commands[159],	/* M-f */
	(data_obj *) &commands[159],	/* M-g */
	(data_obj *) &commands[159],	/* M-h */
	(data_obj *) &commands[159],	/* M-i */
	(data_obj *) &commands[159],	/* M-j */
	(data_obj *) &commands[159],	/* M-k */
	(data_obj *) &commands[159],	/* M-l */
	(data_obj *) &commands[159],	/* M-m */
	(data_obj *) &commands[159],	/* M-n */
	(data_obj *) &commands[159],	/* M-o */
	(data_obj *) &commands[159],	/* M-p */
	(data_obj *) &commands[159],	/* M-q */
	(data_obj *) &commands[159],	/* M-r */
	(data_obj *) &commands[159],	/* M-s */
	(data_obj *) &commands[159],	/* M-t */
	(data_obj *) &commands[159],	/* M-u */
	(data_obj *) &commands[159],	/* M-v */
	(data_obj *) &commands[159],	/* M-w */
	(data_obj *) &commands[159],	/* M-x */
	(data_obj *) &commands[159],	/* M-y */
	(data_obj *) &commands[159],	/* M-z */
	(data_obj *) &commands[159],	/* M-{ */
	(data_obj *) &commands[159],	/* M-| */
	(data_obj *) &commands[159],	/* M-} */
	(data_obj *) &commands[159],	/* M-~ */
#ifdef IBMPC
	(data_obj *) 0,                 /* M-^? */
#else
	(data_obj *) &commands[159],	/* M-^? */
#endif	/* IBMPC */
#endif /* ASCII */
};

data_obj *EscKeys[NCHARS] = {
	(data_obj *) &commands[161],	/* C-@ */
	(data_obj *) 0,                 /* C-A */
	(data_obj *) &commands[10],	/* C-B */
	(data_obj *) 0,                 /* C-C */
	(data_obj *) &commands[64],	/* C-D */
	(data_obj *) 0,                 /* C-E */
	(data_obj *) &commands[87],	/* C-F */
	(data_obj *) 0,                 /* C-G */
	(data_obj *) 0,                 /* C-H */
	(data_obj *) 0,                 /* C-I */
	(data_obj *) 0,                 /* C-J */
	(data_obj *) &commands[103],	/* C-K */
	(data_obj *) &commands[32],	/* C-L */
	(data_obj *) 0,                 /* C-M */
	(data_obj *) &commands[85],	/* C-N */
	(data_obj *) 0,                 /* C-O */
	(data_obj *) &commands[8],	/* C-P */
	(data_obj *) 0,                 /* C-Q */
	(data_obj *) 0,                 /* C-R */
	(data_obj *) 0,                 /* C-S */
	(data_obj *) 0,                 /* C-T */
	(data_obj *) &commands[12],	/* C-U */
	(data_obj *) &commands[124],	/* C-V */
	(data_obj *) 0,                 /* C-W */
	(data_obj *) 0,                 /* C-X */
	(data_obj *) 0,                 /* C-Y */
	(data_obj *) 0,                 /* C-Z */
	(data_obj *) 0,                 /* ESC */
	(data_obj *) 0,                 /* C-\ */
	(data_obj *) 0,                 /* C-] */
	(data_obj *) 0,                 /* C-^ */
	(data_obj *) 0,                 /* C-_ */
	(data_obj *) 0,                 /*   */
	(data_obj *) 0,                 /* ! */
	(data_obj *) 0,                 /* " */
	(data_obj *) 0,                 /* # */
	(data_obj *) 0,                 /* $ */
	(data_obj *) 0,                 /* % */
	(data_obj *) 0,                 /* & */
	(data_obj *) 0,                 /* ' */
	(data_obj *) 0,                 /* ( */
	(data_obj *) 0,                 /* ) */
	(data_obj *) 0,                 /* * */
	(data_obj *) 0,                 /* + */
	(data_obj *) &commands[17],	/* , */
	(data_obj *) &commands[52],	/* - */
	(data_obj *) &commands[69],	/* . */
	(data_obj *) 0,                 /* / */
	(data_obj *) &commands[52],	/* 0 */
	(data_obj *) &commands[52],	/* 1 */
	(data_obj *) &commands[52],	/* 2 */
	(data_obj *) &commands[52],	/* 3 */
	(data_obj *) &commands[52],	/* 4 */
	(data_obj *) &commands[52],	/* 5 */
	(data_obj *) &commands[52],	/* 6 */
	(data_obj *) &commands[52],	/* 7 */
	(data_obj *) &commands[52],	/* 8 */
	(data_obj *) &commands[52],	/* 9 */
	(data_obj *) 0,                 /* : */
	(data_obj *) 0,                 /* ; */
	(data_obj *) &commands[15],	/* < */
	(data_obj *) 0,                 /* = */
	(data_obj *) &commands[67],	/* > */
	(data_obj *) &commands[49],	/* ? */
	(data_obj *) 0,                 /* @ */
	(data_obj *) &commands[11],	/* A */
	(data_obj *) &commands[13],	/* B */
	(data_obj *) &commands[27],	/* C */
	(data_obj *) &commands[100],	/* D */
	(data_obj *) &commands[88],	/* E */
	(data_obj *) &commands[89],	/* F */
	(data_obj *) &commands[93],	/* G */
	(data_obj *) 0,                 /* H */
	(data_obj *) &commands[113],	/* I */
	(data_obj *) &commands[77],	/* J */
	(data_obj *) &commands[107],	/* K */
	(data_obj *) &commands[28],	/* L */
	(data_obj *) &commands[83],	/* M */
	(data_obj *) 0,                 /* N */
	(data_obj *) 0,                 /* O */
	(data_obj *) 0,                 /* P */
	(data_obj *) &commands[139],	/* Q */
	(data_obj *) &commands[147],	/* R */
	(data_obj *) 0,                 /* S */
	(data_obj *) 0,                 /* T */
	(data_obj *) &commands[29],	/* U */
	(data_obj *) &commands[133],	/* V */
	(data_obj *) &commands[34],	/* W */
	(data_obj *) &commands[72],	/* X */
	(data_obj *) &commands[191],	/* Y */
	(data_obj *) &commands[150],	/* Z */
	(data_obj *) &commands[9],	/* [ */
	(data_obj *) &commands[46],	/* \ */
	(data_obj *) &commands[86],	/* ] */
	(data_obj *) 0,                 /* ^ */
	(data_obj *) 0,                 /* _ */
	(data_obj *) 0,                 /* ` */
	(data_obj *) &commands[11],	/* a */
	(data_obj *) &commands[13],	/* b */
	(data_obj *) &commands[27],	/* c */
	(data_obj *) &commands[100],	/* d */
	(data_obj *) &commands[88],	/* e */
	(data_obj *) &commands[89],	/* f */
	(data_obj *) &commands[93],	/* g */
	(data_obj *) 0,                 /* h */
	(data_obj *) &commands[113],	/* i */
	(data_obj *) &commands[77],	/* j */
	(data_obj *) &commands[107],	/* k */
	(data_obj *) &commands[28],	/* l */
	(data_obj *) &commands[83],	/* m */
	(data_obj *) 0,                 /* n */
	(data_obj *) 0,                 /* o */
	(data_obj *) 0,                 /* p */
	(data_obj *) &commands[139],	/* q */
	(data_obj *) &commands[147],	/* r */
	(data_obj *) 0,                 /* s */
	(data_obj *) 0,                 /* t */
	(data_obj *) &commands[29],	/* u */
	(data_obj *) &commands[133],	/* v */
	(data_obj *) &commands[34],	/* w */
	(data_obj *) &commands[72],	/* x */
	(data_obj *) &commands[191],	/* y */
	(data_obj *) &commands[150],	/* z */
	(data_obj *) 0,                 /* { */
	(data_obj *) 0,                 /* | */
	(data_obj *) 0,                 /* } */
	(data_obj *) &commands[111],	/* ~ */
#ifdef ASCII
	(data_obj *) &commands[101],	/* ^? */
#else /* IBMPC or MAC */
	(data_obj *) &commands[101],	/* ^? */
	(data_obj *) 0,                 /* M-C-@ */
	(data_obj *) 0,                 /* M-C-A */
	(data_obj *) 0,                 /* M-C-B */
	(data_obj *) 0,                 /* M-C-C */
	(data_obj *) 0,                 /* M-C-D */
	(data_obj *) 0,                 /* M-C-E */
	(data_obj *) 0,                 /* M-C-F */
	(data_obj *) 0,                 /* M-C-G */
	(data_obj *) 0,                 /* M-C-H */
	(data_obj *) 0,                 /* M-C-I */
	(data_obj *) 0,                 /* M-C-J */
	(data_obj *) 0,                 /* M-C-K */
	(data_obj *) 0,                 /* M-C-L */
	(data_obj *) 0,                 /* M-C-M */
	(data_obj *) 0,                 /* M-C-N */
	(data_obj *) 0,                 /* M-C-O */
	(data_obj *) 0,                 /* M-C-P */
	(data_obj *) 0,                 /* M-C-Q */
	(data_obj *) 0,                 /* M-C-R */
	(data_obj *) 0,                 /* M-C-S */
	(data_obj *) 0,                 /* M-C-T */
	(data_obj *) 0,                 /* M-C-U */
	(data_obj *) 0,                 /* M-C-V */
	(data_obj *) 0,                 /* M-C-W */
	(data_obj *) 0,                 /* M-C-X */
	(data_obj *) 0,                 /* M-C-Y */
	(data_obj *) 0,                 /* M-C-Z */
	(data_obj *) 0,                 /* M-ESC */
	(data_obj *) 0,                 /* M-C-\ */
	(data_obj *) 0,                 /* M-C-] */
	(data_obj *) 0,                 /* M-C-^ */
	(data_obj *) 0,                 /* M-C-_ */
	(data_obj *) 0,                 /* M-  */
	(data_obj *) 0,                 /* M-! */
	(data_obj *) 0,                 /* M-" */
	(data_obj *) 0,                 /* M-# */
	(data_obj *) 0,                 /* M-$ */
	(data_obj *) 0,                 /* M-% */
	(data_obj *) 0,                 /* M-& */
	(data_obj *) 0,                 /* M-' */
	(data_obj *) 0,                 /* M-( */
	(data_obj *) 0,                 /* M-) */
	(data_obj *) 0,                 /* M-* */
	(data_obj *) 0,                 /* M-+ */
	(data_obj *) 0,                 /* M-, */
	(data_obj *) 0,                 /* M-- */
	(data_obj *) 0,                 /* M-. */
	(data_obj *) 0,                 /* M-/ */
	(data_obj *) 0,                 /* M-0 */
	(data_obj *) 0,                 /* M-1 */
	(data_obj *) 0,                 /* M-2 */
	(data_obj *) 0,                 /* M-3 */
	(data_obj *) 0,                 /* M-4 */
	(data_obj *) 0,                 /* M-5 */
	(data_obj *) 0,                 /* M-6 */
	(data_obj *) 0,                 /* M-7 */
	(data_obj *) 0,                 /* M-8 */
	(data_obj *) 0,                 /* M-9 */
	(data_obj *) 0,                 /* M-: */
	(data_obj *) 0,                 /* M-; */
	(data_obj *) 0,                 /* M-< */
	(data_obj *) 0,                 /* M-= */
	(data_obj *) 0,                 /* M-> */
	(data_obj *) 0,                 /* M-? */
	(data_obj *) 0,                 /* M-@ */
	(data_obj *) 0,                 /* M-A */
	(data_obj *) 0,                 /* M-B */
	(data_obj *) 0,                 /* M-C */
	(data_obj *) 0,                 /* M-D */
	(data_obj *) 0,                 /* M-E */
	(data_obj *) 0,                 /* M-F */
	(data_obj *) 0,                 /* M-G */
	(data_obj *) 0,                 /* M-H */
	(data_obj *) 0,                 /* M-I */
	(data_obj *) 0,                 /* M-J */
	(data_obj *) 0,                 /* M-K */
	(data_obj *) 0,                 /* M-L */
	(data_obj *) 0,                 /* M-M */
	(data_obj *) 0,                 /* M-N */
	(data_obj *) 0,                 /* M-O */
	(data_obj *) 0,                 /* M-P */
	(data_obj *) 0,                 /* M-Q */
	(data_obj *) 0,                 /* M-R */
	(data_obj *) 0,                 /* M-S */
	(data_obj *) 0,                 /* M-T */
	(data_obj *) 0,                 /* M-U */
	(data_obj *) 0,                 /* M-V */
	(data_obj *) 0,                 /* M-W */
	(data_obj *) 0,                 /* M-X */
	(data_obj *) 0,                 /* M-Y */
	(data_obj *) 0,                 /* M-Z */
	(data_obj *) 0,                 /* M-[ */
	(data_obj *) 0,                 /* M-\ */
	(data_obj *) 0,                 /* M-] */
	(data_obj *) 0,                 /* M-^ */
	(data_obj *) 0,                 /* M-_ */
	(data_obj *) 0,                 /* M-` */
	(data_obj *) 0,                 /* M-a */
	(data_obj *) 0,                 /* M-b */
	(data_obj *) 0,                 /* M-c */
	(data_obj *) 0,                 /* M-d */
	(data_obj *) 0,                 /* M-e */
	(data_obj *) 0,                 /* M-f */
	(data_obj *) 0,                 /* M-g */
	(data_obj *) 0,                 /* M-h */
	(data_obj *) 0,                 /* M-i */
	(data_obj *) 0,                 /* M-j */
	(data_obj *) 0,                 /* M-k */
	(data_obj *) 0,                 /* M-l */
	(data_obj *) 0,                 /* M-m */
	(data_obj *) 0,                 /* M-n */
	(data_obj *) 0,                 /* M-o */
	(data_obj *) 0,                 /* M-p */
	(data_obj *) 0,                 /* M-q */
	(data_obj *) 0,                 /* M-r */
	(data_obj *) 0,                 /* M-s */
	(data_obj *) 0,                 /* M-t */
	(data_obj *) 0,                 /* M-u */
	(data_obj *) 0,                 /* M-v */
	(data_obj *) 0,                 /* M-w */
	(data_obj *) 0,                 /* M-x */
	(data_obj *) 0,                 /* M-y */
	(data_obj *) 0,                 /* M-z */
	(data_obj *) 0,                 /* M-{ */
	(data_obj *) 0,                 /* M-| */
	(data_obj *) 0,                 /* M-} */
	(data_obj *) 0,                 /* M-~ */
	(data_obj *) 0,                 /* M-^? */
#endif /* ASCII */
};

data_obj	*CtlxKeys[NCHARS] = {
	(data_obj *) 0,                 /* C-@ */
	(data_obj *) 0,                 /* C-A */
	(data_obj *) &commands[110],	/* C-B */
	(data_obj *) &commands[75],	/* C-C */
	(data_obj *) 0,                 /* C-D */
	(data_obj *) &commands[33],	/* C-E */
	(data_obj *) &commands[80],	/* C-F */
	(data_obj *) 0,                 /* C-G */
	(data_obj *) 0,                 /* C-H */
	(data_obj *) &commands[99],	/* C-I */
	(data_obj *) 0,                 /* C-J */
	(data_obj *) 0,                 /* C-K */
	(data_obj *) 0,                 /* C-L */
	(data_obj *) &commands[188],	/* C-M */
	(data_obj *) &commands[118],	/* C-N */
	(data_obj *) &commands[40],	/* C-O */
	(data_obj *) &commands[131],	/* C-P */
	(data_obj *) 0,                 /* C-Q */
	(data_obj *) &commands[182],	/* C-R */
	(data_obj *) &commands[149],	/* C-S */
	(data_obj *) &commands[178],	/* C-T */
	(data_obj *) 0,                 /* C-U */
	(data_obj *) &commands[182],	/* C-V */
	(data_obj *) &commands[186],	/* C-W */
	(data_obj *) &commands[71],	/* C-X */
	(data_obj *) 0,                 /* C-Y */
	(data_obj *) 0,                 /* C-Z */
	(data_obj *) 0,                 /* ESC */
	(data_obj *) &commands[149],	/* C-\ */
	(data_obj *) 0,                 /* C-] */
	(data_obj *) 0,                 /* C-^ */
	(data_obj *) 0,                 /* C-_ */
	(data_obj *) 0,                 /*   */
	(data_obj *) &commands[162],	/* ! */
	(data_obj *) 0,                 /* " */
	(data_obj *) 0,                 /* # */
	(data_obj *) 0,                 /* $ */
	(data_obj *) 0,                 /* % */
	(data_obj *) 0,                 /* & */
	(data_obj *) 0,                 /* ' */
	(data_obj *) &commands[14],	/* ( */
	(data_obj *) &commands[66],	/* ) */
	(data_obj *) 0,                 /* * */
	(data_obj *) 0,                 /* + */
	(data_obj *) 0,                 /* , */
	(data_obj *) 0,                 /* - */
	(data_obj *) 0,                 /* . */
	(data_obj *) 0,                 /* / */
	(data_obj *) 0,                 /* 0 */
	(data_obj *) &commands[44],	/* 1 */
	(data_obj *) &commands[172],	/* 2 */
	(data_obj *) 0,                 /* 3 */
	(data_obj *) &commands[183],	/* 4 */
	(data_obj *) 0,                 /* 5 */
	(data_obj *) 0,                 /* 6 */
	(data_obj *) 0,                 /* 7 */
	(data_obj *) 0,                 /* 8 */
	(data_obj *) 0,                 /* 9 */
	(data_obj *) 0,                 /* : */
	(data_obj *) 0,                 /* ; */
	(data_obj *) 0,                 /* < */
	(data_obj *) 0,                 /* = */
	(data_obj *) 0,                 /* > */
	(data_obj *) &commands[50],	/* ? */
	(data_obj *) 0,                 /* @ */
	(data_obj *) 0,                 /* A */
	(data_obj *) &commands[158],	/* B */
	(data_obj *) 0,                 /* C */
	(data_obj *) &commands[47],	/* D */
	(data_obj *) &commands[73],	/* E */
	(data_obj *) 0,                 /* F */
	(data_obj *) 0,                 /* G */
	(data_obj *) 0,                 /* H */
	(data_obj *) 0,                 /* I */
	(data_obj *) 0,                 /* J */
	(data_obj *) &commands[41],	/* K */
	(data_obj *) 0,                 /* L */
	(data_obj *) 0,                 /* M */
	(data_obj *) &commands[121],	/* N */
	(data_obj *) &commands[134],	/* O */
	(data_obj *) &commands[134],	/* P */
	(data_obj *) 0,                 /* Q */
	(data_obj *) 0,                 /* R */
	(data_obj *) &commands[149],	/* S */
	(data_obj *) &commands[81],	/* T */
	(data_obj *) 0,                 /* U */
	(data_obj *) 0,                 /* V */
	(data_obj *) 0,                 /* W */
	(data_obj *) 0,                 /* X */
	(data_obj *) 0,                 /* Y */
	(data_obj *) 0,                 /* Z */
	(data_obj *) 0,                 /* [ */
	(data_obj *) 0,                 /* \ */
	(data_obj *) 0,                 /* ] */
	(data_obj *) &commands[95],	/* ^ */
	(data_obj *) 0,                 /* _ */
	(data_obj *) 0,                 /* ` */
	(data_obj *) 0,                 /* a */
	(data_obj *) &commands[158],	/* b */
	(data_obj *) 0,                 /* c */
	(data_obj *) &commands[47],	/* d */
	(data_obj *) &commands[73],	/* e */
	(data_obj *) 0,                 /* f */
	(data_obj *) 0,                 /* g */
	(data_obj *) 0,                 /* h */
	(data_obj *) 0,                 /* i */
	(data_obj *) 0,                 /* j */
	(data_obj *) &commands[41],	/* k */
	(data_obj *) 0,                 /* l */
	(data_obj *) 0,                 /* m */
	(data_obj *) &commands[121],	/* n */
	(data_obj *) &commands[134],	/* o */
	(data_obj *) &commands[134],	/* p */
	(data_obj *) 0,                 /* q */
	(data_obj *) 0,                 /* r */
	(data_obj *) &commands[149],	/* s */
	(data_obj *) &commands[81],	/* t */
	(data_obj *) 0,                 /* u */
	(data_obj *) 0,                 /* v */
	(data_obj *) 0,                 /* w */
	(data_obj *) 0,                 /* x */
	(data_obj *) 0,                 /* y */
	(data_obj *) 0,                 /* z */
	(data_obj *) 0,                 /* { */
	(data_obj *) 0,                 /* | */
	(data_obj *) 0,                 /* } */
	(data_obj *) 0,                 /* ~ */
#ifdef ASCII
	(data_obj *) &commands[105],	/* ^? */
#else /* IBMPC or MAC */
	(data_obj *) &commands[105],	/* ^? */
	(data_obj *) 0,                 /* M-C-@ */
	(data_obj *) 0,                 /* M-C-A */
	(data_obj *) 0,                 /* M-C-B */
	(data_obj *) 0,                 /* M-C-C */
	(data_obj *) 0,                 /* M-C-D */
	(data_obj *) 0,                 /* M-C-E */
	(data_obj *) 0,                 /* M-C-F */
	(data_obj *) 0,                 /* M-C-G */
	(data_obj *) 0,                 /* M-C-H */
	(data_obj *) 0,                 /* M-C-I */
	(data_obj *) 0,                 /* M-C-J */
	(data_obj *) 0,                 /* M-C-K */
	(data_obj *) 0,                 /* M-C-L */
	(data_obj *) 0,                 /* M-C-M */
	(data_obj *) 0,                 /* M-C-N */
	(data_obj *) 0,                 /* M-C-O */
	(data_obj *) 0,                 /* M-C-P */
	(data_obj *) 0,                 /* M-C-Q */
	(data_obj *) 0,                 /* M-C-R */
	(data_obj *) 0,                 /* M-C-S */
	(data_obj *) 0,                 /* M-C-T */
	(data_obj *) 0,                 /* M-C-U */
	(data_obj *) 0,                 /* M-C-V */
	(data_obj *) 0,                 /* M-C-W */
	(data_obj *) 0,                 /* M-C-X */
	(data_obj *) 0,                 /* M-C-Y */
	(data_obj *) 0,                 /* M-C-Z */
	(data_obj *) 0,                 /* M-ESC */
	(data_obj *) 0,                 /* M-C-\ */
	(data_obj *) 0,                 /* M-C-] */
	(data_obj *) 0,                 /* M-C-^ */
	(data_obj *) 0,                 /* M-C-_ */
	(data_obj *) 0,                 /* M-  */
	(data_obj *) 0,                 /* M-! */
	(data_obj *) 0,                 /* M-" */
	(data_obj *) 0,                 /* M-# */
	(data_obj *) 0,                 /* M-$ */
	(data_obj *) 0,                 /* M-% */
	(data_obj *) 0,                 /* M-& */
	(data_obj *) 0,                 /* M-' */
	(data_obj *) 0,                 /* M-( */
	(data_obj *) 0,                 /* M-) */
	(data_obj *) 0,                 /* M-* */
	(data_obj *) 0,                 /* M-+ */
	(data_obj *) 0,                 /* M-, */
	(data_obj *) 0,                 /* M-- */
	(data_obj *) 0,                 /* M-. */
	(data_obj *) 0,                 /* M-/ */
	(data_obj *) 0,                 /* M-0 */
	(data_obj *) 0,                 /* M-1 */
	(data_obj *) 0,                 /* M-2 */
	(data_obj *) 0,                 /* M-3 */
	(data_obj *) 0,                 /* M-4 */
	(data_obj *) 0,                 /* M-5 */
	(data_obj *) 0,                 /* M-6 */
	(data_obj *) 0,                 /* M-7 */
	(data_obj *) 0,                 /* M-8 */
	(data_obj *) 0,                 /* M-9 */
	(data_obj *) 0,                 /* M-: */
	(data_obj *) 0,                 /* M-; */
	(data_obj *) 0,                 /* M-< */
	(data_obj *) 0,                 /* M-= */
	(data_obj *) 0,                 /* M-> */
	(data_obj *) 0,                 /* M-? */
	(data_obj *) 0,                 /* M-@ */
	(data_obj *) 0,                 /* M-A */
	(data_obj *) 0,                 /* M-B */
	(data_obj *) 0,                 /* M-C */
	(data_obj *) 0,                 /* M-D */
	(data_obj *) 0,                 /* M-E */
	(data_obj *) 0,                 /* M-F */
	(data_obj *) 0,                 /* M-G */
	(data_obj *) 0,                 /* M-H */
	(data_obj *) 0,                 /* M-I */
	(data_obj *) 0,                 /* M-J */
	(data_obj *) 0,                 /* M-K */
	(data_obj *) 0,                 /* M-L */
	(data_obj *) 0,                 /* M-M */
	(data_obj *) 0,                 /* M-N */
	(data_obj *) 0,                 /* M-O */
	(data_obj *) 0,                 /* M-P */
	(data_obj *) 0,                 /* M-Q */
	(data_obj *) 0,                 /* M-R */
	(data_obj *) 0,                 /* M-S */
	(data_obj *) 0,                 /* M-T */
	(data_obj *) 0,                 /* M-U */
	(data_obj *) 0,                 /* M-V */
	(data_obj *) 0,                 /* M-W */
	(data_obj *) 0,                 /* M-X */
	(data_obj *) 0,                 /* M-Y */
	(data_obj *) 0,                 /* M-Z */
	(data_obj *) 0,                 /* M-[ */
	(data_obj *) 0,                 /* M-\ */
	(data_obj *) 0,                 /* M-] */
	(data_obj *) 0,                 /* M-^ */
	(data_obj *) 0,                 /* M-_ */
	(data_obj *) 0,                 /* M-` */
	(data_obj *) 0,                 /* M-a */
	(data_obj *) 0,                 /* M-b */
	(data_obj *) 0,                 /* M-c */
	(data_obj *) 0,                 /* M-d */
	(data_obj *) 0,                 /* M-e */
	(data_obj *) 0,                 /* M-f */
	(data_obj *) 0,                 /* M-g */
	(data_obj *) 0,                 /* M-h */
	(data_obj *) 0,                 /* M-i */
	(data_obj *) 0,                 /* M-j */
	(data_obj *) 0,                 /* M-k */
	(data_obj *) 0,                 /* M-l */
	(data_obj *) 0,                 /* M-m */
	(data_obj *) 0,                 /* M-n */
	(data_obj *) 0,                 /* M-o */
	(data_obj *) 0,                 /* M-p */
	(data_obj *) 0,                 /* M-q */
	(data_obj *) 0,                 /* M-r */
	(data_obj *) 0,                 /* M-s */
	(data_obj *) 0,                 /* M-t */
	(data_obj *) 0,                 /* M-u */
	(data_obj *) 0,                 /* M-v */
	(data_obj *) 0,                 /* M-w */
	(data_obj *) 0,                 /* M-x */
	(data_obj *) 0,                 /* M-y */
	(data_obj *) 0,                 /* M-z */
	(data_obj *) 0,                 /* M-{ */
	(data_obj *) 0,                 /* M-| */
	(data_obj *) 0,                 /* M-} */
	(data_obj *) 0,                 /* M-~ */
	(data_obj *) 0,                 /* M-^? */
#endif /* ASCII */
};
