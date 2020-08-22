// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/capi/wallet/payment_address.h>

#include <kth/capi/helpers.hpp>
#include <kth/capi/type_conversions.h>

#include <kth/domain/multi_crypto_support.hpp>
#include <kth/domain/wallet/payment_address.hpp>

KTH_CONV_DEFINE(wallet, kth_payment_address_t, kth::domain::wallet::payment_address, payment_address)

//TODO(fernando): payment_address has to be in the wallet API

// ---------------------------------------------------------------------------
extern "C" {

#if defined(KTH_CURRENCY_BCH)
void kth_wallet_payment_address_set_cashaddr_prefix(char const* prefix) {
    std::string prefix_cpp(prefix);
    kth::set_cashaddr_prefix(prefix_cpp);
}
#endif //KTH_CURRENCY_BCH

kth_payment_address_t kth_wallet_payment_address_construct_from_string(char const* address) {
    return new kth::domain::wallet::payment_address(std::string(address));
}

//User is responsible for releasing return value memory
char* kth_wallet_payment_address_encoded(kth_payment_address_t payment_address) {
    std::string str = kth_wallet_payment_address_const_cpp(payment_address).encoded();
    return kth::create_c_str(str);
}

#if defined(KTH_CURRENCY_BCH)
//User is responsible for releasing return value memory
char* kth_wallet_payment_address_encoded_cashaddr(kth_payment_address_t payment_address) {
    std::string str = kth_wallet_payment_address_const_cpp(payment_address).encoded_cashaddr();
    return kth::create_c_str(str);
}
#endif //KTH_CURRENCY_BCH

short_kth_hash_t kth_wallet_payment_address_hash(kth_payment_address_t payment_address) {
    auto const& hash_cpp = kth_wallet_payment_address_const_cpp(payment_address).hash();
    return kth::to_short_kth_hash_t(hash_cpp);
}

uint8_t kth_wallet_payment_address_version(kth_payment_address_t payment_address) {
    return kth_wallet_payment_address_const_cpp(payment_address).version();
}

bool_t kth_wallet_payment_address_is_valid(kth_payment_address_t payment_address) {
    return kth::bool_to_int(static_cast<bool>(wallet_payment_address_const_cpp(payment_address)));
}

void kth_wallet_payment_address_destruct(kth_payment_address_t payment_address) {
    delete &wallet_payment_address_cpp(payment_address);
}

} // extern "C"
