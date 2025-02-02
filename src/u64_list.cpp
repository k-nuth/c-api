// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/capi/u64_list.h>

#include <vector>

#include <kth/capi/list_creator.h>

KTH_LIST_DEFINE_CONVERTERS(core, kth_u64_list_t, uint64_t, u64_list)

// ---------------------------------------------------------------------------
extern "C" {

kth_u64_list_t kth_core_u64_list_construct() {
    return new std::vector<uint64_t>();
}

void kth_core_u64_list_destruct(kth_u64_list_t u64_list) {
    delete &kth_core_u64_list_cpp(u64_list);
}

void kth_core_u64_list_push_back(kth_u64_list_t u64_list, uint64_t value) {
    kth_core_u64_list_cpp(u64_list).emplace_back(value);
}

uint64_t kth_core_u64_list_nth(kth_u64_list_t u64_list, kth_size_t index) {
    return kth_core_u64_list_cpp(u64_list)[index];
}

kth_size_t kth_core_u64_list_count(kth_u64_list_t u64_list) {
    return kth_core_u64_list_cpp(u64_list).size();
}

} // extern "C"