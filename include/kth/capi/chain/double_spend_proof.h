// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_CAPI_CHAIN_DOUBLE_SPEND_PROOF_H_
#define KTH_CAPI_CHAIN_DOUBLE_SPEND_PROOF_H_

#include <stdint.h>

#include <kth/capi/primitives.h>
#include <kth/capi/visibility.h>

#ifdef __cplusplus
extern "C" {
#endif

KTH_EXPORT
kth_outputpoint_const_t kth_chain_double_spend_proof_out_point(kth_double_spend_proof_t dsp);

KTH_EXPORT
kth_double_spend_proof_spender_const_t kth_chain_double_spend_proof_spender1(kth_double_spend_proof_t dsp);

KTH_EXPORT
kth_double_spend_proof_spender_const_t kth_chain_double_spend_proof_spender2(kth_double_spend_proof_t dsp);

KTH_EXPORT
kth_hash_t kth_chain_double_spend_proof_hash(kth_double_spend_proof_t dsp);

KTH_EXPORT
void kth_chain_double_spend_proof_hash_out(kth_double_spend_proof_t dsp, kth_hash_t* out_hash);

KTH_EXPORT
kth_bool_t kth_chain_double_spend_proof_is_valid(kth_double_spend_proof_t dsp);

KTH_EXPORT
kth_size_t kth_chain_double_spend_proof_serialized_size(kth_double_spend_proof_t dsp, uint32_t version);

KTH_EXPORT
void kth_chain_double_spend_proof_destruct(kth_double_spend_proof_t dsp);

KTH_EXPORT
void kth_chain_double_spend_proof_reset(kth_double_spend_proof_t dsp);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* KTH_CAPI_CHAIN_DOUBLE_SPEND_PROOF_H_ */
