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

#include <bitprim/nodecint/transaction.h>
#include <bitcoin/bitcoin/message/transaction.hpp>

libbitcoin::message::transaction const& tx_const_cpp(transaction_t transaction) {
    return *static_cast<libbitcoin::message::transaction const*>(transaction);
}

libbitcoin::message::transaction& tx_cpp(transaction_t transaction) {
    return *static_cast<libbitcoin::message::transaction*>(transaction);
}

extern "C" {

void transaction_destruct(transaction_t transaction) {
    auto transaction_cpp = static_cast<libbitcoin::message::transaction*>(transaction);
    delete transaction_cpp;
}

int transaction_is_valid(transaction_t transaction) {
    return tx_const_cpp(transaction).is_valid();
}

uint32_t transaction_version(transaction_t transaction) {
    return tx_const_cpp(transaction).version();
}

void transaction_set_version(transaction_t transaction, uint32_t version) {
    return static_cast<libbitcoin::message::transaction*>(transaction)->set_version(version);
}

hash_t transaction_hash(transaction_t transaction) {
    auto hash_cpp = tx_const_cpp(transaction).hash();
    return hash_cpp.data();
}




uint32_t transaction_locktime(transaction_t transaction) {
    return tx_const_cpp(transaction).locktime();
}

size_t transaction_serialized_size(transaction_t transaction, int wire /*= true*/) {
    return tx_const_cpp(transaction).serialized_size(wire);
}

uint64_t transaction_fees(transaction_t transaction) {
    return tx_const_cpp(transaction).fees();
}

size_t transaction_signature_operations(transaction_t transaction) {
    return tx_const_cpp(transaction).signature_operations();
}

size_t transaction_signature_operations_bip16_active(transaction_t transaction, int /*bool*/ bip16_active) {
    return tx_const_cpp(transaction).signature_operations(bip16_active);
}

uint64_t transaction_total_input_value(transaction_t transaction) {
    return tx_const_cpp(transaction).total_input_value();
}

uint64_t transaction_total_output_value(transaction_t transaction) {
    return tx_const_cpp(transaction).total_output_value();
}

int /*bool*/ transaction_is_coinbase(transaction_t transaction) {
    return tx_const_cpp(transaction).is_coinbase();
}

int /*bool*/ transaction_is_null_non_coinbase(transaction_t transaction) {
    return tx_const_cpp(transaction).is_null_non_coinbase();
}

int /*bool*/ transaction_is_oversized_coinbase(transaction_t transaction) {
    return tx_const_cpp(transaction).is_oversized_coinbase();
}

int /*bool*/ transaction_is_immature(transaction_t transaction, size_t target_height) {
    return tx_const_cpp(transaction).is_immature(target_height);
}

int /*bool*/ transaction_is_overspent(transaction_t transaction) {
    return tx_const_cpp(transaction).is_overspent();
}

int /*bool*/ transaction_is_double_spend(transaction_t transaction, bool include_unconfirmed) {
    return tx_const_cpp(transaction).is_double_spend(include_unconfirmed);
}

int /*bool*/ transaction_is_missing_previous_outputs(transaction_t transaction) {
    return tx_const_cpp(transaction).is_missing_previous_outputs();
}

int /*bool*/ transaction_is_final(transaction_t transaction, size_t block_height, uint32_t block_time) {
    return tx_const_cpp(transaction).is_final(block_height, block_time);
}

int /*bool*/ transaction_is_locktime_conflict(transaction_t transaction) {
    return tx_const_cpp(transaction).is_locktime_conflict();
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
//const input::list& inputs() const;
//void set_inputs(const ins& value);
//void set_inputs(ins&& value);
//
//const outs& outputs() const;
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
