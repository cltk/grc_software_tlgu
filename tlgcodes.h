/* tlgcodes.h
 *
 * This is part of the tlgu utility
 * Copyright (C) 2004, 2005, 2011, 2020 Dimitri Marinakis
 * see the file tlgu.c for copying conditions
 *
 * Code arrays for escape sequences
 * See: handle_escape_codes
 *
 */

/* Punctuation codes (%) 0 - 170
	FIXME: %12, %29, %47, %48-%49, (%50 - %81), %105,
	%138, %139, %140, %144, %145, %151-153, %157, %171, %186
	15-May-2020 dm -- updated i.a.w. quickbeta.pdf (14-Jan-2016)
*/
#define MAX_PUNCTUATION 190
unsigned int punctuation[] = {
	0x2020, 0x003f, 0x002a, 0x002f, 0x0021, 0x007c, 0x003d, 0x002b, 0x0025, 0x0026,
	0x003a, 0x2022, 0x203b, 0x2021, 0x00a7, 0x02c8, 0x00a6, 0x2016, 0x0027, 0x2013,
	0x0301, 0x0300, 0x0302, 0x0308, 0x0342, 0x0327, 0x0304, 0x0306, 0x0308, 0x0324,
	0x02bc, 0x02bd, 0x00b4, 0x0060, 0x1fc0, 0x1fce, 0x1fde, 0x1fdd, 0x1fdf, 0x00a8,
	0x23d1, 0x2013, 0x23D5, 0x00d7, 0x23d2, 0x23d3, 0x23d4, 0x003d, 0x0025, 0x0025,
	0x0025, 0x0025, 0x0025, 0x0025, 0x0025, 0x0025, 0x0025, 0x0025, 0x0025, 0x0025,
	0x0025, 0x0025, 0x0025, 0x0025, 0x0025, 0x0025, 0x0025, 0x0025, 0x0025, 0x0025,
	0x0025, 0x0025, 0x0025, 0x0025, 0x0025, 0x0025, 0x0025, 0x0025, 0x0025, 0x0025,
	0x0025, 0x0025, 0x0025, 0x0025, 0x0025, 0x0025, 0x0025, 0x0025, 0x0025, 0x0025,
	0x0025, 0x0485, 0x0486, 0x1dc0, 0x0307, 0x1dc1, 0x035c, 0x0307, 0x0022, 0x2248,
	0x003b, 0x0023, 0x2018, 0x005c, 0x005e, 0x2980, 0x224c, 0x007e, 0x00b1, 0x00b7,
	0x25cb, 0x0025, 0x0025, 0x0025, 0x0025, 0x0025, 0x0025, 0x0025, 0x0025, 0x0025,
	0x0025, 0x0025, 0x0025, 0x0025, 0x0025, 0x0025, 0x0025, 0x032f, 0x030C, 0x2020,
	0x0307, 0x0025, 0x0385, 0x1fcd, 0x1fcf, 0x0025, 0x0025, 0x0025, 0x0025, 0x0025,
	0x2261, 0x23D6, 0x2510, 0x0025, 0x0025, 0x0025, 0x00b7, 0x030a, 0x030c, 0x0328,
	0x007c, 0x002d, 0x2219, 0x002d, 0x2234, 0x2235, 0x0025, 0x0025, 0x2042, 0x00d7,
	0x002d, 0x00f7, 0x0338, 0x00b6, 0x0025, 0x0025, 0x0025, 0x0025, 0x0025, 0x0025,
	0x0359, 0x002f, 0x02bc, 0x02bd, 0x00b4, 0x0060, 0x1fc0, 0x0313, 0x0314, 0x0323,
    0x033d, 0x032d, 0x0361, 0x035d, 0x035e, 0x2319, 0x0025, 0x00ac, 0x031a, 0x0025
	};

/* Text Symbols (#) 0 - 1528
 * May be preceded by upper case (*) this table contains only upper case characters
 *
 * FIXME-TEST: #20, #21, #24, #25, #27, #30, #31, #53, #54, #56,
 *        #61, #62, #64, #66, #68, #87, #102, -#134, #136-#150, #152-#199
 *	      #240-end
 *	15-May-2020 dm -- updated i.a.w. quickbeta.pdf (14-Jan-2016)
 */
#define MAX_TEXT_SYMBOLS 1530
unsigned int text_symbols[] = {
	0x00374, 0x003de, 0x003da, 0x003d8, 0x003de, 0x003e0, 0x02e0f, 0x00023, 0x02e10, 0x00301,
	0x003fd, 0x003ff, 0x02014, 0x0203b, 0x02e16, 0x0003e, 0x003fe, 0x0002f, 0x0003c, 0x00300,
	0x10175, 0x10176, 0x00375, 0x003d8, 0x10176, 0x10176, 0x02e0f, 0x0221a, 0x00023, 0x000b7,
	0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023,
	0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023,
	0x00023, 0x000b7, 0x0205a, 0x0205d, 0x00023, 0x02059, 0x00023, 0x00023, 0x00023, 0x003fd,
	0x00399, 0x10142, 0x10143, 0x00394, 0x10144, 0x00397, 0x10145, 0x003a7, 0x10146, 0x0039c,
	0x0002e, 0x000b7, 0x002d9, 0x0205a, 0x0205d, 0x0002e, 0x00023, 0x00023, 0x00023, 0x00023,
	0x00308, 0x00027, 0x002ca, 0x002cb, 0x01fc0, 0x002bd, 0x002bc, 0x00023, 0x00023, 0x00023,
	0x02014, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023,
/* 100 */
	0x10186, 0x1017b, 0x10182, 0x0039b, 0x10182, 0x00023, 0x10184, 0x00023, 0x00023, 0x10182,
	0x00023, 0x10182, 0x10188, 0x1017c, 0x10140, 0x10189, 0x1017c, 0x10183, 0x003bb, 0x1017d,
	0x10184, 0x003be, 0x1017d, 0x1017c, 0x00023, 0x10182, 0x00023, 0x00023, 0x003fc, 0x00023,
	0x1018a, 0x10177, 0x00023, 0x00023, 0x00023, 0x002d9, 0x003a3, 0x00023, 0x00023, 0x00023,
	0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023,
	0x0221e, 0x02014, 0x00023, 0x00023, 0x00023, 0x00023, 0x02310, 0x00023, 0x00023, 0x00023,
	0x00043, 0x10175, 0x025a1, 0x00375, 0x00023, 0x005d0, 0x02a5a, 0x00023, 0x00023, 0x10175,
	0x02161, 0x10175, 0x10176, 0x10175, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023,
	0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023,
	0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023,
/* 200 */
	0x02643, 0x025a1, 0x0264f, 0x0264d, 0x02640, 0x02650, 0x02644, 0x02609, 0x0263f, 0x0263e,
	0x02642, 0x02651, 0x0264c, 0x02648, 0x0264e, 0x0264a, 0x0264b, 0x02653, 0x02652, 0x02649,
	0x0260d, 0x0263d, 0x0260c, 0x02605, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023,
	0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023,
	0x10177, 0x0260b, 0x02651, 0x00023, 0x0264c, 0x0264e, 0x02126, 0x02127, 0x00023, 0x00023,
	0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023,
	0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023,
	0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023,
	0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023,
	0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023,
/* 300 */
	0x02321, 0x00023, 0x02e0e, 0x0003e, 0x02e0e, 0x02e0e, 0x0003d, 0x02e0e, 0x00023, 0x02e0e,
	0x02e0e, 0x02e0e, 0x02e0e, 0x02e0e, 0x02e0e, 0x02251, 0x00023, 0x00023, 0x00023, 0x02022,
	0x02629, 0x02629, 0x02627, 0x0003e, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023,
	0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023,
	0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023,
	0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023,
	0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023,
	0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023,
	0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023,
	0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023,
/* 400 */
	0x00370, 0x00373, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023,
	0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023,
	0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023,
	0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023,
	0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023,
	0x00023, 0x00283, 0x02e10, 0x02e11, 0x02e10, 0x02e11, 0x02e0e, 0x02e0f, 0x003a7, 0x000b7,
	0x02014, 0x0007c, 0x02627, 0x00023, 0x00023, 0x02627, 0x02138, 0x02192, 0x00023, 0x00023,
	0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00283, 0x00023, 0x00023, 0x00023,
	0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023,
	0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023,
/* 500 */
	0x00023, 0x00023, 0x02609, 0x00023, 0x02e0e, 0x0205c, 0x02e15, 0x02e14, 0x0203b, 0x00023,
	0x00023, 0x00023, 0x003fd, 0x00023, 0x00023, 0x10185, 0x00023, 0x10185, 0x10179, 0x02191,
	0x02629, 0x00023, 0x00023, 0x02e13, 0x02297, 0x0271b, 0x02190, 0x002c6, 0x00023, 0x00023,
	0x00023, 0x0035c, 0x02e12, 0x003da, 0x00311, 0x00023, 0x00023, 0x00023, 0x001b7, 0x00023,
	0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x02263,
	0x02237, 0x025cc, 0x005e6, 0x005d1, 0x022bb, 0x02208, 0x02629, 0x00023, 0x00023, 0x00023,
	0x00023, 0x02191, 0x00305, 0x1d242, 0x1d243, 0x1d244, 0x1d231, 0x1d213, 0x1d233, 0x1d236,
	0x003f9, 0x10143, 0x1d229, 0x1d212, 0x00393, 0x1d215, 0x1d216, 0x003a6, 0x003a1, 0x0039c,
	0x00399, 0x00398, 0x02228, 0x0039d, 0x02127, 0x00396, 0x1d239, 0x00395, 0x1d208, 0x1d21a,
	0x1d23f, 0x1d21b, 0x1d240, 0x0039b, 0x022b8, 0x00036, 0x00039, 0x0230b, 0x00394, 0x1d214,
/* 600 */
	0x1d228, 0x00023, 0x1d237, 0x003a0, 0x1d226, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023,
	0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x1d230, 0x1d21e, 0x003a9, 0x00023, 0x003bb,
	0x00023, 0x1d205, 0x1d201, 0x00023, 0x00023, 0x00023, 0x00023, 0x1d217, 0x0039f, 0x0039e,
	0x00394, 0x00399, 0x1d20e, 0x1d232, 0x1d239, 0x1d200, 0x1d203, 0x1d207, 0x1d209, 0x1d20c,
	0x1d211, 0x003a9, 0x00397, 0x1d21d, 0x1d21f, 0x1d221, 0x1d225, 0x1d22c, 0x1d235, 0x1d20b,
	0x1d20f, 0x003a7, 0x003a4, 0x1d219, 0x1d21c, 0x1d202, 0x1d224, 0x1d22e, 0x1d23e, 0x1d241,
	0x00391, 0x00392, 0x003a5, 0x003a8, 0x1d23a, 0x1d234, 0x1d22f, 0x1d22d, 0x1d210, 0x1d20a,
	0x1d207, 0x1d21b, 0x1d218, 0x1d223, 0x1d222, 0x1d240, 0x1d23d, 0x003bc, 0x1d220, 0x1d204,
	0x00023, 0x00023, 0x00023, 0x02733, 0x1d22a, 0x00023, 0x00023, 0x00023, 0x00023, 0x10175,
	0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x1d227, 0x1d245, 0x00023, 0x00023,
/* 700 */
	0x0205e, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x0223b,
	0x00023, 0x02201, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023,
	0x00023, 0x00023, 0x00023, 0x1d516, 0x0210c, 0x1d510, 0x00023, 0x00023, 0x00023, 0x00023,
	0x02014, 0x023d7, 0x023d8, 0x023d9, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023,
	0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023,
	0x00023, 0x00661, 0x00662, 0x00663, 0x00664, 0x00665, 0x00666, 0x00667, 0x00668, 0x00669,
	0x00660, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023,
	0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023,
	0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023,
	0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023,
/* 800 */
	0x02733, 0x10141, 0x10140, 0x003a7, 0x0002f, 0x003a4, 0x0039a, 0x10166, 0x10148, 0x00023,
	0x00023, 0x00023, 0x10148, 0x10149, 0x1014a, 0x1014b, 0x1014c, 0x1014d, 0x1014e, 0x00023,
	0x00023, 0x00023, 0x1014f, 0x10150, 0x10151, 0x10152, 0x10153, 0x10154, 0x00023, 0x10155,
	0x10147, 0x10147, 0x10156, 0x0039c, 0x10157, 0x003a7, 0x003a3, 0x003a4, 0x10143, 0x10141,
	0x02551, 0x02980, 0x000b7, 0x1015b, 0x0205b, 0x10158, 0x10110, 0x1015e, 0x10112, 0x00023,
	0x00023, 0x00023, 0x00023, 0x00399, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023,
	0x00023, 0x00023, 0x00394, 0x10144, 0x00023, 0x10145, 0x003a7, 0x10146, 0x00023, 0x00023,
	0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023,
	0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023,
	0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023,
/* 900 */
	0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023,
	0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023,
	0x00023, 0x00023, 0x1d228, 0x00023, 0x00023, 0x1d217, 0x1d232, 0x00057, 0x1d20b, 0x1d214,
	0x00023, 0x00023, 0x02733, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x001a7, 0x0007e,
	0x00023, 0x1d205, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023,
	0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023,
	0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023,
	0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023,
	0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023,
	0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023,
/* 1000 */
	0x1017c, 0x1017d, 0x1017e, 0x1017f, 0x10180, 0x003a7, 0x00023, 0x00023, 0x00023, 0x00023,
	0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023,
	0x0003c, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023,
	0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023,
	0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023,
	0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023,
	0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023,
	0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023,
	0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023,
	0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023,
/* 1100 */
	0x02183, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023,
	0x00023, 0x00023, 0x00023, 0x00023, 0x1d201, 0x0007c, 0x001a7, 0x0005a, 0x00023, 0x00110,
	0x00023, 0x0005a, 0x00023, 0x00023, 0x0211e, 0x00023, 0x0004f, 0x00023, 0x00023, 0x00023,
	0x0005c, 0x00023, 0x00023, 0x00023, 0x00023, 0x00039, 0x02112, 0x00023, 0x00023, 0x00023,
	0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023,
	0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023,
	0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023,
	0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023,
	0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023,
	0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023,
/* 1200 */
	0x000a2, 0x02021, 0x020a4, 0x000df, 0x000b0, 0x00023, 0x00023, 0x00023, 0x00023, 0x00127,
	0x00023, 0x00023, 0x00023, 0x00152, 0x00153, 0x000c6, 0x000e6, 0x00023, 0x00023, 0x00024,
	0x00040, 0x00131, 0x00130, 0x00023, 0x02295, 0x000a9, 0x02731, 0x02021, 0x00023, 0x00023,
	0x025ad, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023,
	0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023,
	0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023,
	0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023,
	0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023,
	0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023,
	0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023,
/* 1300 */
	0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023,
	0x00023, 0x00023, 0x00023, 0x0223d, 0x00023, 0x00023, 0x00023, 0x00023, 0x0223b, 0x00023,
	0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023,
	0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x0003e, 0x1017e, 0x00023,
	0x02116, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023,
	0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023,
	0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023,
	0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023,
	0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023,
	0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023,
/* 1400 */
	0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023,
	0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023,
	0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023,
	0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023,
	0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023,
	0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023,
	0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023,
	0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023,
	0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023,
	0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023,
/* 1500 */
	0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023,
	0x00023, 0x00023, 0x0003c, 0x10175, 0x000f7, 0x1d20f, 0x00023, 0x00023, 0x1d229, 0x00023,
	0x00023, 0x00222, 0x00023, 0x0205b, 0x00023, 0x00023, 0x00023, 0x00023, 0x00023, 0x02227
	};

/* Quotation Marks (") 0 - 60
 * FIXME: check pairs, find symbols for "50-"69
 * 15-May-2020 dm -- updated i.a.w. quickbeta.pdf (14-Jan-2016)
 */
#define MAX_QUOTATION 61
unsigned int quotation_open[MAX_QUOTATION];
unsigned int quotation_open_symbol[] = {
	0x201c, 0x201e, 0x201c, 0x2018, 0x201a, 0x201b, 0x00ab, 0x2039, 0x201c, 0x0022,
	0x0022, 0x0022, 0x0022, 0x0022, 0x0022, 0x0022, 0x0022, 0x0022, 0x0022, 0x0022,
	0x0022, 0x0022, 0x0022, 0x0022, 0x0022, 0x0022, 0x0022, 0x0022, 0x0022, 0x0022,
	0x0022, 0x0022, 0x0022, 0x0022, 0x0022, 0x0022, 0x0022, 0x0022, 0x0022, 0x0022,
	0x0022, 0x0022, 0x0022, 0x0022, 0x0022, 0x0022, 0x0022, 0x0022, 0x0022, 0x0022,
	0x0022, 0x0022, 0x0022, 0x0022, 0x0022, 0x0022, 0x0022, 0x0022, 0x0022, 0x0022,
	0x0022
	};
unsigned int quotation_close_symbol[] = {
	0x201d, 0x201d, 0x201d, 0x2019, 0x2019, 0x2019, 0x00bb, 0x203a, 0x201e, 0x0022,
	0x0022, 0x0022, 0x0022, 0x0022, 0x0022, 0x0022, 0x0022, 0x0022, 0x0022, 0x0022,
	0x0022, 0x0022, 0x0022, 0x0022, 0x0022, 0x0022, 0x0022, 0x0022, 0x0022, 0x0022,
	0x0022, 0x0022, 0x0022, 0x0022, 0x0022, 0x0022, 0x0022, 0x0022, 0x0022, 0x0022,
	0x0022, 0x0022, 0x0022, 0x0022, 0x0022, 0x0022, 0x0022, 0x0022, 0x0022, 0x0022,
	0x0022, 0x0022, 0x0022, 0x0022, 0x0022, 0x0022, 0x0022, 0x0022, 0x0022, 0x0022,
	0x0022
	};


/* Brackets ([) 0 - 89
 * FIXME: [10, [13, [14, [15, [17, [33-[69 
 * 15-May-2020 dm -- updated i.a.w. quickbeta.pdf (14-Jan-2016)
 */
#define MAX_BRACKET 90
unsigned int bracket_open[MAX_BRACKET];
unsigned int bracket_open_symbol[] = {
	0x005b, 0x0028, 0x2329, 0x007b, 0x27e6, 0x2e24, 0x2e22, 0x2e22, 0x2e24, 0x2027,
	0x005b, 0x208d, 0x2192, 0x005b, 0x005b, 0x005b, 0x27e6, 0x300e, 0x27ea, 0x005b,
	0x23a7, 0x23aa, 0x23a8, 0x23a9, 0x005b, 0x005b, 0x005b, 0x005b, 0x005b, 0x005b,
	0x239b, 0x239c, 0x239d, 0x005b, 0x005b, 0x005b, 0x005b, 0x005b, 0x005b, 0x005b,
	0x005b, 0x005b, 0x005b, 0x005b, 0x005b, 0x005b, 0x005b, 0x005b, 0x005b, 0x005b,
	0x005b, 0x005b, 0x005b, 0x005b, 0x005b, 0x005b, 0x005b, 0x005b, 0x005b, 0x005b,
	0x005b, 0x005b, 0x005b, 0x005b, 0x005b, 0x005b, 0x005b, 0x005b, 0x005b, 0x005b,
    0x2e02, 0x2e04, 0x2e09, 0x2e0b, 0x005b, 0x005b, 0x005b, 0x005b, 0x005b, 0x005b,
	0x002f, 0x2afd, 0x2e20, 0x2e21, 0x2e26, 0x2e28, 0x005b, 0x005b, 0x005b, 0x005b,
	};
unsigned int bracket_close_symbol[] = {
	0x005d, 0x0029, 0x232a, 0x007d, 0x27e7, 0x2e25, 0x2e23, 0x2e25, 0x2e23, 0x2027,
	0x005d, 0x208e, 0x2190, 0x005d, 0x005d, 0x005d, 0x27e7, 0x300f, 0x27eb, 0x005d,
	0x23ab, 0x23aa, 0x23ac, 0x23ad, 0x005d, 0x005d, 0x005d, 0x005d, 0x005d, 0x005d,
	0x239e, 0x239f, 0x23a0, 0x005d, 0x005d, 0x005d, 0x005d, 0x005d, 0x005d, 0x005d,
	0x005d, 0x005d, 0x005d, 0x005d, 0x005d, 0x005d, 0x005d, 0x005d, 0x005d, 0x005d,
	0x005d, 0x005d, 0x005d, 0x005d, 0x005d, 0x005d, 0x005d, 0x005d, 0x005d, 0x005d,
	0x005d, 0x005d, 0x005d, 0x005d, 0x005d, 0x005d, 0x005d, 0x005d, 0x005d, 0x005d,
	0x2e03, 0x2e05, 0x2e0a, 0x2e0c, 0x005d, 0x005d, 0x005d, 0x005d, 0x005d, 0x005d,
	0x002f, 0x2afd, 0x2e21, 0x2e20, 0x2e27, 0x2e29, 0x005d, 0x005d, 0x005d, 0x005d,
	};

/* Quasi-Brackets (<) 0 - 100 */
/* FIXME: markup handling
 * * 15-May-2020 dm -- updated i.a.w. quickbeta.pdf (14-Jan-2016)
 */
#define MAX_QUASI_BRACKET 101
unsigned int quasi_bracket_code = 0;
unsigned int quasi_bracket_open[MAX_QUASI_BRACKET];
unsigned int quasi_bracket_open_symbol[] = {
	0x0305, 0x0332, 0x2035, 0x0361, 0x035c, 0x035d, 0x003c, 0x003c, 0x0333, 0x003c,
	0x003c, 0x003c, 0x003c, 0x003c, 0x003c, 0x003c, 0x2035, 0x0333, 0x0336, 0x2035,
	0x003c, 0x003c, 0x003c, 0x003c, 0x003c, 0x003c, 0x003c, 0x003c, 0x003c, 0x003c,
	0x003c, 0x0336, 0x0332, 0x221a, 0x003c, 0x003c, 0x003c, 0x003c, 0x003c, 0x003c,
	0x003c, 0x003c, 0x003c, 0x003c, 0x003c, 0x003c, 0x003c, 0x003c, 0x003c, 0x003c,
	0x003c, 0x003c, 0x003c, 0x003c, 0x003c, 0x003c, 0x003c, 0x003c, 0x003c, 0x003c,
	0x003c, 0x003c, 0x003c, 0x003c, 0x003c, 0x003c, 0x003c, 0x003c, 0x003c, 0x003c,
	0x25ba, 0x0028, 0x0028, 0x003c, 0x003c, 0x003c, 0x003c, 0x003c, 0x003c, 0x003c,
	0x003c, 0x003c, 0x003c, 0x003c, 0x003c, 0x003c, 0x003c, 0x003c, 0x003c, 0x003c,
	0x003c, 0x003c, 0x003c, 0x003c, 0x003c, 0x003c, 0x003c, 0x003c, 0x003c, 0x003c,
	0x003c,
	};
unsigned int quasi_bracket_close_symbol[] = {
	0x003e, 0x003e, 0x2032, 0x003e, 0x003e, 0x003e, 0x003e, 0x003e, 0x003e, 0x003e,
	0x003e, 0x003e, 0x003e, 0x003e, 0x003e, 0x003e, 0x2032, 0x003e, 0x003e, 0x2032,
	0x003e, 0x003e, 0x003e, 0x003e, 0x003e, 0x003e, 0x003e, 0x003e, 0x003e, 0x003e,
	0x003e, 0x003e, 0x003e, 0x003e, 0x003e, 0x003e, 0x003e, 0x003e, 0x003e, 0x003e,
	0x003e, 0x003e, 0x003e, 0x003e, 0x003e, 0x003e, 0x003e, 0x003e, 0x003e, 0x003e,
	0x003e, 0x003e, 0x003e, 0x003e, 0x003e, 0x003e, 0x003e, 0x003e, 0x003e, 0x003e,
	0x003e, 0x003e, 0x003e, 0x003e, 0x003e, 0x003e, 0x003e, 0x003e, 0x003e, 0x003e,
	0x25c4, 0x0029, 0x0029, 0x003e, 0x003e, 0x003e, 0x003e, 0x003e, 0x003e, 0x003e,
	0x003e, 0x003e, 0x003e, 0x003e, 0x003e, 0x003e, 0x003e, 0x003e, 0x003e, 0x003e,
	0x003e, 0x003e, 0x003e, 0x003e, 0x003e, 0x003e, 0x003e, 0x003e, 0x003e, 0x003e,
	0x003e,
	};

/* Non-Text ({) 0 - 71 */
/*FIXME: decide on representation */
#define MAX_NON_TEXT 72
unsigned int non_text_open[MAX_NON_TEXT];
unsigned int non_text_open_symbol[] = {
	0x007b, 0x007b, 0x007b, 0x007b, 0x007b, 0x007b, 0x007b, 0x007b, 0x007b, 0x007b,
	0x007b, 0x007b, 0x007b, 0x007b, 0x007b, 0x007b, 0x007b, 0x007b, 0x007b, 0x007b,
	0x007b, 0x007b, 0x007b, 0x007b, 0x007b, 0x007b, 0x007b, 0x007b, 0x007b, 0x007b,
	0x007b, 0x007b, 0x007b, 0x007b, 0x007b, 0x007b, 0x007b, 0x007b, 0x007b, 0x007b,
	0x007b, 0x007b, 0x007b, 0x007b, 0x007b, 0x007b, 0x007b, 0x007b, 0x007b, 0x007b,
	0x007b, 0x007b, 0x007b, 0x007b, 0x007b, 0x007b, 0x007b, 0x007b, 0x007b, 0x007b,
	0x007b, 0x007b, 0x007b, 0x007b, 0x007b, 0x007b, 0x007b, 0x007b, 0x007b, 0x007b,
	0x007b, 0x007b,
	};
unsigned int non_text_close_symbol[] = {
	0x007d, 0x007d, 0x007d, 0x007d, 0x007d, 0x007d, 0x007d, 0x007d, 0x007d, 0x007d,
	0x007d, 0x007d, 0x007d, 0x007d, 0x007d, 0x007d, 0x007d, 0x007d, 0x007d, 0x007d,
	0x007d, 0x007d, 0x007d, 0x007d, 0x007d, 0x007d, 0x007d, 0x007d, 0x007d, 0x007d,
	0x007d, 0x007d, 0x007d, 0x007d, 0x007d, 0x007d, 0x007d, 0x007d, 0x007d, 0x007d,
	0x007d, 0x007d, 0x007d, 0x007d, 0x007d, 0x007d, 0x007d, 0x007d, 0x007d, 0x007d,
	0x007d, 0x007d, 0x007d, 0x007d, 0x007d, 0x007d, 0x007d, 0x007d, 0x007d, 0x007d,
	0x007d, 0x007d, 0x007d, 0x007d, 0x007d, 0x007d, 0x007d, 0x007d, 0x007d, 0x007d,
	0x007d, 0x007d,
	};
