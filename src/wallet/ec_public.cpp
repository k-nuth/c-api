/**
 * Copyright (c) 2016-2018 Bitprim Inc.
 *
 * This file is part of Bitprim.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <bitprim/nodecint/wallet/ec_public.h>

#include <bitcoin/bitcoin/wallet/transaction_functions.hpp>

#include <bitprim/nodecint/convertions.hpp>
#include <bitprim/nodecint/helpers.hpp>
#include <bitprim/nodecint/type_convertions.h>

BITPRIM_CONV_DEFINE(wallet, ec_public_t, libbitcoin::wallet::ec_public, ec_public)

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
    return bitprim::bool_to_int(wallet_ec_public_const_cpp(obj).compressed());
}

} // extern "C"
