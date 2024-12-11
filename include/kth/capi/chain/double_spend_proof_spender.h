// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_CAPI_CHAIN_DOUBLE_SPEND_PROOF_SPENDER_H_
#define KTH_CAPI_CHAIN_DOUBLE_SPEND_PROOF_SPENDER_H_

#include <stdint.h>

#include <kth/capi/primitives.h>
#include <kth/capi/visibility.h>

#ifdef __cplusplus
extern "C" {
#endif

KTH_EXPORT
uint32_t kth_chain_double_spend_proof_spender_version(kth_double_spend_proof_spender_const_t spender);

KTH_EXPORT
uint32_t kth_chain_double_spend_proof_spender_out_sequence(kth_double_spend_proof_spender_const_t spender);

KTH_EXPORT
uint32_t kth_chain_double_spend_proof_spender_locktime(kth_double_spend_proof_spender_const_t spender);

KTH_EXPORT
kth_hash_t kth_chain_double_spend_proof_spender_prev_outs_hash(kth_double_spend_proof_spender_const_t spender);

KTH_EXPORT
void kth_chain_double_spend_proof_spender_prev_outs_hash_out(kth_double_spend_proof_spender_const_t dsp, kth_hash_t* out_hash);

KTH_EXPORT
kth_hash_t kth_chain_double_spend_proof_spender_sequence_hash(kth_double_spend_proof_spender_const_t spender);

KTH_EXPORT
void kth_chain_double_spend_proof_spender_sequence_hash_out(kth_double_spend_proof_spender_const_t dsp, kth_hash_t* out_hash);

KTH_EXPORT
kth_hash_t kth_chain_double_spend_proof_spender_outputs_hash(kth_double_spend_proof_spender_const_t spender);

KTH_EXPORT
void kth_chain_double_spend_proof_spender_outputs_hash_out(kth_double_spend_proof_spender_const_t dsp, kth_hash_t* out_hash);

KTH_EXPORT
uint8_t const* kth_chain_double_spend_proof_spender_push_data(kth_double_spend_proof_spender_const_t spender, kth_size_t* out_size);

KTH_EXPORT
kth_bool_t kth_chain_double_spend_proof_spender_is_valid(kth_double_spend_proof_spender_const_t spender);

KTH_EXPORT
kth_size_t kth_chain_double_spend_proof_spender_serialized_size(kth_double_spend_proof_spender_const_t spender);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* KTH_CAPI_CHAIN_DOUBLE_SPEND_PROOF_SPENDER_H_ */
