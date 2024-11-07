// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/capi/wallet/hd_private.h>

#include <kth/capi/conversions.hpp>
#include <kth/capi/helpers.hpp>

#include <kth/capi/wallet/conversions.hpp>

#include <kth/infrastructure/wallet/hd_private.hpp>

KTH_CONV_DEFINE(wallet, kth_hd_private_t, kth::infrastructure::wallet::hd_private, hd_private)

extern "C" {

kth_hd_private_t kth_wallet_hd_private_construct_default() {
    return new kth::infrastructure::wallet::hd_private();
}

kth_hd_private_t kth_wallet_hd_private_construct_key(kth_hd_key_t const* private_key) {
    return new kth::infrastructure::wallet::hd_private(detail::from_hd_key_t(*private_key));
}

kth_hd_private_t kth_wallet_hd_private_construct_key_prefix(kth_hd_key_t const* private_key, uint32_t prefix) {
    return new kth::infrastructure::wallet::hd_private(detail::from_hd_key_t(*private_key), prefix);
}

kth_hd_private_t kth_wallet_hd_private_construct_key_prefixes(kth_hd_key_t const* private_key, uint64_t prefixes) {
    return new kth::infrastructure::wallet::hd_private(detail::from_hd_key_t(*private_key), prefixes);
}

kth_hd_private_t kth_wallet_hd_private_construct_seed(uint8_t const* seed, kth_size_t size, uint64_t prefixes) {
    kth::data_chunk const seed_chunk(seed, seed + size);
    return new kth::infrastructure::wallet::hd_private(seed_chunk, prefixes);
}

kth_hd_private_t kth_wallet_hd_private_construct_string(char const* encoded) {
    return new kth::infrastructure::wallet::hd_private(std::string(encoded));
}

kth_hd_private_t kth_wallet_hd_private_construct_string_prefix(char const* encoded, uint32_t prefix) {
    return new kth::infrastructure::wallet::hd_private(std::string(encoded), prefix);
}

kth_hd_private_t kth_wallet_hd_private_construct_string_prefixes(char const* encoded, uint64_t prefixes) {
    return new kth::infrastructure::wallet::hd_private(std::string(encoded), prefixes);
}

void kth_wallet_hd_private_destruct(kth_hd_private_t hd_private) {
    delete &kth_wallet_hd_private_cpp(hd_private);
}

kth_bool_t kth_wallet_hd_private_is_valid(kth_hd_private_t hd_private) {
    bool valid = kth_wallet_hd_private_const_cpp(hd_private);
    return kth::bool_to_int(valid);
}

char* kth_wallet_hd_private_encoded(kth_hd_private_t hd_private) {
    std::string encoded = kth_wallet_hd_private_const_cpp(hd_private).encoded();
    return kth::create_c_str(encoded);
}

kth_ec_secret_t kth_wallet_hd_private_secret(kth_hd_private_t hd_private) {
    auto const& secret_cpp = kth_wallet_hd_private_const_cpp(hd_private).secret();
    return detail::to_ec_secret_t(secret_cpp);
}

// Accessors.
kth_hd_chain_code_t kth_wallet_hd_private_chain_code(kth_hd_private_t hd_private) {
    auto const& chain_code_cpp = kth_wallet_hd_private_const_cpp(hd_private).chain_code();
    return detail::to_hd_chain_code_t(chain_code_cpp);
}

kth_hd_lineage_t kth_wallet_hd_private_lineage(kth_hd_private_t hd_private) {
    auto const& lineage_cpp = kth_wallet_hd_private_const_cpp(hd_private).lineage();
    return detail::to_hd_lineage_t(lineage_cpp);
}

kth_ec_compressed_t kth_wallet_hd_private_point(kth_hd_private_t hd_private) {
    auto const& point_cpp = kth_wallet_hd_private_const_cpp(hd_private).point();
    return detail::to_ec_compressed_t(point_cpp);
}

kth_hd_key_t kth_wallet_hd_private_to_hd_key(kth_hd_private_t hd_private) {
    auto const& hd_key_cpp = kth_wallet_hd_private_const_cpp(hd_private).to_hd_key();
    return detail::to_hd_key_t(hd_key_cpp);
}

kth_hd_public_t kth_wallet_hd_private_to_public(kth_hd_private_t hd_private) {
    auto const& hd_public_cpp = kth_wallet_hd_private_const_cpp(hd_private).to_public();
    return kth::move_or_copy_and_leak(std::move(hd_public_cpp));
}

kth_hd_private_t kth_wallet_hd_private_derive_private(kth_hd_private_t hd_private, uint32_t index) {
    auto const& derived_private_cpp = kth_wallet_hd_private_const_cpp(hd_private).derive_private(index);
    return kth::move_or_copy_and_leak(std::move(derived_private_cpp));
}

kth_hd_public_t kth_wallet_hd_private_derive_public(kth_hd_private_t hd_private, uint32_t index) {
    auto const& derived_public_cpp = kth_wallet_hd_private_const_cpp(hd_private).derive_public(index);
    return kth::move_or_copy_and_leak(std::move(derived_public_cpp));
}

} // extern "C"
