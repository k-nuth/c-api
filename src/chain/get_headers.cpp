// Copyright (c) 2016-2023 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/capi/chain/header.h>

#include <kth/capi/conversions.hpp>
#include <kth/capi/helpers.hpp>

#include <kth/domain/message/get_headers.hpp>


KTH_CONV_DEFINE(chain, kth_get_headers_t, kth::domain::message::get_headers, get_headers)

// ---------------------------------------------------------------------------
extern "C" {

kth_get_headers_t kth_chain_get_headers_construct_default() {
    return new kth::domain::message::get_headers();
}

kth_get_headers_t kth_chain_get_headers_construct(kth_hash_list_t start, kth_hash_t stop) {
    auto const& start_cpp = kth_core_hash_list_const_cpp(start);
    auto stop_cpp = kth::to_array(stop.hash);

    return new kth::domain::message::get_headers(start_cpp, stop_cpp);
}

void kth_chain_get_headers_destruct(kth_get_headers_t get_b) {
    delete &kth_chain_get_headers_cpp(get_b);
}

kth_hash_list_t kth_chain_get_headers_start_hashes(kth_get_headers_t get_b) {
    auto& list = kth_chain_get_headers_cpp(get_b).start_hashes();
    return kth_core_hash_list_construct_from_cpp(list);
}

void kth_chain_get_headers_set_start_hashes(kth_get_headers_t get_b, kth_hash_list_t value) {
    auto const& value_cpp = kth_core_hash_list_const_cpp(value);
    kth_chain_get_headers_cpp(get_b).set_start_hashes(value_cpp);
}

kth_hash_t kth_chain_get_headers_stop_hash(kth_get_headers_t get_b) {
    auto& stop = kth_chain_get_headers_cpp(get_b).stop_hash();
    return kth::to_hash_t(stop);
}

void kth_chain_get_headers_stop_hash_out(kth_get_headers_t get_b, kth_hash_t* out_stop_hash) {
    auto& stop = kth_chain_get_headers_cpp(get_b).stop_hash();
    kth::copy_c_hash(stop, out_stop_hash);
}

void kth_chain_get_headers_set_stop_hash(kth_get_headers_t get_b, kth_hash_t value) {
    auto value_cpp = kth::to_array(value.hash);
    kth_chain_get_headers_cpp(get_b).set_stop_hash(value_cpp);
}

kth_bool_t kth_chain_get_headers_is_valid(kth_get_headers_t get_b) {
    return kth::bool_to_int(kth_chain_get_headers_cpp(get_b).is_valid());
}

void kth_chain_get_headers_reset(kth_get_headers_t get_b) {
    kth_chain_get_headers_cpp(get_b).reset();
}

kth_size_t kth_chain_get_headers_serialized_size(kth_get_headers_t get_b, uint32_t version) {
    return kth_chain_get_headers_cpp(get_b).serialized_size(version);
}

} // extern "C"
