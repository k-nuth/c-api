/**
 * Copyright (c) 2016-2018 Bitprim Inc.
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

#include <chrono>
#include <csignal>
#include <cstdio>
#include <iostream>
#include <thread>

#include <bitprim/nodecint/chain/chain.h>
#include <bitprim/nodecint/chain/history_compact.h>
#include <bitprim/nodecint/chain/history_compact_list.h>
#include <bitprim/nodecint/chain/input.h>
#include <bitprim/nodecint/chain/input_list.h>
#include <bitprim/nodecint/chain/output.h>
#include <bitprim/nodecint/chain/output_list.h>
#include <bitprim/nodecint/chain/output_point.h>
#include <bitprim/nodecint/chain/script.h>
#include <bitprim/nodecint/chain/transaction.h>
#include <bitprim/nodecint/executor_c.h>
#include <bitprim/nodecint/hash_list.h>
#include <bitprim/nodecint/helpers.hpp>
#include <bitprim/nodecint/wallet/payment_address.h>
#include <bitprim/nodecint/wallet/wallet.h>
#include <bitprim/nodecint/wallet/word_list.h>

#include <bitprim/nodecint/keoken/get_assets_data.h>
#include <bitprim/nodecint/keoken/get_assets_list.h>
#include <bitprim/nodecint/keoken/manager.h>
#include <bitprim/nodecint/keoken/memory_state.h>
#include <bitprim/nodecint/keoken/state_delegated.h>

#include <bitcoin/bitcoin/message/transaction.hpp>
#include <bitcoin/bitcoin/utility/binary.hpp>
#include <bitcoin/bitcoin/wallet/hd_private.hpp>


void my_set_initial_asset_id(void*  /*ctx*/, keoken_asset_id_t asset_id_initial) {
    printf("my_set_initial_asset_id - asset_id_initial: %d\n", asset_id_initial);
}

void my_create_asset(void*  /*ctx*/, char const* asset_name, keoken_amount_t  /*asset_amount*/, payment_address_t  /*owner*/, uint64_t /*size_t*/  /*block_height*/, hash_t  /*txid*/) {
    printf("my_create_asset - asset_name: %s\n", asset_name);
}

void my_create_balance_entry(void*  /*ctx*/, keoken_asset_id_t asset_id, keoken_amount_t  /*asset_amount*/, payment_address_t  /*source*/, payment_address_t  /*target*/,  uint64_t /*size_t*/  /*block_height*/, hash_t  /*txid*/) {
    printf("my_create_balance_entry - asset_id: %d\n", asset_id);
}

bool_t my_asset_id_exists(void*  /*ctx*/, keoken_asset_id_t id) {
    printf("my_asset_id_exists - id: %d\n", id);
    return 0;
}

keoken_amount_t my_get_balance(void*  /*ctx*/, keoken_asset_id_t  /*id*/, payment_address_t  /*addr*/) {
    printf("my_get_balance\n");
    return 0;
}

get_assets_by_address_list_t my_get_assets_by_address(void*  /*ctx*/, payment_address_t  /*addr*/) {
    printf("my_get_assets_by_address\n");
    return nullptr;
}

get_assets_list_t my_get_assets(void*  /*ctx*/) {
    printf("my_get_assets\n");
    return nullptr;
}

get_all_asset_addresses_list_t my_get_all_asset_addresses(void*  /*ctx*/) {
    printf("my_get_all_asset_addresses\n");
    return nullptr;
}












void my_set_initial_asset_id_state(void* ctx, keoken_asset_id_t asset_id_initial) {
    printf("my_set_initial_asset_id_state - asset_id_initial: %d\n", asset_id_initial);
    auto st = static_cast<keoken_memory_state_t>(ctx);
    keoken_memory_state_set_initial_asset_id(st, asset_id_initial);
}

void my_create_asset_state(void* ctx, char const* asset_name, keoken_amount_t asset_amount, payment_address_t owner, uint64_t /*size_t*/ block_height, hash_t txid) {
    printf("my_create_asset_state - asset_name: %s\n", asset_name);
    auto owner_enc = wallet_payment_address_encoded(owner);
    printf("my_create_asset_state - owner_enc: %s\n", owner_enc);

    auto st = static_cast<keoken_memory_state_t>(ctx);
    keoken_memory_state_create_asset(st, asset_name, asset_amount, owner, block_height, txid);
}

void my_create_balance_entry_state(void* ctx, keoken_asset_id_t asset_id, keoken_amount_t asset_amount, payment_address_t source, payment_address_t target,  uint64_t /*size_t*/ block_height, hash_t txid) {
    printf("my_create_balance_entry_state - asset_id: %d\n", asset_id);
    auto st = static_cast<keoken_memory_state_t>(ctx);
    keoken_memory_state_create_balance_entry(st, asset_id, asset_amount, source, target, block_height, txid);
}

bool_t my_asset_id_exists_state(void* ctx, keoken_asset_id_t id) {
    printf("my_asset_id_exists_state - id: %d\n", id);
    auto st = static_cast<keoken_memory_state_t>(ctx);
    return keoken_memory_state_asset_id_exists(st, id);
}

keoken_amount_t my_get_balance_state(void* ctx, keoken_asset_id_t id, payment_address_t addr) {
    printf("my_get_balance_state\n");
    auto st = static_cast<keoken_memory_state_t>(ctx);
    return keoken_memory_state_get_balance(st, id, addr);
}

get_assets_by_address_list_t my_get_assets_by_address_state(void* ctx, payment_address_t addr) {
    printf("my_get_assets_by_address_state\n");
    auto st = static_cast<keoken_memory_state_t>(ctx);
    return keoken_memory_state_get_assets_by_address(st, addr);
}

get_assets_list_t my_get_assets_state(void* ctx) {
    printf("my_get_assets_state\n");
    auto st = static_cast<keoken_memory_state_t>(ctx);
    return keoken_memory_state_get_assets(st);
}

get_all_asset_addresses_list_t my_get_all_asset_addresses_state(void* ctx) {
    printf("my_get_all_asset_addresses_state\n");
    auto st = static_cast<keoken_memory_state_t>(ctx);
    return keoken_memory_state_get_all_asset_addresses(st);
}


    




executor_t exec;
bool stopped = false;

void handle_stop(int  /*signal*/) {
    std::cout << "handle_stop()\n";
    executor_stop(exec);
}

int main(int /*argc*/, char* /*argv*/[]) {
//    using namespace std::chrono_literals;

    std::signal(SIGINT, handle_stop);
    std::signal(SIGTERM, handle_stop);

    exec = executor_construct("cfg1", stdout, stderr);

    // int res1 = executor_initchain(exec);
    // if (res1 == 0) {
    //     printf("Error initializing files\n");
    //     executor_destruct(exec);
    //     return -1;
    // }

    int res2 = executor_run_wait(exec);

    if (res2 != 0) {
        printf("Error initializing files\n");
        executor_destruct(exec);
        return -1;
    }
    std::this_thread::sleep_for(std::chrono::seconds(10));


    // chain_t chain = executor_get_chain(exec);

    keoken_manager_t keo_manager = executor_get_keoken_manager(exec);

    // keoken_manager_configure_state(keo_manager
    //                        , nullptr 
    //                        , my_set_initial_asset_id
    //                        , my_create_asset
    //                        , my_create_balance_entry
    //                        , my_asset_id_exists
    //                        , my_get_balance
    //                        , my_get_assets_by_address
    //                        , my_get_assets
    //                        , my_get_all_asset_addresses);

    keoken_memory_state_t memory_state = keoken_memory_state_construct_default();
    keoken_manager_configure_state(keo_manager
                           , memory_state 
                           , my_set_initial_asset_id_state
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

    get_assets_list_t list = keoken_manager_get_assets(keo_manager);
    auto n = keoken_get_assets_list_count(list);
    printf("keoken_get_assets_list_count: %llu\n", n);

    while (n-- != 0u) {
        printf("while n: %llu\n", n);
        auto elem = keoken_get_assets_list_nth(list, n);


        auto asset_id = keoken_get_assets_data_asset_id(elem);
        char const* asset_name = keoken_get_assets_data_asset_name(elem);
        auto amount = keoken_get_assets_data_amount(elem);

        printf("asset_id:   %d\n", asset_id);
        printf("asset_name: %s\n", asset_name);
        printf("amount:     %lld\n", amount);
    }    

    while (executor_stopped(exec) == 0) {
        printf("sleeping for 10 seconds...\n");
        std::this_thread::sleep_for(std::chrono::seconds(10));
    }

    executor_destruct(exec);
    return 0;
}
