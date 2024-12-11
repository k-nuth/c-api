// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_CAPI_CHAIN_CHAIN_SYNC_H_
#define KTH_CAPI_CHAIN_CHAIN_SYNC_H_

#include <stdint.h>

#include <kth/capi/primitives.h>
#include <kth/capi/visibility.h>

#ifdef __cplusplus
extern "C" {
#endif

KTH_EXPORT
kth_error_code_t kth_chain_sync_last_height(kth_chain_t chain, kth_size_t* out_height);

KTH_EXPORT
kth_error_code_t kth_chain_sync_block_height(kth_chain_t chain, kth_hash_t hash, kth_size_t* out_height);


// Block Header ---------------------------------------------------------------------
KTH_EXPORT
kth_error_code_t kth_chain_sync_block_header_by_height(kth_chain_t chain, kth_size_t height, kth_header_t* out_header, kth_size_t* out_height);

KTH_EXPORT
kth_error_code_t kth_chain_sync_block_header_by_hash(kth_chain_t chain, kth_hash_t hash, kth_header_t* out_header, kth_size_t* out_height);

// Block ---------------------------------------------------------------------
KTH_EXPORT
kth_error_code_t kth_chain_sync_block_by_height(kth_chain_t chain, kth_size_t height, kth_block_t* out_block, kth_size_t* out_height);

KTH_EXPORT
kth_error_code_t kth_chain_sync_block_by_height_timestamp(kth_chain_t chain, kth_size_t height, kth_hash_t* out_hash, uint32_t* out_timestamp);

KTH_EXPORT
kth_error_code_t kth_chain_sync_block_by_hash(kth_chain_t chain, kth_hash_t hash, kth_block_t* out_block, kth_size_t* out_height);

KTH_EXPORT
kth_error_code_t kth_chain_sync_block_header_byhash_txs_size(kth_chain_t chain, kth_hash_t hash, kth_header_t* out_header, uint64_t* out_block_height, kth_hash_list_t* out_tx_hashes, uint64_t* out_serialized_size);

KTH_EXPORT
kth_error_code_t kth_chain_sync_block_hash(kth_chain_t chain, kth_size_t height, kth_hash_t* out_hash);

// Merkle Block ---------------------------------------------------------------------
KTH_EXPORT
kth_error_code_t kth_chain_sync_merkle_block_by_height(kth_chain_t chain, kth_size_t height, kth_merkleblock_t* out_block, kth_size_t* out_height);

KTH_EXPORT
kth_error_code_t kth_chain_sync_merkle_block_by_hash(kth_chain_t chain, kth_hash_t hash, kth_merkleblock_t* out_block, kth_size_t* out_height);

// Compact Block ---------------------------------------------------------------------
KTH_EXPORT
kth_error_code_t kth_chain_sync_compact_block_by_height(kth_chain_t chain, kth_size_t height, kth_compact_block_t* out_block, kth_size_t* out_height);

KTH_EXPORT
kth_error_code_t kth_chain_sync_compact_block_by_hash(kth_chain_t chain, kth_hash_t hash, kth_compact_block_t* out_block, kth_size_t* out_height);

// Transaction ---------------------------------------------------------------------
KTH_EXPORT
kth_error_code_t kth_chain_sync_transaction(kth_chain_t chain, kth_hash_t hash, int require_confirmed, kth_transaction_t* out_transaction, kth_size_t* out_height, kth_size_t* out_index);

KTH_EXPORT
kth_error_code_t kth_chain_sync_transaction_position(kth_chain_t chain, kth_hash_t hash, int require_confirmed, kth_size_t* out_position, kth_size_t* out_height);


// Spend ---------------------------------------------------------------------
KTH_EXPORT
kth_error_code_t kth_chain_sync_spend(kth_chain_t chain, kth_outputpoint_t op, kth_inputpoint_t* out_input_point);

// History ---------------------------------------------------------------------
KTH_EXPORT
kth_error_code_t kth_chain_sync_history(kth_chain_t chain, kth_payment_address_t address, kth_size_t limit, kth_size_t from_height, kth_history_compact_list_t* out_history);

KTH_EXPORT
kth_error_code_t kth_chain_sync_confirmed_transactions(kth_chain_t chain, kth_payment_address_t address, uint64_t max, uint64_t start_height, kth_hash_list_t* out_tx_hashes);

// // Stealth ---------------------------------------------------------------------
// KTH_EXPORT
// kth_error_code_t kth_chain_sync_stealth(kth_chain_t chain, kth_binary_t filter, uint64_t from_height, kth_stealth_compact_list_t* out_list);

KTH_EXPORT
kth_mempool_transaction_list_t kth_chain_sync_mempool_transactions(kth_chain_t chain, kth_payment_address_t address, kth_bool_t use_testnet_rules);

KTH_EXPORT
kth_transaction_list_t kth_chain_sync_mempool_transactions_from_wallets(kth_chain_t chain, kth_payment_address_list_t addresses, kth_bool_t use_testnet_rules);

// Organizers.
//-------------------------------------------------------------------------
KTH_EXPORT
int kth_chain_sync_organize_block(kth_chain_t chain, kth_block_t block);

KTH_EXPORT
int kth_chain_sync_organize_transaction(kth_chain_t chain, kth_transaction_t transaction);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* KTH_CAPI_CHAIN_CHAIN_SYNC_H_ */
