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

#include <bitprim/nodecint/chain/header.h>

#include <bitprim/nodecint/convertions.hpp>
#include <bitprim/nodecint/helpers.hpp>

libbitcoin::message::header const& chain_header_const_cpp(header_t header) {
    return *static_cast<libbitcoin::message::header const*>(header);
}

libbitcoin::message::header& chain_header_cpp(header_t header) {
    return *static_cast<libbitcoin::message::header*>(header);
}

extern "C" {

header_t chain_header_factory_from_data(uint32_t version, uint8_t* data, uint64_t n) {
    libbitcoin::data_chunk data_cpp(data, std::next(data, n));
    auto header = libbitcoin::message::header::factory_from_data(version, data_cpp);
    return new libbitcoin::message::header(std::move(header)); // TODO(fernando): revisar todos los "new"'s que hay por todos lados para ver si podemos hacer un move de los recursos...
}

uint64_t /*size_t*/ chain_header_satoshi_fixed_size(uint32_t version) {
    return libbitcoin::message::header::satoshi_fixed_size(version);
}

//Note: It is the responsability of the user to release/destruct the array
uint8_t const* chain_header_to_data(header_t header, uint32_t version, uint64_t* /*size_t*/ out_size) {
    auto const& header_cpp = chain_header_const_cpp(header);
    auto data = header_cpp.to_data(version);
    return bitprim::create_c_array(data, *out_size);
}

void chain_header_reset(header_t header) {
    return chain_header_cpp(header).reset();
}

uint64_t /*size_t*/ chain_header_serialized_size(header_t header, uint32_t version) {
    return chain_header_const_cpp(header).serialized_size(version);
}

header_t chain_header_construct_default() {
    return new libbitcoin::message::header();
}

header_t chain_header_construct(uint32_t version, uint8_t* previous_block_hash, uint8_t* merkle, uint32_t timestamp, uint32_t bits, uint32_t nonce) {
    //precondition: [previous_block_hash, 32) is a valid range
    //              && [merkle, 32) is a valid range

    auto previous_block_hash_cpp = bitprim::hash_to_cpp(previous_block_hash);
    auto merkle_cpp = bitprim::hash_to_cpp(merkle);
    return new libbitcoin::message::header(version, previous_block_hash_cpp, merkle_cpp, timestamp, bits, nonce);
}

void chain_header_destruct(header_t header) {
    delete &chain_header_cpp(header);
}

int chain_header_is_valid(header_t header) {
    return static_cast<int>(chain_header_const_cpp(header).is_valid());
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

//Note: user of the function has to release the resource (memory) manually
char const* chain_header_proof_str(header_t header) {
    std::string proof_str = chain_header_const_cpp(header).proof().str();
    return bitprim::create_c_str(proof_str);
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
    return bitprim::to_hash_t(hash_cpp);
}

void chain_header_previous_block_hash_out(header_t header, hash_t* out_previous_block_hash) {
    auto const& previous_block_hash_cpp = chain_header_const_cpp(header).previous_block_hash();
    // std::memcpy(static_cast<void*>(out_previous_block_hash->hash), previous_block_hash_cpp.data(), BITCOIN_HASH_SIZE);
    bitprim::copy_c_hash(previous_block_hash_cpp, out_previous_block_hash);
}

hash_t chain_header_merkle(header_t header) {
    auto const& hash_cpp = chain_header_const_cpp(header).merkle();
    return bitprim::to_hash_t(hash_cpp);
}

void chain_header_merkle_out(header_t header, hash_t* out_merkle) {
    auto const& merkle_hash_cpp = chain_header_const_cpp(header).merkle();
    // std::memcpy(static_cast<void*>(out_merkle->hash), merkle_hash_cpp.data(), BITCOIN_HASH_SIZE);
    bitprim::copy_c_hash(merkle_hash_cpp, out_merkle);
}

hash_t chain_header_hash(header_t header) {
    auto const& hash_cpp = chain_header_const_cpp(header).hash();
    return bitprim::to_hash_t(hash_cpp);
}

void chain_header_hash_out(header_t header, hash_t* out_hash) {
    auto const& hash_cpp = chain_header_const_cpp(header).hash();
    bitprim::copy_c_hash(hash_cpp, out_hash);
}

} // extern "C"
