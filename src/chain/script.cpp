// Copyright (c) 2016-2023 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/capi/chain/script.h>

#include <kth/capi/conversions.hpp>
#include <kth/capi/helpers.hpp>

KTH_CONV_DEFINE(chain, kth_script_t, kth::domain::chain::script, script)

// ---------------------------------------------------------------------------
extern "C" {

kth_script_t kth_chain_script_construct_default() {
    return new kth::domain::chain::script();
}

// script::script(const data_chunk& encoded, bool prefix)
kth_script_t kth_chain_script_construct(uint8_t* encoded, kth_size_t n, kth_bool_t prefix) {
    kth::data_chunk encoded_cpp(encoded, std::next(encoded, n));
    return new kth::domain::chain::script(encoded_cpp, kth::int_to_bool(prefix));
}

void kth_chain_script_destruct(kth_script_t script) {
    delete &kth_chain_script_cpp(script);
}

kth_bool_t kth_chain_script_is_valid(kth_script_t script) {
    return kth::bool_to_int(kth_chain_script_const_cpp(script).is_valid());
}

kth_bool_t kth_chain_script_is_valid_operations(kth_script_t script) {
    return kth::bool_to_int(kth_chain_script_const_cpp(script).is_valid_operations());
}

kth_size_t kth_chain_script_satoshi_content_size(kth_script_t script) {
    return kth_chain_script_const_cpp(script).serialized_size(false);
}

kth_size_t kth_chain_script_serialized_size(kth_script_t script, kth_bool_t prefix) {
    return kth_chain_script_const_cpp(script).serialized_size(kth::int_to_bool(prefix));
}

char const* kth_chain_script_to_string(kth_script_t script, uint32_t active_forks) {
    auto str = kth_chain_script_const_cpp(script).to_string(active_forks);
    return kth::create_c_str(str);
}

// TODO(fernando): Move this logic elsewhere (this does not go in a wrapper like c-api)
char const* kth_chain_script_type(kth_script_t script) {
    auto script_pattern = kth_chain_script_const_cpp(script).pattern();
    std::string type = "non_standard";
    switch(script_pattern) {
        case kth::infrastructure::machine::script_pattern::null_data: type = "nulldata"; break;
        case kth::infrastructure::machine::script_pattern::pay_multisig: type = "pay_multisig"; break;
        case kth::infrastructure::machine::script_pattern::pay_public_key: type = "pay_public_key"; break;
        case kth::infrastructure::machine::script_pattern::pay_key_hash: type = "pay_key_hash"; break;
        case kth::infrastructure::machine::script_pattern::pay_script_hash: type = "pay_script_hash"; break;
        case kth::infrastructure::machine::script_pattern::sign_multisig: type = "sign_multisig"; break;
        case kth::infrastructure::machine::script_pattern::sign_public_key: type = "sign_public_key"; break;
        case kth::infrastructure::machine::script_pattern::sign_key_hash: type = "sign_key_hash"; break;
        case kth::infrastructure::machine::script_pattern::sign_script_hash: type = "sign_script_hash"; break;
        default: type = "non_standard"; break;
    }

    return kth::create_c_str(type);
}

uint8_t const* kth_chain_script_to_data(kth_script_t script, kth_bool_t prefix, kth_size_t* out_size) {
    auto script_data = kth_chain_script_const_cpp(script).to_data(kth::int_to_bool(prefix));
    return kth::create_c_array(script_data, *out_size);
}

kth_size_t kth_chain_script_sigops(kth_script_t script, kth_bool_t embedded) {
    return kth_chain_script_const_cpp(script).sigops(kth::int_to_bool(embedded));
}

} // extern "C"
