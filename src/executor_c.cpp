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
        , actual(libbitcoin::node::configuration(libbitcoin::config::settings::mainnet), sin_, sout_, serr_)
    {
        std::ostream os(&sout_buffer_);
        os << "Hello World!" << std::endl;
    }


    boost::iostreams::stream_buffer<boost::iostreams::file_descriptor_source> sin_buffer_;
    boost::iostreams::stream_buffer<boost::iostreams::file_descriptor_sink> sout_buffer_;
    boost::iostreams::stream_buffer<boost::iostreams::file_descriptor_sink> serr_buffer_;

    std::istream sin_;
    std::ostream sout_;
    std::ostream serr_;

    bitprim::node::executor actual;
};

executor_t executor_construct(char const* path, FILE* sin, FILE* sout, FILE* serr) {
    return std::make_unique<executor>(path, stdin, stdout, stderr).release();
}

void executor_destruct(executor_t exec) {
    delete exec;
}

int executor_initchain(executor_t exec) {
    return exec->actual.do_initchain();
}

int executor_run(executor_t exec) {
    return exec->actual.run();
}

void executor_stop(executor_t exec) {
    exec->actual.stop();
}


} /* extern "C" */
