// Copyright (c) 2016-2023 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/capi/config/blockchain_settings.h>

#include <kth/blockchain/settings.hpp>
#include <kth/capi/config/blockchain_helpers.hpp>

// ---------------------------------------------------------------------------
extern "C" {

kth_blockchain_settings kth_config_blockchain_settings_default(kth_network_t net) {
    kth::blockchain::settings cpp(kth::network_to_cpp(net));
    return kth::capi::helpers::blockchain_settings_to_c(cpp);
}

} // extern "C"
