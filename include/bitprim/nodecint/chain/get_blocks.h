// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#ifndef KTH_NODECINT_CHAIN_GET_BLOCKS_H_
#define KTH_NODECINT_CHAIN_GET_BLOCKS_H_

#include <stdint.h>

#include <knuth/nodecint/visibility.h>
#include <knuth/nodecint/primitives.h>

#ifdef __cplusplus
extern "C" {
#endif

KTH_EXPORT
get_blocks_t chain_get_blocks_construct_default(void);

KTH_EXPORT
get_blocks_t chain_get_blocks_construct(hash_list_t start, hash_t stop);

KTH_EXPORT
void chain_get_blocks_destruct(get_blocks_t get_b);

KTH_EXPORT
hash_list_t chain_get_blocks_start_hashes(get_blocks_t get_b);

KTH_EXPORT
void chain_get_blocks_set_start_hashes(get_blocks_t get_b, hash_list_t value);

KTH_EXPORT
hash_t chain_get_blocks_stop_hash(get_blocks_t get_b);

KTH_EXPORT
void chain_get_blocks_stop_hash_out(get_blocks_t get_b, hash_t* out_stop_hash);

KTH_EXPORT
void chain_get_blocks_set_stop_hash(get_blocks_t get_b, hash_t value);

KTH_EXPORT
bool_t chain_get_blocks_is_valid(get_blocks_t get_b);

KTH_EXPORT
void chain_get_blocks_reset(get_blocks_t get_b);

KTH_EXPORT
uint64_t /*size_t*/ chain_get_blocks_serialized_size(get_blocks_t get_b, uint32_t version);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* KTH_NODECINT_CHAIN_GET_BLOCKS_H_ */
