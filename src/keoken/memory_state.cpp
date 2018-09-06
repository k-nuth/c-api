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

#include <bitprim/nodecint/keoken/memory_state.h>

#include <bitprim/keoken/memory_state.hpp>
#include <bitprim/keoken/state_dto.hpp>
#include <bitprim/nodecint/conversions.hpp>
#include <bitprim/nodecint/helpers.hpp>
#include <bitprim/nodecint/type_conversions.h>

BITPRIM_CONV_DEFINE(keoken, keoken_memory_state_t, bitprim::keoken::memory_state, memory_state)

// ---------------------------------------------------------------------------
extern "C" {

keoken_memory_state_t keoken_memory_state_construct_default() {
    return new bitprim::keoken::memory_state();
}

void keoken_memory_state_destruct(keoken_memory_state_t state) {
    delete &keoken_memory_state_cpp(state);
}

void keoken_memory_state_set_initial_asset_id(keoken_memory_state_t state, keoken_asset_id_t asset_id_initial) {
    keoken_memory_state_cpp(state).set_initial_asset_id(asset_id_initial);
}

void keoken_memory_state_reset(keoken_memory_state_t state) {
    keoken_memory_state_cpp(state).reset();
}

void keoken_memory_state_remove_up_to(keoken_memory_state_t state, uint64_t /*size_t*/ height) {
    keoken_memory_state_cpp(state).remove_up_to(height);
}

void keoken_memory_state_create_asset(keoken_memory_state_t state, char const* asset_name, keoken_amount_t asset_amount, payment_address_t owner, uint64_t /*size_t*/ block_height, hash_t txid) {
    keoken_memory_state_cpp(state).create_asset(
        std::string(asset_name),
        asset_amount,
        wallet_payment_address_const_cpp(owner),
        block_height,
        bitprim::to_array(txid.hash)
    );
}

void keoken_memory_state_create_balance_entry(keoken_memory_state_t state, keoken_asset_id_t asset_id, keoken_amount_t asset_amount, payment_address_t source, payment_address_t target,  uint64_t /*size_t*/ block_height, hash_t txid) {
    keoken_memory_state_cpp(state).create_balance_entry(
        asset_id,
        asset_amount,
        wallet_payment_address_const_cpp(source),
        wallet_payment_address_const_cpp(target),
        block_height,
        bitprim::to_array(txid.hash)
    );
}

bool_t keoken_memory_state_asset_id_exists(keoken_memory_state_t state, keoken_asset_id_t id) {
    return bitprim::bool_to_int(keoken_memory_state_const_cpp(state).asset_id_exists(id));
}

keoken_amount_t keoken_memory_state_get_balance(keoken_memory_state_t state, keoken_asset_id_t id, payment_address_t addr) {
    return keoken_memory_state_const_cpp(state).get_balance(id, wallet_payment_address_const_cpp(addr)); 
}

get_assets_by_address_list_t keoken_memory_state_get_assets_by_address(keoken_memory_state_t state, payment_address_t addr) {
    auto result = keoken_memory_state_const_cpp(state).get_assets_by_address(wallet_payment_address_const_cpp(addr));
    return bitprim::move_or_copy_and_leak(std::move(result));         //Must be released by caller
}

get_assets_list_t keoken_memory_state_get_assets(keoken_memory_state_t state) {
    auto result = keoken_memory_state_const_cpp(state).get_assets();
    return bitprim::move_or_copy_and_leak(std::move(result));         //Must be released by caller
}

get_all_asset_addresses_list_t keoken_memory_state_get_all_asset_addresses(keoken_memory_state_t state) {
    auto result = keoken_memory_state_const_cpp(state).get_all_asset_addresses();
    return bitprim::move_or_copy_and_leak(std::move(result));         //Must be released by caller
}

} // extern "C"
