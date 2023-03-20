// Copyright (c) 2016-2023 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_CAPI_CHAIN_GET_HEADERS_H_
#define KTH_CAPI_CHAIN_GET_HEADERS_H_

#include <stdint.h>

#include <kth/capi/visibility.h>
#include <kth/capi/primitives.h>

#ifdef __cplusplus
extern "C" {
#endif

KTH_EXPORT
kth_get_headers_t kth_chain_get_headers_construct_default(void);

KTH_EXPORT
kth_get_headers_t kth_chain_get_headers_construct(kth_hash_list_t start, kth_hash_t stop);

KTH_EXPORT
void kth_chain_get_headers_destruct(kth_get_headers_t get_b);

KTH_EXPORT
kth_hash_list_t kth_chain_get_headers_start_hashes(kth_get_headers_t get_b);

KTH_EXPORT
void kth_chain_get_headers_set_start_hashes(kth_get_headers_t get_b, kth_hash_list_t value);

KTH_EXPORT
kth_hash_t kth_chain_get_headers_stop_hash(kth_get_headers_t get_b);

KTH_EXPORT
void kth_chain_get_headers_stop_hash_out(kth_get_headers_t get_b, kth_hash_t* out_stop_hash);

KTH_EXPORT
void kth_chain_get_headers_set_stop_hash(kth_get_headers_t get_b, kth_hash_t value);

KTH_EXPORT
kth_bool_t kth_chain_get_headers_is_valid(kth_get_headers_t get_b);

KTH_EXPORT
void kth_chain_get_headers_reset(kth_get_headers_t get_b);

KTH_EXPORT
kth_size_t kth_chain_get_headers_serialized_size(kth_get_headers_t get_b, uint32_t version);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* KTH_CAPI_CHAIN_GET_HEADERS_H_ */
