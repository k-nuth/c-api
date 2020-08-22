// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_CAPI_NODE_SETTINGS_H_
#define KTH_CAPI_NODE_SETTINGS_H_

#include <stdint.h>

#include <kth/capi/primitives.h>
#include <kth/capi/visibility.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum currency {
    kth_currency_none,
    kth_currency_bitcoin,
    kth_currency_bitcoin_cash,
    kth_currency_litecoin
} currency_t;

// settings
typedef enum network {
    kth_network_none,
    kth_network_mainnet,
    kth_network_testnet,
    kth_network_regtest
} network_t;

KTH_EXPORT
currency_t kth_node_settings_get_currency();

KTH_EXPORT
network_t kth_node_settings_get_network(executor_t exec);

KTH_EXPORT
char const* kth_node_settings_cashaddr_prefix();

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* KTH_CAPI_NODE_SETTINGS_H_ */
