// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/capi/config/settings.h>

#include <filesystem>
#include <sstream>

#include <kth/capi/config/blockchain_helpers.hpp>
#include <kth/capi/config/database_helpers.hpp>
#include <kth/capi/config/network_helpers.hpp>
#include <kth/capi/config/node_helpers.hpp>
#include <kth/node/configuration.hpp>
#include <kth/node/parser.hpp>

namespace detail {

template <typename CharT>
kth_settings config_settings_get_from_file(CharT const* path, kth_bool_t* out_ok, char** out_error_message) {
    kth::node::parser metadata(kth::domain::config::network::mainnet);
    auto file = std::filesystem::path(path);

    std::ostringstream stream;
    bool ok = metadata.parse_from_file(file, stream);
    *out_ok = ok;

    kth_settings res;
    if (ok) {
        auto const& config = metadata.configured;
        res.node = kth::capi::helpers::node_settings_to_c(config.node);
        res.chain = kth::capi::helpers::blockchain_settings_to_c(config.chain);
        res.database = kth::capi::helpers::database_settings_to_c(config.database);
        res.network = kth::capi::helpers::network_settings_to_c(config.network);
    } else {
        auto error_string = stream.str();
        *out_error_message = kth::mnew<char>(error_string.size() + 1);
        std::copy_n(std::begin(error_string), std::size(error_string) + 1, *out_error_message);
    }
    return res;
}

}

extern "C" {

kth_settings kth_config_settings_default(kth_network_t net) {
    kth_settings res;
    res.node = kth_config_node_settings_default(net);
    res.chain = kth_config_blockchain_settings_default(net);
    res.database = kth_config_database_settings_default(net);
    res.network = kth_config_network_settings_default(net);
    return res;
}

kth_settings kth_config_settings_get_from_file(char const* path, kth_bool_t* out_ok, char** out_error_message) {
    auto res = detail::config_settings_get_from_file(path, out_ok, out_error_message);
    return res;
}

#if defined(_WIN32)
kth_settings kth_config_settings_get_from_fileW(wchar_t const* path, kth_bool_t* out_ok, char** out_error_message) {
    auto res = detail::config_settings_get_from_file(path, out_ok, out_error_message);
    return res;
}
#endif // defined(_WIN32)


} // extern "C"
