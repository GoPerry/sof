/* SPDX-License-Identifier: BSD-3-Clause
 *
 * Copyright(c) 2019 Intel Corporation. All rights reserved.
 *
 * Author: Seppo Ingalsuo <seppo.ingalsuo@linux.intel.com>
 */

#include <stdint.h>

const int32_t src_int32_8_7_2468_5000_fir[160] = {
	-422312,
	2368615,
	-2932237,
	-6298674,
	29944688,
	-51331034,
	27508209,
	84975216,
	-288642914,
	550226014,
	1492511281,
	366054334,
	-272264560,
	114432366,
	-643192,
	-38936495,
	29421864,
	-9395591,
	-831919,
	1737031,
	-450331,
	2911312,
	-5240201,
	-1927127,
	27606697,
	-60666473,
	57006069,
	43363869,
	-280640765,
	739270064,
	1449470990,
	194951241,
	-236285528,
	130864798,
	-25275082,
	-24927424,
	26493783,
	-11152171,
	903853,
	1106185,
	-389881,
	3262243,
	-7538523,
	3502411,
	22171979,
	-65590354,
	85257214,
	-8324029,
	-244620187,
	924243478,
	1365722127,
	43890492,
	-186212161,
	134540977,
	-44767352,
	-10703736,
	21764905,
	-11636733,
	2183673,
	545101,
	-212745,
	3316164,
	-9563008,
	9619476,
	13682497,
	-64988142,
	109436523,
	-66829799,
	-178444662,
	1096001202,
	1245771731,
	-81751262,
	-127840184,
	126719244,
	-58124757,
	2495918,
	15913455,
	-11024297,
	2979126,
	98609,
	98609,
	2979126,
	-11024297,
	15913455,
	2495918,
	-58124757,
	126719244,
	-127840184,
	-81751262,
	1245771731,
	1096001202,
	-178444662,
	-66829799,
	109436523,
	-64988142,
	13682497,
	9619476,
	-9563008,
	3316164,
	-212745,
	545101,
	2183673,
	-11636733,
	21764905,
	-10703736,
	-44767352,
	134540977,
	-186212161,
	43890492,
	1365722127,
	924243478,
	-244620187,
	-8324029,
	85257214,
	-65590354,
	22171979,
	3502411,
	-7538523,
	3262243,
	-389881,
	1106185,
	903853,
	-11152171,
	26493783,
	-24927424,
	-25275082,
	130864798,
	-236285528,
	194951241,
	1449470990,
	739270064,
	-280640765,
	43363869,
	57006069,
	-60666473,
	27606697,
	-1927127,
	-5240201,
	2911312,
	-450331,
	1737031,
	-831919,
	-9395591,
	29421864,
	-38936495,
	-643192,
	114432366,
	-272264560,
	366054334,
	1492511281,
	550226014,
	-288642914,
	84975216,
	27508209,
	-51331034,
	29944688,
	-6298674,
	-2932237,
	2368615,
	-422312

};

struct src_stage src_int32_8_7_2468_5000 = {
	6, 7, 8, 20, 160, 7, 8, 0, 0,
	src_int32_8_7_2468_5000_fir};
