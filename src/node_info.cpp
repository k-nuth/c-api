// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/capi/node_info.h>

#include <functional>
#include <iostream>
#include <thread>

#include <kth/capi/config/database_helpers.hpp>
#include <kth/capi/helpers.hpp>
#include <kth/capi/version.h>
#include <kth/node/executor/executor_info.hpp>
#include <kth/node/version.hpp>

extern "C" {

void kth_node_print_thread_id() {
    std::cout << std::this_thread::get_id() << '\n';
}

uint64_t kth_node_get_thread_id() {
    std::hash<std::thread::id> hasher;
    return hasher(std::this_thread::get_id());
}

char const* kth_node_capi_version() {
    return KTH_CAPI_VERSION;
}

char const* kth_node_cppapi_version() {
    return kth::node::version();
}

char const* kth_node_microarchitecture() {
    // I can use .data() because the string is comming from a null-terminated string
    return kth::node::microarchitecture().data();
}

char const* kth_node_march_names() {
    return kth::node::march_names().data();
}

char const* kth_node_currency_symbol() {
    return kth::node::currency_symbol().data();
}

char const* kth_node_currency() {
    return kth::node::currency().data();
}

char const* kth_node_db_type(kth_db_mode_t mode) {
    return kth::node::db_type(kth::capi::helpers::db_mode_converter(mode)).data();
}

uint32_t kth_node_cppapi_build_timestamp() {
    return kth::node::build_timestamp();
}

} // extern "C"
