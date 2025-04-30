// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/capi/chain/header.h>

#include <kth/capi/conversions.hpp>
#include <kth/capi/helpers.hpp>

KTH_CONV_DEFINE(chain, kth_header_t, kth::domain::chain::header, header)

extern "C" {

kth_header_t kth_chain_header_factory_from_data(uint8_t* data, kth_size_t n) {
    kth::data_chunk data_cpp(data, std::next(data, n));
    auto header = kth::domain::create_old<kth::domain::chain::header>(data_cpp);
    return kth::move_or_copy_and_leak(std::move(header));
}

kth_size_t kth_chain_header_satoshi_fixed_size() {
    return kth::domain::chain::header::satoshi_fixed_size();
}

//Note: It is the responsability of the user to release/destruct the array
uint8_t const* kth_chain_header_to_data(kth_header_t header, kth_size_t* out_size) {
    auto const& header_cpp = kth_chain_header_const_cpp(header);
    auto data = header_cpp.to_data();
    return kth::create_c_array(data, *out_size);
}

void kth_chain_header_reset(kth_header_t header) {
    return kth_chain_header_cpp(header).reset();
}

kth_size_t kth_chain_header_serialized_size(kth_header_t header) {
    return kth_chain_header_const_cpp(header).serialized_size();
}

kth_header_t kth_chain_header_construct_default() {
    return new kth::domain::chain::header();
}

kth_header_t kth_chain_header_construct(uint32_t version, uint8_t* previous_block_hash, uint8_t* merkle, uint32_t timestamp, uint32_t bits, uint32_t nonce) {
    //precondition: [previous_block_hash, 32) is a valid range
    //              && [merkle, 32) is a valid range

    auto previous_block_hash_cpp = kth::hash_to_cpp(previous_block_hash);
    auto merkle_cpp = kth::hash_to_cpp(merkle);
    return new kth::domain::chain::header(version, previous_block_hash_cpp, merkle_cpp, timestamp, bits, nonce);
}

void kth_chain_header_destruct(kth_header_t header) {
    delete &kth_chain_header_cpp(header);
}

kth_bool_t kth_chain_header_is_valid(kth_header_t header) {
    return kth::bool_to_int(kth_chain_header_const_cpp(header).is_valid());
}

uint32_t kth_chain_header_version(kth_header_t header) {
    return kth_chain_header_const_cpp(header).version();
}

void kth_chain_header_set_version(kth_header_t header, uint32_t version) {
    return kth_chain_header_cpp(header).set_version(version);
}

uint32_t kth_chain_header_timestamp(kth_header_t header) {
    return kth_chain_header_const_cpp(header).timestamp();
}

void kth_chain_header_set_timestamp(kth_header_t header, uint32_t timestamp) {
    return kth_chain_header_cpp(header).set_timestamp(timestamp);
}

uint32_t kth_chain_header_bits(kth_header_t header) {
    return kth_chain_header_const_cpp(header).bits();
}

char const* kth_chain_header_proof_str(kth_header_t header) {
    std::string proof_str = kth_chain_header_const_cpp(header).proof().str();
    return kth::create_c_str(proof_str);
}

void kth_chain_header_set_bits(kth_header_t header, uint32_t bits) {
    return kth_chain_header_cpp(header).set_bits(bits);
}

uint32_t kth_chain_header_nonce(kth_header_t header) {
    return kth_chain_header_const_cpp(header).nonce();
}

void kth_chain_header_set_nonce(kth_header_t header, uint32_t nonce) {
    return kth_chain_header_cpp(header).set_nonce(nonce);
}

kth_hash_t kth_chain_header_previous_block_hash(kth_header_t header) {
    auto const& hash_cpp = kth_chain_header_const_cpp(header).previous_block_hash();
    return kth::to_hash_t(hash_cpp);
}

void kth_chain_header_previous_block_hash_out(kth_header_t header, kth_hash_t* out_previous_block_hash) {
    auto const& previous_block_hash_cpp = kth_chain_header_const_cpp(header).previous_block_hash();
    kth::copy_c_hash(previous_block_hash_cpp, out_previous_block_hash);
}

kth_hash_t kth_chain_header_merkle(kth_header_t header) {
    auto const& hash_cpp = kth_chain_header_const_cpp(header).merkle();
    return kth::to_hash_t(hash_cpp);
}

void kth_chain_header_merkle_out(kth_header_t header, kth_hash_t* out_merkle) {
    auto const& merkle_hash_cpp = kth_chain_header_const_cpp(header).merkle();
    kth::copy_c_hash(merkle_hash_cpp, out_merkle);
}

kth_hash_t kth_chain_header_hash(kth_header_t header) {
    auto const& hash_cpp = kth_chain_header_const_cpp(header).hash();
    return kth::to_hash_t(hash_cpp);
}

void kth_chain_header_hash_out(kth_header_t header, kth_hash_t* out_hash) {
    auto const& hash_cpp = kth_chain_header_const_cpp(header).hash();
    kth::copy_c_hash(hash_cpp, out_hash);
}

} // extern "C"
