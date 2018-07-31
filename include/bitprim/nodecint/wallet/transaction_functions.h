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

#ifndef BITPRIM_NODECINT_WALLET_TRANSACTION_FUNCTIONS_H_
#define BITPRIM_NODECINT_WALLET_TRANSACTION_FUNCTIONS_H_

#include <bitprim/nodecint/primitives.h>
#include <bitprim/nodecint/visibility.h>

#ifdef __cplusplus
extern "C" {
#endif

// BITPRIM_EXPORT
// long_hash_t wallet_mnemonics_to_seed(word_list_t mnemonics);


BITPRIM_EXPORT
error_code_t wallet_tx_encode_with_extra_outputs(
    point_list_t outputs_to_spend,
    raw_output_list_t destiny_and_amount,
    output_list_t extra_outputs,
    uint32_t locktime /*= 0*/,
    uint32_t tx_version /*= 1*/,
    uint8_t script_version /*= 5*/,
    transaction_t* out_transaction);

BITPRIM_EXPORT
error_code_t wallet_tx_encode(
    point_list_t outputs_to_spend,
    raw_output_list_t destiny_and_amount,
    uint32_t locktime /*= 0*/,
    uint32_t tx_version /*= 1*/,
    uint8_t script_version /*= 5*/,
    transaction_t* out_transaction);

BITPRIM_EXPORT
error_code_t input_signature_old(
    ec_secret_t private_key,
    script_t output_script,
    transaction_t tx,
    uint32_t index,
    uint8_t sign_type /*= 0x01*/,
    bool_t anyone_can_pay /*= false*/,
    uint8_t** out_signature,
    uint64_t* /*size_t*/ out_signature_size);

BITPRIM_EXPORT
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

BITPRIM_EXPORT
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

BITPRIM_EXPORT
error_code_t input_set(
    script_t script,
    transaction_t tx,
    uint32_t index /*= 0*/,
    transaction_t* out_transaction);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* BITPRIM_NODECINT_WALLET_TRANSACTION_FUNCTIONS_H_ */
