/**
 * Copyright (c) 2017 Bitprim developers (see AUTHORS)
 *
 * This file is part of Bitprim.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef BITPRIM_NODECINT_CHAIN_OUTPUT_POINT_H_
#define BITPRIM_NODECINT_CHAIN_OUTPUT_POINT_H_

#include <stdio.h>
#include <stdint.h>

#include <bitprim/nodecint/visibility.h>
#include <bitprim/nodecint/primitives.h>


#ifdef __cplusplus
extern "C" {
#endif


BITPRIM_EXPORT
hash_t output_point_get_hash(output_point_t op);

BITPRIM_EXPORT
output_point_t op_point_construct(void);

BITPRIM_EXPORT
uint32_t output_point_get_index(output_point_t op);

BITPRIM_EXPORT
void output_point_destruct(output_point_t op);

#ifdef __cplusplus
} // extern "C"
#endif


#endif /* BITPRIM_NODECINT_CHAIN_OUTPUT_POINT_H_ */
