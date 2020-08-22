// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_CAPI_PRIMITIVES_H_
#define KTH_CAPI_PRIMITIVES_H_

#include <stdint.h>

#include <kth/capi/error.h>
#include <kth/capi/visibility.h>

#ifdef __cplusplus
extern "C" {
#endif

#define KTH_BITCOIN_SHORT_HASH_SIZE 20
#define KTH_BITCOIN_HASH_SIZE 32
#define KTH_BITCOIN_LONG_HASH_SIZE 64

#define KTH_BITCOIN_EC_SECRET_SIZE 32

#define KTH_BITCOIN_MINIMUM_SEED_BITS 128
#define KTH_BITCOIN_BYTE_BITS 8
#define KTH_BITCOIN_MINIMUM_SEED_SIZE (KTH_BITCOIN_MINIMUM_SEED_BITS / KTH_BITCOIN_BYTE_BITS)

typedef int kth_bool_t;
typedef uint64_t kth_size_t;    // It is std::size_t in the C++ code.

typedef enum point_kind {output = 0, spend = 1} kth_point_kind_t;

typedef struct executor_helper* kth_node_t;
typedef void* kth_chain_t;
typedef void* kth_p2p_t;

//typedef struct kth_outputpoint_t {
//    uint8_t* hash;
//    uint32_t index;
//} kth_outputpoint_t;


// TODO(fernando): check if we can encapsulate the pointer into a struct to make them more "type safe"
typedef void* kth_block_t;
typedef void* kth_block_indexes_t;
typedef void* kth_block_list_t;

typedef void* kth_compactblock_t;
typedef void* kth_header_t;
typedef void* kth_history_compact_t;
typedef void* history_compact_list_t;

typedef void* kth_input_t;
typedef void* kth_input_list_t;
typedef void* kth_inputpoint_t;

typedef void* kth_merkleblock_t;
typedef void* kth_script_t;

typedef void* kth_output_t;
typedef void* kth_output_list_t;
typedef void* kth_outputpoint_t;

typedef void* kth_point_t;
typedef void* kth_point_list_t;
typedef void* kth_transaction_t;
typedef void* kth_transaction_list_t;

typedef void* kth_mempool_transaction_t;
typedef void* kth_mempool_transaction_list_t;

typedef void* kth_get_blocks_t;
typedef void* kth_get_blocks_ptr_t;
typedef void* kth_get_headers_t;
typedef void* kth_get_headers_ptr_t;

typedef void* kth_payment_address_t;
typedef void* kth_payment_address_list_t;
typedef void* kth_binary_t;
typedef void* kth_stealth_compact_t;
typedef void* kth_stealth_compact_list_t;

typedef void* kth_hash_list_t;

typedef void* kth_raw_output_t;
typedef void* kth_raw_output_list_t;

typedef void* kth_string_list_t;

typedef struct kth_shorthash_t {
    uint8_t hash[KTH_BITCOIN_SHORT_HASH_SIZE];  //kth::hash_size
} kth_shorthash_t;

typedef struct kth_hash_t {
    uint8_t hash[KTH_BITCOIN_HASH_SIZE];        //kth::hash_size
} kth_hash_t;

typedef struct kth_longhash_t {
    uint8_t hash[KTH_BITCOIN_LONG_HASH_SIZE];   //kth::long_hash_size
} kth_longhash_t;


// Wallet ------------------------------------------------------------
typedef struct kth_ec_secret_t {
    uint8_t data[KTH_BITCOIN_EC_SECRET_SIZE];
} kth_ec_secret_t;

typedef void* kth_ec_public_t;
typedef void* kth_hd_private_t;
typedef void* kth_word_list_t;
// Wallet (end) -------------------------------------------------------

// Keoken -------------------------------------------------------------
#ifdef KTH_WITH_KEOKEN
// Keoken Primitives
typedef uint32_t keoken_asset_id_t;
typedef int64_t keoken_amount_t;

typedef void* keoken_manager_t;
typedef void* keoken_memory_state_t;

// Keoken DTOs
typedef void* keoken_get_assets_by_address_data_t;
typedef void* keoken_get_assets_data_t;
typedef void* keoken_get_all_asset_addresses_data_t;
typedef void* keoken_get_assets_by_address_list_t;
typedef void* keoken_get_assets_list_t;
typedef void* keoken_get_all_asset_addresses_list_t;

#endif //KTH_WITH_KEOKEN


// Callback signatures ------------------------------------------------
typedef void (*kth_run_handler_t)(kth_node_t, void*, int);
typedef void (*kth_stealth_fetch_handler_t)(kth_chain_t, void*, kth_error_code_t, kth_stealth_compact_list_t);
typedef void (*kth_block_fetch_handler_t)(kth_chain_t, void*, kth_error_code_t, kth_block_t, kth_size_t);
typedef void (*kth_block_header_txs_size_fetch_handler_t)(kth_chain_t, void*, kth_error_code_t, kth_header_t, kth_size_t, kth_hash_list_t, uint64_t);
typedef void (*kth_blockhash_timestamp_fetch_handler_t)(kth_chain_t, void*, kth_error_code_t, kth_hash_t, uint32_t, kth_size_t);
typedef void (*kth_block_height_fetch_handler_t)(kth_chain_t, void*, kth_error_code_t, kth_size_t);
typedef void (*kth_block_header_fetch_handler_t)(kth_chain_t, void*, kth_error_code_t, kth_header_t, kth_size_t);
typedef void (*kth_compactblock_fetch_handler_t)(kth_chain_t, void*, kth_error_code_t, kth_compactblock_t, kth_size_t);
typedef void (*kth_history_fetch_handler_t)(kth_chain_t, void*, kth_error_code_t, history_compact_list_t);
typedef void (*kth_last_height_fetch_handler_t)(kth_chain_t, void*, kth_error_code_t, kth_size_t);
typedef void (*kth_merkleblock_fetch_handler_t)(kth_chain_t, void*, kth_error_code_t, kth_merkleblock_t, kth_size_t);
typedef void (*kth_output_fetch_handler_t)(kth_chain_t, void*, kth_error_code_t, kth_output_t output);
typedef void (*kth_spend_fetch_handler_t)(kth_chain_t, void*, kth_error_code_t, kth_inputpoint_t);
typedef void (*kth_transaction_fetch_handler_t)(kth_chain_t, void*, kth_error_code_t, kth_transaction_t, kth_size_t, kth_size_t);
typedef void (*kth_transaction_index_fetch_handler_t)(kth_chain_t, void*, kth_error_code_t, kth_size_t, kth_size_t);
typedef void (*kth_validate_tx_handler_t)(kth_chain_t, void*, kth_error_code_t, char const*);
typedef void (*kth_block_locator_fetch_handler_t)(kth_chain_t, void*, kth_error_code_t, kth_get_headers_ptr_t);
typedef void (*kth_result_handler_t)(kth_chain_t, void*, kth_error_code_t);
typedef kth_bool_t (*kth_subscribe_blockchain_handler_t)(kth_node_t, kth_chain_t, void*, kth_error_code_t, kth_size_t, kth_block_list_t, kth_block_list_t);
typedef kth_bool_t (*kth_subscribe_transaction_handler_t)(kth_node_t, kth_chain_t, void*, kth_error_code_t, kth_transaction_t);
typedef void (*kth_transactions_by_addres_fetch_handler_t)(kth_chain_t, void*, kth_error_code_t, kth_hash_list_t);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* KTH_CAPI_PRIMITIVES_H_ */
