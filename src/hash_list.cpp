// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/capi/hash_list.h>

#include <kth/capi/conversions.hpp>
#include <kth/capi/helpers.hpp>

KTH_LIST_DEFINE_CONVERTERS(core, kth_hash_list_t, kth::hash_digest, hash_list)
KTH_LIST_DEFINE_CONSTRUCT_FROM_CPP(core, kth_hash_list_t, kth::hash_digest, hash_list)

// ---------------------------------------------------------------------------

extern "C" {

kth_hash_list_t kth_core_hash_list_construct_default() {
    return new std::vector<kth::hash_digest>();
}

void kth_core_hash_list_push_back(kth_hash_list_t list, kth_hash_t hash) {
    auto hash_cpp = kth::to_array(hash.hash);
    kth_core_hash_list_cpp(list).push_back(hash_cpp);
}

void kth_core_hash_list_destruct(kth_hash_list_t list) {
    delete &kth_core_hash_list_cpp(list);
}

kth_size_t kth_core_hash_list_count(kth_hash_list_t list) {
    return kth_core_hash_list_const_cpp(list).size();
}

kth_hash_t kth_core_hash_list_nth(kth_hash_list_t list, kth_size_t n) {
    auto const& x = kth_core_hash_list_cpp(list)[n];
    return kth::to_hash_t(x);
}

void kth_core_hash_list_nth_out(kth_hash_list_t list, kth_size_t n, kth_hash_t* out_hash) {
    auto const& x = kth_core_hash_list_cpp(list)[n];
    kth::copy_c_hash(x, out_hash);
}

} // extern "C"
