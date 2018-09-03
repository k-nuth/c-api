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

#ifndef BITPRIM_NODECINT_KEOKEN_MEMORY_STATE_H_
#define BITPRIM_NODECINT_KEOKEN_MEMORY_STATE_H_

#include <bitprim/nodecint/primitives.h>
#include <bitprim/nodecint/visibility.h>

#ifdef __cplusplus
extern "C" {
#endif


BITPRIM_EXPORT
keoken_memory_state_t keoken_memory_state_construct_default(void);

BITPRIM_EXPORT
void keoken_memory_state_destruct(keoken_memory_state_t state);

// Commands.
// ---------------------------------------------------------------------------------

BITPRIM_EXPORT
void keoken_memory_state_set_initial_asset_id(keoken_memory_state_t state, keoken_asset_id_t asset_id_initial);

BITPRIM_EXPORT
void keoken_memory_state_reset(keoken_memory_state_t state);

BITPRIM_EXPORT
void keoken_memory_state_rollback_to(keoken_memory_state_t state, uint64_t /*size_t*/ height);

BITPRIM_EXPORT
void keoken_memory_state_create_asset(keoken_memory_state_t state, char const* asset_name, keoken_amount_t asset_amount, payment_address_t owner, uint64_t /*size_t*/ block_height, hash_t txid);

BITPRIM_EXPORT
void keoken_memory_state_create_balance_entry(keoken_memory_state_t state, keoken_asset_id_t asset_id, keoken_amount_t asset_amount, payment_address_t source, payment_address_t target,  uint64_t /*size_t*/ block_height, hash_t txid);

// Queries.
// ---------------------------------------------------------------------------------
BITPRIM_EXPORT
bool_t keoken_memory_state_asset_id_exists(keoken_memory_state_t state, keoken_asset_id_t id);

BITPRIM_EXPORT
keoken_amount_t keoken_memory_state_get_balance(keoken_memory_state_t state, keoken_asset_id_t id, payment_address_t addr);

BITPRIM_EXPORT
get_assets_by_address_list_t keoken_memory_state_get_assets_by_address(keoken_memory_state_t state, payment_address_t addr);

BITPRIM_EXPORT
get_assets_list_t keoken_memory_state_get_assets(keoken_memory_state_t state);

BITPRIM_EXPORT
get_all_asset_addresses_list_t keoken_memory_state_get_all_asset_addresses(keoken_memory_state_t state);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* BITPRIM_NODECINT_KEOKEN_MEMORY_STATE_H_ */
