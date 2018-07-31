/**
 * Copyright (c) 2016-2018 Bitprim Inc.
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

#ifndef BITPRIM_NODECINT_NODE_SETTINGS_H_
#define BITPRIM_NODECINT_NODE_SETTINGS_H_

#include <stdint.h>

#include <bitprim/nodecint/primitives.h>
#include <bitprim/nodecint/visibility.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum currency {
    bitprim_currency_none,
    bitprim_currency_bitcoin,
    bitprim_currency_bitcoin_cash,
    bitprim_currency_litecoin
} currency_t;

// settings
typedef enum network {
    bitprim_network_none,
    bitprim_network_mainnet,
    bitprim_network_testnet,
    bitprim_network_regtest
} network_t;

BITPRIM_EXPORT
currency_t node_settings_get_currency();

BITPRIM_EXPORT
network_t node_settings_get_network(executor_t exec);

BITPRIM_EXPORT
char const* node_settings_cashaddr_prefix();

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* BITPRIM_NODECINT_NODE_SETTINGS_H_ */
