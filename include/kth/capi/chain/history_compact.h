// Copyright (c) 2016-2020 Knuth Project developers.
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
point_kind_t chain_history_compact_get_point_kind(history_compact_t history);

KTH_EXPORT
point_t chain_history_compact_get_point(history_compact_t history);

KTH_EXPORT
uint32_t chain_history_compact_get_height(history_compact_t history);

KTH_EXPORT
uint64_t chain_history_compact_get_value_or_previous_checksum(history_compact_t history);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // KTH_CAPI_CHAIN_HISTORY_COMPACT_H
