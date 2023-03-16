// Copyright (c) 2016-2023 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/capi/chain/token_data.h>

#include <kth/capi/conversions.hpp>
#include <kth/capi/helpers.hpp>

KTH_CONV_DEFINE(chain, kth_token_data_t, kth::domain::chain::token_data, token_data)

// ---------------------------------------------------------------------------
extern "C" {

kth_token_data_t kth_chain_token_data_construct_default() {
    return new kth::domain::chain::token_data();
}

// // token_data::token_data(const data_chunk& encoded, bool prefix)
// kth_token_data_t kth_chain_token_data_construct() {
//     kth::data_chunk encoded_cpp(encoded, std::next(encoded, n));
//     return new kth::domain::chain::token_data(encoded_cpp, kth::int_to_bool(prefix));
// }

void kth_chain_token_data_destruct(kth_token_data_t token_data) {
    delete &kth_chain_token_data_cpp(token_data);
}

kth_bool_t kth_chain_token_data_is_valid(kth_token_data_t token_data) {
    return kth::bool_to_int(
        kth::domain::chain::is_valid(
            kth_chain_token_data_const_cpp(token_data)
        )
    );
}

kth_size_t kth_chain_token_data_serialized_size(kth_token_data_t token_data) {
    return kth::domain::chain::encoding::serialized_size(
            kth_chain_token_data_const_cpp(token_data)
        );
}

uint8_t const* kth_chain_token_data_to_data(kth_token_data_t token_data, kth_size_t* out_size) {
    auto token_data_data = kth::domain::chain::encoding::to_data(kth_chain_token_data_const_cpp(token_data));
    return kth::create_c_array(token_data_data, *out_size);
}

} // extern "C"
