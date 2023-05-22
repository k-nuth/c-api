// Copyright (c) 2016-2023 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/infrastructure/wallet/hd_private.hpp>

KTH_CONV_DEFINE(wallet, kth_hd_private_t, kth::infrastructure::wallet::hd_private, hd_private)

extern "C" {

kth_hd_private_t kth_wallet_hd_private_construct_default() {
    return new kth::infrastructure::wallet::hd_private();
}

kth_hd_private_t kth_wallet_hd_private_construct(kth_hd_key_t const* private_key) {
    return new kth::infrastructure::wallet::hd_private(detail::from_hd_key_t(*private_key));
}

kth_hd_private_t kth_wallet_hd_private_construct_with_prefix(kth_hd_key_t const* private_key, uint32_t prefix) {
    return new kth::infrastructure::wallet::hd_private(detail::from_hd_key_t(*private_key), prefix);
}

kth_hd_private_t kth_wallet_hd_private_construct_with_prefixes(kth_hd_key_t const* private_key, uint64_t prefixes) {
    return new kth::infrastructure::wallet::hd_private(detail::from_hd_key_t(*private_key), prefixes);
}

kth_hd_private_t kth_wallet_hd_private_construct_with_seed(uint8_t const* seed, size_t size, uint64_t prefixes) {
    kth::data_chunk const seed_chunk(seed, seed + size);
    return new kth::infrastructure::wallet::hd_private(seed_chunk, prefixes);
}

kth_hd_private_t kth_wallet_hd_private_construct_string(char const* encoded) {
    return new kth::infrastructure::wallet::hd_private(std::string(encoded));
}

kth_hd_private_t kth_wallet_hd_private_construct_string_with_prefix(char const* encoded, uint32_t prefix) {
    return new kth::infrastructure::wallet::hd_private(std::string(encoded), prefix);
}

void kth_wallet_hd_private_destruct(kth_hd_private_t hd_private) {
    delete &kth_wallet_hd_private_cpp(hd_private);
}

char const* kth_wallet_hd_private_encoded(kth_hd_private_t hd_private) {
    std::string encoded = kth_wallet_hd_private_const_cpp(hd_private).encoded();
    return kth::create_c_str(encoded);
}

kth_ec_secret_t kth_wallet_hd_private_secret(kth_hd_private_t hd_private) {
    auto const& secret_cpp = kth_wallet_hd_private_const_cpp(hd_private).secret();
    return detail::to_ec_secret_t(secret_cpp);
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
