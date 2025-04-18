// Copyright (c) 2016-2025 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/capi/wallet/payment_address.h>

#include <kth/capi/helpers.hpp>
#include <kth/capi/type_conversions.h>

#include <kth/domain/multi_crypto_support.hpp>
#include <kth/domain/wallet/payment_address.hpp>

#include <kth/capi/conversions.hpp>

KTH_CONV_DEFINE(wallet, kth_payment_address_t, kth::domain::wallet::payment_address, payment_address)

// ---------------------------------------------------------------------------
extern "C" {

kth_payment_address_t kth_wallet_payment_address_construct_from_string(char const* address) {
    return new kth::domain::wallet::payment_address(std::string(address));
}

kth_payment_address_t kth_wallet_payment_address_construct_from_short_hash(kth_shorthash_t const* hash, uint8_t version) {
    auto const hash_cpp = kth::short_hash_to_cpp(hash->hash);
    return new kth::domain::wallet::payment_address(hash_cpp, version);
}

kth_payment_address_t kth_wallet_payment_address_construct_from_hash(kth_hash_t const* hash, uint8_t version) {
    auto const hash_cpp = kth::hash_to_cpp(hash->hash);
    return new kth::domain::wallet::payment_address(hash_cpp, version);
}

kth_payment_address_t kth_wallet_payment_address_construct_from_point(kth_ec_public_t point, uint8_t version) {
    auto const point_cpp = kth_wallet_ec_public_const_cpp(point);
    return new kth::domain::wallet::payment_address(point_cpp, version);
}

kth_payment_address_t kth_wallet_payment_address_construct_from_script(kth_script_t script, uint8_t version) {
    auto script_cpp = kth_chain_script_const_cpp(script);
    return new kth::domain::wallet::payment_address(script_cpp, version);
}

kth_payment_address_t kth_wallet_payment_address_from_pay_public_key_hash_script(kth_script_t script, uint8_t version) {
    auto script_cpp = kth_chain_script_const_cpp(script);
    auto pa = kth::domain::wallet::payment_address::from_pay_public_key_hash_script(script_cpp, version);
    return kth::move_or_copy_and_leak(std::move(pa));
}


void kth_wallet_payment_address_destruct(kth_payment_address_t payment_address) {
    delete &kth_wallet_payment_address_cpp(payment_address);
}

#if defined(KTH_CURRENCY_BCH)
void kth_wallet_payment_address_set_cashaddr_prefix(char const* prefix) {
    std::string prefix_cpp(prefix);
    kth::set_cashaddr_prefix(prefix_cpp);
}
#endif //KTH_CURRENCY_BCH

//User is responsible for releasing return value memory
char* kth_wallet_payment_address_encoded_legacy(kth_payment_address_t payment_address) {
    std::string str = kth_wallet_payment_address_const_cpp(payment_address).encoded_legacy();
    return kth::create_c_str(str);
}

#if defined(KTH_CURRENCY_BCH)
//User is responsible for releasing return value memory
char* kth_wallet_payment_address_encoded_cashaddr(kth_payment_address_t payment_address, kth_bool_t token_aware) {
    std::string str = kth_wallet_payment_address_const_cpp(payment_address).encoded_cashaddr(token_aware);
    return kth::create_c_str(str);
}
#endif //KTH_CURRENCY_BCH

kth_shorthash_t kth_wallet_payment_address_hash20(kth_payment_address_t payment_address) {
    auto hash_cpp = kth_wallet_payment_address_const_cpp(payment_address).hash20();
    // printf("kth_wallet_payment_address_hash20()\n");
    // for (auto i = 0; i < 20; i++) {
    //     printf("%d ", int(hash_cpp[i]));
    // }
    // printf("\n");
    return kth::to_shorthash_t(hash_cpp);
}

kth_hash_t kth_wallet_payment_address_hash32(kth_payment_address_t payment_address) {
    auto hash_cpp = kth_wallet_payment_address_const_cpp(payment_address).hash32();
    // printf("kth_wallet_payment_address_hash32()\n");
    // for (auto i = 0; i < 32; i++) {
    //     printf("%d ", int(hash_cpp[i]));
    // }
    // printf("\n");
    return kth::to_hash_t(hash_cpp);
}

uint8_t kth_wallet_payment_address_version(kth_payment_address_t payment_address) {
    return kth_wallet_payment_address_const_cpp(payment_address).version();
}

kth_bool_t kth_wallet_payment_address_is_valid(kth_payment_address_t payment_address) {
    return kth::bool_to_int(static_cast<bool>(kth_wallet_payment_address_const_cpp(payment_address)));
}

kth_payment_address_list_const_t kth_wallet_payment_address_extract(kth_script_t script, uint8_t p2kh_version, uint8_t p2sh_version) {
    auto const& script_cpp = kth_chain_script_const_cpp(script);
    auto addrs = kth::domain::wallet::payment_address::extract(script_cpp, p2kh_version, p2sh_version);
    return kth::move_or_copy_and_leak(std::move(addrs));
}

kth_payment_address_list_const_t kth_wallet_payment_address_extract_input(kth_script_t script, uint8_t p2kh_version, uint8_t p2sh_version) {
    auto const& script_cpp = kth_chain_script_const_cpp(script);
    auto addrs = kth::domain::wallet::payment_address::extract_input(script_cpp, p2kh_version, p2sh_version);
    return kth::move_or_copy_and_leak(std::move(addrs));
}

kth_payment_address_list_const_t kth_wallet_payment_address_extract_output(kth_script_t script, uint8_t p2kh_version, uint8_t p2sh_version) {
    auto const& script_cpp = kth_chain_script_const_cpp(script);
    auto addrs = kth::domain::wallet::payment_address::extract_output(script_cpp, p2kh_version, p2sh_version);
    return kth::move_or_copy_and_leak(std::move(addrs));
}

} // extern "C"
