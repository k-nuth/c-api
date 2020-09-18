// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/capi/node.h>

#include <cstdio>
#include <memory>

#include <boost/iostreams/device/file_descriptor.hpp>
#include <boost/thread/latch.hpp>

#include <kth/capi/config/settings_helper.hpp>
#include <kth/capi/executor.hpp>
#include <kth/capi/helpers.hpp>
#include <kth/capi/version.h>

#include <kth/infrastructure/wallet/mnemonic.hpp>  //Warning, put it after boost headers


inline
FILE* devnull_file() {
#ifdef BOOST_IOSTREAMS_WINDOWS
    return fopen ("nul", "w");
#else
    return fopen ("/dev/null", "w");
#endif
}

inline
int devnull_fileno() {
#ifdef BOOST_IOSTREAMS_WINDOWS
    return _fileno(devnull_file());
#else
    return fileno(devnull_file());
#endif
}

inline
int fileno_or_devnull(FILE* f) {
    if (f == nullptr) {
        return devnull_fileno();
    }

#ifdef BOOST_IOSTREAMS_WINDOWS
    return _fileno(f);
#else
    return fileno(f);
#endif
}

inline
int fileno_or_devnull(int fd) {
    if (fd < 0) {
        return devnull_fileno();
    }
    return fd;
}

#ifdef BOOST_IOSTREAMS_WINDOWS
using handle_sink = typename boost::iostreams::file_descriptor_sink::handle_type;

#endif /* BOOST_IOSTREAMS_WINDOWS */

// ---------------------------------------------------------------------------
extern "C" {

struct executor_helper {

    executor_helper(kth::node::configuration const& config, FILE* sout, FILE* serr)
        : sout_buffer_(boost::iostreams::file_descriptor_sink(fileno_or_devnull(sout), boost::iostreams::never_close_handle))
        , serr_buffer_(boost::iostreams::file_descriptor_sink(fileno_or_devnull(serr), boost::iostreams::never_close_handle))
        , sout_(&sout_buffer_)
        , serr_(&serr_buffer_)
        , cpp_executor_(config, sout_, serr_) 
    {}

    executor_helper(kth::node::configuration const& config, int sout_fd, int serr_fd)
        : sout_buffer_(boost::iostreams::file_descriptor_sink(fileno_or_devnull(sout_fd), boost::iostreams::never_close_handle))
        , serr_buffer_(boost::iostreams::file_descriptor_sink(fileno_or_devnull(serr_fd), boost::iostreams::never_close_handle))
        , sout_(&sout_buffer_)
        , serr_(&serr_buffer_)
        , cpp_executor_(config, sout_, serr_) 
    {
        printf("C-API executor_helper 1\n");
    }

#ifdef BOOST_IOSTREAMS_WINDOWS
    executor_helper(kth::node::configuration const& config, handle_sink sout, handle_sink serr)
        : sout_buffer_(boost::iostreams::file_descriptor_sink(sout, boost::iostreams::never_close_handle))
        , serr_buffer_(boost::iostreams::file_descriptor_sink(serr, boost::iostreams::never_close_handle))
        , sout_(&sout_buffer_)
        , serr_(&serr_buffer_)
        , cpp_executor_(config, sout_, serr_) 
    {}
#endif /* BOOST_IOSTREAMS_WINDOWS */

    boost::iostreams::stream_buffer<boost::iostreams::file_descriptor_sink> sout_buffer_;
    boost::iostreams::stream_buffer<boost::iostreams::file_descriptor_sink> serr_buffer_;
    std::ostream sout_;
    std::ostream serr_;
    kth::capi::executor cpp_executor_;
};

kth_node_t kth_node_construct(kth_settings const* settings, FILE* sout, FILE* serr) {
    auto cpp = kth::capi::helpers::settings_to_cpp(*settings);
    return new executor_helper(cpp, sout, serr);
}

kth_node_t kth_node_construct_fd(kth_settings const* settings, int sout_fd, int serr_fd) {
    printf("C-API kth_node_construct_fd 1\n");
    auto cpp = kth::capi::helpers::settings_to_cpp(*settings);
    printf("C-API kth_node_construct_fd 2\n");
    return new executor_helper(cpp, sout_fd, serr_fd);
}

#ifdef BOOST_IOSTREAMS_WINDOWS
kth_node_t kth_node_construct_handles(kth_settings const* settings, void* sout, void* serr) {
    auto cpp = kth::capi::helpers::settings_to_cpp(*settings);
    return new executor_helper(cpp, sout, serr);
}
#endif /* BOOST_IOSTREAMS_WINDOWS */

void kth_node_destruct(kth_node_t node) {
    delete node;
}

#if ! defined(KTH_DB_READONLY)
int kth_node_initchain(kth_node_t node) {
    // TODO(fernando): return error_t to inform error in detail
    try {
        return kth::bool_to_int(node->cpp_executor_.do_initchain());
//    } catch (const std::exception& e) {
//        return 0;
    } catch (...) {
        return 0;
    }
}
#endif // ! defined(KTH_DB_READONLY)

void kth_node_run(kth_node_t node, void* ctx, kth_run_handler_t handler) {
    try {
        node->cpp_executor_.run([node, ctx, handler](std::error_code const& ec) {
            if (handler != nullptr) {
                handler(node, ctx, ec.value());
            }
        });
    } catch (...) {
        handler(node, ctx, 1); // TODO(fernando): return error_t to inform errors in detail
    }
}

#if ! defined(KTH_DB_READONLY)
void kth_node_init_and_run(kth_node_t node, void* ctx, kth_run_handler_t handler) {
    try {
        node->cpp_executor_.init_and_run([node, ctx, handler](std::error_code const& ec) {
            if (handler != nullptr) {
                handler(node, ctx, ec.value());
            }
        });
    } catch (...) {
        handler(node, ctx, 1); // TODO(fernando): return error_t to inform errors in detail
    }
}

void kth_node_init_run_and_wait_for_signal(kth_node_t node, void* ctx, kth_run_handler_t handler) {
    node->cpp_executor_.init_run_and_wait_for_signal([node, ctx, handler](std::error_code const& ec) {
        if (handler != nullptr) {
            handler(node, ctx, ec.value());
        }
    });
}

#endif // ! defined(KTH_DB_READONLY)

int kth_node_run_wait(kth_node_t node) {
    boost::latch latch(2); //Note: workaround to fix an error on some versions of Boost.Threads

    int res;
    bool run_res = false;

    try {
        run_res = node->cpp_executor_.run([&](std::error_code const& ec) {
            res = ec.value();
            latch.count_down();
        });
    } catch (...) {
        run_res = false;
    }

    if (run_res) {
        latch.count_down_and_wait();
        return res;
    }

    return 1; // TODO(fernando): return error_t to inform errors in detail
}

#if ! defined(KTH_DB_READONLY)
int kth_node_init_and_run_wait(kth_node_t node) {
    
    boost::latch latch(2); //Note: workaround to fix an error on some versions of Boost.Threads

    int res;
    bool run_res = false;

    try {
        run_res = node->cpp_executor_.init_and_run([&](std::error_code const& ec) {
            res = ec.value();
            latch.count_down();
        });
    } catch (...) {
        run_res = false;
    }

    if (run_res) {
        latch.count_down_and_wait();
        return res;
    }

    return 1; // TODO(fernando): return error_t to inform errors in detail
}
#endif // ! defined(KTH_DB_READONLY)


int kth_node_stop(kth_node_t node) {
    auto res = static_cast<int>(node->cpp_executor_.stop());
    return res;
}

void kth_node_signal_stop(kth_node_t node) {
    node->cpp_executor_.signal_stop();
}

int kth_node_close(kth_node_t node) {
   return node->cpp_executor_.node().close();
}

int kth_node_stopped(kth_node_t node) {
    return static_cast<int>(node->cpp_executor_.stopped());
}

kth_chain_t kth_node_get_chain(kth_node_t node) {
    return &(node->cpp_executor_.node().chain());
}

kth_p2p_t kth_node_get_p2p(kth_node_t node) {
    return &static_cast<kth::network::p2p&>(node->cpp_executor_.node());
}

void kth_node_print_thread_id() {
    std::cout << std::this_thread::get_id() << '\n';
}

#ifdef KTH_WITH_KEOKEN
keoken_manager_t kth_node_get_keoken_manager(kth_node_t node) {
    // return &(node->cpp_executor_.node().keoken_manager());
    return &(node->cpp_executor_.keoken_manager());
}
#endif

char const* kth_node_version() {
    return KTH_CAPI_VERSION;
}

} // extern "C"
