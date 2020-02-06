// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#include <kth/capi/chain/block.h>

#include <kth/domain/message/get_blocks.hpp>

#include <kth/capi/conversions.hpp>
#include <kth/capi/helpers.hpp>

KTH_CONV_DEFINE(chain, get_blocks_t, kth::message::get_blocks, get_blocks)

// ---------------------------------------------------------------------------
extern "C" {

get_blocks_t chain_get_blocks_construct_default() {
    return new kth::message::get_blocks();
}

get_blocks_t chain_get_blocks_construct(hash_list_t start, hash_t stop) {
    auto const& start_cpp = core_hash_list_const_cpp(start);
    auto stop_cpp = kth::to_array(stop.hash);
    return new kth::message::get_blocks(start_cpp, stop_cpp);
}

void chain_get_blocks_destruct(get_blocks_t get_b) {
    delete &chain_get_blocks_cpp(get_b);
}

hash_list_t chain_get_blocks_start_hashes(get_blocks_t get_b) {
    auto& list = chain_get_blocks_cpp(get_b).start_hashes();
    return core_hash_list_construct_from_cpp(list);
}

void chain_get_blocks_set_start_hashes(get_blocks_t get_b, hash_list_t value) {
    auto const& value_cpp = core_hash_list_const_cpp(value);
    chain_get_blocks_cpp(get_b).set_start_hashes(value_cpp);
}

hash_t chain_get_blocks_stop_hash(get_blocks_t get_b) {
    auto& stop = chain_get_blocks_cpp(get_b).stop_hash();
    return kth::to_hash_t(stop);
}

void chain_get_blocks_stop_hash_out(get_blocks_t get_b, hash_t* out_stop_hash) {
    auto& stop = chain_get_blocks_cpp(get_b).stop_hash();
    kth::copy_c_hash(stop, out_stop_hash);
}

//TODO(fernando): pass the hash_t by reference (pointer)
void chain_get_blocks_set_stop_hash(get_blocks_t get_b, hash_t value) {
    auto value_cpp = kth::to_array(value.hash);
    chain_get_blocks_cpp(get_b).set_stop_hash(value_cpp);
}

bool_t chain_get_blocks_is_valid(get_blocks_t get_b) {
    return kth::bool_to_int(chain_get_blocks_cpp(get_b).is_valid());
}

void chain_get_blocks_reset(get_blocks_t get_b) {
    chain_get_blocks_cpp(get_b).reset();
}

uint64_t /*size_t*/ chain_get_blocks_serialized_size(get_blocks_t get_b, uint32_t version) {
    return chain_get_blocks_cpp(get_b).serialized_size(version);
}

} // extern "C"
