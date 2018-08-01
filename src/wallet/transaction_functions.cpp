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


#include <bitprim/nodecint/wallet/transaction_functions.h>

#include <bitcoin/bitcoin/wallet/payment_address.hpp>
#include <bitcoin/bitcoin/wallet/transaction_functions.hpp>

#include <bitprim/nodecint/conversions.hpp>
#include <bitprim/nodecint/helpers.hpp>
#include <bitprim/nodecint/primitives.h>

// ---------------------------------------------------------------------------
extern "C" {

error_code_t wallet_tx_encode_with_extra_outputs(
    point_list_t outputs_to_spend,
    raw_output_list_t destiny_and_amount,
    output_list_t extra_outputs,
    uint32_t locktime /*= 0*/,
    uint32_t tx_version /*= 1*/,
    uint8_t script_version /*= 5*/,
    transaction_t* out_transaction) {

    auto p = libbitcoin::wallet::tx_encode(
                chain_point_list_const_cpp(outputs_to_spend),
                wallet_raw_output_list_const_cpp(destiny_and_amount),
                chain_output_list_const_cpp(extra_outputs),
                locktime,
                tx_version,
                script_version
               );

    if (p.first == libbitcoin::error::success) {
        *out_transaction = new libbitcoin::message::transaction(std::move(p.second));
    } else {
        *out_transaction = nullptr;
    }

    return bitprim::to_c_err(p.first);
}

error_code_t wallet_tx_encode(
    point_list_t outputs_to_spend,
    raw_output_list_t destiny_and_amount,
    uint32_t locktime /*= 0*/,
    uint32_t tx_version /*= 1*/,
    uint8_t script_version /*= 5*/,
    transaction_t* out_transaction) {

    auto p = libbitcoin::wallet::tx_encode(
                chain_point_list_const_cpp(outputs_to_spend),
                wallet_raw_output_list_const_cpp(destiny_and_amount),
                locktime,
                tx_version,
                script_version
               );

    if (p.first == libbitcoin::error::success) {
        *out_transaction = new libbitcoin::message::transaction(std::move(p.second));
    } else {
        *out_transaction = nullptr;
    }

    return bitprim::to_c_err(p.first);
}

error_code_t input_signature_old(
    ec_secret_t private_key,    /*32 element byte array*/
    script_t output_script,
    transaction_t tx,
    uint32_t index,
    uint8_t sign_type /*= 0x01*/,
    bool_t anyone_can_pay /*= false*/,
    uint8_t** out_signature,
    uint64_t* /*size_t*/ out_signature_size) {

    auto p = libbitcoin::wallet::input_signature_old(
        bitprim::to_array(private_key.data),
        chain_script_const_cpp(output_script),
        chain_transaction_const_cpp(tx),
        index,
        sign_type,
        bitprim::int_to_bool(anyone_can_pay)
    );

    if (p.first == libbitcoin::error::success) {
        *out_signature = bitprim::create_c_array(p.second, *out_signature_size);
    } else {
        *out_signature_size = 0;
        *out_signature = nullptr;
    }

    return bitprim::to_c_err(p.first);
}

error_code_t input_signature_btc(
    ec_secret_t private_key,    /*32 element byte array*/
    script_t output_script,
    transaction_t tx,
    uint64_t amount,    
    uint32_t index,
    uint8_t sign_type /*= 0x01*/,
    bool_t anyone_can_pay /*= false*/,
    uint8_t** out_signature,
    uint64_t* /*size_t*/ out_signature_size) {

    auto p = libbitcoin::wallet::input_signature_btc(
        bitprim::to_array(private_key.data),
        chain_script_const_cpp(output_script),
        chain_transaction_const_cpp(tx),
        amount,
        index,
        sign_type,
        bitprim::int_to_bool(anyone_can_pay)
    );

    if (p.first == libbitcoin::error::success) {
        *out_signature = bitprim::create_c_array(p.second, *out_signature_size);
    } else {
        *out_signature_size = 0;
        *out_signature = nullptr;
    }

    return bitprim::to_c_err(p.first);
}

error_code_t input_signature_bch(
    ec_secret_t private_key,    /*32 element byte array*/
    script_t output_script,
    transaction_t tx,
    uint64_t amount,    
    uint32_t index,
    uint8_t sign_type /*= 0x01*/,
    bool_t anyone_can_pay /*= false*/,
    uint8_t** out_signature,
    uint64_t* /*size_t*/ out_signature_size) {

    auto p = libbitcoin::wallet::input_signature_bch(
        bitprim::to_array(private_key.data),
        chain_script_const_cpp(output_script),
        chain_transaction_const_cpp(tx),
        amount,
        index,
        sign_type,
        bitprim::int_to_bool(anyone_can_pay)
    );

    if (p.first == libbitcoin::error::success) {
        *out_signature = bitprim::create_c_array(p.second, *out_signature_size);
    } else {
        *out_signature_size = 0;
        *out_signature = nullptr;
    }

    return bitprim::to_c_err(p.first);
}

error_code_t input_set_script(
    script_t script,
    transaction_t tx,
    uint32_t index /*= 0*/,
    transaction_t* out_transaction) {

    auto p = libbitcoin::wallet::input_set(
                chain_script_const_cpp(script),
                chain_transaction_const_cpp(tx),
                index
               );

    if (p.first == libbitcoin::error::success) {
        *out_transaction = new libbitcoin::message::transaction(std::move(p.second));
    } else {
        *out_transaction = nullptr;
    }

    return bitprim::to_c_err(p.first);
}

// error_code_t input_set_signature(
//     uint8_t* signature, 
//     uint64_t /*size_t*/ signature_n,
//     ec_public_t public_key,
//     transaction_t tx,
//     uint32_t index /*= 0*/,
//     transaction_t* out_transaction) {

//     libbitcoin::data_chunk signature_cpp(signature, std::next(signature, signature_n));

//     auto p = libbitcoin::wallet::input_set(
//                 signature_cpp,
//                 wallet_ec_public_const_cpp(public_key),
//                 chain_transaction_const_cpp(tx),
//                 index
//                );

//     if (p.first == libbitcoin::error::success) {
//         *out_transaction = new libbitcoin::message::transaction(std::move(p.second));
//     } else {
//         *out_transaction = nullptr;
//     }

//     return bitprim::to_c_err(p.first);
// }



// BC_API std::pair<error::error_code_t, chain::transaction> input_set(data_chunk const& signature,
//                                                                     wallet::ec_public const& public_key,
//                                                                     chain::transaction const& tx, 
//                                                                      uint32_t index = 0);


} // extern "C"
