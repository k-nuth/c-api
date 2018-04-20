/**
 * Copyright (c) 2017 Bitprim developers (see AUTHORS)
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

#ifndef BITPRIM_NODECINT_CHAIN_TRANSACTIONV2_H_
#define BITPRIM_NODECINT_CHAIN_TRANSACTIONV2_H_

#include <stdio.h>
#include <stdint.h>

#include <bitprim/nodecint/visibility.h>
#include <bitprim/nodecint/primitives.h>


#ifdef __cplusplus
extern "C" {
#endif

BITPRIM_EXPORT
transactionv2_t chain_transactionv2_factory_from_data(uint32_t version, uint8_t* data, uint64_t n);

//transaction(void);
BITPRIM_EXPORT
transactionv2_t chain_transactionv2_construct_default(void);

//transaction(uint32_t version, uint32_t locktime, chain::input::list&& inputs, chain::output::list&& outputs);
//transaction(uint32_t version, uint32_t locktime, const chain::input::list& inputs, const chain::output::list& outputs);
// BITPRIM_EXPORT
// transactionv2_t chain_transactionv2_construct(uint32_t version, uint32_t locktime, input_list_t inputs, output_list_t outputs);

BITPRIM_EXPORT
void chain_transactionv2_destruct(transactionv2_t transaction);

BITPRIM_EXPORT
int chain_transactionv2_is_valid(transactionv2_t transaction);

BITPRIM_EXPORT
uint32_t chain_transactionv2_version(transactionv2_t transaction);

BITPRIM_EXPORT
void chain_transactionv2_set_version(transactionv2_t transaction, uint32_t version);

BITPRIM_EXPORT
hash_t chain_transactionv2_hash(transactionv2_t transaction);

BITPRIM_EXPORT
void chain_transactionv2_hash_out(transactionv2_t transaction, hash_t* out_hash);

BITPRIM_EXPORT
hash_t chain_transactionv2_hash_sighash_type(transactionv2_t transaction, uint32_t sighash_type);

BITPRIM_EXPORT
void chain_transactionv2_hash_sighash_type_out(transactionv2_t transaction, uint32_t sighash_type, hash_t* out_hash);

BITPRIM_EXPORT
uint32_t chain_transactionv2_locktime(transactionv2_t transaction);

BITPRIM_EXPORT
uint64_t /*size_t*/ chain_transactionv2_serialized_size(transactionv2_t transaction, int wire /*= true*/);

BITPRIM_EXPORT
uint64_t chain_transactionv2_fees(transactionv2_t transaction);

// BITPRIM_EXPORT
// uint64_t /*size_t*/ chain_transactionv2_signature_operations(transactionv2_t transaction);

BITPRIM_EXPORT
uint64_t /*size_t*/ chain_transactionv2_signature_operations_bip16_active(transactionv2_t transaction, int /*bool*/ bip16_active);

BITPRIM_EXPORT
uint64_t chain_transactionv2_total_input_value(transactionv2_t transaction);

BITPRIM_EXPORT
uint64_t chain_transactionv2_total_output_value(transactionv2_t transaction);

BITPRIM_EXPORT
int /*bool*/ chain_transactionv2_is_coinbase(transactionv2_t transaction);

BITPRIM_EXPORT
int /*bool*/ chain_transactionv2_is_null_non_coinbase(transactionv2_t transaction);

BITPRIM_EXPORT
int /*bool*/ chain_transactionv2_is_oversized_coinbase(transactionv2_t transaction);

BITPRIM_EXPORT
int /*bool*/ chain_transactionv2_is_mature(transactionv2_t transaction, uint64_t /*size_t*/ target_height);

BITPRIM_EXPORT
int /*bool*/ chain_transactionv2_is_overspent(transactionv2_t transaction);

BITPRIM_EXPORT
int /*bool*/ chain_transactionv2_is_double_spend(transactionv2_t transaction, int /*bool*/ include_unconfirmed);

BITPRIM_EXPORT
int /*bool*/ chain_transactionv2_is_missing_previous_outputs(transactionv2_t transaction);

BITPRIM_EXPORT
int /*bool*/ chain_transactionv2_is_final(transactionv2_t transaction, uint64_t /*size_t*/ block_height, uint32_t block_time);

BITPRIM_EXPORT
int /*bool*/ chain_transactionv2_is_locktime_conflict(transactionv2_t transaction);

BITPRIM_EXPORT
output_list_t chain_transactionv2_outputs(transactionv2_t transaction);

BITPRIM_EXPORT
input_list_t chain_transactionv2_inputs(transactionv2_t transaction);

BITPRIM_EXPORT
uint8_t const* chain_transactionv2_to_data(transactionv2_t script, int /*bool*/ wire, uint64_t* /*size_t*/ out_size);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* BITPRIM_NODECINT_CHAIN_TRANSACTIONV2_H_ */
