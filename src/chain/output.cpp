// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/capi/chain/output.h>

#include <kth/capi/chain/script.h>
#include <kth/capi/conversions.hpp>
#include <kth/capi/helpers.hpp>

KTH_CONV_DEFINE(chain, output_t, kth::domain::chain::output, output)

// ---------------------------------------------------------------------------
extern "C" {

output_t kth_chain_output_construct_default() {
    return new kth::domain::chain::output();
}

output_t kth_chain_output_construct(uint64_t value, script_t script) {
    return new kth::domain::chain::output(value, kth_chain_script_const_cpp(script));
}

void kth_chain_output_destruct(output_t output) {
    delete &chain_output_cpp(output);
}

int kth_chain_output_is_valid(output_t output) {
    return kth::bool_to_int(chain_output_const_cpp(output).is_valid());
}

uint64_t /*size_t*/ kth_chain_output_serialized_size(output_t output, bool_t wire /* = true */) {
    return kth_chain_output_const_cpp(output).serialized_size(kth::int_to_bool(wire));
}

uint64_t kth_chain_output_value(output_t output) {
    return kth_chain_output_const_cpp(output).value();
}

uint64_t /*size_t*/ kth_chain_output_signature_operations(output_t output) {
#if defined(KTH_CURRENCY_BCH)
    bool_t bip141_active = 0;
#else
    bool_t bip141_active = 1;
#endif   
    return kth_chain_output_const_cpp(output).signature_operations(kth::int_to_bool(bip141_active));
}

script_t kth_chain_output_script(output_t output) {
    return &(chain_output_cpp(output).script());
}

kth_payment_address_t kth_chain_output_payment_address(output_t output, bool_t use_testnet_rules) {
    auto payment_address = kth_chain_output_cpp(output).address(kth::int_to_bool(use_testnet_rules));
    return new kth::domain::wallet::payment_address(payment_address);
}

uint8_t* kth_chain_output_to_data(output_t output, bool_t wire, uint64_t* /*size_t*/ out_size) {
    auto output_data = kth_chain_output_const_cpp(output).to_data(kth::int_to_bool(wire));
    return kth::create_c_array(output_data, *out_size);
}

} // extern "C"
