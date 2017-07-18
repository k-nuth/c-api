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

#include <bitprim/nodecint/chain/block.h>
#include <bitcoin/bitcoin/message/block.hpp>
#include <bitcoin/bitcoin/message/transaction.hpp>

libbitcoin::message::block const& block_const_cpp(block_t block) {
    return *static_cast<libbitcoin::message::block const*>(block);
}

libbitcoin::message::block& block_cpp(block_t block) {
    return *static_cast<libbitcoin::message::block*>(block);
}

extern "C" {

void block_destruct(block_t block) {
    delete &block_cpp(block);
}

int block_is_valid(block_t block) {
    return block_const_cpp(block).is_valid();
}

header_t block_header(block_t block) {
    return &block_cpp(block).header();
}

hash_t block_hash(block_t block) {
    auto const& hash_cpp = block_const_cpp(block).hash();
    return hash_cpp.data(); //TODO: returning a dangling pointer
}

uint64_t /*size_t*/ block_transaction_count(block_t block) {
    return block_const_cpp(block).transactions().size();
}

transaction_t block_transactions(block_t block, uint64_t /*size_t*/* n) {
    auto* blk = &block_cpp(block);
    *n = blk->transactions().size();
    return blk->transactions().data();
}

transaction_t block_transaction_next(transaction_t transaction) {
    auto* transaction_cpp = static_cast<libbitcoin::message::transaction*>(transaction);
    ++transaction_cpp;
    return transaction_cpp;
}

transaction_t block_transaction_nth(block_t block, uint64_t /*size_t*/ n) {
    //precondition: n >=0 && n < transactions().size()

    auto* blk = &block_cpp(block);
    auto& tx_n = blk->transactions()[n];
    return &tx_n;
}


// -----------------------

uint64_t /*size_t*/ block_serialized_size(block_t block, uint32_t version) {
    return block_const_cpp(block).serialized_size(version);
}

/*static*/
uint64_t block_subsidy(uint64_t /*size_t*/ height) {
    return libbitcoin::message::block::subsidy(height);
}

//static uint256_t block_proof(uint32_t bits) {}

///*static*/
//uint256_t block_proof(uint64_t /*size_t*/ height) {
//    return libbitcoin::message::block::proof(height);
//}

uint64_t block_fees(block_t block) {
    return block_const_cpp(block).fees();
}

uint64_t block_claim(block_t block) {
    return block_const_cpp(block).claim();
}

uint64_t block_reward(block_t block, uint64_t /*size_t*/ height) {
    return block_const_cpp(block).reward(height);
}

//uint256_t block_proof(block_t block) {}
//hash_digest block_generate_merkle_root(block_t block) {}

//Note: The user is responsible for the resource release
hash_t block_generate_merkle_root(block_t block) {
    auto hash_cpp = block_const_cpp(block).generate_merkle_root();
    uint8_t* ret = (uint8_t*)malloc(hash_cpp.size() * sizeof(uint8_t));
    std::copy_n(std::begin(hash_cpp), hash_cpp.size(), ret);
    return ret;
}

uint64_t /*size_t*/ block_signature_operations(block_t block) {
    return block_const_cpp(block).signature_operations();
}

uint64_t /*size_t*/ block_signature_operations_bip16_active(block_t block, int /*bool*/ bip16_active) {
    return block_const_cpp(block).signature_operations(bip16_active);
}

uint64_t /*size_t*/ block_total_inputs(block_t block, int /*bool*/ with_coinbase=true) {
    return block_const_cpp(block).total_inputs(with_coinbase);
}

int /*bool*/ block_is_extra_coinbases(block_t block) {
    return block_const_cpp(block).is_extra_coinbases();
}

int /*bool*/ block_is_final(block_t block, uint64_t /*size_t*/ height) {
    return block_const_cpp(block).is_final(height);
}

int /*bool*/ block_is_distinct_transaction_set(block_t block) {
    return block_const_cpp(block).is_distinct_transaction_set();
}

int /*bool*/ block_is_valid_coinbase_claim(block_t block, uint64_t /*size_t*/ height) {
    return block_const_cpp(block).is_valid_coinbase_claim(height);
}

int /*bool*/ block_is_valid_coinbase_script(block_t block, uint64_t /*size_t*/ height) {
    return block_const_cpp(block).is_valid_coinbase_script(height);
}

int /*bool*/ block_is_internal_double_spend(block_t block) {
    return block_const_cpp(block).is_internal_double_spend();
}

int /*bool*/ block_is_valid_merkle_root(block_t block) {
    return block_const_cpp(block).is_valid_merkle_root();
}



//
//bool from_data(const data_chunk& data);
//bool from_data(std::istream& stream);
//bool from_data(reader& source);
//
//
//// Serialization.
////-------------------------------------------------------------------------
//
//data_chunk to_data() const;
//void to_data(std::ostream& stream) const;
//void to_data(writer& sink) const;
//hash_list to_hashes() const;
//
//// Properties (size, accessors, cache).
////-------------------------------------------------------------------------
//
//void set_header(const chain::header& value);
//void set_header(chain::header&& value);
//
//void set_transactions(const transaction::list& value);
//void set_transactions(transaction::list&& value);
//
//

//// Validation.
////-------------------------------------------------------------------------
//
//static uint256_t proof(uint32_t bits);
//
//uint256_t proof() const;
//hash_digest generate_merkle_root() const;
//
//code check() const;
//code check_transactions() const;
//code accept(bool transactions=true) const;
//code accept(const chain_state& state, bool transactions=true) const;
//code accept_transactions(const chain_state& state) const;
//code connect() const;
//code connect(const chain_state& state) const;
//code connect_transactions(const chain_state& state) const;

} /* extern "C" */
