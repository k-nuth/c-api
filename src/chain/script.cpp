// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#include <kth/capi/chain/script.h>

#include <kth/capi/conversions.hpp>
#include <kth/capi/helpers.hpp>

KTH_CONV_DEFINE(chain, script_t, kth::chain::script, script)

// ---------------------------------------------------------------------------
extern "C" {

script_t chain_script_construct_default() {
    return new kth::chain::script();
}

// script::script(const data_chunk& encoded, bool prefix)
script_t chain_script_construct(uint8_t* encoded, uint64_t n, bool_t prefix) {
    kth::data_chunk encoded_cpp(encoded, std::next(encoded, n));
    return new kth::chain::script(encoded_cpp, knuth::int_to_bool(prefix));
}

void chain_script_destruct(script_t script) {
    delete &chain_script_cpp(script);
}

bool_t chain_script_is_valid(script_t script) {
    return knuth::bool_to_int(chain_script_const_cpp(script).is_valid());
}

bool_t chain_script_is_valid_operations(script_t script) {
    return knuth::bool_to_int(chain_script_const_cpp(script).is_valid_operations());
}

uint64_t /*size_t*/ chain_script_satoshi_content_size(script_t script) {
    return chain_script_const_cpp(script).serialized_size(false);
}

uint64_t /*size_t*/ chain_script_serialized_size(script_t script, bool_t prefix) {
    return chain_script_const_cpp(script).serialized_size(knuth::int_to_bool(prefix));
}

//Note: user of the function has to release the resource (memory) manually
char* chain_script_to_string(script_t script, uint32_t active_forks) {
    auto str = chain_script_const_cpp(script).to_string(active_forks);
    return knuth::create_c_str(str);
}

// TODO(fernando): Move this logic elsewhere (this does not go in a wrapper like node-cint)
char* chain_script_type(script_t script) {
    auto script_pattern = chain_script_const_cpp(script).pattern();
    std::string type = "non_standard";
    switch(script_pattern) {
        case kth::machine::script_pattern::null_data: type = "nulldata"; break;
        case kth::machine::script_pattern::pay_multisig: type = "pay_multisig"; break;
        case kth::machine::script_pattern::pay_public_key: type = "pay_public_key"; break;
        case kth::machine::script_pattern::pay_key_hash: type = "pay_key_hash"; break;
        case kth::machine::script_pattern::pay_script_hash: type = "pay_script_hash"; break;
        case kth::machine::script_pattern::sign_multisig: type = "sign_multisig"; break;
        case kth::machine::script_pattern::sign_public_key: type = "sign_public_key"; break;
        case kth::machine::script_pattern::sign_key_hash: type = "sign_key_hash"; break;
        case kth::machine::script_pattern::sign_script_hash: type = "sign_script_hash"; break;
        default: type = "non_standard"; break;
    }

    return knuth::create_c_str(type);
}

uint8_t* chain_script_to_data(script_t script, bool_t prefix, uint64_t* /*size_t*/ out_size) {
    auto script_data = chain_script_const_cpp(script).to_data(knuth::int_to_bool(prefix));
    return knuth::create_c_array(script_data, *out_size);
}

uint64_t /*size_t*/ chain_script_sigops(script_t script, bool_t embedded) {
    return chain_script_const_cpp(script).sigops(knuth::int_to_bool(embedded));
}

} // extern "C"
