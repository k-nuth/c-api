// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <iostream>

#include <kth/capi/libconfig/libconfig.h>

int main(int argc, char* argv[]) {

    auto config = kth_libconfig_get();

    std::cout << "log_library:          " << config.log_library << '\n';
    std::cout << "use_libmdbx:          " << config.use_libmdbx << '\n';
    std::cout << "version:              " << config.version << '\n';
    std::cout << "microarchitecture_id: " << config.microarchitecture_id << '\n';
    std::cout << "currency:             " << config.currency << '\n';
    std::cout << "mempool:              " << config.mempool << '\n';
    // std::cout << "db_mode:              " << config.db_mode << '\n';
    std::cout << "db_readonly:          " << config.db_readonly << '\n';
    std::cout << "debug_mode:           " << config.debug_mode << '\n';
    std::cout << "architecture:         " << config.architecture << '\n';
    std::cout << "os_name:              " << config.os_name << '\n';
    std::cout << "compiler_name:        " << config.compiler_name << '\n';
    std::cout << "compiler_version:     " << config.compiler_version << '\n';
    std::cout << "optimization_level:   " << config.optimization_level << '\n';
    std::cout << "build_timestamp:      " << config.build_timestamp << '\n';

    std::cout << "endianness:           " << config.endianness << '\n';
    std::cout << "size_int:             " << int(config.type_sizes.size_int) << '\n';
    std::cout << "size_long:            " << int(config.type_sizes.size_long) << '\n';
    std::cout << "size_pointer:         " << int(config.type_sizes.size_pointer) << '\n';
}
