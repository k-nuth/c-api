// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/capi/config/network_settings.h>

#include <kth/capi/config/helpers.hpp>
#include <kth/capi/config/network_helpers.hpp>
#include <kth/network/settings.hpp>

// ---------------------------------------------------------------------------
extern "C" {

kth_network_settings kth_config_network_settings_default(kth_network_t net) {
    kth::network::settings cpp(kth::network_to_cpp(net));
    return kth::capi::helpers::network_settings_to_c(cpp);
}

} // extern "C"
