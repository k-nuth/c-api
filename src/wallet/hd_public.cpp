// Copyright (c) 2016-2023 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/capi/wallet/hd_public.h>

#include <kth/capi/conversions.hpp>
#include <kth/capi/helpers.hpp>

#include <kth/capi/wallet/conversions.hpp>

KTH_CONV_DEFINE(wallet, kth_hd_public_t, kth::infrastructure::wallet::hd_public, hd_public)

extern "C" {

kth_hd_public_t kth_wallet_hd_public_construct_default() {
    return new kth::infrastructure::wallet::hd_public();
}

kth_hd_public_t kth_wallet_hd_public_construct_string(char const* encoded) {
    return new kth::infrastructure::wallet::hd_public(std::string(encoded));
}

kth_hd_public_t kth_wallet_hd_public_construct_string_prefix(char const* encoded, uint32_t prefix) {
    return new kth::infrastructure::wallet::hd_public(std::string(encoded), prefix);
}

kth_hd_public_t kth_wallet_hd_public_construct_key(kth_hd_key_t const* public_key) {
    return new kth::infrastructure::wallet::hd_public(detail::from_hd_key_t(*public_key));
}

kth_hd_public_t kth_wallet_hd_public_construct_key_prefix(kth_hd_key_t const* public_key, uint32_t prefix) {
    return new kth::infrastructure::wallet::hd_public(detail::from_hd_key_t(*public_key), prefix);
}

void kth_wallet_hd_public_destruct(kth_hd_public_t hd_public) {
    delete &kth_wallet_hd_public_cpp(hd_public);
}

kth_bool_t kth_wallet_hd_public_is_valid(kth_hd_public_t hd_public) {
    bool valid = kth_wallet_hd_public_const_cpp(hd_public);
    return kth::bool_to_int(valid);
}

// Serializer.
char* kth_wallet_hd_public_encoded(kth_hd_public_t hd_public) {
    std::string encoded = kth_wallet_hd_public_const_cpp(hd_public).encoded();
    return kth::create_c_str(encoded);
}

// Accessors.
kth_hd_chain_code_t kth_wallet_hd_public_chain_code(kth_hd_public_t hd_public) {
    auto const& chain_code_cpp = kth_wallet_hd_public_const_cpp(hd_public).chain_code();
    return detail::to_hd_chain_code_t(chain_code_cpp);
}

kth_hd_lineage_t kth_wallet_hd_public_lineage(kth_hd_public_t hd_public) {
    auto const& lineage_cpp = kth_wallet_hd_public_const_cpp(hd_public).lineage();
    return detail::to_hd_lineage_t(lineage_cpp);
}

kth_ec_compressed_t kth_wallet_hd_public_point(kth_hd_public_t hd_public) {
    auto const& point_cpp = kth_wallet_hd_public_const_cpp(hd_public).point();
    return detail::to_ec_compressed_t(point_cpp);
}

kth_hd_key_t kth_wallet_hd_public_to_hd_key(kth_hd_public_t hd_public) {
    auto const& hd_key_cpp = kth_wallet_hd_public_const_cpp(hd_public).to_hd_key();
    return detail::to_hd_key_t(hd_key_cpp);
}

kth_hd_public_t kth_wallet_hd_public_derive_public(kth_hd_public_t hd_public, uint32_t index) {
    auto const& derived_public_cpp = kth_wallet_hd_public_const_cpp(hd_public).derive_public(index);
    return kth::move_or_copy_and_leak(std::move(derived_public_cpp));
}

} // extern "C"
