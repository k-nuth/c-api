// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#ifndef KTH_NODECINT_CHAIN_CHAIN_H_
#define KTH_NODECINT_CHAIN_CHAIN_H_

#include <stdint.h>

#include <kth/capi/primitives.h>
#include <kth/capi/visibility.h>

#ifdef __cplusplus
extern "C" {
#endif

KTH_EXPORT
void chain_fetch_last_height(chain_t chain, void* ctx, last_height_fetch_handler_t handler);

KTH_EXPORT
error_code_t chain_get_last_height(chain_t chain, uint64_t* /*size_t*/ out_height);

KTH_EXPORT
void chain_fetch_block_height(chain_t chain, void* ctx, hash_t hash, block_height_fetch_handler_t handler);

KTH_EXPORT
error_code_t chain_get_block_height(chain_t chain, hash_t hash, uint64_t* /*size_t*/ out_height);


// Block Header ---------------------------------------------------------------------
KTH_EXPORT
void chain_fetch_block_header_by_height(chain_t chain, void* ctx, uint64_t /*size_t*/ height, block_header_fetch_handler_t handler);

KTH_EXPORT
error_code_t chain_get_block_header_by_height(chain_t chain, uint64_t /*size_t*/ height, header_t* out_header, uint64_t* /*size_t*/ out_height);

KTH_EXPORT
void chain_fetch_block_header_by_hash(chain_t chain, void* ctx, hash_t hash, block_header_fetch_handler_t handler);

KTH_EXPORT
error_code_t chain_get_block_header_by_hash(chain_t chain, hash_t hash, header_t* out_header, uint64_t* /*size_t*/ out_height);


#if defined(KTH_DB_LEGACY) || defined(KTH_DB_NEW_BLOCKS) || defined(KTH_DB_NEW_FULL)
// Block ---------------------------------------------------------------------
KTH_EXPORT
void chain_fetch_block_by_height(chain_t chain, void* ctx, uint64_t /*size_t*/ height, block_fetch_handler_t handler);

KTH_EXPORT
error_code_t chain_get_block_by_height(chain_t chain, uint64_t /*size_t*/ height, block_t* out_block, uint64_t* /*size_t*/ out_height);

KTH_EXPORT
void chain_fetch_block_by_height_timestamp(chain_t chain, void* ctx, uint64_t /*size_t*/ height, block_hash_timestamp_fetch_handler_t handler);

KTH_EXPORT
error_code_t chain_get_block_by_height_timestamp(chain_t chain, uint64_t /*size_t*/ height, hash_t* out_hash, uint32_t* out_timestamp);

KTH_EXPORT
void chain_fetch_block_by_hash(chain_t chain, void* ctx, hash_t hash, block_fetch_handler_t handler);

KTH_EXPORT
error_code_t chain_get_block_by_hash(chain_t chain, hash_t hash, block_t* out_block, uint64_t* /*size_t*/ out_height);

KTH_EXPORT
void chain_fetch_block_header_by_hash_txs_size(chain_t chain, void* ctx, hash_t hash, block_header_txs_size_fetch_handler_t handler);

KTH_EXPORT
error_code_t chain_get_block_header_by_hash_txs_size(chain_t chain, hash_t hash, header_t* out_header, uint64_t* out_block_height, hash_list_t* out_tx_hashes, uint64_t* out_serialized_size);

KTH_EXPORT
error_code_t chain_get_block_hash(chain_t chain, uint64_t height, hash_t* out_hash);

// Merkle Block ---------------------------------------------------------------------
KTH_EXPORT
void chain_fetch_merkle_block_by_height(chain_t chain, void* ctx, uint64_t /*size_t*/ height, merkle_block_fetch_handler_t handler);

KTH_EXPORT
error_code_t chain_get_merkle_block_by_height(chain_t chain, uint64_t /*size_t*/ height, merkle_block_t* out_block, uint64_t* /*size_t*/ out_height);

KTH_EXPORT
void chain_fetch_merkle_block_by_hash(chain_t chain, void* ctx, hash_t hash, merkle_block_fetch_handler_t handler);

KTH_EXPORT
error_code_t chain_get_merkle_block_by_hash(chain_t chain, hash_t hash, merkle_block_t* out_block, uint64_t* /*size_t*/ out_height);

// Compact Block ---------------------------------------------------------------------
KTH_EXPORT
void chain_fetch_compact_block_by_height(chain_t chain, void* ctx, uint64_t /*size_t*/ height, compact_block_fetch_handler_t handler);

KTH_EXPORT
error_code_t chain_get_compact_block_by_height(chain_t chain, uint64_t /*size_t*/ height, compact_block_t* out_block, uint64_t* /*size_t*/ out_height);

KTH_EXPORT
void chain_fetch_compact_block_by_hash(chain_t chain, void* ctx, hash_t hash, compact_block_fetch_handler_t handler);

KTH_EXPORT
error_code_t chain_get_compact_block_by_hash(chain_t chain, hash_t hash, compact_block_t* out_block, uint64_t* /*size_t*/ out_height);


#endif // defined(KTH_DB_LEGACY) || KTH_DB_NEW_BLOCKS || defined(KTH_DB_NEW_FULL)


#if defined(KTH_DB_LEGACY) || defined(KTH_DB_NEW_FULL) 

// Transaction ---------------------------------------------------------------------
KTH_EXPORT
void chain_fetch_transaction(chain_t chain, void* ctx, hash_t hash, int require_confirmed, transaction_fetch_handler_t handler);

KTH_EXPORT
error_code_t chain_get_transaction(chain_t chain, hash_t hash, int require_confirmed, transaction_t* out_transaction, uint64_t* /*size_t*/ out_height, uint64_t* /*size_t*/ out_index);

KTH_EXPORT
void chain_fetch_transaction_position(chain_t chain, void* ctx, hash_t hash, int require_confirmed, transaction_index_fetch_handler_t handler);

KTH_EXPORT
error_code_t chain_get_transaction_position(chain_t chain, hash_t hash, int require_confirmed, uint64_t* /*size_t*/ out_position, uint64_t* /*size_t*/ out_height);

#endif //KTH_DB_LEGACY || defined(KTH_DB_NEW_FULL)


#if (defined(KTH_DB_LEGACY) && defined(KTH_DB_SPENDS)) || defined(KTH_DB_NEW_FULL) 
// Spend ---------------------------------------------------------------------
KTH_EXPORT
void chain_fetch_spend(chain_t chain, void* ctx, output_point_t op, spend_fetch_handler_t handler);

KTH_EXPORT
error_code_t chain_get_spend(chain_t chain, output_point_t op, input_point_t* out_input_point);
#endif //defined(KTH_DB_LEGACY) && defined(KTH_DB_SPENDS) || defined(KTH_DB_NEW_FULL)

#if (defined(KTH_DB_LEGACY) && defined(KTH_DB_HISTORY)) || defined(KTH_DB_NEW_FULL) 
// History ---------------------------------------------------------------------
KTH_EXPORT
void chain_fetch_history(chain_t chain, void* ctx, payment_address_t address, uint64_t /*size_t*/ limit, uint64_t /*size_t*/ from_height, history_fetch_handler_t handler);

KTH_EXPORT
error_code_t chain_get_history(chain_t chain, payment_address_t address, uint64_t /*size_t*/ limit, uint64_t /*size_t*/ from_height, history_compact_list_t* out_history);
#endif // defined(KTH_DB_LEGACY) && defined(KTH_DB_HISTORY) || defined(KTH_DB_NEW_FULL)


#if defined(KTH_DB_TRANSACTION_UNCONFIRMED) || defined(KTH_DB_NEW_FULL)
KTH_EXPORT
void chain_fetch_confirmed_transactions(chain_t chain, void* ctx, payment_address_t address, uint64_t max, uint64_t start_height, transactions_by_addres_fetch_handler_t handler);

KTH_EXPORT
error_code_t chain_get_confirmed_transactions(chain_t chain, payment_address_t address, uint64_t max, uint64_t start_height, hash_list_t* out_tx_hashes);
#endif // defined(KTH_DB_TRANSACTION_UNCONFIRMED) || defined(KTH_DB_NEW_FULL)

#if defined(KTH_DB_STEALTH)
// Stealth ---------------------------------------------------------------------
KTH_EXPORT
void chain_fetch_stealth(chain_t chain, void* ctx, binary_t filter, uint64_t from_height, stealth_fetch_handler_t handler);

KTH_EXPORT
error_code_t chain_get_stealth(chain_t chain, binary_t filter, uint64_t from_height, stealth_compact_list_t* out_list);
#endif // defined(KTH_DB_STEALTH)

//KTH_EXPORT
//void chain_fetch_stealth(const binary& filter, uint64_t /*size_t*/ from_height, stealth_fetch_handler handler);

// KTH_EXPORT
// void chain_fetch_block_locator(chain_t chain, void* ctx, block_indexes_t heights, block_locator_fetch_handler_t handler);

// KTH_EXPORT
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

#if defined(KTH_DB_TRANSACTION_UNCONFIRMED) || defined(KTH_DB_NEW_FULL)
KTH_EXPORT
mempool_transaction_list_t chain_get_mempool_transactions(chain_t chain, payment_address_t address, bool_t use_testnet_rules);
#endif // defined(KTH_DB_TRANSACTION_UNCONFIRMED) || defined(KTH_DB_NEW_FULL)

KTH_EXPORT
transaction_list_t chain_get_mempool_transactions_from_wallets(chain_t chain, payment_address_list_t addresses, bool_t use_testnet_rules);

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


KTH_EXPORT
void chain_subscribe_blockchain(executor_t exec, chain_t chain, void* ctx, subscribe_blockchain_handler_t handler);

KTH_EXPORT
void chain_subscribe_transaction(executor_t exec, chain_t chain, void* ctx, subscribe_transaction_handler_t handler);

KTH_EXPORT
void chain_unsubscribe(chain_t chain);
    
// Organizers.
//-------------------------------------------------------------------------

KTH_EXPORT
void chain_organize_block(chain_t chain, void* ctx, block_t block, result_handler_t handler);

KTH_EXPORT
int chain_organize_block_sync(chain_t chain, block_t block);

KTH_EXPORT
void chain_organize_transaction(chain_t chain, void* ctx, transaction_t transaction, result_handler_t handler);

KTH_EXPORT
int chain_organize_transaction_sync(chain_t chain, transaction_t transaction);


// Validation.
//-------------------------------------------------------------------------

KTH_EXPORT
void chain_validate_tx(chain_t chain, void* ctx, transaction_t tx, validate_tx_handler_t handler);

KTH_EXPORT
void chain_transaction_validate(chain_t chain, void* ctx, transaction_t tx, validate_tx_handler_t handler);

KTH_EXPORT
void chain_transaction_validate_sequential(chain_t chain, void* ctx, transaction_t tx, validate_tx_handler_t handler);
 

// Queries.
//-------------------------------------------------------------------------

KTH_EXPORT
bool_t chain_is_stale(chain_t chain);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* KTH_NODECINT_CHAIN_CHAIN_H_ */
