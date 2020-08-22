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

#define BITCOIN_SHORT_HASH_SIZE 20
#define BITCOIN_HASH_SIZE 32
#define BITCOIN_LONG_HASH_SIZE 64

#define BITCOIN_EC_SECRET_SIZE 32

#define BITCOIN_MINIMUM_SEED_BITS 128
#define BITCOIN_BYTE_BITS 8
#define BITCOIN_MINIMUM_SEED_SIZE (BITCOIN_MINIMUM_SEED_BITS / BITCOIN_BYTE_BITS)

typedef int bool_t;

typedef enum point_kind {output = 0, spend = 1} point_kind_t;

typedef struct executor* executor_t;
typedef void* kth_chain_t;
typedef void* p2p_t;

//typedef struct output_kth_point_t {
//    uint8_t* hash;
//    uint32_t index;
//} output_kth_point_t;


// TODO(fernando): check if we can encapsulate the pointer into a struct to make them more "type safe"
typedef void* kth_block_t;
typedef void* kth_block_indexes_t;
typedef void* kth_block_list_t;

typedef void* compact_kth_block_t;
typedef void* header_t;
typedef void* history_compact_t;
typedef void* history_compact_list_t;

typedef void* input_t;
typedef void* input_list_t;
typedef void* input_kth_point_t;

typedef void* merkle_kth_block_t;
typedef void* script_t;

typedef void* output_t;
typedef void* kth_output_list_t;
typedef void* output_kth_point_t;

typedef void* kth_point_t;
typedef void* kth_point_list_t;
typedef void* kth_transaction_t;
typedef void* kth_transaction_list_t;

typedef void* mempool_kth_transaction_t;
typedef void* mempool_transaction_list_t;

typedef void* get_blocks_t;
typedef void* get_blocks_ptr_t;
typedef void* get_headers_t;
typedef void* get_headers_ptr_t;

typedef void* kth_payment_address_t;
typedef void* kth_payment_address_list_t;
typedef void* binary_t;
typedef void* stealth_compact_t;
typedef void* stealth_compact_list_t;

typedef void* hash_list_t;

typedef void* kth_raw_output_t;
typedef void* kth_raw_output_list_t;

typedef void* string_list_t;

typedef struct short_kth_hash_t {
    uint8_t hash[BITCOIN_SHORT_HASH_SIZE];  //kth::hash_size
} short_kth_hash_t;

typedef struct kth_hash_t {
    uint8_t hash[BITCOIN_HASH_SIZE];        //kth::hash_size
} kth_hash_t;

typedef struct long_kth_hash_t {
    uint8_t hash[BITCOIN_LONG_HASH_SIZE];   //kth::long_hash_size
} long_kth_hash_t;


// Wallet ------------------------------------------------------------
typedef struct ec_secret_t {
    uint8_t data[BITCOIN_EC_SECRET_SIZE];
} ec_secret_t;

typedef void* ec_public_t;
typedef void* hd_private_t;
typedef void* word_list_t;
// Wallet (end) -------------------------------------------------------

// Keoken -------------------------------------------------------------
#ifdef KTH_WITH_KEOKEN
// Keoken Primitives
typedef uint32_t keoken_asset_id_t;
typedef int64_t keoken_amount_t;

typedef void* keoken_manager_t;
typedef void* keoken_memory_state_t;

// Keoken DTOs
typedef void* get_assets_by_address_data_t;
typedef void* get_assets_data_t;
typedef void* get_all_asset_addresses_data_t;
typedef void* get_assets_by_address_list_t;
typedef void* get_assets_list_t;
typedef void* get_all_asset_addresses_list_t;

#endif //KTH_WITH_KEOKEN


// Callback signatures ------------------------------------------------
typedef void (*run_handler_t)(executor_t, void*, int);
typedef void (*stealth_fetch_handler_t)(kth_chain_t, void*, error_code_t, stealth_compact_list_t);
typedef void (*kth_block_fetch_handler_t)(kth_chain_t, void*, error_code_t, kth_block_t, uint64_t /*size_t*/);
typedef void (*block_header_txs_size_fetch_handler_t)(kth_chain_t, void*, error_code_t, header_t, uint64_t /*size_t*/, hash_list_t, uint64_t);
typedef void (*block_kth_hash_timestamp_fetch_handler_t)(kth_chain_t, void*, error_code_t, kth_hash_t, uint32_t, uint64_t /*size_t*/);
typedef void (*block_height_fetch_handler_t)(kth_chain_t, void*, error_code_t, uint64_t /*size_t*/);
typedef void (*block_header_fetch_handler_t)(kth_chain_t, void*, error_code_t, header_t, uint64_t /*size_t*/);
typedef void (*compact_kth_block_fetch_handler_t)(kth_chain_t, void*, error_code_t, compact_kth_block_t, uint64_t /*size_t*/);
typedef void (*history_fetch_handler_t)(kth_chain_t, void*, error_code_t, history_compact_list_t);
typedef void (*last_height_fetch_handler_t)(kth_chain_t, void*, error_code_t, uint64_t /*size_t*/);
typedef void (*merkle_kth_block_fetch_handler_t)(kth_chain_t, void*, error_code_t, merkle_kth_block_t, uint64_t /*size_t*/);
typedef void (*output_fetch_handler_t)(kth_chain_t, void*, error_code_t, output_t output);
typedef void (*spend_fetch_handler_t)(kth_chain_t, void*, error_code_t, input_kth_point_t);
typedef void (*transaction_fetch_handler_t)(kth_chain_t, void*, error_code_t, kth_transaction_t, uint64_t /*size_t*/, uint64_t /*size_t*/);
typedef void (*transaction_index_fetch_handler_t)(kth_chain_t, void*, error_code_t, uint64_t /*size_t*/, uint64_t /*size_t*/);
typedef void (*validate_tx_handler_t)(kth_chain_t, void*, error_code_t, char const*);
typedef void (*block_locator_fetch_handler_t)(kth_chain_t, void*, error_code_t, get_headers_ptr_t);
typedef void (*result_handler_t)(kth_chain_t, void*, error_code_t);
typedef bool_t (*subscribe_blockchain_handler_t)(executor_t, kth_chain_t, void*, error_code_t, uint64_t /*size_t*/, kth_block_list_t, kth_block_list_t);
typedef bool_t (*subscribe_transaction_handler_t)(executor_t, kth_chain_t, void*, error_code_t, kth_transaction_t);
typedef void (*transactions_by_addres_fetch_handler_t)(kth_chain_t, void*, error_code_t, hash_list_t);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* KTH_CAPI_PRIMITIVES_H_ */
