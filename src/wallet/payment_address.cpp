// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#include <kth/capi/wallet/payment_address.h>

#include <kth/capi/helpers.hpp>
#include <kth/capi/type_conversions.h>

#include <kth/bitcoin/multi_crypto_support.hpp>
#include <kth/bitcoin/wallet/payment_address.hpp>

KTH_CONV_DEFINE(wallet, payment_address_t, kth::wallet::payment_address, payment_address)

//TODO(fernando): payment_address has to be in the wallet API

// ---------------------------------------------------------------------------
extern "C" {

#ifdef KTH_CURRENCY_BCH
void wallet_payment_address_set_cashaddr_prefix(char const* prefix) {
    std::string prefix_cpp(prefix);
    kth::set_cashaddr_prefix(prefix_cpp);
}
#endif //KTH_CURRENCY_BCH

payment_address_t wallet_payment_address_construct_from_string(char const* address) {
    return new kth::wallet::payment_address(std::string(address));
}

//User is responsible for releasing return value memory
char* wallet_payment_address_encoded(payment_address_t payment_address) {
    std::string str = wallet_payment_address_const_cpp(payment_address).encoded();
    return knuth::create_c_str(str);
}

#ifdef KTH_CURRENCY_BCH
//User is responsible for releasing return value memory
char* wallet_payment_address_encoded_cashaddr(payment_address_t payment_address) {
    std::string str = wallet_payment_address_const_cpp(payment_address).encoded_cashaddr();
    return knuth::create_c_str(str);
}
#endif //KTH_CURRENCY_BCH

short_hash_t wallet_payment_address_hash(payment_address_t payment_address) {
    auto const& hash_cpp = wallet_payment_address_const_cpp(payment_address).hash();
    return knuth::to_short_hash_t(hash_cpp);
}

uint8_t wallet_payment_address_version(payment_address_t payment_address) {
    return wallet_payment_address_const_cpp(payment_address).version();
}

bool_t wallet_payment_address_is_valid(payment_address_t payment_address) {
    return knuth::bool_to_int(static_cast<bool>(wallet_payment_address_const_cpp(payment_address)));
}

void wallet_payment_address_destruct(payment_address_t payment_address) {
    delete &wallet_payment_address_cpp(payment_address);
}

} // extern "C"
