// Copyright (c) 2016-2023 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/capi/libconfig/libconfig.h>

#include <kth/capi/node/settings.h>
#include <kth/capi/version.h>

#define KTH_QUOTE(name) #name
#define KTH_STR(macro) KTH_QUOTE(macro)

extern "C" {

kth_libconfig_t kth_libconfig_get() {
    kth_libconfig_t res;

#if defined(KTH_LOG_LIBRARY_BOOST)
    res.log_library = kth_libconfig_log_library_boost;
#elif defined(KTH_LOG_LIBRARY_SPDLOG)
    res.log_library = kth_libconfig_log_library_spdlog;
#elif defined(KTH_LOG_LIBRARY_BINLOG)
    res.log_library = kth_libconfig_log_library_binlog;
#endif

#if defined(KTH_USE_LIBMDBX)
    res.use_libmdbx = 1;
#else
    res.use_libmdbx = 0;
#endif

    res.version = KTH_CAPI_VERSION;
    res.microarchitecture_id = KTH_STR(KTH_MARCH_ID);

    res.currency = kth_node_settings_get_currency();

#if defined(KTH_WITH_MEMPOOL)
    res.mempool = 1;
#else
    res.mempool = 0;
#endif

// #if defined(KTH_DB_NEW_FULL)
//     res.db_mode = kth_libconfig_db_mode_full_indexed;
// #elif defined(KTH_DB_NEW_BLOCKS)
//     res.db_mode = kth_libconfig_db_mode_normal;
// #elif defined(KTH_DB_NEW)
//     res.db_mode = kth_libconfig_db_mode_pruned;
// #endif

#if defined(KTH_DB_READONLY)
    res.db_readonly = 1;
#else
    res.db_readonly = 0;
#endif

#if defined(DEBUG)
    res.debug_mode = 1;
#else
    res.debug_mode = 0;
#endif

    return res;
}

#undef KTH_QUOTE
#undef KTH_STR

} // extern "C"
