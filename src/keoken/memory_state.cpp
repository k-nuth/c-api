// Copyright (c) 2016-2021 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/capi/keoken/memory_state.h>

#include <kth/keoken/memory_state.hpp>
#include <kth/keoken/state_dto.hpp>
#include <kth/capi/conversions.hpp>
#include <kth/capi/helpers.hpp>
#include <kth/capi/type_conversions.h>

KTH_CONV_DEFINE(keoken, keoken_memory_state_t, kth::keoken::memory_state, memory_state)

// ---------------------------------------------------------------------------
extern "C" {

keoken_memory_state_t keoken_memory_state_construct_default() {
    return new kth::keoken::memory_state();
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

void keoken_memory_state_remove_up_to(keoken_memory_state_t state, kth_size_t height) {
    keoken_memory_state_cpp(state).remove_up_to(height);
}

void keoken_memory_state_create_asset(keoken_memory_state_t state, char const* asset_name, keoken_amount_t asset_amount, kth_payment_address_t owner, kth_size_t block_height, kth_hash_t txid) {
    keoken_memory_state_cpp(state).create_asset(
        std::string(asset_name),
        asset_amount,
        kth_wallet_payment_address_const_cpp(owner),
        block_height,
        kth::to_array(txid.hash)
    );
}

void keoken_memory_state_create_balance_entry(keoken_memory_state_t state, keoken_asset_id_t asset_id, keoken_amount_t asset_amount, kth_payment_address_t source, kth_payment_address_t target,  kth_size_t block_height, kth_hash_t txid) {
    keoken_memory_state_cpp(state).create_balance_entry(
        asset_id,
        asset_amount,
        kth_wallet_payment_address_const_cpp(source),
        kth_wallet_payment_address_const_cpp(target),
        block_height,
        kth::to_array(txid.hash)
    );
}

kth_bool_t keoken_memory_state_asset_id_exists(keoken_memory_state_t state, keoken_asset_id_t id) {
    return kth::bool_to_int(keoken_memory_state_const_cpp(state).asset_id_exists(id));
}

keoken_amount_t keoken_memory_state_get_balance(keoken_memory_state_t state, keoken_asset_id_t id, kth_payment_address_t addr) {
    return keoken_memory_state_const_cpp(state).get_balance(id, kth_wallet_payment_address_const_cpp(addr)); 
}

keoken_get_assets_by_address_list_t keoken_memory_state_get_assets_by_address(keoken_memory_state_t state, kth_payment_address_t addr) {
    auto result = keoken_memory_state_const_cpp(state).get_assets_by_address(kth_wallet_payment_address_const_cpp(addr));
    return kth::move_or_copy_and_leak(std::move(result));         //Must be released by caller
}

keoken_get_assets_list_t keoken_memory_state_get_assets(keoken_memory_state_t state) {
    auto result = keoken_memory_state_const_cpp(state).get_assets();
    return kth::move_or_copy_and_leak(std::move(result));         //Must be released by caller
}

keoken_get_all_asset_addresses_list_t keoken_memory_state_get_all_asset_addresses(keoken_memory_state_t state) {
    auto result = keoken_memory_state_const_cpp(state).get_all_asset_addresses();
    return kth::move_or_copy_and_leak(std::move(result));         //Must be released by caller
}

} // extern "C"
