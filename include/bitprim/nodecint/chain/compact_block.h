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

#ifndef BITPRIM_NODECINT_CHAIN_COMPACT_BLOCK_H_
#define BITPRIM_NODECINT_CHAIN_COMPACT_BLOCK_H_

#include <stdio.h>
#include <stdint.h>

#include <bitprim/nodecint/visibility.h>
#include <bitprim/nodecint/primitives.h>

#ifdef __cplusplus
extern "C" {
#endif

// TODO(fernando): Dario check how to map compact_block::short_ids()

BITPRIM_EXPORT
header_t compact_block_header(compact_block_t block);

BITPRIM_EXPORT
int /*bool*/ compact_block_is_valid(compact_block_t block);

BITPRIM_EXPORT
uint64_t /*size_t*/ compact_block_serialized_size(compact_block_t block, uint32_t version);

BITPRIM_EXPORT
uint64_t /*size_t*/ compact_block_transaction_count(compact_block_t block);

BITPRIM_EXPORT
transaction_t compact_block_transaction_nth(compact_block_t block, uint64_t /*size_t*/ n);

BITPRIM_EXPORT
uint64_t compact_block_nonce(compact_block_t block);

BITPRIM_EXPORT
void compact_block_destruct(compact_block_t block);

BITPRIM_EXPORT
void compact_block_reset(compact_block_t block);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* BITPRIM_NODECINT_CHAIN_COMPACT_BLOCK_H_ */
