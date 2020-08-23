// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_CAPI_KEOKEN_MANAGER_H_
#define KTH_CAPI_KEOKEN_MANAGER_H_

#include <kth/capi/keoken/state_delegated.h>
#include <kth/capi/primitives.h>
#include <kth/capi/visibility.h>

#ifdef __cplusplus
extern "C" {
#endif

KTH_EXPORT
void keoken_manager_configure_state(keoken_manager_t manager
    , void* ctx
    , keoken_state_delegated_set_initial_asset_id_t set_initial_asset_id

    , keoken_state_delegated_reset_t reset
    , keoken_state_delegated_remove_up_to_t remove_up_to

    , keoken_state_delegated_create_asset_t create_asset
    , keoken_state_delegated_create_balance_entry_t create_balance_entry
    , keoken_state_delegated_asset_id_exists_t asset_id_exists
    , keoken_state_delegated_get_balance_t get_balance
    , keoken_state_delegated_get_assets_by_address_t get_assets_by_address
    , keoken_state_delegated_get_assets_t get_assets
    , keoken_state_delegated_get_all_asset_addresses_t get_all_asset_addresses);

KTH_EXPORT
void keoken_manager_initialize_from_blockchain(keoken_manager_t manager);

KTH_EXPORT
kth_bool_t keoken_manager_initialized(keoken_manager_t manager);

KTH_EXPORT
keoken_get_assets_by_address_list_t keoken_manager_get_assets_by_address(keoken_manager_t manager, kth_payment_address_t address);

KTH_EXPORT
keoken_get_assets_list_t keoken_manager_get_assets(keoken_manager_t manager);

KTH_EXPORT
keoken_get_all_asset_addresses_list_t keoken_manager_get_all_asset_addresses(keoken_manager_t manager);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* KTH_CAPI_KEOKEN_MANAGER_H_ */
