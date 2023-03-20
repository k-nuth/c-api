// Copyright (c) 2016-2023 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_CAPI_CHAIN_POINT_H_
#define KTH_CAPI_CHAIN_POINT_H_

#include <stdint.h>

#include <kth/capi/primitives.h>
#include <kth/capi/visibility.h>

#ifdef __cplusplus
extern "C" {
#endif

KTH_EXPORT
kth_hash_t kth_chain_point_get_hash(kth_point_t point);

KTH_EXPORT
void kth_chain_point_get_hash_out(kth_point_t point, kth_hash_t* out_hash);

KTH_EXPORT
kth_bool_t kth_chain_point_is_valid(kth_point_t point);

KTH_EXPORT
uint32_t kth_chain_point_get_index(kth_point_t point);

KTH_EXPORT
uint64_t kth_chain_point_get_checksum(kth_point_t point);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* KTH_CAPI_CHAIN_POINT_H_ */
