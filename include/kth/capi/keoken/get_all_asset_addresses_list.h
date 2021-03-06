// Copyright (c) 2016-2021 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_CAPI_KEOKEN_GET_ALL_ASSETS_ADDRESSES_LIST_H_
#define KTH_CAPI_KEOKEN_GET_ALL_ASSETS_ADDRESSES_LIST_H_

#include <kth/capi/list_creator.h>
#include <kth/capi/primitives.h>
#include <kth/capi/visibility.h>

#ifdef __cplusplus
extern "C" {
#endif

KTH_LIST_DECLARE(keoken, keoken_get_all_asset_addresses_list_t, keoken_get_all_asset_addresses_data_t, get_all_asset_addresses_list)

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* KTH_CAPI_KEOKEN_GET_ALL_ASSETS_ADDRESSES_LIST_H_ */
