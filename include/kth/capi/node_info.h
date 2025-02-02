// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_CAPI_NODE_INFO_H_
#define KTH_CAPI_NODE_INFO_H_

#include <stdint.h>
#include <stdio.h>

#include <kth/capi/config/settings.h>
#include <kth/capi/primitives.h>
#include <kth/capi/visibility.h>

#ifdef __cplusplus
extern "C" {
#endif

KTH_EXPORT
void kth_node_print_thread_id();

KTH_EXPORT
uint64_t kth_node_get_thread_id();

KTH_EXPORT
char const* kth_node_capi_version(void);

KTH_EXPORT
char const* kth_node_cppapi_version(void);

KTH_EXPORT
char const* kth_node_microarchitecture(void);

KTH_EXPORT
char const* kth_node_march_names(void);

KTH_EXPORT
char const* kth_node_currency_symbol(void);

KTH_EXPORT
char const* kth_node_currency(void);

// #ifndef __EMSCRIPTEN__
KTH_EXPORT
char const* kth_node_db_type(kth_db_mode_t mode);
// #endif

KTH_EXPORT
uint32_t kth_node_cppapi_build_timestamp(void);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // KTH_CAPI_NODE_INFO_H_
