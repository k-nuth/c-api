// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#include <kth/capi/wallet/ec_public.h>

#include <kth/domain/wallet/transaction_functions.hpp>

#include <kth/capi/conversions.hpp>
#include <kth/capi/helpers.hpp>
#include <kth/capi/type_conversions.h>

KTH_CONV_DEFINE(wallet, ec_public_t, kth::domain::wallet::ec_public, ec_public)

extern "C" {

ec_public_t wallet_ec_public_construct_default() {
    return new kth::domain::wallet::ec_public();
}

// payment_address_t wallet_ec_public_destiny(ec_public_t obj) {
//     return &wallet_ec_public_cpp(obj).first;
// }

uint16_t wallet_ec_public_version(ec_public_t obj) {
    return wallet_ec_public_const_cpp(obj).version();
}

uint8_t wallet_ec_public_payment_version(ec_public_t obj) {
    return wallet_ec_public_const_cpp(obj).payment_version();
}

uint8_t wallet_ec_public_wif_version(ec_public_t obj) {
    return wallet_ec_public_const_cpp(obj).wif_version();
}

bool_t wallet_ec_public_compressed(ec_public_t obj) {
    return kth::bool_to_int(wallet_ec_public_const_cpp(obj).compressed());
}

} // extern "C"
