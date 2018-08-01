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

#include <bitprim/nodecint/wallet/raw_output.h>

#include <bitcoin/bitcoin/wallet/transaction_functions.hpp>

#include <bitprim/nodecint/conversions.hpp>
#include <bitprim/nodecint/helpers.hpp>
#include <bitprim/nodecint/type_conversions.h>

BITPRIM_CONV_DEFINE(wallet, raw_output_t, libbitcoin::wallet::raw_output, raw_output)

// C++ class declaration
// using raw_output = std::pair<payment_address, uint64_t>;

extern "C" {

payment_address_t wallet_raw_output_destiny(raw_output_t obj) {
    return &wallet_raw_output_cpp(obj).first;
}

uint64_t wallet_raw_output_amount(raw_output_t obj) {
    return wallet_raw_output_const_cpp(obj).second;
}


// raw_output_t wallet_raw_output_construct_default() {
//     return new libbitcoin::wallet::raw_output();
// }

// raw_output_t wallet_raw_output_construct(uint32_t version, uint8_t* previous_block_hash, uint8_t* merkle, uint32_t timestamp, uint32_t bits, uint32_t nonce) {
//     //precondition: [previous_block_hash, 32) is a valid range
//     //              && [merkle, 32) is a valid range

//     auto previous_block_hash_cpp = bitprim::hash_to_cpp(previous_block_hash);
//     auto merkle_cpp = bitprim::hash_to_cpp(merkle);
//     return new libbitcoin::wallet::raw_output(version, previous_block_hash_cpp, merkle_cpp, timestamp, bits, nonce);
// }


} // extern "C"
