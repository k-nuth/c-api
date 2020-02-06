// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.



#include <kth/capi/wallet/transaction_functions.h>

#include <kth/domain/wallet/payment_address.hpp>
#include <kth/domain/wallet/transaction_functions.hpp>

#include <kth/capi/conversions.hpp>
#include <kth/capi/helpers.hpp>
#include <kth/capi/primitives.h>

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

    auto p = kth::wallet::tx_encode(
                chain_point_list_const_cpp(outputs_to_spend),
                wallet_raw_output_list_const_cpp(destiny_and_amount),
                chain_output_list_const_cpp(extra_outputs),
                locktime,
                tx_version,
                script_version
               );

    if (p.first == kth::error::success) {
        *out_transaction = new kth::message::transaction(std::move(p.second));
    } else {
        *out_transaction = nullptr;
    }

    return kth::to_c_err(p.first);
}

error_code_t wallet_tx_encode(
    point_list_t outputs_to_spend,
    raw_output_list_t destiny_and_amount,
    uint32_t locktime /*= 0*/,
    uint32_t tx_version /*= 1*/,
    uint8_t script_version /*= 5*/,
    transaction_t* out_transaction) {

    auto p = kth::wallet::tx_encode(
                chain_point_list_const_cpp(outputs_to_spend),
                wallet_raw_output_list_const_cpp(destiny_and_amount),
                locktime,
                tx_version,
                script_version
               );

    if (p.first == kth::error::success) {
        *out_transaction = new kth::message::transaction(std::move(p.second));
    } else {
        *out_transaction = nullptr;
    }

    return kth::to_c_err(p.first);
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

    auto p = kth::wallet::input_signature_old(
        kth::to_array(private_key.data),
        chain_script_const_cpp(output_script),
        chain_transaction_const_cpp(tx),
        index,
        sign_type,
        kth::int_to_bool(anyone_can_pay)
    );

    if (p.first == kth::error::success) {
        *out_signature = kth::create_c_array(p.second, *out_signature_size);
    } else {
        *out_signature_size = 0;
        *out_signature = nullptr;
    }

    return kth::to_c_err(p.first);
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

    auto p = kth::wallet::input_signature_btc(
        kth::to_array(private_key.data),
        chain_script_const_cpp(output_script),
        chain_transaction_const_cpp(tx),
        amount,
        index,
        sign_type,
        kth::int_to_bool(anyone_can_pay)
    );

    if (p.first == kth::error::success) {
        *out_signature = kth::create_c_array(p.second, *out_signature_size);
    } else {
        *out_signature_size = 0;
        *out_signature = nullptr;
    }

    return kth::to_c_err(p.first);
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

    auto p = kth::wallet::input_signature_bch(
        kth::to_array(private_key.data),
        chain_script_const_cpp(output_script),
        chain_transaction_const_cpp(tx),
        amount,
        index,
        sign_type,
        kth::int_to_bool(anyone_can_pay)
    );

    if (p.first == kth::error::success) {
        *out_signature = kth::create_c_array(p.second, *out_signature_size);
    } else {
        *out_signature_size = 0;
        *out_signature = nullptr;
    }

    return kth::to_c_err(p.first);
}

error_code_t input_set_script(
    script_t script,
    transaction_t tx,
    uint32_t index /*= 0*/,
    transaction_t* out_transaction) {

    auto p = kth::wallet::input_set(
                chain_script_const_cpp(script),
                chain_transaction_const_cpp(tx),
                index
               );

    if (p.first == kth::error::success) {
        *out_transaction = new kth::message::transaction(std::move(p.second));
    } else {
        *out_transaction = nullptr;
    }

    return kth::to_c_err(p.first);
}

// error_code_t input_set_signature(
//     uint8_t* signature, 
//     uint64_t /*size_t*/ signature_n,
//     ec_public_t public_key,
//     transaction_t tx,
//     uint32_t index /*= 0*/,
//     transaction_t* out_transaction) {

//     kth::data_chunk signature_cpp(signature, std::next(signature, signature_n));

//     auto p = kth::wallet::input_set(
//                 signature_cpp,
//                 wallet_ec_public_const_cpp(public_key),
//                 chain_transaction_const_cpp(tx),
//                 index
//                );

//     if (p.first == kth::error::success) {
//         *out_transaction = new kth::message::transaction(std::move(p.second));
//     } else {
//         *out_transaction = nullptr;
//     }

//     return kth::to_c_err(p.first);
// }



// BC_API std::pair<error::error_code_t, chain::transaction> input_set(data_chunk const& signature,
//                                                                     wallet::ec_public const& public_key,
//                                                                     chain::transaction const& tx, 
//                                                                      uint32_t index = 0);


} // extern "C"
