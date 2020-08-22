// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_CAPI_KEOKEN_GET_ASSETS_DATA_H_
#define KTH_CAPI_KEOKEN_GET_ASSETS_DATA_H_

#include <kth/capi/primitives.h>
#include <kth/capi/visibility.h>

#ifdef __cplusplus
extern "C" {
#endif

// KTH_EXPORT
// keoken_get_assets_data_t keoken_get_assets_data_construct_default(void);

KTH_EXPORT
keoken_get_assets_data_t keoken_get_assets_data_construct(keoken_asset_id_t asset_id, char const* asset_name, kth_payment_address_t asset_creator, keoken_amount_t amount);

KTH_EXPORT
void keoken_get_assets_data_destruct(keoken_get_assets_data_t obj);

KTH_EXPORT
keoken_asset_id_t keoken_get_assets_data_asset_id(keoken_get_assets_data_t obj);

KTH_EXPORT
char const* keoken_get_assets_data_asset_name(keoken_get_assets_data_t obj);

KTH_EXPORT
kth_payment_address_t keoken_get_assets_data_asset_creator(keoken_get_assets_data_t obj);

KTH_EXPORT
keoken_amount_t keoken_get_assets_data_amount(keoken_get_assets_data_t obj);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* KTH_CAPI_KEOKEN_GET_ASSETS_DATA_H_ */
