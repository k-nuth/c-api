// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/capi/node/settings.h>

#include <algorithm>
#include <cstdlib>
#include <string>

#include <kth/capi/node.h>
#include <kth/capi/helpers.hpp>

#include <kth/domain/multi_crypto_support.hpp>
#include <kth/network/p2p.hpp>

// ---------------------------------------------------------------------------
extern "C" {

currency_t kth_node_settings_get_currency() {
    return static_cast<currency_t>(static_cast<int>(kth::get_currency()));
}

network_t kth_node_settings_get_network(kth_node_t exec) {

    kth_p2p_t p2p_node = kth_node_get_p2p(exec);
    auto const& node = *static_cast<kth::network::p2p*>(p2p_node);

    // auto const& node = exec->actual.node();
    auto const& sett = node.network_settings();
    auto id = sett.identifier;

    return static_cast<network_t>(static_cast<int>(kth::get_network(id)));

    // return static_cast<network_t>(static_cast<int>(kth::get_network(exec->actual.node().network_settings().identifier)));
}

char const* kth_node_settings_cashaddr_prefix() {
#if defined(KTH_CURRENCY_BCH)
    auto str = kth::cashaddr_prefix();
#else
    std::string str; //Note: to avoid checking compilation-time feature at other languages
#endif
    return kth::create_c_str(str);
}

} // extern "C"
