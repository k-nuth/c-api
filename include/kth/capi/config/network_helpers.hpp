// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_CAPI_CONFIG_NETWORK_HELPERS_HPP_
#define KTH_CAPI_CONFIG_NETWORK_HELPERS_HPP_

#include <vector>

#include <kth/capi/config/authority_helpers.hpp>
#include <kth/capi/config/endpoint_helpers.hpp>
#include <kth/capi/config/helpers.hpp>
#include <kth/capi/helpers.hpp>
#include <kth/network/settings.hpp>

namespace kth::capi::helpers {

namespace {

template <typename Target, typename Source>
Target network_settings_to_common(Source const& x) {
    Target res;

    res.threads = x.threads;
    res.protocol_maximum = x.protocol_maximum;
    res.protocol_minimum = x.protocol_minimum;
    res.services = x.services;
    res.invalid_services = x.invalid_services;
    res.relay_transactions = x.relay_transactions;
    res.validate_checksum = x.validate_checksum;
    res.identifier = x.identifier;
    res.inbound_port = x.inbound_port;
    res.inbound_connections = x.inbound_connections;
    res.outbound_connections = x.outbound_connections;
    res.manual_attempt_limit = x.manual_attempt_limit;
    res.connect_batch_size = x.connect_batch_size;
    res.connect_timeout_seconds = x.connect_timeout_seconds;
    res.channel_handshake_seconds = x.channel_handshake_seconds;
    res.channel_heartbeat_minutes = x.channel_heartbeat_minutes;
    res.channel_inactivity_minutes = x.channel_inactivity_minutes;
    res.channel_expiration_minutes = x.channel_expiration_minutes;
    res.channel_germination_seconds = x.channel_germination_seconds;
    res.host_pool_capacity = x.host_pool_capacity;
    res.rotation_size = x.rotation_size;
    res.minimum_free_space = x.minimum_free_space;
    res.maximum_archive_size = x.maximum_archive_size;
    res.maximum_archive_files = x.maximum_archive_files;
    res.verbose = x.verbose;
    res.use_ipv6 = x.use_ipv6;

    return res;
}
}

inline
std::vector<std::string> string_list_to_cpp(char** data, size_t size) {
    return kth::capi::helpers::list_to_cpp(data, size, kth::create_cpp_str);
}

inline
char** string_list_to_c(std::vector<std::string> const& data, size_t& out_size) {
    return kth::capi::helpers::list_to_c(data, out_size, kth::create_c_str);
}

inline
kth::network::settings network_settings_to_cpp(kth_network_settings const& x) {
    auto res = network_settings_to_common<kth::network::settings>(x);
    res.hosts_file = x.hosts_file;
    res.debug_file = x.debug_file;
    res.error_file = x.error_file;
    res.archive_directory = x.archive_directory;
    res.self = kth::capi::helpers::authority_to_cpp(x.self);
    res.blacklists = kth::capi::helpers::authority_list_to_cpp(x.blacklists, x.blacklist_count);
    res.peers = kth::capi::helpers::endpoint_list_to_cpp(x.peers, x.peer_count);
    res.seeds = kth::capi::helpers::endpoint_list_to_cpp(x.seeds, x.seed_count);
    res.statistics_server = kth::capi::helpers::authority_to_cpp(x.statistics_server);
    res.user_agent_blacklist = string_list_to_cpp(x.user_agent_blacklist, x.user_agent_blacklist_count);
    return res;
}

inline
kth_network_settings network_settings_to_c(kth::network::settings const& x) {
    auto res = network_settings_to_common<kth_network_settings>(x);
    res.hosts_file = kth::capi::helpers::path_to_c(x.hosts_file);
    res.debug_file = kth::capi::helpers::path_to_c(x.debug_file);
    res.error_file = kth::capi::helpers::path_to_c(x.error_file);
    res.archive_directory = kth::capi::helpers::path_to_c(x.archive_directory);
    res.self = kth::capi::helpers::authority_to_c(x.self);
    res.blacklists = kth::capi::helpers::authority_list_to_c(x.blacklists, res.blacklist_count);
    res.peers = kth::capi::helpers::endpoint_list_to_c(x.peers, res.peer_count);
    res.seeds = kth::capi::helpers::endpoint_list_to_c(x.seeds, res.seed_count);
    res.statistics_server = kth::capi::helpers::authority_to_c(x.statistics_server);
    res.user_agent_blacklist = string_list_to_c(x.user_agent_blacklist, res.user_agent_blacklist_count);
    return res;
}

} // namespace kth::capi::helpers

#endif // KTH_CAPI_CONFIG_NETWORK_HELPERS_HPP_
