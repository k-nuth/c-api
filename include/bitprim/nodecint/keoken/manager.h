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

#include <bitprim/nodecint/keoken/state_delegated.h>
#include <bitprim/nodecint/primitives.h>
#include <bitprim/nodecint/visibility.h>

#ifdef __cplusplus
extern "C" {
#endif

BITPRIM_EXPORT
void keoken_manager_configure_state(keoken_manager_t manager
    , void* ctx
    , keoken_state_delegated_set_initial_asset_id_t set_initial_asset_id

    , keoken_state_delegated_reset_t reset
    , keoken_state_delegated_rollback_to_t rollback_to

    , keoken_state_delegated_create_asset_t create_asset
    , keoken_state_delegated_create_balance_entry_t create_balance_entry
    , keoken_state_delegated_asset_id_exists_t asset_id_exists
    , keoken_state_delegated_get_balance_t get_balance
    , keoken_state_delegated_get_assets_by_address_t get_assets_by_address
    , keoken_state_delegated_get_assets_t get_assets
    , keoken_state_delegated_get_all_asset_addresses_t get_all_asset_addresses);

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
