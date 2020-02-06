// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#include <kth/capi/chain/output.h>

#include <kth/capi/chain/script.h>
#include <kth/capi/conversions.hpp>
#include <kth/capi/helpers.hpp>

KTH_CONV_DEFINE(chain, output_t, kth::chain::output, output)

// ---------------------------------------------------------------------------
extern "C" {

output_t chain_output_construct_default() {
    return new kth::chain::output();
}

output_t chain_output_construct(uint64_t value, script_t script) {
    return new kth::chain::output(value, chain_script_const_cpp(script));
}

void chain_output_destruct(output_t output) {
    delete &chain_output_cpp(output);
}

int chain_output_is_valid(output_t output) {
    return knuth::bool_to_int(chain_output_const_cpp(output).is_valid());
}

uint64_t /*size_t*/ chain_output_serialized_size(output_t output, bool_t wire /* = true */) {
    return chain_output_const_cpp(output).serialized_size(knuth::int_to_bool(wire));
}

uint64_t chain_output_value(output_t output) {
    return chain_output_const_cpp(output).value();
}

uint64_t /*size_t*/ chain_output_signature_operations(output_t output) {
#ifdef KTH_CURRENCY_BCH
    bool_t bip141_active = 0;
#else
    bool_t bip141_active = 1;
#endif   
    return chain_output_const_cpp(output).signature_operations(knuth::int_to_bool(bip141_active));
}

script_t chain_output_script(output_t output) {
    return &(chain_output_cpp(output).script());
}

payment_address_t chain_output_payment_address(output_t output, bool_t use_testnet_rules) {
    auto payment_address = chain_output_cpp(output).address(knuth::int_to_bool(use_testnet_rules));
    return new kth::wallet::payment_address(payment_address);
}

uint8_t* chain_output_to_data(output_t output, bool_t wire, uint64_t* /*size_t*/ out_size) {
    auto output_data = chain_output_const_cpp(output).to_data(knuth::int_to_bool(wire));
    return knuth::create_c_array(output_data, *out_size);
}

} // extern "C"
