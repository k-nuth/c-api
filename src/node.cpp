// Copyright (c) 2016-2021 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/capi/node.h>

#include <cstdio>
#include <memory>

#include <boost/iostreams/device/file_descriptor.hpp>
#include <boost/thread/latch.hpp>

#include <kth/capi/config/settings_helper.hpp>
#include <kth/capi/helpers.hpp>
#include <kth/capi/version.h>

#include <kth/node/executor/executor.hpp>
#include <kth/infrastructure/wallet/mnemonic.hpp>  //Warning, put it after boost headers

std::string version() {
    return "Node C lib v" KTH_CAPI_VERSION;
}

kth::node::executor const& kth_node_const_cpp(kth_node_t o) {
    return *static_cast<kth::node::executor const*>(o);
}

kth::node::executor& kth_node_cpp(kth_node_t o) {
    return *static_cast<kth::node::executor*>(o);
}

// ---------------------------------------------------------------------------
extern "C" {

kth_node_t kth_node_construct(kth_settings const* settings, kth_bool_t stdout_enabled) {
    auto cpp = kth::capi::helpers::settings_to_cpp(*settings);
    return new kth::node::executor(cpp, stdout_enabled);
}

void kth_node_destruct(kth_node_t node) {
    delete &kth_node_cpp(node);
}

#if ! defined(KTH_DB_READONLY)
int kth_node_initchain(kth_node_t node) {
    // TODO(fernando): return error_t to inform error in detail
    try {
        return kth::bool_to_int(kth_node_cpp(node).do_initchain(version()));
    } catch (...) {
        return 0;
    }
}
#endif // ! defined(KTH_DB_READONLY)

#if ! defined(KTH_DB_READONLY)
void kth_node_init_run_and_wait_for_signal(kth_node_t node, void* ctx, kth_start_modules_t mods, kth_run_handler_t handler) {
    kth_node_cpp(node).init_run_and_wait_for_signal(
        version(),
        kth::start_modules_to_cpp(mods),
        [node, ctx, handler](std::error_code const& ec) {
            if (handler != nullptr) {
                handler(node, ctx, kth::to_c_err(ec));
            }
    });
}

#endif // ! defined(KTH_DB_READONLY)

void kth_node_signal_stop(kth_node_t node) {
    kth_node_cpp(node).signal_stop();
}

int kth_node_close(kth_node_t node) {
   return kth_node_cpp(node).node().close();
}

int kth_node_stopped(kth_node_t node) {
    return static_cast<int>(kth_node_cpp(node).stopped());
}

kth_chain_t kth_node_get_chain(kth_node_t node) {
    return &(kth_node_cpp(node).node().chain());
}

kth_p2p_t kth_node_get_p2p(kth_node_t node) {
    return &static_cast<kth::network::p2p&>(kth_node_cpp(node).node());
}

void kth_node_print_thread_id() {
    std::cout << std::this_thread::get_id() << '\n';
}

#ifdef KTH_WITH_KEOKEN
keoken_manager_t kth_node_get_keoken_manager(kth_node_t node) {
    // return &(kth_node_cpp(node).node().keoken_manager());
    return &(kth_node_cpp(node).keoken_manager());
}
#endif

char const* kth_node_version() {
    return KTH_CAPI_VERSION;
}

} // extern "C"
