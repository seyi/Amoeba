/*	@(#)icon_font.c	1.4	96/02/27 13:52:50 */
/*
 * Copyright 1994 Vrije Universiteit, The Netherlands.
 * For full copyright and restrictions on use see the file COPYRIGHT in the
 * top level of the Amoeba distribution.
 */

#include "amoeba.h"
#include "window/wtypes.h"
#include "window/font.h"

struct Font icon_Font = {
	"iconfont",
	{ 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 } /* NULLPORT */,
	11	/* cnt */,
	20	/* ptsize */,
	0	/* first */,
	11	/* last */,
	0xffff	/* space */,
	0	/* ref_count */
};

struct Font_ch icon_Font_ch[] = {
	{ { NULL, 1, { { 0, 0 }, { 8, 14 } } }, { 0, 0 },    0 },
	{ { NULL, 1, { { 0, 0 }, { 8, 4 } } }, { 0, 0 },   14 },
	{ { NULL, 1, { { 0, 0 }, { 8, 7 } } }, { 0, 0 },   18 },
	{ { NULL, 1, { { 0, 0 }, { 8, 9 } } }, { 0, 0 },   25 },
	{ { NULL, 1, { { 0, 0 }, { 8, 8 } } }, { 0, 0 },   34 },
	{ { NULL, 1, { { 0, 0 }, { 8, 8 } } }, { 0, 0 },   42 },
	{ { NULL, 1, { { 0, 0 }, { 18, 18 } } }, { 0, 0 },   50 },
	{ { NULL, 1, { { 0, 0 }, { 9, 7 } } }, { 0, 0 },   68 },
	{ { NULL, 1, { { 0, 0 }, { 8, 16 } } }, { 0, 0 },   75 },
	{ { NULL, 1, { { 0, 0 }, { 24, 24 } } }, { 0, 0 },   91 },
	{ { NULL, 1, { { 0, 0 }, { 20, 19 } } }, { 0, 0 },  115 },
};

long icon_Bitmap[] = {
	0xff000000,
	0xff000000,
	0xff000000,
	0xff000000,
	0xff000000,
	0xff000000,
	0xff000000,
	0xff000000,
	0xff000000,
	0xff000000,
	0xff000000,
	0xff000000,
	0xff000000,
	0xff000000,
	0x0,
	0x18000000,
	0x18000000,
	0x0,
	0x0,
	0x8000000,
	0x8000000,
	0x3e000000,
	0x8000000,
	0x8000000,
	0x0,
	0x0,
	0x8000000,
	0x2a000000,
	0x1c000000,
	0x1c000000,
	0x1c000000,
	0x2a000000,
	0x8000000,
	0x0,
	0x0,
	0x3c000000,
	0x42000000,
	0x42000000,
	0x42000000,
	0x42000000,
	0x3c000000,
	0x0,
	0x0,
	0x42000000,
	0x24000000,
	0x18000000,
	0x18000000,
	0x24000000,
	0x42000000,
	0x0,
	0xffc00000,
	0xff800000,
	0xff000000,
	0xfe000000,
	0xfe000000,
	0xff000000,
	0xff800000,
	0xe7c00000,
	0xc3e00000,
	0x81f00000,
	0xf80000,
	0x7c0000,
	0x3e0000,
	0x1f0000,
	0xf8000,
	0x7c000,
	0x38000,
	0x10000,
	0x1c000000,
	0x22000000,
	0x41000000,
	0x9c800000,
	0x41000000,
	0x22000000,
	0x1c000000,
	0x80000000,
	0xc0000000,
	0xe0000000,
	0xf0000000,
	0xf8000000,
	0xfc000000,
	0xfe000000,
	0xff000000,
	0xf8000000,
	0xd8000000,
	0x8c000000,
	0xc000000,
	0x6000000,
	0x6000000,
	0x3000000,
	0x3000000,
	0x7e0000,
	0x1ff8000,
	0x7c3e000,
	0xe007000,
	0x1c003800,
	0x38003c00,
	0x30007c00,
	0x6000e600,
	0x6001c600,
	0xc0038300,
	0xc0070300,
	0xc00e0300,
	0xc01c0300,
	0xc0380300,
	0xc0700300,
	0x60e00600,
	0x61c00600,
	0x33800c00,
	0x3f001c00,
	0x1e003800,
	0xe007000,
	0x7c3e000,
	0x1ff8000,
	0x7e0000,
	0xfffff000,
	0xfffff000,
	0xc0003000,
	0xd8003000,
	0xcc003000,
	0xc6003000,
	0xc3003000,
	0xc1803000,
	0xc0c03000,
	0xc0603000,
	0xc0303000,
	0xc0183000,
	0xc00c3000,
	0xc0063000,
	0xc0033000,
	0xc001b000,
	0xc0003000,
	0xfffff000,
	0xfffff000,
};