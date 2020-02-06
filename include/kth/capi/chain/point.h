// Copyright (c) 2016-2020 Knuth Project developers.
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
hash_t chain_point_get_hash(point_t point);

KTH_EXPORT
void chain_point_get_hash_out(point_t point, hash_t* out_hash);

KTH_EXPORT
bool_t chain_point_is_valid(point_t point);

KTH_EXPORT
uint32_t chain_point_get_index(point_t point);

KTH_EXPORT
uint64_t chain_point_get_checksum(point_t point);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* KTH_CAPI_CHAIN_POINT_H_ */
