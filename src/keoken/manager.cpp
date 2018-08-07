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

#include <bitprim/nodecint/keoken/manager.h>

#include <bitprim/nodecint/conversions.hpp>
#include <bitprim/nodecint/helpers.hpp>
#include <bitprim/nodecint/keoken/conversions.hpp>
#include <bitprim/nodecint/type_conversions.h>

#include <bitprim/keoken/manager.hpp>
#include <bitprim/keoken/primitives.hpp>
#include <bitprim/keoken/state.hpp>
#include <bitprim/keoken/state_delegated.hpp>
#include <bitprim/keoken/state_dto.hpp>

using keoken_manager_cpp_t = bitprim::keoken::manager<bitprim::keoken::state_delegated>;
BITPRIM_CONV_DEFINE(keoken, keoken_manager_t, keoken_manager_cpp_t, manager)

template <typename T>
void* obj_to_c(T const& x) {
    void const* ptr = &x;
    return const_cast<void*>(ptr);
}

// ---------------------------------------------------------------------------
extern "C" {

void keoken_manager_configure_state(keoken_manager_t manager
    , void* ctx
    , keoken_state_delegated_set_initial_asset_id_t set_initial_asset_id
    , keoken_state_delegated_create_asset_t create_asset
    , keoken_state_delegated_create_balance_entry_t create_balance_entry
    , keoken_state_delegated_asset_id_exists_t asset_id_exists
    , keoken_state_delegated_get_balance_t get_balance
    , keoken_state_delegated_get_assets_by_address_t get_assets_by_address
    , keoken_state_delegated_get_assets_t get_assets
    , keoken_state_delegated_get_all_asset_addresses_t get_all_asset_addresses) {

    using bitprim::keoken::amount_t;
    using bitprim::keoken::asset_id_t;

    keoken_manager_cpp(manager).configure_state(
        [set_initial_asset_id, ctx](bitprim::keoken::asset_id_t asset_id_initial) {
            set_initial_asset_id(ctx, asset_id_initial);
        },
        [create_asset, ctx](std::string asset_name, amount_t asset_amount, bc::wallet::payment_address const& owner, size_t block_height, libbitcoin::hash_digest const& txid) {
            create_asset(ctx, asset_name.c_str(), asset_amount, obj_to_c(owner), block_height, bitprim::to_hash_t(txid));
        },
        [create_balance_entry, ctx](asset_id_t asset_id, amount_t asset_amount, bc::wallet::payment_address const& source, bc::wallet::payment_address const& target, size_t block_height, libbitcoin::hash_digest const& txid) {
            create_balance_entry(ctx, asset_id, asset_amount, obj_to_c(source), obj_to_c(target), block_height, bitprim::to_hash_t(txid));
        },
        [asset_id_exists, ctx](bitprim::keoken::asset_id_t id) {
            return bitprim::int_to_bool(asset_id_exists(ctx, id));
        },
        [get_balance, ctx](asset_id_t id, bc::wallet::payment_address const& addr) {
            return get_balance(ctx, id, obj_to_c(addr));
        },
        [get_assets_by_address, ctx](bc::wallet::payment_address const& addr) {
            auto res = get_assets_by_address(ctx, obj_to_c(addr));
            return keoken_get_assets_by_address_list_const_cpp(res);
        },
        [get_assets, ctx]() {
            auto res = get_assets(ctx);
            return keoken_get_assets_list_const_cpp(res);
        },
        [get_all_asset_addresses, ctx]() {
            auto res = get_all_asset_addresses(ctx);
            return keoken_get_all_asset_addresses_list_const_cpp(res);
        }
    );
}

void keoken_manager_initialize_from_blockchain(keoken_manager_t manager) {
    keoken_manager_cpp(manager).initialize_from_blockchain();
}

bool_t keoken_manager_initialized(keoken_manager_t manager) {
    return bitprim::bool_to_int(keoken_manager_const_cpp(manager).initialized());
}

get_assets_by_address_list_t keoken_manager_get_assets_by_address(keoken_manager_t manager, payment_address_t address) {
    auto result = keoken_manager_const_cpp(manager).get_assets_by_address(wallet_payment_address_const_cpp(address));
    return bitprim::move_or_copy_and_leak(std::move(result));         //Must be released by caller
}

get_assets_list_t keoken_manager_get_assets(keoken_manager_t manager) {
    auto result = keoken_manager_const_cpp(manager).get_assets();
    return bitprim::move_or_copy_and_leak(std::move(result));         //Must be released by caller
}

get_all_asset_addresses_list_t keoken_manager_get_all_asset_addresses(keoken_manager_t manager) {
    auto result = keoken_manager_const_cpp(manager).get_all_asset_addresses();
    return bitprim::move_or_copy_and_leak(std::move(result));         //Must be released by caller
}

} // extern "C"
