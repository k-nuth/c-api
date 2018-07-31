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

#include <bitprim/nodecint/chain/transaction.h>

#include <bitprim/nodecint/chain/input_list.h>
#include <bitprim/nodecint/chain/output_list.h>
#include <bitprim/nodecint/convertions.hpp>
#include <bitprim/nodecint/helpers.hpp>

libbitcoin::message::transaction const& chain_transaction_const_cpp(transaction_t transaction) {
    return *static_cast<libbitcoin::message::transaction const*>(transaction);
}

libbitcoin::message::transaction& chain_transaction_cpp(transaction_t transaction) {
    return *static_cast<libbitcoin::message::transaction*>(transaction);
}


// ---------------------------------------------------------------------------
extern "C" {

transaction_t chain_transaction_factory_from_data(uint32_t version, uint8_t* data, uint64_t n) {
    libbitcoin::data_chunk data_cpp(data, std::next(data, n));
    auto tx = libbitcoin::message::transaction::factory_from_data(version, data_cpp);
    // return new libbitcoin::message::transaction(std::move(tx));
    return bitprim::move_or_copy_and_leak(std::move(tx));
}

transaction_t chain_transaction_construct_default() {
    return new libbitcoin::message::transaction();
}

transaction_t chain_transaction_construct(uint32_t version, uint32_t locktime, input_list_t inputs, output_list_t outputs) {
    return new libbitcoin::message::transaction(version, locktime,
                                                chain_input_list_const_cpp(inputs),
                                                chain_output_list_const_cpp(outputs));
}

void chain_transaction_destruct(transaction_t transaction) {
    auto transaction_cpp = static_cast<libbitcoin::message::transaction*>(transaction);
    delete transaction_cpp;
}

bool_t chain_transaction_is_valid(transaction_t transaction) {
    return static_cast<int>(chain_transaction_const_cpp(transaction).is_valid());
}

uint32_t chain_transaction_version(transaction_t transaction) {
    return chain_transaction_const_cpp(transaction).version();
}

void chain_transaction_set_version(transaction_t transaction, uint32_t version) {
    return static_cast<libbitcoin::message::transaction*>(transaction)->set_version(version);
}

hash_t chain_transaction_hash(transaction_t transaction) {
    auto const& hash_cpp = chain_transaction_const_cpp(transaction).hash();
    return bitprim::to_hash_t(hash_cpp);
}

void chain_transaction_hash_out(transaction_t transaction, hash_t* out_hash) {
    auto const& hash_cpp = chain_transaction_const_cpp(transaction).hash();
    bitprim::copy_c_hash(hash_cpp, out_hash);
}

hash_t chain_transaction_hash_sighash_type(transaction_t transaction, uint32_t sighash_type) {
    auto const& hash_cpp = chain_transaction_const_cpp(transaction).hash(sighash_type != 0u);
    return bitprim::to_hash_t(hash_cpp);
}

void chain_transaction_hash_sighash_type_out(transaction_t transaction, uint32_t sighash_type, hash_t* out_hash) {
    auto const& hash_cpp = chain_transaction_const_cpp(transaction).hash(sighash_type != 0u);
    bitprim::copy_c_hash(hash_cpp, out_hash);
}

uint32_t chain_transaction_locktime(transaction_t transaction) {
    return chain_transaction_const_cpp(transaction).locktime();
}

uint64_t /*size_t*/ chain_transaction_serialized_size(transaction_t transaction, int wire /*= true*/) {
    return chain_transaction_const_cpp(transaction).serialized_size(wire);
}

uint64_t chain_transaction_fees(transaction_t transaction) {
    return chain_transaction_const_cpp(transaction).fees();
}

uint64_t /*size_t*/ chain_transaction_signature_operations(transaction_t transaction) {
    return chain_transaction_const_cpp(transaction).signature_operations();
}

uint64_t /*size_t*/ chain_transaction_signature_operations_bip16_active(transaction_t transaction, bool_t bip16_active) {
#ifdef BITPRIM_CURRENCY_BCH
    bool_t bip141_active = 0;
#else
    bool_t bip141_active = 1;
#endif
    return chain_transaction_const_cpp(transaction).signature_operations(bitprim::int_to_bool(bip16_active), bitprim::int_to_bool(bip141_active));
}

uint64_t chain_transaction_total_input_value(transaction_t transaction) {
    return chain_transaction_const_cpp(transaction).total_input_value();
}

uint64_t chain_transaction_total_output_value(transaction_t transaction) {
    return chain_transaction_const_cpp(transaction).total_output_value();
}

bool_t chain_transaction_is_coinbase(transaction_t transaction) {
    return static_cast<int>(chain_transaction_const_cpp(transaction).is_coinbase());
}

bool_t chain_transaction_is_null_non_coinbase(transaction_t transaction) {
    return static_cast<int>(chain_transaction_const_cpp(transaction).is_null_non_coinbase());
}

bool_t chain_transaction_is_oversized_coinbase(transaction_t transaction) {
    return static_cast<int>(chain_transaction_const_cpp(transaction).is_oversized_coinbase());
}

bool_t chain_transaction_is_mature(transaction_t transaction, uint64_t /*size_t*/ target_height) {
    return static_cast<int>(chain_transaction_const_cpp(transaction).is_mature(target_height));
}

bool_t chain_transaction_is_overspent(transaction_t transaction) {
    return static_cast<int>(chain_transaction_const_cpp(transaction).is_overspent());
}

bool_t chain_transaction_is_double_spend(transaction_t transaction, bool_t include_unconfirmed) {
    return static_cast<int>(chain_transaction_const_cpp(transaction).is_double_spend(bitprim::int_to_bool(include_unconfirmed)));
}

bool_t chain_transaction_is_missing_previous_outputs(transaction_t transaction) {
    return static_cast<int>(chain_transaction_const_cpp(transaction).is_missing_previous_outputs());
}

bool_t chain_transaction_is_final(transaction_t transaction, uint64_t /*size_t*/ block_height, uint32_t block_time) {
    return static_cast<int>(chain_transaction_const_cpp(transaction).is_final(block_height, block_time));
}

bool_t chain_transaction_is_locktime_conflict(transaction_t transaction) {
    return static_cast<int>(chain_transaction_const_cpp(transaction).is_locktime_conflict());
}

output_list_t chain_transaction_outputs(transaction_t transaction) {
    auto& tx = chain_transaction_cpp(transaction);
    return chain_output_list_construct_from_cpp(tx.outputs()); // TODO(fernando): transaction::outputs() is deprecated... check how to do it better...
}

input_list_t chain_transaction_inputs(transaction_t transaction) {
    auto& tx = chain_transaction_cpp(transaction);
    return chain_input_list_construct_from_cpp(tx.inputs()); // TODO(fernando): transaction::inputs() is deprecated... check how to do it better...
}

uint8_t* chain_transaction_to_data(transaction_t transaction, bool_t wire, uint64_t* /*size_t*/ out_size) {
    auto tx_data = chain_transaction_const_cpp(transaction).to_data(wire);
    return bitprim::create_c_array(tx_data, *out_size);
}

} // extern "C"
