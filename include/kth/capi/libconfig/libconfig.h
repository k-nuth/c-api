// Copyright (c) 2016-2023 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_CAPI_LIBCONFIG_LIBCONFIG_H_
#define KTH_CAPI_LIBCONFIG_LIBCONFIG_H_

#include <kth/capi/config/blockchain_settings.h>
#include <kth/capi/config/database_settings.h>
#include <kth/capi/config/network_settings.h>
#include <kth/capi/config/node_settings.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    kth_libconfig_log_library_boost = 0,
    kth_libconfig_log_library_spdlog = 1,
    kth_libconfig_log_library_binlog = 2,
} kth_libconfig_log_library_t;

typedef struct {
    kth_libconfig_log_library_t log_library;
    kth_bool_t use_libmdbx;
    char const* version;
    char const* microarchitecture_id;
    kth_currency_t currency;
    kth_bool_t mempool;
    kth_bool_t db_readonly;
    kth_bool_t debug_mode;
} kth_libconfig_t;

KTH_EXPORT
kth_libconfig_t kth_libconfig_get();

#ifdef __cplusplus
} // extern "C"
#endif


#endif // KTH_CAPI_LIBCONFIG_LIBCONFIG_H_
