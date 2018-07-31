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

#ifndef BITPRIM_NODECINT_KEOKEN_GET_ASSETS_BY_ADDRESS_DATA_H_
#define BITPRIM_NODECINT_KEOKEN_GET_ASSETS_BY_ADDRESS_DATA_H_

#include <bitprim/nodecint/primitives.h>
#include <bitprim/nodecint/visibility.h>

#ifdef __cplusplus
extern "C" {
#endif

// BITPRIM_EXPORT
// get_assets_by_address_data_t keoken_get_assets_by_address_data_construct_default(void);

BITPRIM_EXPORT
get_assets_by_address_data_t keoken_get_assets_by_address_data_construct(keoken_asset_id_t asset_id, char const* asset_name, payment_address_t asset_creator, keoken_amount_t amount);

BITPRIM_EXPORT
void keoken_get_assets_by_address_data_destruct(get_assets_by_address_data_t obj);

BITPRIM_EXPORT
keoken_asset_id_t keoken_get_assets_by_address_data_asset_id(get_assets_by_address_data_t obj);

BITPRIM_EXPORT
char const* keoken_get_assets_by_address_data_asset_name(get_assets_by_address_data_t obj);

BITPRIM_EXPORT
payment_address_t keoken_get_assets_by_address_data_asset_creator(get_assets_by_address_data_t obj);

BITPRIM_EXPORT
keoken_amount_t keoken_get_assets_by_address_data_amount(get_assets_by_address_data_t obj);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* BITPRIM_NODECINT_KEOKEN_GET_ASSETS_BY_ADDRESS_DATA_H_ */
