// Copyright (c) 2016-2023 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/domain/message/double_spend_proof.hpp>

#include <kth/capi/chain/double_spend_proof_spender.h>
#include <kth/capi/conversions.hpp>
#include <kth/capi/helpers.hpp>
#include <kth/capi/type_conversions.h>

KTH_CONV_DEFINE_JUST_CONST(chain, kth_double_spend_proof_spender_const_t, kth::domain::message::double_spend_proof::spender, double_spend_proof_spender)

// ---------------------------------------------------------------------------
extern "C" {

uint32_t kth_chain_double_spend_proof_spender_version(kth_double_spend_proof_spender_const_t spender) {
    return kth_chain_double_spend_proof_spender_const_cpp(spender).version;
}

uint32_t kth_chain_double_spend_proof_spender_out_sequence(kth_double_spend_proof_spender_const_t spender) {
    return kth_chain_double_spend_proof_spender_const_cpp(spender).out_sequence;
}

uint32_t kth_chain_double_spend_proof_spender_locktime(kth_double_spend_proof_spender_const_t spender) {
    return kth_chain_double_spend_proof_spender_const_cpp(spender).locktime;
}

kth_hash_t kth_chain_double_spend_proof_spender_prev_outs_hash(kth_double_spend_proof_spender_const_t spender) {
    auto const& hash_cpp = kth_chain_double_spend_proof_spender_const_cpp(spender).prev_outs_hash;
    return kth::to_hash_t(hash_cpp);
}

void kth_chain_double_spend_proof_spender_prev_outs_hash_out(kth_double_spend_proof_spender_const_t spender, kth_hash_t* out_hash) {
    auto const& hash_cpp = kth_chain_double_spend_proof_spender_const_cpp(spender).prev_outs_hash;
    kth::copy_c_hash(hash_cpp, out_hash);
}

kth_hash_t kth_chain_double_spend_proof_spender_sequence_hash(kth_double_spend_proof_spender_const_t spender) {
    auto const& hash_cpp = kth_chain_double_spend_proof_spender_const_cpp(spender).sequence_hash;
    return kth::to_hash_t(hash_cpp);
}

void kth_chain_double_spend_proof_spender_sequence_hash_out(kth_double_spend_proof_spender_const_t spender, kth_hash_t* out_hash) {
    auto const& hash_cpp = kth_chain_double_spend_proof_spender_const_cpp(spender).sequence_hash;
    kth::copy_c_hash(hash_cpp, out_hash);
}


kth_hash_t kth_chain_double_spend_proof_spender_outputs_hash(kth_double_spend_proof_spender_const_t spender) {
    auto const& hash_cpp = kth_chain_double_spend_proof_spender_const_cpp(spender).outputs_hash;
    return kth::to_hash_t(hash_cpp);
}

void kth_chain_double_spend_proof_spender_outputs_hash_out(kth_double_spend_proof_spender_const_t spender, kth_hash_t* out_hash) {
    auto const& hash_cpp = kth_chain_double_spend_proof_spender_const_cpp(spender).outputs_hash;
    kth::copy_c_hash(hash_cpp, out_hash);
}


uint8_t const* kth_chain_double_spend_proof_spender_push_data(kth_double_spend_proof_spender_const_t spender, kth_size_t* out_size) {
    auto const& data = kth_chain_double_spend_proof_spender_const_cpp(spender).push_data;
    return kth::create_c_array(data, *out_size);
}

kth_bool_t kth_chain_double_spend_proof_spender_is_valid(kth_double_spend_proof_spender_const_t spender) {
    return kth::bool_to_int(kth_chain_double_spend_proof_spender_const_cpp(spender).is_valid());
}

kth_size_t kth_chain_double_spend_proof_spender_serialized_size(kth_double_spend_proof_spender_const_t spender) {
    return kth_chain_double_spend_proof_spender_const_cpp(spender).serialized_size();
}

} // extern "C"
