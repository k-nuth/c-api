// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#include <kth/domain/chain/history.hpp>

#include <kth/capi/chain/history_compact.h>
#include <kth/capi/type_conversions.h>

KTH_CONV_DEFINE(chain, history_compact_t, kth::chain::history_compact, history_compact)

// ---------------------------------------------------------------------------
extern "C" {

point_kind_t chain_history_compact_get_point_kind(history_compact_t history) {
    return static_cast<point_kind_t>(chain_history_compact_const_cpp(history).kind);
}

point_t chain_history_compact_get_point(history_compact_t history) {
    return &chain_history_compact_cpp(history).point;
}

uint32_t chain_history_compact_get_height(history_compact_t history) {
    return chain_history_compact_const_cpp(history).height;
}

uint64_t chain_history_compact_get_value_or_previous_checksum(history_compact_t history) {
    auto const& history_const_cpp = chain_history_compact_const_cpp(history);
    return history_const_cpp.value;
}

} // extern "C"
