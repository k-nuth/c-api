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

#include <bitprim/nodecint/block.h>
#include <bitcoin/bitcoin/message/block.hpp>
#include <bitcoin/bitcoin/message/transaction.hpp>
//#include <memory>
//#include <boost/iostreams/device/file_descriptor.hpp>
//#include <bitprim/nodecint/executor.hpp>
// #include <inttypes.h>   //TODO: Remove, it is for the printf (printing pointer addresses)

extern "C" {

void block_destruct(block_t block) {
    auto block_cpp = static_cast<libbitcoin::message::block*>(block);
    delete block_cpp;
}

int block_is_valid(block_t block) {
    return static_cast<libbitcoin::message::block const*>(block)->is_valid();
}

header_t block_header(block_t block) {
    auto& header = static_cast<libbitcoin::message::block*>(block)->header();
    return &header;
}

hash_t block_hash(block_t block) {
    auto hash_cpp = static_cast<libbitcoin::message::block const*>(block)->hash();
    return hash_cpp.data();
}

size_t block_transaction_count(block_t block) {
    return static_cast<libbitcoin::message::block const*>(block)->transactions().size();
}

transaction_t block_transactions(block_t block, size_t* n) {
    auto* block_cpp = static_cast<libbitcoin::message::block*>(block);
    *n = block_cpp->transactions().size();
    return block_cpp->transactions().data();
}

transaction_t block_transaction_next(transaction_t transaction) {
    auto* transaction_cpp = static_cast<libbitcoin::message::transaction*>(transaction);
    ++transaction_cpp;
    return transaction_cpp;
}

transaction_t block_transaction_nth(block_t block, size_t n) {
    //precondition: n >=0 && n < transactions().size()

    auto* block_cpp = static_cast<libbitcoin::message::block*>(block);
    auto& tx_n = block_cpp->transactions()[n];
    return &tx_n;
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
//size_t serialized_size() const;
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
//static uint64_t subsidy(size_t height);
//static uint256_t proof(uint32_t bits);
//
//uint64_t fees() const;
//uint64_t claim() const;
//uint64_t reward(size_t height) const;
//uint256_t proof() const;
//hash_digest generate_merkle_root() const;
//size_t signature_operations() const;
//size_t signature_operations(bool bip16_active) const;
//size_t total_inputs(bool with_coinbase=true) const;
//
//bool is_extra_coinbases() const;
//bool is_final(size_t height) const;
//bool is_distinct_transaction_set() const;
//bool is_valid_coinbase_claim(size_t height) const;
//bool is_valid_coinbase_script(size_t height) const;
//bool is_internal_double_spend() const;
//bool is_valid_merkle_root() const;
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
