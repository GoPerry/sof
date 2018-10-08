/*
 * Copyright (c) 2018, Intel Corporation
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   * Neither the name of the Intel Corporation nor the
 *     names of its contributors may be used to endorse or promote products
 *     derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * Author: Marcin Maka <marcin.maka@linux.intel.com>
 */

#include <sof/dai.h>

struct dai_info {
	struct dai_type_info *dai_type_array;
	size_t num_dai_types;
};

static struct dai_info lib_dai = {
	.dai_type_array = NULL,
	.num_dai_types = 0
};

void dai_install(struct dai_type_info *dai_type_array, size_t num_dai_types)
{
	lib_dai.dai_type_array = dai_type_array;
	lib_dai.num_dai_types = num_dai_types;
}

static inline struct dai_type_info *dai_find_type(uint32_t type)
{
	struct dai_type_info *dti;
	for (dti = lib_dai.dai_type_array;
	     dti < lib_dai.dai_type_array + lib_dai.num_dai_types; dti++) {
		if (dti->type == type)
			return dti;
	}
	return NULL;
}

struct dai *dai_get(uint32_t type, uint32_t index)
{
	int ret = 0;
	struct dai_type_info *dti;
	struct dai *d;

	dti = dai_find_type(type);
	if (!dti)
		return NULL; /* type not found */

	for (d = dti->dai_array; d < dti->dai_array + dti->num_dais; d++) {
		if (d->index != index)
			continue;
		/* device created? */
		spin_lock(&d->lock);
		if (d->sref == 0) {
			trace_event(TRACE_CLASS_DAI,
				    "dai-probe type %d index %d",
				    type, index);

			ret = dai_probe(d);
			if (ret < 0) {
				trace_error(TRACE_CLASS_DAI,
					    "probe failed %d",
					    ret);
			}
		}
		if (!ret)
			d->sref++;
		trace_event(TRACE_CLASS_DAI, "dai-get %p sref %d",
			    (uintptr_t)d, d->sref);
		spin_unlock(&d->lock);
		return !ret ? d : NULL;
	}
	trace_error(TRACE_CLASS_DAI, "dai-get type %d index %d not found",
		    type, index);
	return NULL;
}