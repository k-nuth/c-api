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

#ifndef BITPRIM_NODECINT_KEOKEN_GET_ALL_ASSETS_ADDRESSES_LIST_H_
#define BITPRIM_NODECINT_KEOKEN_GET_ALL_ASSETS_ADDRESSES_LIST_H_

#include <bitprim/nodecint/list_creator.h>
#include <bitprim/nodecint/primitives.h>
#include <bitprim/nodecint/visibility.h>

#ifdef __cplusplus
extern "C" {
#endif

BITPRIM_LIST_DECLARE(keoken, get_all_asset_addresses_list_t, get_all_asset_addresses_data_t, get_all_asset_addresses_list)

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* BITPRIM_NODECINT_KEOKEN_GET_ALL_ASSETS_ADDRESSES_LIST_H_ */
