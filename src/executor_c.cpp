// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#include <kth/capi/executor_c.h>

#include <cstdio>
#include <memory>

#include <boost/iostreams/device/file_descriptor.hpp>
#include <boost/thread/latch.hpp>

#include <kth/capi/executor.hpp>
#include <kth/capi/helpers.hpp>
#include <kth/capi/version.h>

#include <kth/infrastructure/wallet/mnemonic.hpp>  //Warning, put it after boost headers

kth::node::configuration make_config(char const* path) {
    kth::node::configuration config(kth::infrastructure::config::settings::mainnet);
    config.file = std::filesystem::path(path);
    return config;
}

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
//using handle_source = typename boost::iostreams::file_descriptor_source::handle_type;
using handle_sink = typename boost::iostreams::file_descriptor_sink::handle_type;

//inline
//int fileno_or_devnull(handle_sink s) {
//    if (s == nullptr) {
//        return devnull_fileno();
//    } else {
//        return fileno(f);
//    }
//}

#endif /* BOOST_IOSTREAMS_WINDOWS */

// ---------------------------------------------------------------------------
extern "C" {

struct executor {

    executor(char const* path, FILE* sout, FILE* serr)
        : sout_buffer_(boost::iostreams::file_descriptor_sink(fileno_or_devnull(sout), boost::iostreams::never_close_handle))
        , serr_buffer_(boost::iostreams::file_descriptor_sink(fileno_or_devnull(serr), boost::iostreams::never_close_handle))
        , sout_(&sout_buffer_)
        , serr_(&serr_buffer_)
        , actual(make_config(path), sout_, serr_) 
    {}

    executor(char const* path, int sout_fd, int serr_fd)
        : sout_buffer_(boost::iostreams::file_descriptor_sink(fileno_or_devnull(sout_fd), boost::iostreams::never_close_handle))
        , serr_buffer_(boost::iostreams::file_descriptor_sink(fileno_or_devnull(serr_fd), boost::iostreams::never_close_handle))
        , sout_(&sout_buffer_)
        , serr_(&serr_buffer_)
        , actual(make_config(path), sout_, serr_) 
    {}

#ifdef BOOST_IOSTREAMS_WINDOWS
    executor(char const* path, handle_sink sout, handle_sink serr)
        : sout_buffer_(boost::iostreams::file_descriptor_sink(sout, boost::iostreams::never_close_handle))
        , serr_buffer_(boost::iostreams::file_descriptor_sink(serr, boost::iostreams::never_close_handle))
        , sout_(&sout_buffer_)
        , serr_(&serr_buffer_)
        , actual(make_config(path), sout_, serr_) 
    {}
#endif /* BOOST_IOSTREAMS_WINDOWS */

    boost::iostreams::stream_buffer<boost::iostreams::file_descriptor_sink> sout_buffer_;
    boost::iostreams::stream_buffer<boost::iostreams::file_descriptor_sink> serr_buffer_;
    std::ostream sout_;
    std::ostream serr_;
    kth::capi::executor actual;
};

executor_t executor_construct(char const* path, FILE* sout, FILE* serr) {
    // return std::make_unique<executor>(path, sout, serr).release();
    return new executor(path, sout, serr);
}

executor_t executor_construct_fd(char const* path, int sout_fd, int serr_fd) {
    // return std::make_unique<executor>(path, sout_fd, serr_fd).release();
    return new executor(path, sout_fd, serr_fd);
}

#ifdef BOOST_IOSTREAMS_WINDOWS

executor_t executor_construct_handles(char const* path, void* sout, void* serr) {
    // return std::make_unique<executor>(path, sout_fd, serr_fd).release();
    return new executor(path, sout, serr);
}

#endif /* BOOST_IOSTREAMS_WINDOWS */

void executor_destruct(executor_t exec) {
    delete exec;
}

#if ! defined(KTH_DB_READONLY)
int executor_initchain(executor_t exec) {
    // TODO(fernando): return error_t to inform error in detail
    try {
        return kth::bool_to_int(exec->actual.do_initchain());
//    } catch (const std::exception& e) {
//        return 0;
    } catch (...) {
        return 0;
    }
}
#endif // ! defined(KTH_DB_READONLY)

void executor_run(executor_t exec, void* ctx, run_handler_t handler) {
    try {
        exec->actual.run([exec, ctx, handler](std::error_code const& ec) {
            if (handler != nullptr) {
                handler(exec, ctx, ec.value());
            }
        });
    } catch (...) {
        handler(exec, ctx, 1); // TODO(fernando): return error_t to inform errors in detail
    }
}

#if ! defined(KTH_DB_READONLY)
void executor_init_and_run(executor_t exec, void* ctx, run_handler_t handler) {
    try {
        exec->actual.init_and_run([exec, ctx, handler](std::error_code const& ec) {
            if (handler != nullptr) {
                handler(exec, ctx, ec.value());
            }
        });
    } catch (...) {
        handler(exec, ctx, 1); // TODO(fernando): return error_t to inform errors in detail
    }
}

void executor_init_run_and_wait_for_signal(executor_t exec, void* ctx, run_handler_t handler) {
    exec->actual.init_run_and_wait_for_signal([exec, ctx, handler](std::error_code const& ec) {
        if (handler != nullptr) {
            handler(exec, ctx, ec.value());
        }
    });
}

#endif // ! defined(KTH_DB_READONLY)

int executor_run_wait(executor_t exec) {
    boost::latch latch(2); //Note: workaround to fix an error on some versions of Boost.Threads

    int res;
    bool run_res = false;

    try {
        run_res = exec->actual.run([&](std::error_code const& ec) {
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
int executor_init_and_run_wait(executor_t exec) {
    
    boost::latch latch(2); //Note: workaround to fix an error on some versions of Boost.Threads

    int res;
    bool run_res = false;

    try {
        run_res = exec->actual.init_and_run([&](std::error_code const& ec) {
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


int executor_stop(executor_t exec) {
    auto res = static_cast<int>(exec->actual.stop());
    return res;
}

void executor_signal_stop(executor_t exec) {
    exec->actual.signal_stop();
}

int executor_close(executor_t exec) {
   return exec->actual.node().close();
}

int executor_stopped(executor_t exec) {
    return static_cast<int>(exec->actual.stopped());
}

int executor_load_config_valid(executor_t exec) {
    return static_cast<int>(exec->actual.load_config_valid());
}

chain_t executor_get_chain(executor_t exec) {
    return &(exec->actual.node().chain());
}

p2p_t executor_get_p2p(executor_t exec) {
    return &static_cast<kth::network::p2p&>(exec->actual.node());
}

void executor_print_thread_id() {
    std::cout << std::this_thread::get_id() << std::endl;
}

#ifdef KTH_WITH_KEOKEN
keoken_manager_t executor_get_keoken_manager(executor_t exec) {
    // return &(exec->actual.node().keoken_manager());
    return &(exec->actual.keoken_manager());
}
#endif

char const* executor_version() {
    return KTH_CAPI_VERSION;
}

} // extern "C"
