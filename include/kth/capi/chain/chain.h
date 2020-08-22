// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_CAPI_CHAIN_CHAIN_H_
#define KTH_CAPI_CHAIN_CHAIN_H_

#include <stdint.h>

#include <kth/capi/primitives.h>
#include <kth/capi/visibility.h>

#ifdef __cplusplus
extern "C" {
#endif

KTH_EXPORT
void kth_chain_fetch_last_height(kth_chain_t chain, void* ctx, kth_last_height_fetch_handler_t handler);

KTH_EXPORT
kth_error_code_t kth_chain_get_last_height(kth_chain_t chain, kth_size_t* out_height);

KTH_EXPORT
void kth_chain_fetch_block_height(kth_chain_t chain, void* ctx, kth_hash_t hash, kth_block_height_fetch_handler_t handler);

KTH_EXPORT
kth_error_code_t kth_chain_get_block_height(kth_chain_t chain, kth_hash_t hash, kth_size_t* out_height);


// Block Header ---------------------------------------------------------------------
KTH_EXPORT
void kth_chain_fetch_block_header_by_height(kth_chain_t chain, void* ctx, kth_size_t height, kth_block_header_fetch_handler_t handler);

KTH_EXPORT
kth_error_code_t kth_chain_get_block_header_by_height(kth_chain_t chain, kth_size_t height, kth_header_t* out_header, kth_size_t* out_height);

KTH_EXPORT
void kth_chain_fetch_block_header_by_hash(kth_chain_t chain, void* ctx, kth_hash_t hash, kth_block_header_fetch_handler_t handler);

KTH_EXPORT
kth_error_code_t kth_chain_get_block_header_by_hash(kth_chain_t chain, kth_hash_t hash, kth_header_t* out_header, kth_size_t* out_height);


#if defined(KTH_DB_LEGACY) || defined(KTH_DB_NEW_BLOCKS) || defined(KTH_DB_NEW_FULL)
// Block ---------------------------------------------------------------------
KTH_EXPORT
void kth_chain_fetch_block_by_height(kth_chain_t chain, void* ctx, kth_size_t height, kth_block_fetch_handler_t handler);

KTH_EXPORT
kth_error_code_t kth_chain_get_block_by_height(kth_chain_t chain, kth_size_t height, kth_block_t* out_block, kth_size_t* out_height);

KTH_EXPORT
void kth_chain_fetch_block_by_height_timestamp(kth_chain_t chain, void* ctx, kth_size_t height, kth_blockhash_timestamp_fetch_handler_t handler);

KTH_EXPORT
kth_error_code_t kth_chain_get_block_by_height_timestamp(kth_chain_t chain, kth_size_t height, kth_hash_t* out_hash, uint32_t* out_timestamp);

KTH_EXPORT
void kth_chain_fetch_block_by_hash(kth_chain_t chain, void* ctx, kth_hash_t hash, kth_block_fetch_handler_t handler);

KTH_EXPORT
kth_error_code_t kth_chain_get_block_by_hash(kth_chain_t chain, kth_hash_t hash, kth_block_t* out_block, kth_size_t* out_height);

KTH_EXPORT
void kth_chain_fetch_block_header_byhash_txs_size(kth_chain_t chain, void* ctx, kth_hash_t hash, kth_block_header_txs_size_fetch_handler_t handler);

KTH_EXPORT
kth_error_code_t kth_chain_get_block_header_byhash_txs_size(kth_chain_t chain, kth_hash_t hash, kth_header_t* out_header, uint64_t* out_block_height, kth_hash_list_t* out_tx_hashes, uint64_t* out_serialized_size);

KTH_EXPORT
kth_error_code_t kth_chain_get_block_hash(kth_chain_t chain, kth_size_t height, kth_hash_t* out_hash);

// Merkle Block ---------------------------------------------------------------------
KTH_EXPORT
void kth_chain_fetch_merkle_block_by_height(kth_chain_t chain, void* ctx, kth_size_t height, kth_merkleblock_fetch_handler_t handler);

KTH_EXPORT
kth_error_code_t kth_chain_get_merkle_block_by_height(kth_chain_t chain, kth_size_t height, kth_merkleblock_t* out_block, kth_size_t* out_height);

KTH_EXPORT
void kth_chain_fetch_merkle_block_by_hash(kth_chain_t chain, void* ctx, kth_hash_t hash, kth_merkleblock_fetch_handler_t handler);

KTH_EXPORT
kth_error_code_t kth_chain_get_merkle_block_by_hash(kth_chain_t chain, kth_hash_t hash, kth_merkleblock_t* out_block, kth_size_t* out_height);

// Compact Block ---------------------------------------------------------------------
KTH_EXPORT
void kth_chain_fetch_compact_block_by_height(kth_chain_t chain, void* ctx, kth_size_t height, kth_compactblock_fetch_handler_t handler);

KTH_EXPORT
kth_error_code_t kth_chain_get_compact_block_by_height(kth_chain_t chain, kth_size_t height, kth_compactblock_t* out_block, kth_size_t* out_height);

KTH_EXPORT
void kth_chain_fetch_compact_block_by_hash(kth_chain_t chain, void* ctx, kth_hash_t hash, kth_compactblock_fetch_handler_t handler);

KTH_EXPORT
kth_error_code_t kth_chain_get_compact_block_by_hash(kth_chain_t chain, kth_hash_t hash, kth_compactblock_t* out_block, kth_size_t* out_height);


#endif // defined(KTH_DB_LEGACY) || KTH_DB_NEW_BLOCKS || defined(KTH_DB_NEW_FULL)


#if defined(KTH_DB_LEGACY) || defined(KTH_DB_NEW_FULL) 

// Transaction ---------------------------------------------------------------------
KTH_EXPORT
void kth_chain_fetch_transaction(kth_chain_t chain, void* ctx, kth_hash_t hash, int require_confirmed, kth_transaction_fetch_handler_t handler);

KTH_EXPORT
kth_error_code_t kth_chain_get_transaction(kth_chain_t chain, kth_hash_t hash, int require_confirmed, kth_transaction_t* out_transaction, kth_size_t* out_height, kth_size_t* out_index);

KTH_EXPORT
void kth_chain_fetch_transaction_position(kth_chain_t chain, void* ctx, kth_hash_t hash, int require_confirmed, kth_transaction_index_fetch_handler_t handler);

KTH_EXPORT
kth_error_code_t kth_chain_get_transaction_position(kth_chain_t chain, kth_hash_t hash, int require_confirmed, kth_size_t* out_position, kth_size_t* out_height);

#endif //KTH_DB_LEGACY || defined(KTH_DB_NEW_FULL)


#if (defined(KTH_DB_LEGACY) && defined(KTH_DB_SPENDS)) || defined(KTH_DB_NEW_FULL) 
// Spend ---------------------------------------------------------------------
KTH_EXPORT
void kth_chain_fetch_spend(kth_chain_t chain, void* ctx, kth_outputpoint_t op, kth_spend_fetch_handler_t handler);

KTH_EXPORT
kth_error_code_t kth_chain_get_spend(kth_chain_t chain, kth_outputpoint_t op, kth_inputpoint_t* out_input_point);
#endif //defined(KTH_DB_LEGACY) && defined(KTH_DB_SPENDS) || defined(KTH_DB_NEW_FULL)

#if (defined(KTH_DB_LEGACY) && defined(KTH_DB_HISTORY)) || defined(KTH_DB_NEW_FULL) 
// History ---------------------------------------------------------------------
KTH_EXPORT
void kth_chain_fetch_history(kth_chain_t chain, void* ctx, kth_payment_address_t address, kth_size_t limit, kth_size_t from_height, kth_history_fetch_handler_t handler);

KTH_EXPORT
kth_error_code_t kth_chain_get_history(kth_chain_t chain, kth_payment_address_t address, kth_size_t limit, kth_size_t from_height, history_compact_list_t* out_history);
#endif // defined(KTH_DB_LEGACY) && defined(KTH_DB_HISTORY) || defined(KTH_DB_NEW_FULL)


#if defined(KTH_DB_TRANSACTION_UNCONFIRMED) || defined(KTH_DB_NEW_FULL)
KTH_EXPORT
void kth_chain_fetch_confirmed_transactions(kth_chain_t chain, void* ctx, kth_payment_address_t address, uint64_t max, uint64_t start_height, kth_transactions_by_addres_fetch_handler_t handler);

KTH_EXPORT
kth_error_code_t kth_chain_get_confirmed_transactions(kth_chain_t chain, kth_payment_address_t address, uint64_t max, uint64_t start_height, kth_hash_list_t* out_tx_hashes);
#endif // defined(KTH_DB_TRANSACTION_UNCONFIRMED) || defined(KTH_DB_NEW_FULL)

#if defined(KTH_DB_STEALTH)
// Stealth ---------------------------------------------------------------------
KTH_EXPORT
void kth_chain_fetch_stealth(kth_chain_t chain, void* ctx, kth_binary_t filter, uint64_t from_height, kth_stealth_fetch_handler_t handler);

KTH_EXPORT
kth_error_code_t kth_chain_get_stealth(kth_chain_t chain, kth_binary_t filter, uint64_t from_height, kth_stealth_compact_list_t* out_list);
#endif // defined(KTH_DB_STEALTH)

//KTH_EXPORT
//void kth_chain_fetch_stealth(const binary& filter, kth_size_t from_height, stealth_fetch_handler handler);

// KTH_EXPORT
// void kth_chain_fetch_block_locator(kth_chain_t chain, void* ctx, kth_block_indexes_t heights, kth_block_locator_fetch_handler_t handler);

// KTH_EXPORT
// kth_error_code_t kth_chain_get_block_locator(kth_chain_t chain, kth_block_indexes_t heights, kth_get_headers_ptr_t* out_headers);


// ------------------------------------------------------------------
//virtual void fetch_block_locator(chain::block::indexes const& heights, block_locator_fetch_handler handler) const = 0;
//virtual void fetch_locator_block_hashes(get_blocks_const_ptr locator, hash_digest const& threshold, size_t limit, inventory_fetch_handler handler) const = 0;
//virtual void fetch_locator_block_headers(get_headers_const_ptr locator, hash_digest const& threshold, size_t limit, locator_block_headers_fetch_handler handler) const = 0;
//
//// Transaction Pool.
////-------------------------------------------------------------------------
//
//virtual void fetch_template(merkle_block_fetch_handler handler) const = 0;
//virtual void fetch_mempool(size_t count_limit, uint64_t minimum_fee, inventory_fetch_handler handler) const = 0;

#if defined(KTH_DB_TRANSACTION_UNCONFIRMED) || defined(KTH_DB_NEW_FULL)
KTH_EXPORT
kth_mempool_transaction_list_t kth_chain_get_mempool_transactions(kth_chain_t chain, kth_payment_address_t address, kth_bool_t use_testnet_rules);
#endif // defined(KTH_DB_TRANSACTION_UNCONFIRMED) || defined(KTH_DB_NEW_FULL)

KTH_EXPORT
kth_transaction_list_t kth_chain_get_mempool_transactions_from_wallets(kth_chain_t chain, kth_payment_address_list_t addresses, kth_bool_t use_testnet_rules);

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
void kth_chain_subscribe_blockchain(kth_node_t exec, kth_chain_t chain, void* ctx, kth_subscribe_blockchain_handler_t handler);

KTH_EXPORT
void kth_chain_subscribe_transaction(kth_node_t exec, kth_chain_t chain, void* ctx, kth_subscribe_transaction_handler_t handler);

KTH_EXPORT
void kth_chain_unsubscribe(kth_chain_t chain);
    
// Organizers.
//-------------------------------------------------------------------------

KTH_EXPORT
void kth_chain_organize_block(kth_chain_t chain, void* ctx, kth_block_t block, kth_result_handler_t handler);

KTH_EXPORT
int kth_chain_organize_block_sync(kth_chain_t chain, kth_block_t block);

KTH_EXPORT
void kth_chain_organize_transaction(kth_chain_t chain, void* ctx, kth_transaction_t transaction, kth_result_handler_t handler);

KTH_EXPORT
int kth_chain_organize_transaction_sync(kth_chain_t chain, kth_transaction_t transaction);


// Validation.
//-------------------------------------------------------------------------

KTH_EXPORT
void kth_chain_validate_tx(kth_chain_t chain, void* ctx, kth_transaction_t tx, kth_validate_tx_handler_t handler);

KTH_EXPORT
void kth_chain_transaction_validate(kth_chain_t chain, void* ctx, kth_transaction_t tx, kth_validate_tx_handler_t handler);

KTH_EXPORT
void kth_chain_transaction_validate_sequential(kth_chain_t chain, void* ctx, kth_transaction_t tx, kth_validate_tx_handler_t handler);
 

// Queries.
//-------------------------------------------------------------------------

KTH_EXPORT
kth_bool_t kth_chain_is_stale(kth_chain_t chain);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* KTH_CAPI_CHAIN_CHAIN_H_ */
