// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/capi/chain/output.h>

#include <kth/capi/chain/script.h>
#include <kth/capi/conversions.hpp>
#include <kth/capi/helpers.hpp>

KTH_CONV_DEFINE(chain, kth_output_t, kth::domain::chain::output, output)

// ---------------------------------------------------------------------------
extern "C" {

kth_output_t kth_chain_output_construct_default() {
    return new kth::domain::chain::output();
}

//kth_output_t kth_chain_output_construct(uint64_t value, kth_script_t script, kth_token_data_t token_data) {
kth_output_t kth_chain_output_construct(uint64_t value, kth_script_t script) {
    // return new kth::domain::chain::output(value, kth_chain_script_const_cpp(script), kth_chain_token_data_const_cpp(token_data));
    return new kth::domain::chain::output(value, kth_chain_script_const_cpp(script), std::nullopt);
}

kth_output_t kth_chain_output_construct_with_token_fungible(uint64_t value, kth_script_t script, kth_hash_t const* token_category, int64_t token_amount) {
    using kth::domain::chain::amount_t;

    auto token_category_cpp = kth::to_array(token_category->hash);

    kth::domain::chain::token_data_t token_data = {
        token_category_cpp,
        kth::domain::chain::fungible{amount_t{token_amount}}
    };

    return new kth::domain::chain::output(
        value,
        kth_chain_script_const_cpp(script),
        std::move(token_data)
    );
}

kth_output_t kth_chain_output_construct_with_token_non_fungible(uint64_t value, kth_script_t script, kth_hash_t const* token_category, kth_token_capability_t capability, uint8_t* commitment_data, kth_size_t commitment_n) {
    auto token_category_cpp = kth::to_array(token_category->hash);
    auto capability_cpp = kth::token_capability_to_cpp(capability);
    kth::data_chunk commitment_cpp(commitment_data, std::next(commitment_data, commitment_n));

    kth::domain::chain::token_data_t token_data = {
        token_category_cpp,
        kth::domain::chain::non_fungible{capability_cpp, std::move(commitment_cpp)}
    };

    return new kth::domain::chain::output(
        value,
        kth_chain_script_const_cpp(script),
        std::move(token_data)
    );
}

kth_output_t kth_chain_output_construct_with_token_both(uint64_t value, kth_script_t script, kth_hash_t const* token_category, int64_t token_amount, kth_token_capability_t capability, uint8_t* commitment_data, kth_size_t commitment_n) {
    using kth::domain::chain::amount_t;

    auto token_category_cpp = kth::to_array(token_category->hash);
    auto capability_cpp = kth::token_capability_to_cpp(capability);
    kth::data_chunk commitment_cpp(commitment_data, std::next(commitment_data, commitment_n));

    kth::domain::chain::token_data_t token_data = {
        token_category_cpp,
        kth::domain::chain::both_kinds{
            kth::domain::chain::fungible{
                amount_t{token_amount}
            },
            kth::domain::chain::non_fungible{
                capability_cpp,
                std::move(commitment_cpp)
            }
        }
    };

    return new kth::domain::chain::output(
        value,
        kth_chain_script_const_cpp(script),
        std::move(token_data)
    );
}

kth_output_t kth_chain_output_construct_with_token_data(uint64_t value, kth_script_t script, kth_token_data_t token_data) {
    return new kth::domain::chain::output(
        value,
        kth_chain_script_const_cpp(script),
        kth_chain_token_data_const_cpp(token_data)
    );
}

void kth_chain_output_destruct(kth_output_t output) {
    delete &kth_chain_output_cpp(output);
}

kth_output_t kth_chain_output_factory_from_data(uint8_t* data, kth_size_t n) {
    kth::data_chunk data_cpp(data, std::next(data, n));
    auto output = kth::domain::create_old<kth::domain::chain::output>(data_cpp);
    return kth::move_or_copy_and_leak(std::move(output));
}

kth_bool_t kth_chain_output_is_valid(kth_output_t output) {
    return kth::bool_to_int(kth_chain_output_const_cpp(output).is_valid());
}

kth_size_t kth_chain_output_serialized_size(kth_output_t output, kth_bool_t wire /* = true */) {
    return kth_chain_output_const_cpp(output).serialized_size(kth::int_to_bool(wire));
}

uint64_t kth_chain_output_value(kth_output_t output) {
    return kth_chain_output_const_cpp(output).value();
}

kth_size_t kth_chain_output_signature_operations(kth_output_t output) {
#if defined(KTH_CURRENCY_BCH)
    kth_bool_t bip141_active = 0;
#else
    kth_bool_t bip141_active = 1;
#endif
    return kth_chain_output_const_cpp(output).signature_operations(kth::int_to_bool(bip141_active));
}

kth_script_t kth_chain_output_script(kth_output_t output) {
    return &(kth_chain_output_cpp(output).script());
}

kth_payment_address_t kth_chain_output_payment_address(kth_output_t output, kth_bool_t use_testnet_rules) {
    auto payment_address = kth_chain_output_cpp(output).address(kth::int_to_bool(use_testnet_rules));
    return new kth::domain::wallet::payment_address(payment_address);
}

uint8_t const* kth_chain_output_to_data(kth_output_t output, kth_bool_t wire, kth_size_t* out_size) {
    auto output_data = kth_chain_output_const_cpp(output).to_data(kth::int_to_bool(wire));
    return kth::create_c_array(output_data, *out_size);
}

// Cash Tokens ---------------------------------------------------------------

kth_bool_t kth_chain_output_has_token_data(kth_output_t output) {
    return kth::bool_to_int(kth_chain_output_const_cpp(output).token_data().has_value());
}

kth_token_data_t kth_chain_output_token_data(kth_output_t output) {
    if ( ! kth_chain_output_cpp(output).token_data().has_value()) {
        return nullptr;
    }
    return &kth_chain_output_cpp(output).token_data().value();
}

} // extern "C"
