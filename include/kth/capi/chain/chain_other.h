// Copyright (c) 2016-2023 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_CAPI_CHAIN_CHAIN_OTHER_H_
#define KTH_CAPI_CHAIN_CHAIN_OTHER_H_

#include <stdint.h>

#include <kth/capi/primitives.h>
#include <kth/capi/visibility.h>

#ifdef __cplusplus
extern "C" {
#endif

KTH_EXPORT
void kth_chain_subscribe_blockchain(kth_node_t exec, kth_chain_t chain, void* ctx, kth_subscribe_blockchain_handler_t handler);

KTH_EXPORT
void kth_chain_subscribe_transaction(kth_node_t exec, kth_chain_t chain, void* ctx, kth_subscribe_transaction_handler_t handler);

KTH_EXPORT
void kth_chain_subscribe_ds_proof(kth_node_t exec, kth_chain_t chain, void* ctx, kth_subscribe_ds_proof_handler_t handler);

KTH_EXPORT
void kth_chain_unsubscribe(kth_chain_t chain);

// Validation.
//-------------------------------------------------------------------------

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

#endif /* KTH_CAPI_CHAIN_CHAIN_OTHER_H_ */














//void kth_chain_fetch_stealth(const binary& filter, kth_size_t from_height, stealth_fetch_handler handler);

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

