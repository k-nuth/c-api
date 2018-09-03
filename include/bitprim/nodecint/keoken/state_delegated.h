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

#ifndef BITPRIM_NODECINT_KEOKEN_STATE_DELEGATED_H_
#define BITPRIM_NODECINT_KEOKEN_STATE_DELEGATED_H_

#include <bitprim/nodecint/primitives.h>
#include <bitprim/nodecint/visibility.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*keoken_state_delegated_set_initial_asset_id_t)
                (void* /*ctx*/, 
                keoken_asset_id_t /*asset_id_initial*/);

typedef void (*keoken_state_delegated_reset_t)
                (void* /*ctx*/);

typedef void (*keoken_state_delegated_rollback_to_t)
                (void* /*ctx*/, 
                uint64_t /*size_t*/ /*height*/);

typedef void (*keoken_state_delegated_create_asset_t)
                (void* /*ctx*/,
                char const* /*asset_name*/, 
                keoken_amount_t /*asset_amount*/, 
                payment_address_t /*owner*/, 
                uint64_t /*size_t*/ /*block_height*/, 
                hash_t /*txid*/);

typedef void (*keoken_state_delegated_create_balance_entry_t)
                (void* /*ctx*/,
                keoken_asset_id_t /*asset_id*/, 
                keoken_amount_t /*asset_amount*/, 
                payment_address_t /*source*/, 
                payment_address_t /*target*/,  
                uint64_t /*size_t*/ /*block_height*/, 
                hash_t /*txid*/);

typedef bool_t (*keoken_state_delegated_asset_id_exists_t)
                (void* /*ctx*/,
                keoken_asset_id_t /*id*/);

typedef keoken_amount_t (*keoken_state_delegated_get_balance_t)
                (void* /*ctx*/,
                keoken_asset_id_t /*id*/, 
                payment_address_t /*addr*/);

typedef get_assets_by_address_list_t (*keoken_state_delegated_get_assets_by_address_t)
                (void* /*ctx*/,
                payment_address_t /*addr*/);

typedef get_assets_list_t (*keoken_state_delegated_get_assets_t)
                (void* /*ctx*/);

typedef get_all_asset_addresses_list_t (*keoken_state_delegated_get_all_asset_addresses_t)
                (void* /*ctx*/);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* BITPRIM_NODECINT_KEOKEN_STATE_DELEGATED_H_ */
