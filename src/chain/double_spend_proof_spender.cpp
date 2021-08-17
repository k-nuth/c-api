// Copyright (c) 2016-2021 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/domain/message/double_spend_proof.hpp>

#include <kth/capi/chain/double_spend_proof_spender.h>
#include <kth/capi/conversions.hpp>
#include <kth/capi/helpers.hpp>
#include <kth/capi/type_conversions.h>

KTH_CONV_DEFINE(chain, kth_double_spend_proof_spender_t, kth::domain::message::double_spend_proof::spender, double_spend_proof_spender)

// ---------------------------------------------------------------------------
extern "C" {

uint32_t kth_chain_double_spend_proof_spender_version(kth_double_spend_proof_spender_t dsp) {
    return kth_chain_double_spend_proof_spender_cpp(dsp).version;
}

uint32_t kth_chain_double_spend_proof_spender_out_sequence(kth_double_spend_proof_spender_t dsp) {
    return kth_chain_double_spend_proof_spender_cpp(dsp).out_sequence;
}

uint32_t kth_chain_double_spend_proof_spender_locktime(kth_double_spend_proof_spender_t dsp) {
    return kth_chain_double_spend_proof_spender_cpp(dsp).locktime;
}

kth_hash_t kth_chain_double_spend_proof_spender_prev_outs_hash(kth_double_spend_proof_t dsp) {
    auto const& hash_cpp = kth_chain_double_spend_proof_spender_cpp(dsp).prev_outs_hash;
    return kth::to_hash_t(hash_cpp);
}

kth_hash_t kth_chain_double_spend_proof_spender_sequence_hash(kth_double_spend_proof_t dsp) {
    auto const& hash_cpp = kth_chain_double_spend_proof_spender_cpp(dsp).sequence_hash;
    return kth::to_hash_t(hash_cpp);
}

kth_hash_t kth_chain_double_spend_proof_spender_outputs_hash(kth_double_spend_proof_t dsp) {
    auto const& hash_cpp = kth_chain_double_spend_proof_spender_cpp(dsp).outputs_hash;
    return kth::to_hash_t(hash_cpp);
}

uint8_t const* kth_chain_double_spend_proof_spender_push_data(kth_double_spend_proof_t dsp, kth_size_t* out_size) {
    auto const& data = kth_chain_double_spend_proof_spender_cpp(dsp).push_data;
    return kth::create_c_array(data, *out_size);
}

kth_bool_t kth_chain_double_spend_proof_spender_is_valid(kth_double_spend_proof_spender_t dsp) {
    return kth::bool_to_int(kth_chain_double_spend_proof_spender_const_cpp(dsp).is_valid());
}

kth_size_t kth_chain_double_spend_proof_spender_serialized_size(kth_double_spend_proof_spender_t dsp) {
    return kth_chain_double_spend_proof_spender_const_cpp(dsp).serialized_size();
}

void kth_chain_double_spend_proof_spender_reset(kth_double_spend_proof_spender_t dsp) {
    kth_chain_double_spend_proof_spender_cpp(dsp).reset();
}

} // extern "C"
