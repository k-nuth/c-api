// Copyright (c) 2016-2021 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/capi/keoken/get_assets_by_address_list.h>

#include <vector>

#include <kth/keoken/state_dto.hpp>
#include <kth/capi/keoken/conversions.hpp>
#include <kth/capi/list_creator.h>

KTH_LIST_DEFINE_CONVERTERS(keoken, keoken_get_assets_by_address_list_t, kth::keoken::get_assets_by_address_data, get_assets_by_address_list)
KTH_LIST_DEFINE_CONSTRUCT_FROM_CPP(keoken, keoken_get_assets_by_address_list_t, kth::keoken::get_assets_by_address_data, get_assets_by_address_list)

extern "C" {
KTH_LIST_DEFINE(keoken, keoken_get_assets_by_address_list_t, keoken_get_assets_by_address_data_t, get_assets_by_address_list, kth::keoken::get_assets_by_address_data, keoken_get_assets_by_address_data_const_cpp)
} // extern "C"
