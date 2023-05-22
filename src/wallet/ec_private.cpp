// Copyright (c) 2016-2023 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/capi/wallet/ec_private.h>

#include <kth/capi/conversions.hpp>
#include <kth/capi/helpers.hpp>
#include <kth/capi/type_conversions.h>

#include <kth/capi/wallet/conversions.hpp>

KTH_CONV_DEFINE(wallet, kth_ec_private_t, kth::domain::wallet::ec_private, ec_private)

extern "C" {

kth_ec_private_t kth_wallet_ec_private_construct_default() {
    return new kth::domain::wallet::ec_private();
}

kth_ec_private_t kth_wallet_ec_private_construct_string(char const* wif, uint8_t version) {
    return new kth::domain::wallet::ec_private(std::string(wif), version);
}

kth_ec_private_t kth_wallet_ec_private_construct_compressed(kth_wif_compressed_t const* wif, uint8_t version) {
    auto wif_cpp = detail::from_wif_compressed_t(*wif);
    return new kth::domain::wallet::ec_private(wif_cpp, version);
}

kth_ec_private_t kth_wallet_ec_private_construct_uncompressed(kth_wif_uncompressed_t const* wif, uint8_t version) {
    auto wif_cpp = detail::from_wif_uncompressed_t(*wif);
    return new kth::domain::wallet::ec_private(wif_cpp, version);
}

kth_ec_private_t kth_wallet_ec_private_construct_secret(kth_ec_secret_t const* secret, uint16_t version, kth_bool_t compress) {
    auto secret_cpp = detail::from_ec_secret_t(*secret);
    return new kth::domain::wallet::ec_private(secret_cpp, version, kth::int_to_bool(compress));
}

void kth_wallet_ec_private_destruct(kth_ec_private_t obj) {
    delete &kth_wallet_ec_private_cpp(obj);
}

kth_bool_t kth_wallet_ec_private_is_valid(kth_ec_private_t obj) {
    return kth::bool_to_int(kth_wallet_ec_private_const_cpp(obj).operator bool());
}

char* kth_wallet_ec_private_encoded(kth_ec_private_t obj) {
    std::string encoded = kth_wallet_ec_private_const_cpp(obj).encoded();
    return kth::create_c_str(encoded);
}

kth_ec_secret_t kth_wallet_ec_private_secret(kth_ec_private_t obj) {
    auto& secret_cpp = kth_wallet_ec_private_const_cpp(obj).secret();
    return detail::to_ec_secret_t(secret_cpp);
}

uint16_t kth_wallet_ec_private_version(kth_ec_private_t obj) {
    return kth_wallet_ec_private_const_cpp(obj).version();
}

uint8_t kth_wallet_ec_private_payment_version(kth_ec_private_t obj) {
    return kth_wallet_ec_private_const_cpp(obj).payment_version();
}

uint8_t kth_wallet_ec_private_wif_version(kth_ec_private_t obj) {
    return kth_wallet_ec_private_const_cpp(obj).wif_version();
}

kth_bool_t kth_wallet_ec_private_compressed(kth_ec_private_t obj) {
    return kth::bool_to_int(kth_wallet_ec_private_const_cpp(obj).compressed());
}

kth_ec_public_t kth_wallet_ec_private_to_public(kth_ec_private_t obj) {
    auto public_key = kth_wallet_ec_private_const_cpp(obj).to_public();
    return kth::move_or_copy_and_leak(std::move(public_key));
}

kth_payment_address_t kth_wallet_ec_private_to_payment_address(kth_ec_private_t obj) {
    auto payment_address = kth_wallet_ec_private_const_cpp(obj).to_payment_address();
    return kth::move_or_copy_and_leak(std::move(payment_address));
}

} // extern "C"
