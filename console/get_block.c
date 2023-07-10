// Copyright (c) 2016-2023 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <assert.h>
#include <stdio.h>

#include <kth/capi.h>

void handler(kth_chain_t chain, void* ctx, kth_error_code_t error, kth_block_t block, kth_size_t height) {
    if (error != kth_ec_success) {
        printf("kth_chain_async_block_by_height - error: %d\n", error);
        return;
    }
    printf("kth_chain_async_block_by_height - error: %d, height: %llu\n", error, height);
    kth_chain_block_destruct(block);
}

int main() {
    kth_settings settings = kth_config_settings_default(kth_network_mainnet);
    settings.database.db_max_size = 2 * 1024 * 1024;    // 2MiB
    settings.database.directory = "blocks";
    settings.database.db_mode = kth_db_mode_pruned;

    assert(settings.database.db_max_size == 2 * 1024 * 1024);
    assert(strcmp(settings.database.directory, "blockchain") == 0);
    assert(settings.database.db_mode == kth_db_mode_normal);


    // kth_db_mode_pruned = 0,
    // kth_db_mode_normal = 1,
    // kth_db_mode_full_indexed = 2

    kth_node_t node = kth_node_construct(&settings, 1);
    kth_error_code_t res = kth_node_init_run_sync(node, kth_start_modules_just_chain);
    printf("kth_node_init_run_sync - res: %d\n", res);
    kth_chain_t chain = kth_node_get_chain(node);
    // kth_block_t out_block;
    // kth_size_t out_height;
    // res  = kth_chain_sync_block_by_height(chain, 0, &out_block, &out_height);
    // printf("kth_chain_sync_block_by_height - res: %d, height: %llu\n", res, out_height);


    kth_chain_async_block_by_height(chain, NULL, 0, handler);

    return 0;
}

