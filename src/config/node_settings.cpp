// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/capi/config/node_settings.h>

#include <kth/capi/config/helpers.hpp>
#include <kth/capi/config/node_helpers.hpp>
#include <kth/capi/helpers.hpp>
#include <kth/node/settings.hpp>

#include <iostream>

// ---------------------------------------------------------------------------
extern "C" {

kth_node_settings kth_config_node_settings_default(kth_network_t net) {
    kth::node::settings cpp(kth::network_to_cpp(net));
    return kth::capi::helpers::node_settings_to_c(cpp);
}

} // extern "C"
