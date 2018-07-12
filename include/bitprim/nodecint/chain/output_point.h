/**
 * Copyright (c) 2017-2018 Bitprim Inc.
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

#include <stdint.h>

#include <bitprim/nodecint/primitives.h>
#include <bitprim/nodecint/visibility.h>

#ifdef __cplusplus
extern "C" {
#endif

BITPRIM_EXPORT
output_point_t output_point_construct(void);

BITPRIM_EXPORT
output_point_t output_point_construct_from_hash_index(hash_t hash, uint32_t index);

BITPRIM_EXPORT
void output_point_destruct(output_point_t op);

BITPRIM_EXPORT
hash_t output_point_get_hash(output_point_t op);

BITPRIM_EXPORT
void output_point_get_hash_out(output_point_t op, hash_t* out_hash);

BITPRIM_EXPORT
uint32_t output_point_get_index(output_point_t op);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* BITPRIM_NODECINT_CHAIN_OUTPUT_POINT_H_ */
