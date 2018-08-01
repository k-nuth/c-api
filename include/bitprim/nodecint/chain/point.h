/**
 * Copyright (c) 2016-2018 Bitprim Inc.
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

#ifndef BITPRIM_NODECINT_CHAIN_POINT_H_
#define BITPRIM_NODECINT_CHAIN_POINT_H_

#include <stdint.h>

#include <bitprim/nodecint/primitives.h>
#include <bitprim/nodecint/visibility.h>

#ifdef __cplusplus
extern "C" {
#endif

BITPRIM_EXPORT
hash_t chain_point_get_hash(point_t point);

BITPRIM_EXPORT
void chain_point_get_hash_out(point_t point, hash_t* out_hash);

BITPRIM_EXPORT
bool_t chain_point_is_valid(point_t point);

BITPRIM_EXPORT
uint32_t chain_point_get_index(point_t point);

BITPRIM_EXPORT
uint64_t chain_point_get_checksum(point_t point);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* BITPRIM_NODECINT_CHAIN_POINT_H_ */
