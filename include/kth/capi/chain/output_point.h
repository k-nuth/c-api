// Copyright (c) 2016-2024 Knuth Project developers.
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
kth_outputpoint_t kth_chain_output_point_construct(void);

KTH_EXPORT
kth_outputpoint_t kth_chain_output_point_construct_from_hash_index(kth_hash_t const* hash, uint32_t index);

KTH_EXPORT
void kth_chain_output_point_destruct(kth_outputpoint_t op);

KTH_EXPORT
kth_hash_t kth_chain_output_point_get_hash(kth_outputpoint_t op);

KTH_EXPORT
void kth_chain_output_point_get_hash_out(kth_outputpoint_t op, kth_hash_t* out_hash);

KTH_EXPORT
uint32_t kth_chain_output_point_get_index(kth_outputpoint_t op);

KTH_EXPORT
kth_output_t kth_chain_output_point_get_cached_output(kth_outputpoint_t op);

KTH_EXPORT
void kth_chain_output_point_set_hash(kth_outputpoint_t op, kth_hash_t const* hash);

KTH_EXPORT
void kth_chain_output_point_set_index(kth_outputpoint_t op, uint32_t index);

KTH_EXPORT
void kth_chain_output_point_set_cached_output(kth_outputpoint_t op, kth_output_t output);


#ifdef __cplusplus
} // extern "C"
#endif

#endif /* KTH_CAPI_CHAIN_OUTPUT_POINT_H_ */