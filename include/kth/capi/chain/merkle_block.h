// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_CAPI_CHAIN_MERKLE_BLOCK_H_
#define KTH_CAPI_CHAIN_MERKLE_BLOCK_H_

#include <stdint.h>

#include <kth/capi/primitives.h>
#include <kth/capi/visibility.h>

#ifdef __cplusplus
extern "C" {
#endif

KTH_EXPORT
kth_hash_t kth_chain_merkle_block_hash_nth(kth_merkleblock_t block, kth_size_t n);

KTH_EXPORT
void kth_chain_merkle_block_hash_nth_out(kth_merkleblock_t block, kth_size_t n, kth_hash_t* out_hash);

KTH_EXPORT
kth_header_t kth_chain_merkle_block_header(kth_merkleblock_t block);

KTH_EXPORT
kth_bool_t kth_chain_merkle_block_is_valid(kth_merkleblock_t block);

KTH_EXPORT
kth_size_t kth_chain_merkle_block_hash_count(kth_merkleblock_t block);

KTH_EXPORT
kth_size_t kth_chain_merkle_block_serialized_size(kth_merkleblock_t block, uint32_t version);

KTH_EXPORT
kth_size_t kth_chain_merkle_block_total_transaction_count(kth_merkleblock_t block);

KTH_EXPORT
void kth_chain_merkle_block_destruct(kth_merkleblock_t block);

KTH_EXPORT
void kth_chain_merkle_block_reset(kth_merkleblock_t block);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* KTH_CAPI_CHAIN_MERKLE_BLOCK_H_ */
