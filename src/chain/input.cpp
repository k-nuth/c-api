// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#include <kth/capi/chain/input.h>

#include <kth/capi/chain/output_point.h>
#include <kth/capi/chain/script.h>
#include <kth/capi/conversions.hpp>
#include <kth/capi/helpers.hpp>


KTH_CONV_DEFINE(chain, input_t, kth::domain::chain::input, input)

// ---------------------------------------------------------------------------
extern "C" {

input_t chain_input_construct_default() {
    return new kth::domain::chain::input();
}

input_t chain_input_construct(output_point_t previous_output, script_t script, uint32_t sequence) {
    return new kth::domain::chain::input(chain_output_point_const_cpp(previous_output), chain_script_const_cpp(script), sequence);
}

void chain_input_destruct(input_t input) {
    delete &chain_input_cpp(input);
}

bool_t chain_input_is_valid(input_t input) {
    return kth::bool_to_int(chain_input_const_cpp(input).is_valid());
}

bool_t chain_input_is_final(input_t input) {
    return kth::bool_to_int(chain_input_const_cpp(input).is_final());
}

uint64_t /*size_t*/ chain_input_serialized_size(input_t input, bool_t wire /* = true*/) {
    return chain_input_const_cpp(input).serialized_size(kth::int_to_bool(wire));
}

uint32_t chain_input_sequence(input_t input) {
    return chain_input_const_cpp(input).sequence();
}

uint64_t /*size_t*/ chain_input_signature_operations(input_t input, bool_t bip16_active) {
#ifdef KTH_CURRENCY_BCH
    bool_t bip141_active = 0;
#else
    bool_t bip141_active = 1;
#endif
    return chain_input_const_cpp(input).signature_operations(kth::int_to_bool(bip16_active), kth::int_to_bool(bip141_active));
}

script_t chain_input_script(input_t input) {
    return &(chain_input_cpp(input).script());
}

output_point_t chain_input_previous_output(input_t input) {
    return &(chain_input_cpp(input).previous_output());
}

uint8_t* chain_input_to_data(input_t input, bool_t wire, uint64_t* /*size_t*/ out_size) {
    auto input_data = chain_input_const_cpp(input).to_data(kth::int_to_bool(wire));
    return kth::create_c_array(input_data, *out_size);
}

} // extern "C"
