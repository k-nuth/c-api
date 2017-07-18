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

#ifndef BITPRIM_NODECINT_HEADER_H_
#define BITPRIM_NODECINT_HEADER_H_

#include <stdio.h>
#include <stdint.h>

#include <bitprim/nodecint/visibility.h>
#include <bitprim/nodecint/primitives.h>

#ifdef __cplusplus
extern "C" {
#endif

BITPRIM_EXPORT
void header_destruct(header_t header);

BITPRIM_EXPORT
int header_is_valid(header_t header);

BITPRIM_EXPORT
uint32_t header_version(header_t header);

BITPRIM_EXPORT
void header_set_version(header_t header, uint32_t version);

BITPRIM_EXPORT
uint32_t header_timestamp(header_t header);

BITPRIM_EXPORT
void header_set_timestamp(header_t header, uint32_t timestamp);

BITPRIM_EXPORT
uint32_t header_bits(header_t header);

BITPRIM_EXPORT
void header_set_bits(header_t header, uint32_t bits);

BITPRIM_EXPORT
uint32_t header_nonce(header_t header);

BITPRIM_EXPORT
void header_set_nonce(header_t header, uint32_t nonce);

BITPRIM_EXPORT
hash_t header_previous_block_hash(header_t header);

BITPRIM_EXPORT
hash_t header_merkle(header_t header);

BITPRIM_EXPORT
hash_t header_hash(header_t header);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* BITPRIM_NODECINT_HEADER_H_ */
