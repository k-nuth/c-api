// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#include <kth/capi/wallet/raw_output.h>

#include <kth/domain/wallet/transaction_functions.hpp>

#include <kth/capi/conversions.hpp>
#include <kth/capi/helpers.hpp>
#include <kth/capi/type_conversions.h>

KTH_CONV_DEFINE(wallet, raw_output_t, kth::wallet::raw_output, raw_output)

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
//     return new kth::wallet::raw_output();
// }

// raw_output_t wallet_raw_output_construct(uint32_t version, uint8_t* previous_block_hash, uint8_t* merkle, uint32_t timestamp, uint32_t bits, uint32_t nonce) {
//     //precondition: [previous_block_hash, 32) is a valid range
//     //              && [merkle, 32) is a valid range

//     auto previous_block_hash_cpp = kth::hash_to_cpp(previous_block_hash);
//     auto merkle_cpp = kth::hash_to_cpp(merkle);
//     return new kth::wallet::raw_output(version, previous_block_hash_cpp, merkle_cpp, timestamp, bits, nonce);
// }


} // extern "C"
