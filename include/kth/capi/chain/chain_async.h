// Copyright (c) 2016-2023 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_CAPI_CHAIN_CHAIN_ASYNC_H_
#define KTH_CAPI_CHAIN_CHAIN_ASYNC_H_

#include <stdint.h>

#include <kth/capi/primitives.h>
#include <kth/capi/visibility.h>

#ifdef __cplusplus
extern "C" {
#endif

KTH_EXPORT
void kth_chain_async_last_height(kth_chain_t chain, void* ctx, kth_last_height_fetch_handler_t handler);

KTH_EXPORT
void kth_chain_async_block_height(kth_chain_t chain, void* ctx, kth_hash_t hash, kth_block_height_fetch_handler_t handler);

// Block Header ---------------------------------------------------------------------
KTH_EXPORT
void kth_chain_async_block_header_by_height(kth_chain_t chain, void* ctx, kth_size_t height, kth_block_header_fetch_handler_t handler);

KTH_EXPORT
void kth_chain_async_block_header_by_hash(kth_chain_t chain, void* ctx, kth_hash_t hash, kth_block_header_fetch_handler_t handler);

// Block ---------------------------------------------------------------------
KTH_EXPORT
void kth_chain_async_block_by_height(kth_chain_t chain, void* ctx, kth_size_t height, kth_block_fetch_handler_t handler);

KTH_EXPORT
void kth_chain_async_block_by_height_timestamp(kth_chain_t chain, void* ctx, kth_size_t height, kth_blockhash_timestamp_fetch_handler_t handler);

KTH_EXPORT
void kth_chain_async_block_by_hash(kth_chain_t chain, void* ctx, kth_hash_t hash, kth_block_fetch_handler_t handler);

KTH_EXPORT
void kth_chain_async_block_header_by_hash_txs_size(kth_chain_t chain, void* ctx, kth_hash_t hash, kth_block_header_txs_size_fetch_handler_t handler);

// Merkle Block ---------------------------------------------------------------------
KTH_EXPORT
void kth_chain_async_merkle_block_by_height(kth_chain_t chain, void* ctx, kth_size_t height, kth_merkleblock_fetch_handler_t handler);

KTH_EXPORT
void kth_chain_async_merkle_block_by_hash(kth_chain_t chain, void* ctx, kth_hash_t hash, kth_merkleblock_fetch_handler_t handler);

// Compact Block ---------------------------------------------------------------------
KTH_EXPORT
void kth_chain_async_compact_block_by_height(kth_chain_t chain, void* ctx, kth_size_t height, kth_compact_block_fetch_handler_t handler);

KTH_EXPORT
void kth_chain_async_compact_block_by_hash(kth_chain_t chain, void* ctx, kth_hash_t hash, kth_compact_block_fetch_handler_t handler);



// Transaction ---------------------------------------------------------------------
KTH_EXPORT
void kth_chain_async_transaction(kth_chain_t chain, void* ctx, kth_hash_t hash, int require_confirmed, kth_transaction_fetch_handler_t handler);

KTH_EXPORT
void kth_chain_async_transaction_position(kth_chain_t chain, void* ctx, kth_hash_t hash, int require_confirmed, kth_transaction_index_fetch_handler_t handler);


KTH_EXPORT
void kth_chain_async_spend(kth_chain_t chain, void* ctx, kth_outputpoint_t op, kth_spend_fetch_handler_t handler);

KTH_EXPORT
void kth_chain_async_history(kth_chain_t chain, void* ctx, kth_payment_address_t address, kth_size_t limit, kth_size_t from_height, kth_history_fetch_handler_t handler);

KTH_EXPORT
void kth_chain_async_confirmed_transactions(kth_chain_t chain, void* ctx, kth_payment_address_t address, uint64_t max, uint64_t start_height, kth_transactions_by_address_fetch_handler_t handler);

// KTH_EXPORT
// void kth_chain_async_stealth(kth_chain_t chain, void* ctx, kth_binary_t filter, uint64_t from_height, kth_stealth_fetch_handler_t handler);

// Organizers.
//-------------------------------------------------------------------------

KTH_EXPORT
void kth_chain_async_organize_block(kth_chain_t chain, void* ctx, kth_block_t block, kth_result_handler_t handler);

KTH_EXPORT
void kth_chain_async_organize_transaction(kth_chain_t chain, void* ctx, kth_transaction_t transaction, kth_result_handler_t handler);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* KTH_CAPI_CHAIN_CHAIN_ASYNC_H_ */
