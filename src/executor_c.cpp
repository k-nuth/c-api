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

#include <memory>

#include <boost/iostreams/device/file_descriptor.hpp>

#include <bitprim/nodecint/executor.hpp>

#include <inttypes.h>   //TODO: Remove, it is for the printf (printing pointer addresses)


libbitcoin::node::configuration make_config(char const* path) {
    libbitcoin::node::configuration config(libbitcoin::config::settings::mainnet);
    config.file = boost::filesystem::path(path);
    return config;
}

extern "C" {

struct executor {

    // template <typename... Args>
    // node(Args&&... args)
    //     : actual(std::forward<Args>(args)...)
    // {}

    executor(char const* path, FILE* sin, FILE* sout, FILE* serr)
        //: actual(path)
        : sin_buffer_(boost::iostreams::file_descriptor_source(fileno(sin), boost::iostreams::never_close_handle))
        , sout_buffer_(boost::iostreams::file_descriptor_sink(fileno(sout), boost::iostreams::never_close_handle))
        , serr_buffer_(boost::iostreams::file_descriptor_sink(fileno(serr), boost::iostreams::never_close_handle))
        , sin_(&sin_buffer_)
        , sout_(&sout_buffer_)
        , serr_(&serr_buffer_)
//        , actual(libbitcoin::node::configuration(libbitcoin::config::settings::mainnet), sin_, sout_, serr_)
        , actual(make_config(path), sin_, sout_, serr_)
    {
        std::ostream os(&sout_buffer_);
        os << "Hello World!" << std::endl;
    }

    executor(char const* path, int sin_fd, int sout_fd, int serr_fd)
        : sin_buffer_(boost::iostreams::file_descriptor_source(sin_fd, boost::iostreams::never_close_handle))
          , sout_buffer_(boost::iostreams::file_descriptor_sink(sout_fd, boost::iostreams::never_close_handle))
          , serr_buffer_(boost::iostreams::file_descriptor_sink(serr_fd, boost::iostreams::never_close_handle))
          , sin_(&sin_buffer_)
          , sout_(&sout_buffer_)
          , serr_(&serr_buffer_)
          , actual(make_config(path), sin_, sout_, serr_)
    {
        std::ostream os(&sout_buffer_);
        os << "Hello World -- 2!" << std::endl;
    }



    boost::iostreams::stream_buffer<boost::iostreams::file_descriptor_source> sin_buffer_;
    boost::iostreams::stream_buffer<boost::iostreams::file_descriptor_sink> sout_buffer_;
    boost::iostreams::stream_buffer<boost::iostreams::file_descriptor_sink> serr_buffer_;

    std::istream sin_;
    std::ostream sout_;
    std::ostream serr_;

    bitprim::nodecint::executor actual;
};

executor_t executor_construct(char const* path, FILE* sin, FILE* sout, FILE* serr) {
    return std::make_unique<executor>(path, sin, sout, serr).release();
}

executor_t executor_construct_fd(char const* path, int sin_fd, int sout_fd, int serr_fd) {
    return std::make_unique<executor>(path, sin_fd, sout_fd, serr_fd).release();
}

void executor_destruct(executor_t exec) {
    std::cout << "From C++: executor_destruct\n";
    printf("executor_destruct - exec: 0x%" PRIXPTR "\n", (uintptr_t)exec);

    delete exec;
}

int executor_initchain(executor_t exec) {
    return exec->actual.do_initchain();
}

int executor_run(executor_t exec) {
    return exec->actual.run();
}

int executor_run_wait(executor_t exec) {
    return exec->actual.run_wait();
}

void executor_stop(executor_t exec) {
    exec->actual.stop();
}






BITPRIM_EXPORT
void executor_fetch_last_height(executor_t exec, last_height_fetch_handler_t handler) {
    exec->actual.node().chain().fetch_last_height([handler](std::error_code const& ec, size_t h) {
        handler(h);
    });
}

BITPRIM_EXPORT
void executor_fetch_block_height(executor_t exec, hash_t hash, block_height_fetch_handler_t handler) {

    libbitcoin::hash_digest hash_cpp;
    std::copy_n(hash, hash_cpp.size(), std::begin(hash_cpp));

    exec->actual.node().chain().fetch_block_height(hash_cpp, [handler](std::error_code const& ec, size_t h) {
        handler(h);
    });
}

BITPRIM_EXPORT
void executor_fetch_block_header(executor_t exec, size_t height, block_header_fetch_handler_t handler) {

    exec->actual.node().chain().fetch_block_header(height, [handler](std::error_code const& ec, libbitcoin::message::header::ptr header, size_t h) {
        handler(header.get(), h);
    });
}







} /* extern "C" */
