// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/capi/chain/input.h>

#include <kth/capi/chain/output_point.h>
#include <kth/capi/chain/script.h>
#include <kth/capi/conversions.hpp>
#include <kth/capi/helpers.hpp>


KTH_CONV_DEFINE(chain, kth_input_t, kth::domain::chain::input, input)

// ---------------------------------------------------------------------------
extern "C" {

kth_input_t kth_chain_input_construct_default() {
    return new kth::domain::chain::input();
}

kth_input_t kth_chain_input_construct(kth_outputpoint_t previous_output, kth_script_t script, uint32_t sequence) {
    return new kth::domain::chain::input(kth_chain_output_point_const_cpp(previous_output), kth_chain_script_const_cpp(script), sequence);
}

void kth_chain_input_destruct(kth_input_t input) {
    delete &kth_chain_input_cpp(input);
}

kth_input_t kth_chain_input_factory_from_data(uint8_t* data, kth_size_t n) {
    kth::data_chunk data_cpp(data, std::next(data, n));
    auto input = kth::domain::create_old<kth::domain::chain::input>(data_cpp, true);
    return kth::move_or_copy_and_leak(std::move(input));
}

kth_bool_t kth_chain_input_is_valid(kth_input_t input) {
    return kth::bool_to_int(kth_chain_input_const_cpp(input).is_valid());
}

kth_bool_t kth_chain_input_is_final(kth_input_t input) {
    return kth::bool_to_int(kth_chain_input_const_cpp(input).is_final());
}

kth_size_t kth_chain_input_serialized_size(kth_input_t input, kth_bool_t wire /* = true*/) {
    return kth_chain_input_const_cpp(input).serialized_size(kth::int_to_bool(wire));
}

uint32_t kth_chain_input_sequence(kth_input_t input) {
    return kth_chain_input_const_cpp(input).sequence();
}

kth_size_t kth_chain_input_signature_operations(kth_input_t input, kth_bool_t bip16_active) {
#if defined(KTH_CURRENCY_BCH)
    kth_bool_t bip141_active = 0;
#else
    kth_bool_t bip141_active = 1;
#endif
    return kth_chain_input_const_cpp(input).signature_operations(kth::int_to_bool(bip16_active), kth::int_to_bool(bip141_active));
}

kth_script_t kth_chain_input_script(kth_input_t input) {
    return &(kth_chain_input_cpp(input).script());
}

kth_outputpoint_t kth_chain_input_previous_output(kth_input_t input) {
    return &(kth_chain_input_cpp(input).previous_output());
}

uint8_t const* kth_chain_input_to_data(kth_input_t input, kth_bool_t wire, kth_size_t* out_size) {
    auto input_data = kth_chain_input_const_cpp(input).to_data(kth::int_to_bool(wire));
    return kth::create_c_array(input_data, *out_size);
}

} // extern "C"
