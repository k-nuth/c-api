/**
 * Copyright (c) 2016-2018 Bitprim Inc.
 *
 * This file is part of Bitprim.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef BITPRIM_NODECINT_KEOKEN_CONVERSIONS_HPP_
#define BITPRIM_NODECINT_KEOKEN_CONVERSIONS_HPP_

// #include <vector>

#include <bitprim/keoken/state_dto.hpp>

bitprim::keoken::get_all_asset_addresses_data& keoken_get_all_asset_addresses_data_cpp(get_all_asset_addresses_data_t obj);
bitprim::keoken::get_all_asset_addresses_data const& keoken_get_all_asset_addresses_data_const_cpp(get_all_asset_addresses_data_t obj);

bitprim::keoken::get_assets_by_address_data& keoken_get_assets_by_address_data_cpp(get_assets_by_address_data_t obj);
bitprim::keoken::get_assets_by_address_data const& keoken_get_assets_by_address_data_const_cpp(get_assets_by_address_data_t obj);

bitprim::keoken::get_assets_data& keoken_get_assets_data_cpp(get_assets_data_t obj);
bitprim::keoken::get_assets_data const& keoken_get_assets_data_const_cpp(get_assets_data_t obj);

BITPRIM_LIST_DECLARE_CONVERTERS(keoken, get_all_asset_addresses_list_t, bitprim::keoken::get_all_asset_addresses_data, get_all_asset_addresses_list)
BITPRIM_LIST_DECLARE_CONVERTERS(keoken, get_assets_by_address_list_t, bitprim::keoken::get_assets_by_address_data, get_assets_by_address_list)
BITPRIM_LIST_DECLARE_CONVERTERS(keoken, get_assets_list_t, bitprim::keoken::get_assets_data, get_assets_list)


#endif /* BITPRIM_NODECINT_KEOKEN_CONVERSIONS_HPP_ */
