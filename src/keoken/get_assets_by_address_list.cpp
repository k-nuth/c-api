/**
* Copyright (c) 2016-2020 Knuth Project developers.
*
* This file is part of the Knuth Project.
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

#include <kth/capi/keoken/get_assets_by_address_list.h>

#include <vector>

#include <kth/keoken/state_dto.hpp>
#include <kth/capi/keoken/conversions.hpp>
#include <kth/capi/list_creator.h>

KTH_LIST_DEFINE_CONVERTERS(keoken, get_assets_by_address_list_t, kth::keoken::get_assets_by_address_data, get_assets_by_address_list)
KTH_LIST_DEFINE_CONSTRUCT_FROM_CPP(keoken, get_assets_by_address_list_t, kth::keoken::get_assets_by_address_data, get_assets_by_address_list)

extern "C" {
KTH_LIST_DEFINE(keoken, get_assets_by_address_list_t, get_assets_by_address_data_t, get_assets_by_address_list, kth::keoken::get_assets_by_address_data, keoken_get_assets_by_address_data_const_cpp)
} // extern "C"
