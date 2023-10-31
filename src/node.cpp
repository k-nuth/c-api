// Copyright (c) 2016-2023 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/capi/node.h>

#include <cstdio>
#include <latch>
#include <memory>

#include <boost/iostreams/device/file_descriptor.hpp>
// #include <boost/thread/latch.hpp>

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

void kth_node_init_run(kth_node_t node, void* ctx, kth_start_modules_t mods, kth_run_handler_t handler) {
    kth_node_cpp(node).init_run(version(), kth::start_modules_to_cpp(mods),
        [node, ctx, handler](std::error_code const& ec) {
            if (handler != nullptr) {
                handler(node, ctx, kth::to_c_err(ec));
            }
    });
}

kth_error_code_t kth_node_init_run_sync(kth_node_t node, kth_start_modules_t mods) {
    std::latch latch(1); //Note: workaround to fix an error on some versions of Boost.Threads
    kth_error_code_t res;

    kth_node_cpp(node).init_run(version(), kth::start_modules_to_cpp(mods),
        [&](std::error_code const& ec) {
            res = kth::to_c_err(ec);
            latch.count_down();
        }
    );

    latch.wait();
    return res;
}

#endif // ! defined(KTH_DB_READONLY)

void kth_node_signal_stop(kth_node_t node) {
    kth_node_cpp(node).signal_stop();
}

int kth_node_close(kth_node_t node) {
    return kth_node_cpp(node).close();
}

int kth_node_stopped(kth_node_t node) {
    return static_cast<int>(kth_node_cpp(node).stopped());
}

kth_chain_t kth_node_get_chain(kth_node_t node) {
    return &(kth_node_cpp(node).node().chain());
}

kth_p2p_t kth_node_get_p2p(kth_node_t node) {
#if ! defined(__EMSCRIPTEN__)
    return &static_cast<kth::network::p2p&>(kth_node_cpp(node).node());
#else
    return nullptr;
#endif
}

void kth_node_print_thread_id() {
    std::cout << std::this_thread::get_id() << '\n';
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

} // extern "C"
