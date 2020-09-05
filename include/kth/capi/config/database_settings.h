// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_CAPI_CONFIG_DATABASE_SETTINGS_H_
#define KTH_CAPI_CONFIG_DATABASE_SETTINGS_H_

#include <stdint.h>

#include <kth/capi/primitives.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    kth_char_t* directory;
    kth_bool_t flush_writes;
    uint16_t file_growth_rate;
    uint32_t index_start_height;

#ifdef KTH_DB_NEW
    uint32_t reorg_pool_limit;
    uint64_t db_max_size;
    kth_bool_t safe_mode;
#endif // KTH_DB_NEW


// #ifdef KTH_DB_UNSPENT_LEGACY
    uint32_t cache_capacity;
// #endif // KTH_DB_UNSPENT_LEGACY

} kth_database_settings;

KTH_EXPORT
kth_database_settings kth_config_database_settings_default(kth_network_t net);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // KTH_CAPI_CONFIG_DATABASE_SETTINGS_H_
