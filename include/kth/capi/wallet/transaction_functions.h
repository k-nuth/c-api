// // Copyright (c) 2016-2023 Knuth Project developers.
// // Distributed under the MIT software license, see the accompanying
// // file COPYING or http://www.opensource.org/licenses/mit-license.php.

// #ifndef KTH_CAPI_WALLET_TRANSACTION_FUNCTIONS_H_
// #define KTH_CAPI_WALLET_TRANSACTION_FUNCTIONS_H_

// #include <kth/capi/primitives.h>
// #include <kth/capi/visibility.h>

// #ifdef __cplusplus
// extern "C" {
// #endif

// // KTH_EXPORT
// // kth_longhash_t kth_wallet_mnemonics_to_seed(kth_string_list_t mnemonics);


// KTH_EXPORT
// kth_error_code_t kth_wallet_tx_encode_with_extra_outputs(
//     kth_point_list_t outputs_to_spend,
//     kth_raw_output_list_t destiny_and_amount,
//     kth_output_list_t extra_outputs,
//     uint32_t locktime /*= 0*/,
//     uint32_t tx_version /*= 1*/,
//     uint8_t script_version /*= 5*/,
//    kth_transaction_t* out_transaction);

// KTH_EXPORT
// kth_error_code_t kth_wallet_tx_encode(
//     kth_point_list_t outputs_to_spend,
//     kth_raw_output_list_t destiny_and_amount,
//     uint32_t locktime /*= 0*/,
//     uint32_t tx_version /*= 1*/,
//     uint8_t script_version /*= 5*/,
//    kth_transaction_t* out_transaction);

// KTH_EXPORT
// kth_error_code_t input_signature_old(
//     kth_ec_secret_t private_key,
//     kth_script_t output_script,
//    kth_transaction_t tx,
//     uint32_t index,
//     uint8_t sign_type /*= 0x01*/,
//     kth_bool_t anyone_can_pay /*= false*/,
//     uint8_t** out_signature,
//     kth_size_t* out_signature_size);

// KTH_EXPORT
// kth_error_code_t input_signature_btc(
//     kth_ec_secret_t private_key,
//     kth_script_t output_script,
//    kth_transaction_t tx,
//     uint64_t amount,
//     uint32_t index,
//     uint8_t sign_type /*= 0x01*/,
//     kth_bool_t anyone_can_pay /*= false*/,
//     uint8_t** out_signature,
//     kth_size_t* out_signature_size);

// KTH_EXPORT
// kth_error_code_t input_signature_bch(
//     kth_ec_secret_t private_key,
//     kth_script_t output_script,
//    kth_transaction_t tx,
//     uint64_t amount,
//     uint32_t index,
//     uint8_t sign_type /*= 0x01*/,
//     kth_bool_t anyone_can_pay /*= false*/,
//     uint8_t** out_signature,
//     kth_size_t* out_signature_size);

// KTH_EXPORT
// kth_error_code_t input_set(
//     kth_script_t script,
//    kth_transaction_t tx,
//     uint32_t index /*= 0*/,
//    kth_transaction_t* out_transaction);

// #ifdef __cplusplus
// } // extern "C"
// #endif

// #endif /* KTH_CAPI_WALLET_TRANSACTION_FUNCTIONS_H_ */
