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

#ifndef BITPRIM_NODECINT_CHAIN_CHAIN_H_
#define BITPRIM_NODECINT_CHAIN_CHAIN_H_

#include <stdio.h>
#include <stdint.h>

#include <bitprim/nodecint/visibility.h>
#include <bitprim/nodecint/primitives.h>

#ifdef __cplusplus
extern "C" {
#endif


BITPRIM_EXPORT
void chain_fetch_last_height(chain_t chain, void* ctx, last_height_fetch_handler_t handler);

BITPRIM_EXPORT
int chain_get_last_height(chain_t chain, size_t* height);

BITPRIM_EXPORT
void chain_fetch_block_height(chain_t chain, void* ctx, hash_t hash, block_height_fetch_handler_t handler);

BITPRIM_EXPORT
int chain_get_block_height(chain_t chain, hash_t hash, size_t* height);


// Block Header ---------------------------------------------------------------------
BITPRIM_EXPORT
void chain_fetch_block_header_by_height(chain_t chain, void* ctx, size_t height, block_header_fetch_handler_t handler);

BITPRIM_EXPORT
int chain_get_block_header_by_height(chain_t chain, size_t height, header_t* header, size_t* ret_height);

BITPRIM_EXPORT
void chain_fetch_block_header_by_hash(chain_t chain, void* ctx, hash_t hash, block_header_fetch_handler_t handler);

BITPRIM_EXPORT
int chain_get_block_header_by_hash(chain_t chain, hash_t hash, header_t* header, size_t* ret_height);


// Block ---------------------------------------------------------------------
BITPRIM_EXPORT
void chain_fetch_block_by_height(chain_t chain, void* ctx, size_t height, block_fetch_handler_t handler);

BITPRIM_EXPORT
int chain_get_block_by_height(chain_t chain, size_t height, block_t* block, size_t* ret_height);

BITPRIM_EXPORT
void chain_fetch_block_by_hash(chain_t chain, void* ctx, hash_t hash, block_fetch_handler_t handler);

BITPRIM_EXPORT
int chain_get_block_by_hash(chain_t chain, hash_t hash, block_t* block, size_t* ret_height);


// Merkle Block ---------------------------------------------------------------------
BITPRIM_EXPORT
void chain_fetch_merkle_block_by_height(chain_t chain, void* ctx, size_t height, merkle_block_fetch_handler_t handler);

BITPRIM_EXPORT
void chain_fetch_merkle_block_by_hash(chain_t chain, void* ctx, hash_t hash, merkle_block_fetch_handler_t handler);

// Compact Block ---------------------------------------------------------------------
BITPRIM_EXPORT
void chain_fetch_compact_block_by_height(chain_t chain, void* ctx, size_t height, compact_block_fetch_handler_t handler);

BITPRIM_EXPORT
void chain_fetch_compact_block_by_hash(chain_t chain, void* ctx, hash_t hash, compact_block_fetch_handler_t handler);


// Transaction ---------------------------------------------------------------------
BITPRIM_EXPORT
void chain_fetch_transaction(chain_t chain, void* ctx, hash_t hash, int require_confirmed, transaction_fetch_handler_t handler);

BITPRIM_EXPORT
int chain_get_transaction(chain_t chain, hash_t hash, int require_confirmed, transaction_t* transaction, size_t* ret_height, size_t* index);

BITPRIM_EXPORT
void chain_fetch_transaction_position(chain_t chain, void* ctx, hash_t hash, int require_confirmed, transaction_index_fetch_handler_t handler);


// Output  ---------------------------------------------------------------------
BITPRIM_EXPORT
void chain_fetch_output(chain_t chain, void* ctx, hash_t hash, uint32_t index, int require_confirmed, output_fetch_handler_t handler);

BITPRIM_EXPORT
int chain_get_output(chain_t chain, hash_t hash, uint32_t index, int require_confirmed, output_t* output);

// Spend ---------------------------------------------------------------------
BITPRIM_EXPORT
void chain_fetch_spend(chain_t chain, void* ctx, output_point_t outpoint, spend_fetch_handler_t handler);

// History ---------------------------------------------------------------------
BITPRIM_EXPORT
void chain_fetch_history(chain_t chain, void* ctx, payment_address_t address, size_t limit, size_t from_height, history_fetch_handler_t handler);

BITPRIM_EXPORT
int chain_get_history(chain_t chain, payment_address_t address, size_t limit, size_t from_height, history_compact_list_t* out_history);


//BITPRIM_EXPORT
//void chain_fetch_stealth(const binary& filter, size_t from_height, stealth_fetch_handler handler);


// ------------------------------------------------

BITPRIM_EXPORT
transaction_t hex_to_tx(char const* tx_hex);


BITPRIM_EXPORT
void chain_validate_tx(chain_t chain, void* ctx, transaction_t tx, validate_tx_handler_t handler);



#ifdef __cplusplus
} // extern "C"
#endif

#endif /* BITPRIM_NODECINT_CHAIN_CHAIN_H_ */
