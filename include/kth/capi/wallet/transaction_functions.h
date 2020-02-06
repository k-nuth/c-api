// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#ifndef KTH_CAPI_WALLET_TRANSACTION_FUNCTIONS_H_
#define KTH_CAPI_WALLET_TRANSACTION_FUNCTIONS_H_

#include <kth/capi/primitives.h>
#include <kth/capi/visibility.h>

#ifdef __cplusplus
extern "C" {
#endif

// KTH_EXPORT
// long_hash_t wallet_mnemonics_to_seed(word_list_t mnemonics);


KTH_EXPORT
error_code_t wallet_tx_encode_with_extra_outputs(
    point_list_t outputs_to_spend,
    raw_output_list_t destiny_and_amount,
    output_list_t extra_outputs,
    uint32_t locktime /*= 0*/,
    uint32_t tx_version /*= 1*/,
    uint8_t script_version /*= 5*/,
    transaction_t* out_transaction);

KTH_EXPORT
error_code_t wallet_tx_encode(
    point_list_t outputs_to_spend,
    raw_output_list_t destiny_and_amount,
    uint32_t locktime /*= 0*/,
    uint32_t tx_version /*= 1*/,
    uint8_t script_version /*= 5*/,
    transaction_t* out_transaction);

KTH_EXPORT
error_code_t input_signature_old(
    ec_secret_t private_key,
    script_t output_script,
    transaction_t tx,
    uint32_t index,
    uint8_t sign_type /*= 0x01*/,
    bool_t anyone_can_pay /*= false*/,
    uint8_t** out_signature,
    uint64_t* /*size_t*/ out_signature_size);

KTH_EXPORT
error_code_t input_signature_btc(
    ec_secret_t private_key,
    script_t output_script,
    transaction_t tx,
    uint64_t amount,
    uint32_t index,
    uint8_t sign_type /*= 0x01*/,
    bool_t anyone_can_pay /*= false*/,
    uint8_t** out_signature,
    uint64_t* /*size_t*/ out_signature_size);

KTH_EXPORT
error_code_t input_signature_bch(
    ec_secret_t private_key,
    script_t output_script,
    transaction_t tx,
    uint64_t amount,
    uint32_t index,
    uint8_t sign_type /*= 0x01*/,
    bool_t anyone_can_pay /*= false*/,
    uint8_t** out_signature,
    uint64_t* /*size_t*/ out_signature_size);

KTH_EXPORT
error_code_t input_set(
    script_t script,
    transaction_t tx,
    uint32_t index /*= 0*/,
    transaction_t* out_transaction);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* KTH_CAPI_WALLET_TRANSACTION_FUNCTIONS_H_ */
