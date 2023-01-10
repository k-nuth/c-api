// Copyright (c) 2016-2023 Knuth Project developers.
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
    std::cout << "db_mode:              " << config.db_mode << '\n';
    std::cout << "db_readonly:          " << config.db_readonly << '\n';
    std::cout << "debug_mode:           " << config.debug_mode << '\n';
}
