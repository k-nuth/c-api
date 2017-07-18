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

#include <bitprim/nodecint/chain/header.h>
#include <bitcoin/bitcoin/message/header.hpp>

extern "C" {

void header_destruct(header_t header) {
    auto header_cpp = static_cast<libbitcoin::message::header*>(header);
    delete header_cpp;
}

int header_is_valid(header_t header) {
    return static_cast<libbitcoin::message::header const*>(header)->is_valid();
}

uint32_t header_version(header_t header) {
    return static_cast<libbitcoin::message::header const*>(header)->version();
}

void header_set_version(header_t header, uint32_t version) {
    return static_cast<libbitcoin::message::header*>(header)->set_version(version);
}

uint32_t header_timestamp(header_t header) {
    return static_cast<libbitcoin::message::header const*>(header)->timestamp();
}

void header_set_timestamp(header_t header, uint32_t timestamp) {
    return static_cast<libbitcoin::message::header*>(header)->set_timestamp(timestamp);
}

uint32_t header_bits(header_t header) {
    return static_cast<libbitcoin::message::header const*>(header)->bits();
}

void header_set_bits(header_t header, uint32_t bits) {
    return static_cast<libbitcoin::message::header*>(header)->set_bits(bits);
}

uint32_t header_nonce(header_t header) {
    return static_cast<libbitcoin::message::header const*>(header)->nonce();
}

void header_set_nonce(header_t header, uint32_t nonce) {
    return static_cast<libbitcoin::message::header*>(header)->set_nonce(nonce);
}

hash_t header_previous_block_hash(header_t header) {
    auto const& hash_cpp = static_cast<libbitcoin::message::header const*>(header)->previous_block_hash();
    return hash_cpp.data();
}

hash_t header_merkle(header_t header) {
    auto const& hash_cpp = static_cast<libbitcoin::message::header const*>(header)->merkle();
    return hash_cpp.data();
}

hash_t header_hash(header_t header) {
    auto const& hash_cpp = static_cast<libbitcoin::message::header const*>(header)->hash();
    return hash_cpp.data(); //TODO: returning a dangling pointer
}


//const hash_digest& () const;
//void set_previous_block_hash(const hash_digest& value);





//// Serialization.
////-----------------------------------------------------------------------------
//
//data_chunk to_data() const;
//void to_data(std::ostream& stream) const;
//void to_data(writer& sink) const;
//
//// Properties (size, accessors, cache).
////-----------------------------------------------------------------------------
//
//static size_t satoshi_fixed_size();
//size_t serialized_size() const;
//
//
//void set_previous_block_hash(const hash_digest& value);
//void set_previous_block_hash(hash_digest&& value);
//
//
//void set_merkle(const hash_digest& value);
//void set_merkle(hash_digest&& value);
//

//
//#ifdef LITECOIN
//hash_digest litecoin_proof_of_work_hash() const;
//#endif
//
//// Validation.
////-----------------------------------------------------------------------------
//
//bool is_valid_time_stamp() const;
//bool is_valid_proof_of_work() const;
//
//code check() const;
//code accept(const chain_state& state) const;


} /* extern "C" */
