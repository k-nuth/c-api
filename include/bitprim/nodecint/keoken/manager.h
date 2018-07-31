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

#ifndef BITPRIM_NODECINT_KEOKEN_MANAGER_H_
#define BITPRIM_NODECINT_KEOKEN_MANAGER_H_

#include <bitprim/nodecint/primitives.h>
#include <bitprim/nodecint/visibility.h>

#ifdef __cplusplus
extern "C" {
#endif

BITPRIM_EXPORT
void keoken_manager_initialize_from_blockchain(keoken_manager_t manager);

BITPRIM_EXPORT
bool_t keoken_manager_initialized(keoken_manager_t manager);

BITPRIM_EXPORT
get_assets_by_address_list_t keoken_manager_get_assets_by_address(keoken_manager_t manager, payment_address_t address);

BITPRIM_EXPORT
get_assets_list_t keoken_manager_get_assets(keoken_manager_t manager);

BITPRIM_EXPORT
get_all_asset_addresses_list_t keoken_manager_get_all_asset_addresses(keoken_manager_t manager);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* BITPRIM_NODECINT_KEOKEN_MANAGER_H_ */
