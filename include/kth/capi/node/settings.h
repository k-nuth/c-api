// Copyright (c) 2016-2024 Knuth Project developers.
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

KTH_EXPORT
kth_currency_t kth_node_settings_get_currency();

#if ! defined(__EMSCRIPTEN__)
KTH_EXPORT
kth_network_t kth_node_settings_get_network(kth_node_t exec);
#endif

KTH_EXPORT
char const* kth_node_settings_cashaddr_prefix();

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* KTH_CAPI_NODE_SETTINGS_H_ */
