// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <cstdio>

#include <algorithm>
#include <chrono>
#include <stdexcept>
#include <thread>

#include <kth/capi.h>
#include <kth/infrastructure.hpp>
#include <kth/capi/helpers.hpp>

#include <kth/capi/config/checkpoint.h>
#include <kth/capi/config/blockchain_settings.h>
#include <kth/capi/config/database_settings.h>
#include <kth/capi/config/network_settings.h>
#include <kth/capi/config/node_settings.h>
#include <kth/capi/config/settings.h>
#include <kth/capi/hash.h>

int main(int argc, char* argv[]) {

    kth_checkpoint cp1 {kth_str_to_hash("000000000000000000eb9bc1f9557dc9e2cfe576f57a52f6be94720b338029e4"), 478557};
    kth_checkpoint cp2 {kth_str_to_hash("0000000000000000011865af4122fe3b144e2cbeea86142e8ff2fb4107352d43"), 478558};
    kth_checkpoint cp3 {kth_str_to_hash("000000000000000000651ef99cb9fcbe0dadde1d424bd9f15ff20136191a5eec"), 478559};

    kth_blockchain_settings blk_settings = kth_config_blockchain_settings_default(kth_network_mainnet);
    assert(blk_settings.checkpoint_count == 57);
    assert(strcmp(kth_hash_to_str(blk_settings.checkpoints[28].hash), "000000000000000000651ef99cb9fcbe0dadde1d424bd9f15ff20136191a5eec") == 0);
    assert(blk_settings.checkpoints[28].height == 478559);

    kth_database_settings db_settings = kth_config_database_settings_default(kth_network_mainnet);
    assert(strcmp(db_settings.directory, "blockchain") == 0);

    kth_network_settings net_settings = kth_config_network_settings_default(kth_network_mainnet);
    assert(strcmp(net_settings.hosts_file, "hosts.cache") == 0);

    kth_node_settings node_settings = kth_config_node_settings_default(kth_network_mainnet);
    assert(node_settings.block_latency_seconds == 60);

    kth_settings settings = kth_config_settings_default(kth_network_mainnet);
    assert(settings.chain.checkpoint_count == 57);
    assert(strcmp(kth_hash_to_str(settings.chain.checkpoints[28].hash), "000000000000000000651ef99cb9fcbe0dadde1d424bd9f15ff20136191a5eec") == 0);
    assert(settings.chain.checkpoints[28].height == 478559);
    assert(strcmp(settings.database.directory, "blockchain") == 0);
    assert(strcmp(settings.network.hosts_file, "hosts.cache") == 0);
    assert(settings.node.block_latency_seconds == 60);

    return 0;
}
