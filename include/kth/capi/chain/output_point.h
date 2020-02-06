// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#ifndef KTH_CAPI_CHAIN_OUTPUT_POINT_H_
#define KTH_CAPI_CHAIN_OUTPUT_POINT_H_

#include <stdint.h>

#include <kth/capi/primitives.h>
#include <kth/capi/visibility.h>

#ifdef __cplusplus
extern "C" {
#endif

KTH_EXPORT
output_point_t chain_output_point_construct(void);

KTH_EXPORT
output_point_t chain_output_point_construct_from_hash_index(hash_t hash, uint32_t index);

KTH_EXPORT
void chain_output_point_destruct(output_point_t op);

KTH_EXPORT
hash_t chain_output_point_get_hash(output_point_t op);

KTH_EXPORT
void chain_output_point_get_hash_out(output_point_t op, hash_t* out_hash);

KTH_EXPORT
uint32_t chain_output_point_get_index(output_point_t op);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* KTH_CAPI_CHAIN_OUTPUT_POINT_H_ */
