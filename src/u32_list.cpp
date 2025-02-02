// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/capi/u32_list.h>

#include <vector>

#include <kth/capi/list_creator.h>

KTH_LIST_DEFINE_CONVERTERS(core, kth_u32_list_t, uint32_t, u32_list)

// ---------------------------------------------------------------------------
extern "C" {

kth_u32_list_t kth_core_u32_list_construct() {
    return new std::vector<uint32_t>();
}

void kth_core_u32_list_destruct(kth_u32_list_t u32_list) {
    delete &kth_core_u32_list_cpp(u32_list);
}

void kth_core_u32_list_push_back(kth_u32_list_t u32_list, uint32_t value) {
    kth_core_u32_list_cpp(u32_list).emplace_back(value);
}

uint32_t kth_core_u32_list_nth(kth_u32_list_t u32_list, kth_size_t index) {
    return kth_core_u32_list_cpp(u32_list)[index];
}

kth_size_t kth_core_u32_list_count(kth_u32_list_t u32_list) {
    return kth_core_u32_list_cpp(u32_list).size();
}

} // extern "C"