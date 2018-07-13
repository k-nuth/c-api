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

#ifndef BITPRIM_NODECINT_CHAIN_CHAIN_H_
#define BITPRIM_NODECINT_CHAIN_CHAIN_H_

#include <stdint.h>

#include <bitprim/nodecint/primitives.h>
#include <bitprim/nodecint/visibility.h>

#ifdef __cplusplus
extern "C" {
#endif

BITPRIM_EXPORT
void chain_fetch_last_height(chain_t chain, void* ctx, last_height_fetch_handler_t handler);

BITPRIM_EXPORT
error_code_t chain_get_last_height(chain_t chain, uint64_t* /*size_t*/ out_height);

BITPRIM_EXPORT
void chain_fetch_block_height(chain_t chain, void* ctx, hash_t hash, block_height_fetch_handler_t handler);

BITPRIM_EXPORT
error_code_t chain_get_block_height(chain_t chain, hash_t hash, uint64_t* /*size_t*/ out_height);


// Block Header ---------------------------------------------------------------------
BITPRIM_EXPORT
void chain_fetch_block_header_by_height(chain_t chain, void* ctx, uint64_t /*size_t*/ height, block_header_fetch_handler_t handler);

BITPRIM_EXPORT
error_code_t chain_get_block_header_by_height(chain_t chain, uint64_t /*size_t*/ height, header_t* out_header, uint64_t* /*size_t*/ out_height);

BITPRIM_EXPORT
void chain_fetch_block_header_by_hash(chain_t chain, void* ctx, hash_t hash, block_header_fetch_handler_t handler);

BITPRIM_EXPORT
error_code_t chain_get_block_header_by_hash(chain_t chain, hash_t hash, header_t* out_header, uint64_t* /*size_t*/ out_height);


// Block ---------------------------------------------------------------------
BITPRIM_EXPORT
void chain_fetch_block_by_height(chain_t chain, void* ctx, uint64_t /*size_t*/ height, block_fetch_handler_t handler);

BITPRIM_EXPORT
error_code_t chain_get_block_by_height(chain_t chain, uint64_t /*size_t*/ height, block_t* out_block, uint64_t* /*size_t*/ out_height);

BITPRIM_EXPORT
void chain_fetch_block_by_height_timestamp(chain_t chain, void* ctx, uint64_t /*size_t*/ height, block_hash_timestamp_fetch_handler_t handler);

BITPRIM_EXPORT
error_code_t chain_get_block_by_height_timestamp(chain_t chain, uint64_t /*size_t*/ height, hash_t* out_hash, uint32_t* out_timestamp);

BITPRIM_EXPORT
void chain_fetch_block_by_hash(chain_t chain, void* ctx, hash_t hash, block_fetch_handler_t handler);

BITPRIM_EXPORT
error_code_t chain_get_block_by_hash(chain_t chain, hash_t hash, block_t* out_block, uint64_t* /*size_t*/ out_height);

BITPRIM_EXPORT
void chain_fetch_block_header_by_hash_txs_size(chain_t chain, void* ctx, hash_t hash, block_header_txs_size_fetch_handler_t handler);

BITPRIM_EXPORT
error_code_t chain_get_block_header_by_hash_txs_size(chain_t chain, hash_t hash, header_t* out_header, uint64_t* out_block_height, hash_list_t* out_tx_hashes, uint64_t* out_serialized_size);

BITPRIM_EXPORT
error_code_t chain_get_block_hash(chain_t chain, uint64_t height, hash_t* out_hash);


// Merkle Block ---------------------------------------------------------------------
BITPRIM_EXPORT
void chain_fetch_merkle_block_by_height(chain_t chain, void* ctx, uint64_t /*size_t*/ height, merkle_block_fetch_handler_t handler);

BITPRIM_EXPORT
error_code_t chain_get_merkle_block_by_height(chain_t chain, uint64_t /*size_t*/ height, merkle_block_t* out_block, uint64_t* /*size_t*/ out_height);

BITPRIM_EXPORT
void chain_fetch_merkle_block_by_hash(chain_t chain, void* ctx, hash_t hash, merkle_block_fetch_handler_t handler);

BITPRIM_EXPORT
error_code_t chain_get_merkle_block_by_hash(chain_t chain, hash_t hash, merkle_block_t* out_block, uint64_t* /*size_t*/ out_height);


// Compact Block ---------------------------------------------------------------------
BITPRIM_EXPORT
void chain_fetch_compact_block_by_height(chain_t chain, void* ctx, uint64_t /*size_t*/ height, compact_block_fetch_handler_t handler);

BITPRIM_EXPORT
error_code_t chain_get_compact_block_by_height(chain_t chain, uint64_t /*size_t*/ height, compact_block_t* out_block, uint64_t* /*size_t*/ out_height);

BITPRIM_EXPORT
void chain_fetch_compact_block_by_hash(chain_t chain, void* ctx, hash_t hash, compact_block_fetch_handler_t handler);

BITPRIM_EXPORT
error_code_t chain_get_compact_block_by_hash(chain_t chain, hash_t hash, compact_block_t* out_block, uint64_t* /*size_t*/ out_height);

// Transaction ---------------------------------------------------------------------
BITPRIM_EXPORT
void chain_fetch_transaction(chain_t chain, void* ctx, hash_t hash, int require_confirmed, transaction_fetch_handler_t handler);

BITPRIM_EXPORT
error_code_t chain_get_transaction(chain_t chain, hash_t hash, int require_confirmed, transaction_t* out_transaction, uint64_t* /*size_t*/ out_height, uint64_t* /*size_t*/ out_index);

BITPRIM_EXPORT
void chain_fetch_transaction_position(chain_t chain, void* ctx, hash_t hash, int require_confirmed, transaction_index_fetch_handler_t handler);

BITPRIM_EXPORT
error_code_t chain_get_transaction_position(chain_t chain, hash_t hash, int require_confirmed, uint64_t* /*size_t*/ out_position, uint64_t* /*size_t*/ out_height);

// Spend ---------------------------------------------------------------------
BITPRIM_EXPORT
void chain_fetch_spend(chain_t chain, void* ctx, output_point_t op, spend_fetch_handler_t handler);

// History ---------------------------------------------------------------------
BITPRIM_EXPORT
void chain_fetch_history(chain_t chain, void* ctx, payment_address_t address, uint64_t /*size_t*/ limit, uint64_t /*size_t*/ from_height, history_fetch_handler_t handler);

BITPRIM_EXPORT
error_code_t chain_get_history(chain_t chain, payment_address_t address, uint64_t /*size_t*/ limit, uint64_t /*size_t*/ from_height, history_compact_list_t* out_history);

BITPRIM_EXPORT
void chain_fetch_confirmed_transactions(chain_t chain, void* ctx, payment_address_t address, uint64_t max, uint64_t start_height, transactions_by_addres_fetch_handler_t handler);

BITPRIM_EXPORT
error_code_t chain_get_confirmed_transactions(chain_t chain, payment_address_t address, uint64_t max, uint64_t start_height, hash_list_t* out_tx_hashes);

// Stealth ---------------------------------------------------------------------
BITPRIM_EXPORT
void chain_fetch_stealth(chain_t chain, void* ctx, binary_t filter, uint64_t from_height, stealth_fetch_handler_t handler);

BITPRIM_EXPORT
error_code_t chain_get_stealth(chain_t chain, binary_t filter, uint64_t from_height, stealth_compact_list_t* out_list);


//BITPRIM_EXPORT
//void chain_fetch_stealth(const binary& filter, uint64_t /*size_t*/ from_height, stealth_fetch_handler handler);

// BITPRIM_EXPORT
// void chain_fetch_block_locator(chain_t chain, void* ctx, block_indexes_t heights, block_locator_fetch_handler_t handler);

// BITPRIM_EXPORT
// error_code_t chain_get_block_locator(chain_t chain, block_indexes_t heights, get_headers_ptr_t* out_headers);


// ------------------------------------------------------------------
//virtual void fetch_block_locator(const chain::block::indexes& heights, block_locator_fetch_handler handler) const = 0;
//virtual void fetch_locator_block_hashes(get_blocks_const_ptr locator, const hash_digest& threshold, size_t limit, inventory_fetch_handler handler) const = 0;
//virtual void fetch_locator_block_headers(get_headers_const_ptr locator, const hash_digest& threshold, size_t limit, locator_block_headers_fetch_handler handler) const = 0;
//
//// Transaction Pool.
////-------------------------------------------------------------------------
//
//virtual void fetch_template(merkle_block_fetch_handler handler) const = 0;
//virtual void fetch_mempool(size_t count_limit, uint64_t minimum_fee, inventory_fetch_handler handler) const = 0;

BITPRIM_EXPORT
mempool_transaction_list_t chain_get_mempool_transactions(chain_t chain, payment_address_t address, int /*bool*/ use_testnet_rules);

//
//// Filters.
////-------------------------------------------------------------------------
//
//virtual void filter_blocks(get_data_ptr message, result_handler handler) const = 0;
//virtual void filter_transactions(get_data_ptr message, result_handler handler) const = 0;
// ------------------------------------------------------------------



// Subscribers.
//-------------------------------------------------------------------------

//virtual void subscribe_blockchain(reorganize_handler&& handler) = 0;
//virtual void subscribe_transaction(transaction_handler&& handler) = 0;


BITPRIM_EXPORT
void chain_subscribe_blockchain(executor_t exec, chain_t chain, void* ctx, subscribe_blockchain_handler_t handler);

BITPRIM_EXPORT
void chain_subscribe_transaction(executor_t exec, chain_t chain, void* ctx, subscribe_transaction_handler_t handler);

BITPRIM_EXPORT
void chain_unsubscribe(chain_t chain);
    
// Organizers.
//-------------------------------------------------------------------------

BITPRIM_EXPORT
void chain_organize_block(chain_t chain, void* ctx, block_t block, result_handler_t handler);

BITPRIM_EXPORT
int chain_organize_block_sync(chain_t chain, block_t block);

BITPRIM_EXPORT
void chain_organize_transaction(chain_t chain, void* ctx, transaction_t transaction, result_handler_t handler);

BITPRIM_EXPORT
int chain_organize_transaction_sync(chain_t chain, transaction_t transaction);


// Validation.
//-------------------------------------------------------------------------

BITPRIM_EXPORT
void chain_validate_tx(chain_t chain, void* ctx, transaction_t tx, validate_tx_handler_t handler);

BITPRIM_EXPORT
void chain_transaction_validate(chain_t chain, void* ctx, transaction_t tx, validate_tx_handler_t handler);

BITPRIM_EXPORT
void chain_transaction_validate_sequential(chain_t chain, void* ctx, transaction_t tx, validate_tx_handler_t handler);
 

// Queries.
//-------------------------------------------------------------------------

BITPRIM_EXPORT
int /*bool*/ chain_is_stale(chain_t chain);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* BITPRIM_NODECINT_CHAIN_CHAIN_H_ */
