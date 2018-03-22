/**
* Copyright (c) 2017 Bitprim developers (see AUTHORS)
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

#include <bitprim/nodecint/node/settings.h>

#include <algorithm>
#include <cstdlib>
#include <string>

#include <bitprim/nodecint/executor_c.h>

#include <bitcoin/bitcoin/multi_crypto_support.hpp>
#include <bitcoin/network/p2p.hpp>

#ifdef __cplusplus
extern "C" {
#endif

currency_t node_settings_get_currency() {
    return static_cast<currency_t>(static_cast<int>(libbitcoin::get_currency()));
}

network_t node_settings_get_network(executor_t exec) {

    p2p_t p2p_node = executor_get_p2p(exec);
    auto const& node = *static_cast<libbitcoin::network::p2p*>(p2p_node);

    // auto const& node = exec->actual.node();
    auto const& sett = node.network_settings();
    auto id = sett.identifier;

    return static_cast<network_t>(static_cast<int>(libbitcoin::get_network(id)));

    // return static_cast<network_t>(static_cast<int>(libbitcoin::get_network(exec->actual.node().network_settings().identifier)));
}

char const* node_settings_cashaddr_prefix() {
#if defined(BITPRIM_CURRENCY_BCH)
    auto str = libbitcoin::cashaddr_prefix();
#else
    std::string str; //Note: to avoid checking compilation-time feature at other languages
#endif
    auto* ret = (char*)malloc((str.size() + 1) * sizeof(char)); // NOLINT
    std::copy_n(str.begin(), str.size() + 1, ret);
    return ret;
}

} /* extern "C" */
