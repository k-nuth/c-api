// Copyright (c) 2016-2023 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_CAPI_CHAIN_HISTORY_COMPACT_H
#define KTH_CAPI_CHAIN_HISTORY_COMPACT_H

#include <stdint.h>

#include <kth/capi/primitives.h>
#include <kth/capi/visibility.h>

#ifdef __cplusplus
extern "C" {
#endif

KTH_EXPORT
kth_point_kind_t kth_chain_history_compact_get_point_kind(kth_history_compact_t history);

KTH_EXPORT
kth_point_t kth_chain_history_compact_get_point(kth_history_compact_t history);

KTH_EXPORT
uint32_t kth_chain_history_compact_get_height(kth_history_compact_t history);

KTH_EXPORT
uint64_t kth_chain_history_compact_get_value_or_previous_checksum(kth_history_compact_t history);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // KTH_CAPI_CHAIN_HISTORY_COMPACT_H
