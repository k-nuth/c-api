// Copyright (c) 2016-2020 Knuth Project developers.
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
get_headers_t chain_get_headers_construct_default(void);

KTH_EXPORT
get_headers_t chain_get_headers_construct(hash_list_t start, hash_t stop);

KTH_EXPORT
void chain_get_headers_destruct(get_headers_t get_b);

KTH_EXPORT
hash_list_t chain_get_headers_start_hashes(get_headers_t get_b);

KTH_EXPORT
void chain_get_headers_set_start_hashes(get_headers_t get_b, hash_list_t value);

KTH_EXPORT
hash_t chain_get_headers_stop_hash(get_headers_t get_b);

KTH_EXPORT
void chain_get_headers_stop_hash_out(get_headers_t get_b, hash_t* out_stop_hash);

KTH_EXPORT
void chain_get_headers_set_stop_hash(get_headers_t get_b, hash_t value);

KTH_EXPORT
bool_t chain_get_headers_is_valid(get_headers_t get_b);

KTH_EXPORT
void chain_get_headers_reset(get_headers_t get_b);

KTH_EXPORT
uint64_t /*size_t*/ chain_get_headers_serialized_size(get_headers_t get_b, uint32_t version);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* KTH_CAPI_CHAIN_GET_HEADERS_H_ */
