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

libbitcoin::message::merkle_block const& merkle_block_const_cpp(merkle_block_t block) {
    return *static_cast<libbitcoin::message::merkle_block const*>(block);
}

libbitcoin::message::merkle_block& merkle_block_cpp(merkle_block_t block) {
    return *static_cast<libbitcoin::message::merkle_block*>(block);
}

extern "C" {

hash_t merkle_block_hash_nth(merkle_block_t block, size_t n) {
    //precondition: n >=0 && n < hashes().size()

    auto* blk = &merkle_block_cpp(block);
    auto& hash_n = blk->hashes()[n];
    return &hash_n;
}

header_t merkle_block_header(merkle_block_t block) {
    return &merkle_block_cpp(block).header();
}

int merkle_block_is_valid(merkle_block_t block) {
    return merkle_block_const_cpp(block).is_valid();
}

size_t merkle_block_hash_count(merkle_block_t block) {
    return merkle_block_const_cpp(block).hashes().size();
}

size_t merkle_block_serialized_size(merkle_block_t block, uint32_t version) {
    return merkle_block_const_cpp(block).serialized_size(version);
}

size_t merkle_block_total_transaction_count(merkle_block_t block){
    return merkle_block_const_cpp(block).total_transactions();
}

void merkle_block_destruct(merkle_block_t block) {
    delete &merkle_block_cpp(block);
}

void merkle_block_reset(merkle_block_t block){
    merkle_block_cpp(block).reset();
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
