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

#include <bitcoin/bitcoin/multi_crypto_support.hpp>

#ifdef __cplusplus
extern "C" {
#endif

currency_t node_settings_get_currency() {
    return static_cast<currency_t>(static_cast<int>(libbitcoin::get_currency()));
}

network_t node_settings_get_network() {
    return static_cast<network_t>(static_cast<int>(libbitcoin::get_network()));
}

char const* node_settings_cashaddr_prefix() {
    auto str = libbitcoin::cashaddr_prefix();
    auto* ret = (char*)malloc((str.size() + 1) * sizeof(char)); // NOLINT
    std::copy_n(str.begin(), str.size() + 1, ret);
    return ret;
}

// void node_settings_set_network(network_t x) {
//     libbitcoin::set_network(x);
// }

// void node_settings_set_network_with_identifier(uint32_t identifier, bool bitcoin_cash) {
//     libbitcoin::set_network(identifier, bitcoin_cash);
// }

// void node_settings_set_currency(currency_t x) {
//     libbitcoin::set_currency(x);
// }

// bool is_bitcoin_cash();
// void set_bitcoin_cash(bool value);
// void set_cashaddr_prefix(std::string const& x);
// bool is_testnet(uint32_t identifier, bool bitcoin_cash);

} /* extern "C" */
