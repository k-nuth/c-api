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

#ifndef BITPRIM_NODE_CINT_MERKLE_BLOCK_H_
#define BITPRIM_NODE_CINT_MERKLE_BLOCK_H_

#include <stdio.h>
#include <stdint.h>

#include <bitprim/nodecint/visibility.h>
#include <bitprim/nodecint/primitives.h>

#ifdef __cplusplus
extern "C" {
#endif


BITPRIM_EXPORT
void merkle_block_destruct(merkle_block_t block);

BITPRIM_EXPORT
int merkle_block_is_valid(merkle_block_t block);

BITPRIM_EXPORT
header_t merkle_block_header(merkle_block_t block);

BITPRIM_EXPORT
hash_t merkle_block_hash(merkle_block_t block);

BITPRIM_EXPORT
size_t merkle_block_transaction_count(merkle_block_t block);

BITPRIM_EXPORT
transaction_t merkle_block_transactions(merkle_block_t block, size_t* n);

BITPRIM_EXPORT
transaction_t merkle_block_transaction_next(transaction_t transaction);

BITPRIM_EXPORT
transaction_t merkle_block_transaction_nth(merkle_block_t block, size_t n);


BITPRIM_EXPORT
size_t merkle_block_serialized_size(merkle_block_t block, uint32_t version);

BITPRIM_EXPORT
/*static*/
uint64_t merkle_block_subsidy(size_t height);

BITPRIM_EXPORT
uint64_t merkle_block_fees(merkle_block_t block);

BITPRIM_EXPORT
uint64_t merkle_block_claim(merkle_block_t block);

BITPRIM_EXPORT
uint64_t merkle_block_reward(merkle_block_t block, size_t height);

//Note: The user is responsible for the resource release
BITPRIM_EXPORT
hash_t merkle_block_generate_merkle_root(merkle_block_t block);

BITPRIM_EXPORT
size_t merkle_block_signature_operations(merkle_block_t block);

BITPRIM_EXPORT
size_t merkle_block_signature_operations_bip16_active(merkle_block_t block, int /*bool*/ bip16_active);

BITPRIM_EXPORT
size_t merkle_block_total_inputs(merkle_block_t block, int /*bool*/ with_coinbase /*= true*/);

BITPRIM_EXPORT
int /*bool*/ merkle_block_is_extra_coinbases(merkle_block_t block);

BITPRIM_EXPORT
int /*bool*/ merkle_block_is_final(merkle_block_t block, size_t height);

BITPRIM_EXPORT
int /*bool*/ merkle_block_is_distinct_transaction_set(merkle_block_t block);

BITPRIM_EXPORT
int /*bool*/ merkle_block_is_valid_coinbase_claim(merkle_block_t block, size_t height);

BITPRIM_EXPORT
int /*bool*/ merkle_block_is_valid_coinbase_script(merkle_block_t block, size_t height);

BITPRIM_EXPORT
int /*bool*/ merkle_block_is_internal_double_spend(merkle_block_t block);

BITPRIM_EXPORT
int /*bool*/ merkle_block_is_valid_merkle_root(merkle_block_t block);




#ifdef __cplusplus
} // extern "C"
#endif

#endif /* BITPRIM_NODE_CINT_MERKLE_BLOCK_H_ */
