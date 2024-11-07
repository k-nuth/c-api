// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/capi/config/settings.h>

#include <filesystem>
#include <sstream>

#include <kth/capi/config/blockchain_helpers.hpp>
#include <kth/capi/config/database_helpers.hpp>

#if ! defined(__EMSCRIPTEN__)
#include <kth/capi/config/network_helpers.hpp>
#endif

#include <kth/capi/config/node_helpers.hpp>
#include <kth/node/configuration.hpp>
#include <kth/node/parser.hpp>

namespace detail {

template <typename CharT>
kth_bool_t config_settings_get_from_file(CharT const* path, kth_settings** out_settings, char** out_error_message) {
    kth::node::parser metadata(kth::domain::config::network::mainnet);
    auto file = kth::path(path);

    std::ostringstream stream;
    bool ok = metadata.parse_from_file(file, stream);

    if ( ! ok) {
        auto error_string = stream.str();
        *out_error_message = kth::mnew<char>(error_string.size() + 1);
        std::copy_n(error_string.c_str(), std::size(error_string) + 1, *out_error_message);
        return ok;
    }

    *out_settings = new kth_settings;
    auto const& config = metadata.configured;
    (*out_settings)->node = kth::capi::helpers::node_settings_to_c(config.node);
    (*out_settings)->chain = kth::capi::helpers::blockchain_settings_to_c(config.chain);
    (*out_settings)->database = kth::capi::helpers::database_settings_to_c(config.database);
#if ! defined(__EMSCRIPTEN__)
    (*out_settings)->network = kth::capi::helpers::network_settings_to_c(config.network);
#endif

    return ok;
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

kth_bool_t kth_config_settings_get_from_file(char const* path, kth_settings** out_settings, char** out_error_message) {
    auto res = detail::config_settings_get_from_file(path, out_settings, out_error_message);
    return res;
}

#if defined(_WIN32)
kth_bool_t kth_config_settings_get_from_fileW(wchar_t const* path, kth_settings** out_settings, char** out_error_message) {
    auto res = detail::config_settings_get_from_file(path, out_settings, out_error_message);
    return res;
}
#endif // defined(_WIN32)

void kth_config_settings_destruct(void* settings_par) {
    //TODO(fernando): delete the inner data members.
    auto settings = static_cast<kth_settings*>(settings_par);
    kth::capi::helpers::node_settings_delete(&settings->node);
    kth::capi::helpers::blockchain_settings_delete(&settings->chain);
    kth::capi::helpers::database_settings_delete(&settings->database);
#if ! defined(__EMSCRIPTEN__)
    kth::capi::helpers::network_settings_delete(&settings->network);
#endif
    delete settings;
}

} // extern "C"
