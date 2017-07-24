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


libbitcoin::message::header const& chain_header_const_cpp(header_t header) {
    return *static_cast<libbitcoin::message::header const*>(header);
}

libbitcoin::message::header& chain_header_cpp(header_t header) {
    return *static_cast<libbitcoin::message::header*>(header);
}

extern "C" {


//static header factory_from_data(const uint32_t version, const data_chunk& data);
header_t chain_header_factory_from_data(uint32_t version, uint8_t* data, uint64_t n) {
    libbitcoin::data_chunk data_cpp(data, data + n);
    auto header = libbitcoin::message::header::factory_from_data(version, data_cpp);
    return new libbitcoin::message::header(std::move(header)); //TODO: revisar todos los "new"'s que hay por todos lados para ver si podemos hacer un move de los recursos...
}

uint64_t /*size_t*/ chain_header_satoshi_fixed_size(uint32_t version) {
    return libbitcoin::message::header::satoshi_fixed_size(version);
}

//data_chunk to_data(const uint32_t version) const;
//void to_data(const uint32_t version, std::ostream& stream) const;
//void to_data(const uint32_t version, writer& sink) const;
uint8_t* chain_header_to_data(header_t header, uint32_t version) {
    auto const& header_cpp = chain_header_const_cpp(header);
    auto data = header_cpp.to_data(version);

    //Note: It is the responsability of the user to release/destruct the object
    auto* ret = new libbitcoin::data_chunk(std::move(data));
    return ret->data();
}

//void reset();
void chain_header_reset(header_t header) {
    return chain_header_cpp(header).reset();
}

//size_t serialized_size(const uint32_t version) const;
uint64_t /*size_t*/ chain_header_serialized_size(header_t header, uint32_t version) {
    return chain_header_const_cpp(header).serialized_size(version);
}

//header();
header_t chain_header_construct_default() {
    return new libbitcoin::message::header();
}

//header(uint32_t version, const hash_digest& previous_block_hash, const hash_digest& merkle, uint32_t timestamp, uint32_t bits, uint32_t nonce);
header_t chain_header_construct(uint32_t version, uint8_t* previous_block_hash, uint8_t* merkle, uint32_t timestamp, uint32_t bits, uint32_t nonce) {
    //precondition: [previous_block_hash, 32) is a valid range
    //              && [merkle, 32) is a valid range

    libbitcoin::hash_digest previous_block_hash_cpp;
    std::copy_n(previous_block_hash, previous_block_hash_cpp.size(), std::begin(previous_block_hash_cpp));

    libbitcoin::hash_digest merkle_cpp;
    std::copy_n(merkle, merkle_cpp.size(), std::begin(merkle_cpp));

    return new libbitcoin::message::header(version, previous_block_hash_cpp, merkle_cpp, timestamp, bits, nonce);
}

void chain_header_destruct(header_t header) {
    delete &chain_header_cpp(header);
}

int chain_header_is_valid(header_t header) {
    return chain_header_const_cpp(header).is_valid();
}

uint32_t chain_header_version(header_t header) {
    return chain_header_const_cpp(header).version();
}

void chain_header_set_version(header_t header, uint32_t version) {
    return chain_header_cpp(header).set_version(version);
}

uint32_t chain_header_timestamp(header_t header) {
    return chain_header_const_cpp(header).timestamp();
}

void chain_header_set_timestamp(header_t header, uint32_t timestamp) {
    return chain_header_cpp(header).set_timestamp(timestamp);
}

uint32_t chain_header_bits(header_t header) {
    return chain_header_const_cpp(header).bits();
}

void chain_header_set_bits(header_t header, uint32_t bits) {
    return chain_header_cpp(header).set_bits(bits);
}

uint32_t chain_header_nonce(header_t header) {
    return chain_header_const_cpp(header).nonce();
}

void chain_header_set_nonce(header_t header, uint32_t nonce) {
    return chain_header_cpp(header).set_nonce(nonce);
}

hash_t chain_header_previous_block_hash(header_t header) {
    auto const& hash_cpp = chain_header_const_cpp(header).previous_block_hash();
    return hash_cpp.data();
}

hash_t chain_header_merkle(header_t header) {
    auto const& hash_cpp = chain_header_const_cpp(header).merkle();
    return hash_cpp.data();
}

hash_t chain_header_hash(header_t header) {
    auto const& hash_cpp = chain_header_const_cpp(header).hash();
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
