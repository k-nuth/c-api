/**
 * Copyright (c) 2017 Bitprim developers (see AUTHORS)
 *
 * This file is part of Bitprim.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <bitprim/nodecint/executor_c.h>
#include <cstdio>
#include <memory>
#include <boost/iostreams/device/file_descriptor.hpp>
#include <boost/thread/latch.hpp>
#include <bitprim/nodecint/executor.hpp>
#include <bitcoin/bitcoin/wallet/mnemonic.hpp>

libbitcoin::node::configuration make_config(char const* path) {
    libbitcoin::node::configuration config(libbitcoin::config::settings::mainnet);
    config.file = boost::filesystem::path(path);
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
    return fileno(devnull_file());
}

inline
int fileno_or_devnull(FILE* f) {
    if (f == nullptr) {
        return devnull_fileno();
    }

    return fileno(f);
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
    bitprim::nodecint::executor actual;
};

executor_t executor_construct(char const* path, FILE* sout, FILE* serr) {
    return std::make_unique<executor>(path, sout, serr).release();
}

executor_t executor_construct_fd(char const* path, int sout_fd, int serr_fd) {
    return std::make_unique<executor>(path, sout_fd, serr_fd).release();
}

#ifdef BOOST_IOSTREAMS_WINDOWS

executor_t executor_construct_handles(char const* path, void* sout, void* serr) {
    return std::make_unique<executor>(path, sout, serr).release();
}

#endif /* BOOST_IOSTREAMS_WINDOWS */


void executor_destruct(executor_t exec) {
//    std::cout << "From C++: executor_destruct\n";
//    printf("executor_destruct - exec: 0x%" PRIXPTR "\n", (uintptr_t)exec);
    delete exec;
}

int executor_initchain(executor_t exec) {
    // TODO(fernando): return error_t to inform error in detail
    try {
        return static_cast<int>(exec->actual.do_initchain());
//    } catch (const std::exception& e) {
//        return 0;
    } catch (...) {
        return 0;
    }
}

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

void executor_stop(executor_t exec) {
    exec->actual.stop();
}

chain_t executor_get_chain(executor_t exec) {
    return &(exec->actual.node().chain());

}

void executor_get_raw_transaction(executor_t exec) {
    std::cout << "-----------Coinbase tx-----------" << std::endl;
    exec->actual.node().getrawtransaction("9b0fc92260312ce44e74ef369f5c66bbb85848f2eddd5a7a1cde251e54ccfdd5", false);
    std::cout << "-------- NO Coinbase tx----------" << std::endl;
    exec->actual.node().getrawtransaction("f4184fc596403b9d638783cf57adfe4c75c605f6356fbc91338530e9831e9e16", false);
}

void executor_getspentinfo(executor_t exec){
    std::cout << "-----------executor_getspentinfo-----------" << std::endl;
    exec->actual.node().getspentinfo("0437cd7f8525ceed2324359c2d0ba26006d92d856a9c20fa0241106ee5a597c9", 0);
}

void executor_getaddresstxids(executor_t exec){
    std::cout << "-----------executor_getaddresstxids-----------" << std::endl;
    libbitcoin::wallet::payment_address address("12cbQLTFMXRnSzktFkuoG3eHoMeFtpTu3S");
    exec->actual.node().getaddresstxids(address, 0, 190);
}

void executor_getaddressdeltas(executor_t exec){
    std::cout << "-----------executor_getaddressdeltas-----------" << std::endl;
    libbitcoin::wallet::payment_address address("12cbQLTFMXRnSzktFkuoG3eHoMeFtpTu3S");
    exec->actual.node().getaddressdeltas(address, 0, 190, false);
}


p2p_t executor_get_p2p(executor_t exec) {
    return &static_cast<libbitcoin::network::p2p&>(exec->actual.node());
}

} /* extern "C" */
