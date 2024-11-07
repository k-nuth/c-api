// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/domain/message/double_spend_proof.hpp>

#include <kth/capi/chain/double_spend_proof.h>
#include <kth/capi/conversions.hpp>
#include <kth/capi/helpers.hpp>
#include <kth/capi/type_conversions.h>

KTH_CONV_DEFINE(chain, kth_double_spend_proof_t, kth::domain::message::double_spend_proof, double_spend_proof)

// ---------------------------------------------------------------------------
extern "C" {

kth_outputpoint_const_t kth_chain_double_spend_proof_out_point(kth_double_spend_proof_t dsp) {
    return &kth_chain_double_spend_proof_cpp(dsp).out_point();
}

kth_double_spend_proof_spender_const_t kth_chain_double_spend_proof_spender1(kth_double_spend_proof_t dsp) {
    return &kth_chain_double_spend_proof_cpp(dsp).spender1();
}

kth_double_spend_proof_spender_const_t kth_chain_double_spend_proof_spender2(kth_double_spend_proof_t dsp) {
    return &kth_chain_double_spend_proof_cpp(dsp).spender2();
}

kth_hash_t kth_chain_double_spend_proof_hash(kth_double_spend_proof_t dsp) {
    auto const& hash_cpp = kth_chain_double_spend_proof_const_cpp(dsp).hash();
    return kth::to_hash_t(hash_cpp);
}

void kth_chain_double_spend_proof_hash_out(kth_double_spend_proof_t dsp, kth_hash_t* out_hash) {
    auto const& hash_cpp = kth_chain_double_spend_proof_const_cpp(dsp).hash();
    kth::copy_c_hash(hash_cpp, out_hash);
}

kth_bool_t kth_chain_double_spend_proof_is_valid(kth_double_spend_proof_t dsp) {
    return kth::bool_to_int(kth_chain_double_spend_proof_const_cpp(dsp).is_valid());
}

kth_size_t kth_chain_double_spend_proof_serialized_size(kth_double_spend_proof_t dsp, uint32_t version) {
    return kth_chain_double_spend_proof_const_cpp(dsp).serialized_size(version);
}

void kth_chain_double_spend_proof_destruct(kth_double_spend_proof_t dsp) {
    delete &kth_chain_double_spend_proof_cpp(dsp);
}

void kth_chain_double_spend_proof_reset(kth_double_spend_proof_t dsp) {
    kth_chain_double_spend_proof_cpp(dsp).reset();
}

} // extern "C"
