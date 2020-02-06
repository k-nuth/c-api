// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#include <knuth/nodecint/chain/header.h>

#include <knuth/nodecint/conversions.hpp>
#include <knuth/nodecint/helpers.hpp>

KTH_CONV_DEFINE(chain, header_t, kth::message::header, header)

extern "C" {

header_t chain_header_factory_from_data(uint32_t version, uint8_t* data, uint64_t n) {
    kth::data_chunk data_cpp(data, std::next(data, n));
    auto header = kth::message::header::factory_from_data(version, data_cpp);
    return knuth::move_or_copy_and_leak(std::move(header));
}

uint64_t /*size_t*/ chain_header_satoshi_fixed_size(uint32_t version) {
    return kth::message::header::satoshi_fixed_size(version);
}

//Note: It is the responsability of the user to release/destruct the array
uint8_t const* chain_header_to_data(header_t header, uint32_t version, uint64_t* /*size_t*/ out_size) {
    auto const& header_cpp = chain_header_const_cpp(header);
    auto data = header_cpp.to_data(version);
    return knuth::create_c_array(data, *out_size);
}

void chain_header_reset(header_t header) {
    return chain_header_cpp(header).reset();
}

uint64_t /*size_t*/ chain_header_serialized_size(header_t header, uint32_t version) {
    return chain_header_const_cpp(header).serialized_size(version);
}

header_t chain_header_construct_default() {
    return new kth::message::header();
}

header_t chain_header_construct(uint32_t version, uint8_t* previous_block_hash, uint8_t* merkle, uint32_t timestamp, uint32_t bits, uint32_t nonce) {
    //precondition: [previous_block_hash, 32) is a valid range
    //              && [merkle, 32) is a valid range

    auto previous_block_hash_cpp = knuth::hash_to_cpp(previous_block_hash);
    auto merkle_cpp = knuth::hash_to_cpp(merkle);
    return new kth::message::header(version, previous_block_hash_cpp, merkle_cpp, timestamp, bits, nonce);
}

void chain_header_destruct(header_t header) {
    delete &chain_header_cpp(header);
}

int chain_header_is_valid(header_t header) {
    return knuth::bool_to_int(chain_header_const_cpp(header).is_valid());
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
    return knuth::create_c_str(proof_str);
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
    return knuth::to_hash_t(hash_cpp);
}

void chain_header_previous_block_hash_out(header_t header, hash_t* out_previous_block_hash) {
    auto const& previous_block_hash_cpp = chain_header_const_cpp(header).previous_block_hash();
    knuth::copy_c_hash(previous_block_hash_cpp, out_previous_block_hash);
}

hash_t chain_header_merkle(header_t header) {
    auto const& hash_cpp = chain_header_const_cpp(header).merkle();
    return knuth::to_hash_t(hash_cpp);
}

void chain_header_merkle_out(header_t header, hash_t* out_merkle) {
    auto const& merkle_hash_cpp = chain_header_const_cpp(header).merkle();
    knuth::copy_c_hash(merkle_hash_cpp, out_merkle);
}

hash_t chain_header_hash(header_t header) {
    auto const& hash_cpp = chain_header_const_cpp(header).hash();
    return knuth::to_hash_t(hash_cpp);
}

void chain_header_hash_out(header_t header, hash_t* out_hash) {
    auto const& hash_cpp = chain_header_const_cpp(header).hash();
    knuth::copy_c_hash(hash_cpp, out_hash);
}

} // extern "C"
