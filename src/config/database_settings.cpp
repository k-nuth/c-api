// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/capi/config/database_settings.h>

#include <kth/capi/config/helpers.hpp>
#include <kth/capi/config/database_helpers.hpp>
#include <kth/capi/helpers.hpp>
#include <kth/database/settings.hpp>

// ---------------------------------------------------------------------------
extern "C" {

kth_database_settings kth_config_database_settings_default(kth_network_t net) {
    kth::database::settings cpp(kth::network_to_cpp(net));
    return kth::capi::helpers::database_settings_to_c(cpp);
}

} // extern "C"
