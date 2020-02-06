/**
* Copyright (c) 2016-2020 Knuth Project developers.
*
* This file is part of the Knuth Project.
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

#include <kth/capi/node/settings.h>

#include <algorithm>
#include <cstdlib>
#include <string>

#include <kth/capi/executor_c.h>
#include <kth/capi/helpers.hpp>

#include <kth/domain/multi_crypto_support.hpp>
#include <kth/network/p2p.hpp>

// ---------------------------------------------------------------------------
extern "C" {

currency_t node_settings_get_currency() {
    return static_cast<currency_t>(static_cast<int>(kth::get_currency()));
}

network_t node_settings_get_network(executor_t exec) {

    p2p_t p2p_node = executor_get_p2p(exec);
    auto const& node = *static_cast<kth::network::p2p*>(p2p_node);

    // auto const& node = exec->actual.node();
    auto const& sett = node.network_settings();
    auto id = sett.identifier;

    return static_cast<network_t>(static_cast<int>(kth::get_network(id)));

    // return static_cast<network_t>(static_cast<int>(kth::get_network(exec->actual.node().network_settings().identifier)));
}

char const* node_settings_cashaddr_prefix() {
#if defined(KTH_CURRENCY_BCH)
    auto str = kth::cashaddr_prefix();
#else
    std::string str; //Note: to avoid checking compilation-time feature at other languages
#endif
    return kth::create_c_str(str);    
}

} // extern "C"
