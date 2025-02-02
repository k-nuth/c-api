// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/capi/double_list.h>

#include <vector>

#include <kth/capi/list_creator.h>

KTH_LIST_DEFINE_CONVERTERS(core, kth_double_list_t, double, double_list)

// ---------------------------------------------------------------------------
extern "C" {

kth_double_list_t kth_core_double_list_construct() {
    return new std::vector<double>();
}

void kth_core_double_list_destruct(kth_double_list_t double_list) {
    delete &kth_core_double_list_cpp(double_list);
}

void kth_core_double_list_push_back(kth_double_list_t double_list, double value) {
    kth_core_double_list_cpp(double_list).emplace_back(value);
}

double kth_core_double_list_nth(kth_double_list_t double_list, kth_size_t index) {
    return kth_core_double_list_cpp(double_list)[index];
}

kth_size_t kth_core_double_list_count(kth_double_list_t double_list) {
    return kth_core_double_list_cpp(double_list).size();
}

} // extern "C"