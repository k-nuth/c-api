// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <chrono>
#include <csignal>
#include <cstdio>
#include <iostream>
#include <thread>

#include <kth/capi/chain/chain.h>
#include <kth/capi/chain/history_compact.h>
#include <kth/capi/chain/history_compact_list.h>
#include <kth/capi/chain/input.h>
#include <kth/capi/chain/input_list.h>
#include <kth/capi/chain/output.h>
#include <kth/capi/chain/output_list.h>
#include <kth/capi/chain/output_point.h>
#include <kth/capi/chain/script.h>
#include <kth/capi/chain/transaction.h>
#include <kth/capi/chain/transaction_list.h>
#include <kth/capi/node.h>
#include <kth/capi/hash_list.h>
#include <kth/capi/helpers.hpp>
#include <kth/capi/string_list.h>
#include <kth/capi/wallet/payment_address.h>
#include <kth/capi/wallet/wallet.h>
#include <kth/capi/wallet/payment_address_list.h>

#include <kth/domain/message/transaction.hpp>

#include <kth/infrastructure/utility/binary.hpp>
#include <kth/infrastructure/wallet/hd_private.hpp>


#include <kth/capi/chain/header.h>

void print_hex(uint8_t const* data, size_t n) {
    while (n != 0) {
        printf("%02x", *data);
        ++data;
        --n;
    }
    printf("\n");
}

void wait_until_block(kth_chain_t chain, size_t desired_height) {
    uint64_t height;
    int error = kth_chain_sync_last_height(chain, &height);

    while (error == 0 && height < desired_height) {
        error = kth_chain_sync_last_height(chain, &height);

        if (height < desired_height) {
            std::this_thread::sleep_for(std::chrono::seconds(10));
        }
    }
}


int main(int argc, char* argv[]) {
    kth_bool_t ok;
    char* error_message;
    kth_settings settings = kth_config_settings_get_from_file("/home/fernando/testnet4/testnet4.cfg", &ok, &error_message);
    auto node = kth_node_construct(settings, stdout, stderr);
    int runres = kth_node_run_wait(node);
    auto chain = kth_node_get_chain(node);

    kth_header_t header;
    kth_size_t height;
    auto res = kth_chain_sync_block_header_by_height(chain, 2300, &header, &height);
    kth_hash_t hash = kth_chain_header_hash(header);
    print_hex(hash.hash, 32);

    auto version = kth_chain_header_version(header);
    auto previous_block_hash = kth_chain_header_previous_block_hash(header);
    auto merkle = kth_chain_header_merkle(header);
    auto timestamp = kth_chain_header_timestamp(header);
    auto bits = kth_chain_header_bits(header);
    auto nonce = kth_chain_header_nonce(header);

    print_hex(previous_block_hash.hash, 32);
    print_hex(merkle.hash, 32);


    kth_size_t datasize1;
    auto* data1 = kth_chain_header_to_data(header, 0, &datasize1);
    print_hex(data1, datasize1);

    kth_header_t new_header = kth_chain_header_construct(version, previous_block_hash.hash, merkle.hash, timestamp, bits, nonce);
    kth_chain_header_destruct(header);
    kth_hash_t new_hash = kth_chain_header_hash(new_header);
    print_hex(new_hash.hash, 32);

    kth_size_t datasize2;
    auto* data2 = kth_chain_header_to_data(new_header, 0, &datasize2);
    print_hex(data2, datasize2);

}


// 000000206f02957eb726a4a50fc471cb15e25099f6af5a976044a5fae905580800000000f1bb8753254766f2ebea2657aa991782fdd2c99a43db0230b51058421373ba9b93a7445fa3c16e1c59c3b224
// 0000002000000000085805e9faa54460975aaff69950e215cb71c40fa5a426b77e95026f9bba7313425810b53002db439ac9d2fd821799aa5726eaebf26647255387bbf193a7445fa3c16e1c59c3b224
// 00000020
// 6f02957eb726a4a50fc471cb15e25099f6af5a976044a5fae90558 08 00 00 00 00

