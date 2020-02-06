// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#include <knuth/nodecint/wallet/ec_public.h>

#include <bitcoin/bitcoin/wallet/transaction_functions.hpp>

#include <knuth/nodecint/conversions.hpp>
#include <knuth/nodecint/helpers.hpp>
#include <knuth/nodecint/type_conversions.h>

KTH_CONV_DEFINE(wallet, ec_public_t, libbitcoin::wallet::ec_public, ec_public)

extern "C" {

ec_public_t wallet_ec_public_construct_default() {
    return new libbitcoin::wallet::ec_public();
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
    return knuth::bool_to_int(wallet_ec_public_const_cpp(obj).compressed());
}

} // extern "C"
