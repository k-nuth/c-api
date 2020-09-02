// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/capi/config/settings.h>

extern "C" {

kth_settings kth_config_settings_default(kth_network_t net) {
    kth_settings res;

    //TODO(fernando)
    // res.node = kth_config_node_settings_default(net);
    // res.chain = kth_config_blockchain_settings_default(net);
    // res.database = kth_config_database_settings_default(net);
    // res.network = kth_config_network_settings_default(net);

    return res;
}

} // extern "C"
