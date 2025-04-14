// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/capi/string_list.h>

#include <string>
#include <vector>

#include <kth/capi/helpers.hpp>
#include <kth/capi/list_creator.h>

KTH_LIST_DEFINE_CONVERTERS(core, kth_string_list_t, std::string, string_list)
KTH_LIST_DEFINE_CONSTRUCT_FROM_CPP(core, kth_string_list_t, std::string, string_list)

// ---------------------------------------------------------------------------
extern "C" {

kth_string_list_t kth_core_string_list_construct() {
    return new std::vector<std::string>();
}

void kth_core_string_list_destruct(kth_string_list_t string_list) {
    delete &kth_core_string_list_cpp(string_list);
}

void kth_core_string_list_push_back(kth_string_list_t string_list, char const* string) {
    kth_core_string_list_cpp(string_list).emplace_back(std::string(string));
}

char const* kth_core_string_list_nth(kth_string_list_t string_list, kth_size_t index) {
    auto str = kth_core_string_list_cpp(string_list)[index];
    return kth::create_c_str(str);
}

kth_size_t kth_core_string_list_count(kth_string_list_t string_list) {
    return kth_core_string_list_cpp(string_list).size();
}

} // extern "C"