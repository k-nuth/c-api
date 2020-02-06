// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#ifndef KTH_CAPI_KEOKEN_MEMORY_STATE_H_
#define KTH_CAPI_KEOKEN_MEMORY_STATE_H_

#include <kth/capi/primitives.h>
#include <kth/capi/visibility.h>

#ifdef __cplusplus
extern "C" {
#endif


KTH_EXPORT
keoken_memory_state_t keoken_memory_state_construct_default(void);

KTH_EXPORT
void keoken_memory_state_destruct(keoken_memory_state_t state);

// Commands.
// ---------------------------------------------------------------------------------

KTH_EXPORT
void keoken_memory_state_set_initial_asset_id(keoken_memory_state_t state, keoken_asset_id_t asset_id_initial);

KTH_EXPORT
void keoken_memory_state_reset(keoken_memory_state_t state);

KTH_EXPORT
void keoken_memory_state_remove_up_to(keoken_memory_state_t state, uint64_t /*size_t*/ height);

KTH_EXPORT
void keoken_memory_state_create_asset(keoken_memory_state_t state, char const* asset_name, keoken_amount_t asset_amount, payment_address_t owner, uint64_t /*size_t*/ block_height, hash_t txid);

KTH_EXPORT
void keoken_memory_state_create_balance_entry(keoken_memory_state_t state, keoken_asset_id_t asset_id, keoken_amount_t asset_amount, payment_address_t source, payment_address_t target,  uint64_t /*size_t*/ block_height, hash_t txid);

// Queries.
// ---------------------------------------------------------------------------------
KTH_EXPORT
bool_t keoken_memory_state_asset_id_exists(keoken_memory_state_t state, keoken_asset_id_t id);

KTH_EXPORT
keoken_amount_t keoken_memory_state_get_balance(keoken_memory_state_t state, keoken_asset_id_t id, payment_address_t addr);

KTH_EXPORT
get_assets_by_address_list_t keoken_memory_state_get_assets_by_address(keoken_memory_state_t state, payment_address_t addr);

KTH_EXPORT
get_assets_list_t keoken_memory_state_get_assets(keoken_memory_state_t state);

KTH_EXPORT
get_all_asset_addresses_list_t keoken_memory_state_get_all_asset_addresses(keoken_memory_state_t state);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* KTH_CAPI_KEOKEN_MEMORY_STATE_H_ */
