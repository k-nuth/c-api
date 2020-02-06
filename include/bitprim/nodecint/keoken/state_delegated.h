// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#ifndef KTH_NODECINT_KEOKEN_STATE_DELEGATED_H_
#define KTH_NODECINT_KEOKEN_STATE_DELEGATED_H_

#include <knuth/nodecint/primitives.h>
#include <knuth/nodecint/visibility.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*keoken_state_delegated_set_initial_asset_id_t)
                (void* /*ctx*/, 
                keoken_asset_id_t /*asset_id_initial*/);

typedef void (*keoken_state_delegated_reset_t)
                (void* /*ctx*/);

typedef void (*keoken_state_delegated_remove_up_to_t)
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

#endif /* KTH_NODECINT_KEOKEN_STATE_DELEGATED_H_ */
