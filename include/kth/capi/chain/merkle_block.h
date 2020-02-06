// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#ifndef KTH_NODECINT_CHAIN_MERKLE_BLOCK_H_
#define KTH_NODECINT_CHAIN_MERKLE_BLOCK_H_

#include <stdint.h>

#include <kth/capi/primitives.h>
#include <kth/capi/visibility.h>

#ifdef __cplusplus
extern "C" {
#endif

KTH_EXPORT
hash_t chain_merkle_block_hash_nth(merkle_block_t block, uint64_t /*size_t*/ n);

KTH_EXPORT
void chain_merkle_block_hash_nth_out(merkle_block_t block, uint64_t /*size_t*/ n, hash_t* out_hash);

KTH_EXPORT
header_t chain_merkle_block_header(merkle_block_t block);

KTH_EXPORT
bool_t chain_merkle_block_is_valid(merkle_block_t block);

KTH_EXPORT
uint64_t /*size_t*/ chain_merkle_block_hash_count(merkle_block_t block);

KTH_EXPORT
uint64_t /*size_t*/ chain_merkle_block_serialized_size(merkle_block_t block, uint32_t version);

KTH_EXPORT
uint64_t /*size_t*/ chain_merkle_block_total_transaction_count(merkle_block_t block);

KTH_EXPORT
void chain_merkle_block_destruct(merkle_block_t block);

KTH_EXPORT
void chain_merkle_block_reset(merkle_block_t block);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* KTH_NODECINT_CHAIN_MERKLE_BLOCK_H_ */
