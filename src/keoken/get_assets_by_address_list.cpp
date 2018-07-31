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

#include <bitprim/nodecint/keoken/get_assets_by_address_list.h>

#include <vector>

#include <bitprim/keoken/state_dto.hpp>
#include <bitprim/nodecint/keoken/convertions.hpp>
#include <bitprim/nodecint/list_creator.h>

// namespace {
BITPRIM_LIST_DEFINE_CONVERTERS(keoken, get_assets_by_address_list_t, bitprim::keoken::get_assets_by_address_data, get_assets_by_address_list)
// } /* end of anonymous namespace */

BITPRIM_LIST_DEFINE_CONSTRUCT_FROM_CPP(keoken, get_assets_by_address_list_t, bitprim::keoken::get_assets_by_address_data, get_assets_by_address_list)

extern "C" {
BITPRIM_LIST_DEFINE(keoken, get_assets_by_address_list_t, get_assets_by_address_data_t, get_assets_by_address_list, bitprim::keoken::get_assets_by_address_data, keoken_get_assets_by_address_data_const_cpp)
} // extern "C"
