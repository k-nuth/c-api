// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#include <kth/capi/chain/header.h>

#include <kth/capi/conversions.hpp>
#include <kth/capi/helpers.hpp>

#include <kth/domain/message/get_headers.hpp>


KTH_CONV_DEFINE(chain, get_headers_t, kth::message::get_headers, get_headers)

// ---------------------------------------------------------------------------
extern "C" {

get_headers_t chain_get_headers_construct_default() {
    return new kth::message::get_headers();
}

get_headers_t chain_get_headers_construct(hash_list_t start, hash_t stop) {
    auto const& start_cpp = core_hash_list_const_cpp(start);
    auto stop_cpp = kth::to_array(stop.hash);

    return new kth::message::get_headers(start_cpp, stop_cpp);
}

void chain_get_headers_destruct(get_headers_t get_b) {
    delete &chain_get_headers_cpp(get_b);
}

hash_list_t chain_get_headers_start_hashes(get_headers_t get_b) {
    auto& list = chain_get_headers_cpp(get_b).start_hashes();
    return core_hash_list_construct_from_cpp(list);
}

void chain_get_headers_set_start_hashes(get_headers_t get_b, hash_list_t value) {
    auto const& value_cpp = core_hash_list_const_cpp(value);
    chain_get_headers_cpp(get_b).set_start_hashes(value_cpp);
}

hash_t chain_get_headers_stop_hash(get_headers_t get_b) {
    auto& stop = chain_get_headers_cpp(get_b).stop_hash();
    return kth::to_hash_t(stop);
}

void chain_get_headers_stop_hash_out(get_headers_t get_b, hash_t* out_stop_hash) {
    auto& stop = chain_get_headers_cpp(get_b).stop_hash();
    kth::copy_c_hash(stop, out_stop_hash);
}

void chain_get_headers_set_stop_hash(get_headers_t get_b, hash_t value) {
    auto value_cpp = kth::to_array(value.hash);
    chain_get_headers_cpp(get_b).set_stop_hash(value_cpp);
}

bool_t chain_get_headers_is_valid(get_headers_t get_b) {
    return kth::bool_to_int(chain_get_headers_cpp(get_b).is_valid());
}

void chain_get_headers_reset(get_headers_t get_b) {
    chain_get_headers_cpp(get_b).reset();
}

uint64_t /*size_t*/ chain_get_headers_serialized_size(get_headers_t get_b, uint32_t version) {
    return chain_get_headers_cpp(get_b).serialized_size(version);
}

} // extern "C"
