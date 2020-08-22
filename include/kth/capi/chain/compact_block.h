// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_CAPI_CHAIN_COMPACT_BLOCK_H_
#define KTH_CAPI_CHAIN_COMPACT_BLOCK_H_

#include <stdint.h>

#include <kth/capi/primitives.h>
#include <kth/capi/visibility.h>

#ifdef __cplusplus
extern "C" {
#endif

// TODO(fernando): check how to map compact_block::short_ids()

KTH_EXPORT
header_t kth_chain_compact_block_header(compact_kth_block_t block);

KTH_EXPORT
bool_t kth_chain_compact_block_is_valid(compact_kth_block_t block);

KTH_EXPORT
uint64_t /*size_t*/ kth_chain_compact_block_serialized_size(compact_kth_block_t block, uint32_t version);

KTH_EXPORT
uint64_t /*size_t*/ kth_chain_compact_kth_block_transaction_count(compact_kth_block_t block);

KTH_EXPORT
kth_transaction_t kth_chain_compact_kth_block_transaction_nth(compact_kth_block_t block, uint64_t /*size_t*/ n);

KTH_EXPORT
uint64_t kth_chain_compact_block_nonce(compact_kth_block_t block);

KTH_EXPORT
void kth_chain_compact_block_destruct(compact_kth_block_t block);

KTH_EXPORT
void kth_chain_compact_block_reset(compact_kth_block_t block);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* KTH_CAPI_CHAIN_COMPACT_BLOCK_H_ */
