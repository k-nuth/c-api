// Copyright (c) 2016-2023 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_CAPI_CONFIG_SETTINGS_H_
#define KTH_CAPI_CONFIG_SETTINGS_H_

#include <kth/capi/config/blockchain_settings.h>
#include <kth/capi/config/database_settings.h>
#include <kth/capi/config/network_settings.h>
#include <kth/capi/config/node_settings.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    kth_node_settings node;
    kth_blockchain_settings chain;
    kth_database_settings database;
    kth_network_settings network;
} kth_settings;

KTH_EXPORT
kth_settings kth_config_settings_default(kth_network_t network);

KTH_EXPORT
kth_bool_t kth_config_settings_get_from_file(char const* path, kth_settings** out_settings, char** out_error_message);

#if defined(_WIN32)
KTH_EXPORT
kth_bool_t kth_config_settings_get_from_fileW(wchar_t const* path, kth_settings** out_settings, char** out_error_message);
#endif // defined(_WIN32)

KTH_EXPORT
void kth_config_settings_destruct(void* settings);

#ifdef __cplusplus
} // extern "C"
#endif


#endif // KTH_CAPI_CONFIG_SETTINGS_H_
