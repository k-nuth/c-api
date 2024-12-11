// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_CAPI_CONFIG_NODE_HELPERS_HPP_
#define KTH_CAPI_CONFIG_NODE_HELPERS_HPP_

#include <vector>

#include <kth/capi/config/helpers.hpp>
#include <kth/capi/helpers.hpp>
#include <kth/node/settings.hpp>

namespace kth::capi::helpers {

namespace {

template <typename Target, typename Source>
inline
Target node_settings_to_common(Source const& x) {
    Target res;
    res.sync_peers = x.sync_peers;
    res.sync_timeout_seconds = x.sync_timeout_seconds;
    res.block_latency_seconds = x.block_latency_seconds;
    res.refresh_transactions = x.refresh_transactions;
    res.compact_blocks_high_bandwidth = x.compact_blocks_high_bandwidth;
    res.ds_proofs_enabled = x.ds_proofs_enabled;
    return res;
}

} //namespace

inline
kth::node::settings node_settings_to_cpp(kth_node_settings const& x) {
    return node_settings_to_common<kth::node::settings>(x);
}

inline
kth_node_settings node_settings_to_c(kth::node::settings const& x) {
    return node_settings_to_common<kth_node_settings>(x);
}

inline
void node_settings_delete(kth_node_settings*) {
    //do nothing
}

} // namespace kth::capi::helpers

#endif // KTH_CAPI_CONFIG_NODE_HELPERS_HPP_
