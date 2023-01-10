// Copyright (c) 2016-2023 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_CAPI_KEOKEN_CONVERSIONS_HPP_
#define KTH_CAPI_KEOKEN_CONVERSIONS_HPP_

// #include <vector>

#include <kth/keoken/state_dto.hpp>

kth::keoken::get_all_asset_addresses_data& keoken_get_all_asset_addresses_data_cpp(keoken_get_all_asset_addresses_data_t obj);
kth::keoken::get_all_asset_addresses_data const& keoken_get_all_asset_addresses_data_const_cpp(keoken_get_all_asset_addresses_data_t obj);

kth::keoken::get_assets_by_address_data& keoken_get_assets_by_address_data_cpp(keoken_get_assets_by_address_data_t obj);
kth::keoken::get_assets_by_address_data const& keoken_get_assets_by_address_data_const_cpp(keoken_get_assets_by_address_data_t obj);

kth::keoken::get_assets_data& keoken_get_assets_data_cpp(keoken_get_assets_data_t obj);
kth::keoken::get_assets_data const& keoken_get_assets_data_const_cpp(keoken_get_assets_data_t obj);

KTH_LIST_DECLARE_CONVERTERS(keoken, keoken_get_all_asset_addresses_list_t, kth::keoken::get_all_asset_addresses_data, get_all_asset_addresses_list)
KTH_LIST_DECLARE_CONVERTERS(keoken, keoken_get_assets_by_address_list_t, kth::keoken::get_assets_by_address_data, get_assets_by_address_list)
KTH_LIST_DECLARE_CONVERTERS(keoken, keoken_get_assets_list_t, kth::keoken::get_assets_data, get_assets_list)


#endif /* KTH_CAPI_KEOKEN_CONVERSIONS_HPP_ */
