// // Copyright (c) 2016-2024 Knuth Project developers.
// // Distributed under the MIT software license, see the accompanying
// // file COPYING or http://www.opensource.org/licenses/mit-license.php.


// #include <kth/capi/wallet/transaction_functions.h>

// #include <kth/domain/wallet/payment_address.hpp>
// #include <kth/domain/wallet/transaction_functions.hpp>

// #include <kth/capi/conversions.hpp>
// #include <kth/capi/helpers.hpp>
// #include <kth/capi/primitives.h>

// // ---------------------------------------------------------------------------
// extern "C" {

// kth_error_code_t kth_wallet_tx_encode_with_extra_outputs(
//     kth_point_list_t outputs_to_spend,
//     kth_raw_output_list_t destiny_and_amount,
//     kth_output_list_t extra_outputs,
//     uint32_t locktime /*= 0*/,
//     uint32_t tx_version /*= 1*/,
//     uint8_t script_version /*= 5*/,
//     kth_transaction_t* out_transaction) {

//     auto p = kth::domain::wallet::tx_encode(
//                 kth_chain_point_list_const_cpp(outputs_to_spend),
//                 kth_wallet_raw_output_list_const_cpp(destiny_and_amount),
//                 kth_chain_output_list_const_cpp(extra_outputs),
//                 locktime,
//                 tx_version,
//                 script_version
//                );

//     if (p.first == kth::error::success) {
//         *out_transaction = new kth::domain::chain::transaction(std::move(p.second));
//     } else {
//         *out_transaction = nullptr;
//     }

//     return kth::to_c_err(p.first);
// }

// kth_error_code_t kth_wallet_tx_encode(
//     kth_point_list_t outputs_to_spend,
//     kth_raw_output_list_t destiny_and_amount,
//     uint32_t locktime /*= 0*/,
//     uint32_t tx_version /*= 1*/,
//     uint8_t script_version /*= 5*/,
//     kth_transaction_t* out_transaction) {

//     auto p = kth::domain::wallet::tx_encode(
//                 kth_chain_point_list_const_cpp(outputs_to_spend),
//                 kth_wallet_raw_output_list_const_cpp(destiny_and_amount),
//                 locktime,
//                 tx_version,
//                 script_version
//                );

//     if (p.first == kth::error::success) {
//         *out_transaction = new kth::domain::chain::transaction(std::move(p.second));
//     } else {
//         *out_transaction = nullptr;
//     }

//     return kth::to_c_err(p.first);
// }

// kth_error_code_t input_signature_old(
//     kth_ec_secret_t private_key,    /*32 element byte array*/
//     kth_script_t output_script,
//     kth_transaction_t tx,
//     uint32_t index,
//     uint8_t sign_type /*= 0x01*/,
//     kth_bool_t anyone_can_pay /*= false*/,
//     uint8_t** out_signature,
//     kth_size_t* out_signature_size) {

//     auto p = kth::domain::wallet::input_signature_old(
//         kth::to_array(private_key.hash),
//         kth_chain_script_const_cpp(output_script),
//         kth_chain_transaction_const_cpp(tx),
//         index,
//         sign_type,
//         kth::int_to_bool(anyone_can_pay)
//     );

//     if (p.first == kth::error::success) {
//         *out_signature = kth::create_c_array(p.second, *out_signature_size);
//     } else {
//         *out_signature_size = 0;
//         *out_signature = nullptr;
//     }

//     return kth::to_c_err(p.first);
// }

// kth_error_code_t input_signature_btc(
//     kth_ec_secret_t private_key,    /*32 element byte array*/
//     kth_script_t output_script,
//     kth_transaction_t tx,
//     uint64_t amount,
//     uint32_t index,
//     uint8_t sign_type /*= 0x01*/,
//     kth_bool_t anyone_can_pay /*= false*/,
//     uint8_t** out_signature,
//     kth_size_t* out_signature_size) {

//     auto p = kth::domain::wallet::input_signature_btc(
//         kth::to_array(private_key.hash),
//         kth_chain_script_const_cpp(output_script),
//         kth_chain_transaction_const_cpp(tx),
//         amount,
//         index,
//         sign_type,
//         kth::int_to_bool(anyone_can_pay)
//     );

//     if (p.first == kth::error::success) {
//         *out_signature = kth::create_c_array(p.second, *out_signature_size);
//     } else {
//         *out_signature_size = 0;
//         *out_signature = nullptr;
//     }

//     return kth::to_c_err(p.first);
// }

// kth_error_code_t input_signature_bch(
//     kth_ec_secret_t private_key,    /*32 element byte array*/
//     kth_script_t output_script,
//     kth_transaction_t tx,
//     uint64_t amount,
//     uint32_t index,
//     uint8_t sign_type /*= 0x01*/,
//     kth_bool_t anyone_can_pay /*= false*/,
//     uint8_t** out_signature,
//     kth_size_t* out_signature_size) {

//     auto p = kth::domain::wallet::input_signature_bch(
//         kth::to_array(private_key.hash),
//         kth_chain_script_const_cpp(output_script),
//         kth_chain_transaction_const_cpp(tx),
//         amount,
//         index,
//         sign_type,
//         kth::int_to_bool(anyone_can_pay)
//     );

//     if (p.first == kth::error::success) {
//         *out_signature = kth::create_c_array(p.second, *out_signature_size);
//     } else {
//         *out_signature_size = 0;
//         *out_signature = nullptr;
//     }

//     return kth::to_c_err(p.first);
// }

// kth_error_code_t input_set_script(
//     kth_script_t script,
//     kth_transaction_t tx,
//     uint32_t index /*= 0*/,
//     kth_transaction_t* out_transaction) {

//     auto p = kth::domain::wallet::input_set(
//                 kth_chain_script_const_cpp(script),
//                 kth_chain_transaction_const_cpp(tx),
//                 index
//                );

//     if (p.first == kth::error::success) {
//         *out_transaction = new kth::domain::chain::transaction(std::move(p.second));
//     } else {
//         *out_transaction = nullptr;
//     }

//     return kth::to_c_err(p.first);
// }

// // kth_error_code_t input_set_signature(
// //     uint8_t* signature,
// //     kth_size_t signature_n,
// //     kth_ec_public_t public_key,
// //     kth_transaction_t tx,
// //     uint32_t index /*= 0*/,
// //     kth_transaction_t* out_transaction) {

// //     kth::data_chunk signature_cpp(signature, std::next(signature, signature_n));

// //     auto p = kth::domain::wallet::input_set(
// //                 signature_cpp,
// //                 kth_wallet_ec_public_const_cpp(public_key),
// //                 kth_chain_transaction_const_cpp(tx),
// //                 index
// //                );

// //     if (p.first == kth::error::success) {
// //         *out_transaction = new kth::domain::chain::transaction(std::move(p.second));
// //     } else {
// //         *out_transaction = nullptr;
// //     }

// //     return kth::to_c_err(p.first);
// // }



// // BC_API std::pair<error::kth_error_code_t, chain::transaction> input_set(data_chunk const& signature,
// //                                                                     wallet::ec_public const& public_key,
// //                                                                     chain::transaction const& tx,
// //                                                                      uint32_t index = 0);


// } // extern "C"
