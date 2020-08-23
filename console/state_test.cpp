// Copyright (c) 2016-2020 Knuth Project developers.
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
#include <kth/capi/node.h>
#include <kth/capi/hash_list.h>
#include <kth/capi/helpers.hpp>
#include <kth/capi/wallet/payment_address.h>
#include <kth/capi/wallet/wallet.h>
#include <kth/capi/wallet/word_list.h>

#include <kth/capi/keoken/get_assets_data.h>
#include <kth/capi/keoken/get_assets_list.h>
#include <kth/capi/keoken/manager.h>
#include <kth/capi/keoken/memory_state.h>
#include <kth/capi/keoken/state_delegated.h>

#include <kth/domain/message/transaction.hpp>

#include <kth/infrastructure/utility/binary.hpp>
#include <kth/infrastructure/wallet/hd_private.hpp>


void my_set_initial_asset_id(void*  /*ctx*/, keoken_asset_id_t asset_id_initial) {
    printf("my_set_initial_asset_id - asset_id_initial: %d\n", asset_id_initial);
}

void my_create_asset(void*  /*ctx*/, char const* asset_name, keoken_amount_t  /*asset_amount*/, kth_payment_address_t  /*owner*/, kth_size_t  /*block_height*/, kth_hash_t  /*txid*/) {
    printf("my_create_asset - asset_name: %s\n", asset_name);
}

void my_create_balance_entry(void*  /*ctx*/, keoken_asset_id_t asset_id, keoken_amount_t  /*asset_amount*/, kth_payment_address_t  /*source*/, kth_payment_address_t  /*target*/,  kth_size_t  /*block_height*/, kth_hash_t  /*txid*/) {
    printf("my_create_balance_entry - asset_id: %d\n", asset_id);
}

kth_bool_t my_asset_id_exists(void*  /*ctx*/, keoken_asset_id_t id) {
    printf("my_asset_id_exists - id: %d\n", id);
    return 0;
}

keoken_amount_t my_get_balance(void*  /*ctx*/, keoken_asset_id_t  /*id*/, kth_payment_address_t  /*addr*/) {
    printf("my_get_balance\n");
    return 0;
}

keoken_get_assets_by_address_list_t my_get_assets_by_address(void*  /*ctx*/, kth_payment_address_t  /*addr*/) {
    printf("my_get_assets_by_address\n");
    return nullptr;
}

keoken_get_assets_list_t my_get_assets(void*  /*ctx*/) {
    printf("my_get_assets\n");
    return nullptr;
}

keoken_get_all_asset_addresses_list_t my_get_all_asset_addresses(void*  /*ctx*/) {
    printf("my_get_all_asset_addresses\n");
    return nullptr;
}



void my_set_initial_asset_id_state(void* ctx, keoken_asset_id_t asset_id_initial) {
    printf("my_set_initial_asset_id_state - asset_id_initial: %d\n", asset_id_initial);
    auto st = static_cast<keoken_memory_state_t>(ctx);
    keoken_memory_state_set_initial_asset_id(st, asset_id_initial);
}

void my_reset_state(void* ctx) {
    printf("my_reset_state\n");
    auto st = static_cast<keoken_memory_state_t>(ctx);
    keoken_memory_state_reset(st);
}

void my_remove_up_to_state(void* ctx, uint64_t height) {
    printf("my_remove_up_to_state - height: %lu\n", height);
    auto st = static_cast<keoken_memory_state_t>(ctx);
    keoken_memory_state_remove_up_to(st, height);
}

void my_create_asset_state(void* ctx, char const* asset_name, keoken_amount_t asset_amount, kth_payment_address_t owner, kth_size_t block_height, kth_hash_t txid) {
    printf("my_create_asset_state - asset_name: %s\n", asset_name);
    auto owner_enc = kth_wallet_payment_address_encoded(owner);
    printf("my_create_asset_state - owner_enc: %s\n", owner_enc);

    auto st = static_cast<keoken_memory_state_t>(ctx);
    keoken_memory_state_create_asset(st, asset_name, asset_amount, owner, block_height, txid);
}

void my_create_balance_entry_state(void* ctx, keoken_asset_id_t asset_id, keoken_amount_t asset_amount, kth_payment_address_t source, kth_payment_address_t target,  kth_size_t block_height, kth_hash_t txid) {
    printf("my_create_balance_entry_state - asset_id: %d\n", asset_id);
    auto st = static_cast<keoken_memory_state_t>(ctx);
    keoken_memory_state_create_balance_entry(st, asset_id, asset_amount, source, target, block_height, txid);
}

kth_bool_t my_asset_id_exists_state(void* ctx, keoken_asset_id_t id) {
    printf("my_asset_id_exists_state - id: %d\n", id);
    auto st = static_cast<keoken_memory_state_t>(ctx);
    return keoken_memory_state_asset_id_exists(st, id);
}

keoken_amount_t my_get_balance_state(void* ctx, keoken_asset_id_t id, kth_payment_address_t addr) {
    printf("my_get_balance_state\n");
    auto st = static_cast<keoken_memory_state_t>(ctx);
    return keoken_memory_state_get_balance(st, id, addr);
}

keoken_get_assets_by_address_list_t my_get_assets_by_address_state(void* ctx, kth_payment_address_t addr) {
    printf("my_get_assets_by_address_state\n");
    auto st = static_cast<keoken_memory_state_t>(ctx);
    return keoken_memory_state_get_assets_by_address(st, addr);
}

keoken_get_assets_list_t my_get_assets_state(void* ctx) {
    printf("my_get_assets_state\n");
    auto st = static_cast<keoken_memory_state_t>(ctx);
    return keoken_memory_state_get_assets(st);
}

keoken_get_all_asset_addresses_list_t my_get_all_asset_addresses_state(void* ctx) {
    printf("my_get_all_asset_addresses_state\n");
    auto st = static_cast<keoken_memory_state_t>(ctx);
    return keoken_memory_state_get_all_asset_addresses(st);
}


    




kth_node_t exec;
bool stopped = false;

void handle_stop(int  /*signal*/) {
    std::cout << "handle_stop()\n";
    kth_node_stop(exec);
}

int main(int /*argc*/, char* /*argv*/[]) {
//    using namespace std::chrono_literals;

    std::signal(SIGINT, handle_stop);
    std::signal(SIGTERM, handle_stop);

    exec = kth_node_construct("cfg1", stdout, stderr);

    // int res1 = kth_node_initchain(exec);
    // if (res1 == 0) {
    //     printf("Error initializing files\n");
    //     kth_node_destruct(exec);
    //     return -1;
    // }

    int res2 = kth_node_run_wait(exec);

    if (res2 != 0) {
        printf("Error initializing files\n");
        kth_node_destruct(exec);
        return -1;
    }
    std::this_thread::sleep_for(std::chrono::seconds(10));


    // kth_chain_t chain = kth_node_get_chain(exec);

    keoken_manager_t keo_manager = kth_node_get_keoken_manager(exec);

    keoken_memory_state_t memory_state = keoken_memory_state_construct_default();
    keoken_manager_configure_state(keo_manager
                           , memory_state 
                           , my_set_initial_asset_id_state
                           , my_reset_state
                           , my_remove_up_to_state
                           , my_create_asset_state
                           , my_create_balance_entry_state
                           , my_asset_id_exists_state
                           , my_get_balance_state
                           , my_get_assets_by_address_state
                           , my_get_assets_state
                           , my_get_all_asset_addresses_state);

    printf("***************************************************************************************\n");

    keoken_manager_initialize_from_blockchain(keo_manager);

    printf("***************************************************************************************\n");

    keoken_get_assets_list_t list = keoken_manager_get_assets(keo_manager);
    auto n = keoken_get_assets_list_count(list);
    printf("keoken_get_assets_list_count: %lu\n", n);

    while (n-- != 0u) {
        printf("while n: %lu\n", n);
        auto elem = keoken_get_assets_list_nth(list, n);


        auto asset_id = keoken_get_assets_data_asset_id(elem);
        char const* asset_name = keoken_get_assets_data_asset_name(elem);
        auto amount = keoken_get_assets_data_amount(elem);

        printf("asset_id:   %d\n", asset_id);
        printf("asset_name: %s\n", asset_name);
        printf("amount:     %ld\n", amount);
    }    

    while (kth_node_stopped(exec) == 0) {
        printf("sleeping for 10 seconds...\n");
        std::this_thread::sleep_for(std::chrono::seconds(10));
    }

    kth_node_destruct(exec);
    return 0;
}
