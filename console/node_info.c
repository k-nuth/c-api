// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <stdio.h>

#include <kth/capi/node.h>

int main(int argc, char* argv[]) {

    printf("C-API version: %s\n", kth_node_capi_version());
    printf("C++-API version: %s\n", kth_node_cppapi_version());
    printf("Microarchitecture: %s\n", kth_node_microarchitecture());
    printf("March names: %s\n", kth_node_march_names());
    printf("Currency symbol: %s\n", kth_node_currency_symbol());
    printf("Currency: %s\n", kth_node_currency());
    printf("Build timestamp: %u\n", kth_node_cppapi_build_timestamp());
}
