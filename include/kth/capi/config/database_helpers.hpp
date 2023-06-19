// Copyright (c) 2016-2023 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_CAPI_CONFIG_DATABASE_HELPERS_HPP_
#define KTH_CAPI_CONFIG_DATABASE_HELPERS_HPP_

#include <vector>

#include <kth/capi/config/helpers.hpp>
#include <kth/capi/helpers.hpp>
#include <kth/database/settings.hpp>

namespace kth::capi::helpers {

inline
kth::database::db_mode_type db_mode_converter(kth_db_mode_t c_mode) {
    return kth::database::db_mode_type(c_mode);
}

inline
kth_db_mode_t db_mode_converter(kth::database::db_mode_type cpp_mode) {
    return kth_db_mode_t(cpp_mode);
}

namespace {

template <typename Target, typename Source>
Target database_settings_to_common(Source const& x) {
    Target res;

    res.db_mode = db_mode_converter(x.db_mode);
    res.reorg_pool_limit = x.reorg_pool_limit;
    res.db_max_size = x.db_max_size;
    res.safe_mode = x.safe_mode;
    res.cache_capacity = x.cache_capacity;
    return res;
}

}

inline
kth::database::settings database_settings_to_cpp(kth_database_settings const& x) {
    auto res = database_settings_to_common<kth::database::settings>(x);
    res.directory = x.directory;
    return res;
}

inline
kth_database_settings database_settings_to_c(kth::database::settings const& x) {
    auto res = database_settings_to_common<kth_database_settings>(x);
    res.directory = kth::capi::helpers::path_to_c(x.directory);
    return res;
}

inline
void database_settings_delete(kth_database_settings* x) {
    free(x->directory);
}

} // namespace kth::capi::helpers

#endif // KTH_CAPI_CONFIG_DATABASE_HELPERS_HPP_
