/**
 * Copyright (c) 2017-2018 Bitprim Inc.
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


extern "C" {

transaction_t chain_transaction_factory_from_data(uint32_t version, uint8_t* data, uint64_t n) {
    libbitcoin::data_chunk data_cpp(data, std::next(data, n));
    auto tx = libbitcoin::message::transaction::factory_from_data(version, data_cpp);
    return new libbitcoin::message::transaction(std::move(tx));
}

//transaction();
transaction_t chain_transaction_construct_default() {
    return new libbitcoin::message::transaction();
}

//transaction(uint32_t version, uint32_t locktime, chain::input::list&& inputs, chain::output::list&& outputs);
//transaction(uint32_t version, uint32_t locktime, const chain::input::list& inputs, const chain::output::list& outputs);
transaction_t chain_transaction_construct(uint32_t version, uint32_t locktime, input_list_t inputs, output_list_t outputs) {
    return new libbitcoin::message::transaction(version, locktime,
                                                chain_input_list_const_cpp(inputs),
                                                chain_output_list_const_cpp(outputs));
}

void chain_transaction_destruct(transaction_t transaction) {
    auto transaction_cpp = static_cast<libbitcoin::message::transaction*>(transaction);
    delete transaction_cpp;
}

int /*bool*/ chain_transaction_is_valid(transaction_t transaction) {
    return static_cast<int>(chain_transaction_const_cpp(transaction).is_valid());
}

uint32_t chain_transaction_version(transaction_t transaction) {
    return chain_transaction_const_cpp(transaction).version();
}

void chain_transaction_set_version(transaction_t transaction, uint32_t version) {
    return static_cast<libbitcoin::message::transaction*>(transaction)->set_version(version);
}

//hash_t chain_transaction_hash(transaction_t transaction) {
//    auto const& hash_cpp = chain_transaction_const_cpp(transaction).hash();
//    return hash_cpp.data(); //TODO: returning a dangling pointer
//}
//
//hash_t chain_transaction_hash_sighash_type(transaction_t transaction, uint32_t sighash_type) {
//    auto const& hash_cpp = chain_transaction_const_cpp(transaction).hash(sighash_type);
//    return hash_cpp.data(); //TODO: returning a dangling pointer
//}

hash_t chain_transaction_hash(transaction_t transaction) {
    auto const& hash_cpp = chain_transaction_const_cpp(transaction).hash();
    return bitprim::to_hash_t(hash_cpp);
}

void chain_transaction_hash_out(transaction_t transaction, hash_t* out_hash) {
    auto const& hash_cpp = chain_transaction_const_cpp(transaction).hash();
    std::memcpy(static_cast<void*>(out_hash->hash), hash_cpp.data(), BITCOIN_HASH_SIZE);
}

hash_t chain_transaction_hash_sighash_type(transaction_t transaction, uint32_t sighash_type) {
    auto const& hash_cpp = chain_transaction_const_cpp(transaction).hash(sighash_type);
    return bitprim::to_hash_t(hash_cpp);
}

void chain_transaction_hash_sighash_type_out(transaction_t transaction, uint32_t sighash_type, hash_t* out_hash) {
    auto const& hash_cpp = chain_transaction_const_cpp(transaction).hash(sighash_type);
    std::memcpy(static_cast<void*>(out_hash->hash), hash_cpp.data(), BITCOIN_HASH_SIZE);
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

uint64_t /*size_t*/ chain_transaction_signature_operations_bip16_active(transaction_t transaction, int /*bool*/ bip16_active) {
#ifdef BITPRIM_CURRENCY_BCH
    int /*bool*/ bip141_active = 0;
#else
    int /*bool*/ bip141_active = 1;
#endif
    return chain_transaction_const_cpp(transaction).signature_operations(bip16_active != 0, bip141_active != 0);
}

uint64_t chain_transaction_total_input_value(transaction_t transaction) {
    return chain_transaction_const_cpp(transaction).total_input_value();
}

uint64_t chain_transaction_total_output_value(transaction_t transaction) {
    return chain_transaction_const_cpp(transaction).total_output_value();
}

int /*bool*/ chain_transaction_is_coinbase(transaction_t transaction) {
    return static_cast<int>(chain_transaction_const_cpp(transaction).is_coinbase());
}

int /*bool*/ chain_transaction_is_null_non_coinbase(transaction_t transaction) {
    return static_cast<int>(chain_transaction_const_cpp(transaction).is_null_non_coinbase());
}

int /*bool*/ chain_transaction_is_oversized_coinbase(transaction_t transaction) {
    return static_cast<int>(chain_transaction_const_cpp(transaction).is_oversized_coinbase());
}

int /*bool*/ chain_transaction_is_mature(transaction_t transaction, uint64_t /*size_t*/ target_height) {
    return static_cast<int>(chain_transaction_const_cpp(transaction).is_mature(target_height));
}

int /*bool*/ chain_transaction_is_overspent(transaction_t transaction) {
    return static_cast<int>(chain_transaction_const_cpp(transaction).is_overspent());
}

int /*bool*/ chain_transaction_is_double_spend(transaction_t transaction, int /*bool*/ include_unconfirmed) {
    return static_cast<int>(chain_transaction_const_cpp(transaction).is_double_spend(include_unconfirmed != 0));
}

int /*bool*/ chain_transaction_is_missing_previous_outputs(transaction_t transaction) {
    return static_cast<int>(chain_transaction_const_cpp(transaction).is_missing_previous_outputs());
}

int /*bool*/ chain_transaction_is_final(transaction_t transaction, uint64_t /*size_t*/ block_height, uint32_t block_time) {
    return static_cast<int>(chain_transaction_const_cpp(transaction).is_final(block_height, block_time));
}

int /*bool*/ chain_transaction_is_locktime_conflict(transaction_t transaction) {
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

uint8_t* chain_transaction_to_data(transaction_t transaction, int /*bool*/ wire, uint64_t* /*size_t*/ out_size) {
    auto tx_data = chain_transaction_const_cpp(transaction).to_data(wire);
    auto* ret = (uint8_t*)malloc((tx_data.size()) * sizeof(uint8_t)); // NOLINT
    std::copy_n(tx_data.begin(), tx_data.size(), ret);
    *out_size = tx_data.size();
    return ret;
}

//
//// Serialization.
////-----------------------------------------------------------------------------
//
//data_chunk to_data(bool wire=true) const;
//void to_data(std::ostream& stream, bool wire=true) const;
//void to_data(writer& sink, bool wire=true) const;
//
//// Properties (size, accessors, cache).
////-----------------------------------------------------------------------------
//
//void set_locktime(uint32_t value);
//
//void set_inputs(const ins& value);
//void set_inputs(ins&& value);
//
//void set_outputs(const outs& value);
//void set_outputs(outs&& value);
//
//hash_digest hash(uint32_t sighash_type) const;
//
//void recompute_hash();
//
//// Validation.
////-----------------------------------------------------------------------------
//
//output_point::list missing_previous_outputs() const;
//hash_list missing_previous_transactions() const;
//

//code check(bool transaction_pool=true) const;
//code accept(bool transaction_pool=true) const;
//code accept(const chain_state& state, bool transaction_pool=true) const;
//code connect() const;
//code connect(const chain_state& state) const;
//code connect_input(const chain_state& state, size_t input_index) const;


} /* extern "C" */
