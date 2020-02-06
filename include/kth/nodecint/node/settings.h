// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#ifndef KTH_NODECINT_NODE_SETTINGS_H_
#define KTH_NODECINT_NODE_SETTINGS_H_

#include <stdint.h>

#include <knuth/nodecint/primitives.h>
#include <knuth/nodecint/visibility.h>

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
    kth_network_none,
    kth_network_mainnet,
    kth_network_testnet,
    kth_network_regtest
} network_t;

KTH_EXPORT
currency_t node_settings_get_currency();

KTH_EXPORT
network_t node_settings_get_network(executor_t exec);

KTH_EXPORT
char const* node_settings_cashaddr_prefix();

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* KTH_NODECINT_NODE_SETTINGS_H_ */
