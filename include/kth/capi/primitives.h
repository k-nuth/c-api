// Copyright (c) 2016-2024 Knuth Project developers.
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
#define KTH_BITCOIN_ENCRYPTED_SEED_SIZE 96

#define KTH_BITCOIN_MINIMUM_SEED_BITS 128
#define KTH_BITCOIN_BYTE_BITS 8
#define KTH_BITCOIN_MINIMUM_SEED_SIZE (KTH_BITCOIN_MINIMUM_SEED_BITS / KTH_BITCOIN_BYTE_BITS)

#define KTH_WALLET_HD_PUBLIC_MAINNET 76067358
#define KTH_WALLET_HD_PUBLIC_TESTNET 70617039
#define KTH_WALLET_HD_PRIVATE_MAINNET 326702167824577054
#define KTH_WALLET_HD_PRIVATE_TESTNET 303293221666392015

typedef int kth_bool_t;

#if defined(__EMSCRIPTEN__)
typedef uint32_t kth_size_t;    // It is std::size_t in the C++ code.
#else
typedef uint64_t kth_size_t;
#endif

#if defined(_WIN32)
typedef wchar_t kth_char_t;
#else
typedef char kth_char_t;
#endif

typedef enum point_kind {output = 0, spend = 1} kth_point_kind_t;

typedef void* kth_node_t;
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
typedef void* kth_compact_block_t;
typedef void* kth_double_spend_proof_t;
typedef void* kth_double_spend_proof_spender_t;
typedef void const* kth_double_spend_proof_spender_const_t;
typedef void* kth_header_t;
typedef void* kth_history_compact_t;
typedef void* kth_history_compact_list_t;
typedef void* kth_input_t;
typedef void* kth_input_list_t;
typedef void* kth_utxo_list_t;
typedef void* kth_inputpoint_t;
typedef void* kth_merkleblock_t;
typedef void* kth_script_t;
typedef void* kth_token_data_t;
typedef void const* kth_token_data_const_t;

typedef void* kth_operation_list_t;
typedef void const* kth_operation_list_const_t;
typedef void* kth_operation_t;

typedef void* kth_output_list_t;
typedef void* kth_output_t;
typedef void* kth_outputpoint_t;
typedef void* kth_utxo_t;
typedef void const* kth_outputpoint_const_t;
typedef void* kth_point_t;
typedef void* kth_point_list_t;
typedef void* kth_transaction_t;
typedef void const* kth_transaction_const_t;
typedef void* kth_transaction_list_t;
typedef void* kth_mempool_transaction_t;
typedef void* kth_mempool_transaction_list_t;
typedef void* kth_get_blocks_t;
typedef void* kth_get_blocks_ptr_t;
typedef void* kth_get_headers_t;
typedef void* kth_get_headers_ptr_t;
typedef void* kth_payment_address_t;
typedef void* kth_payment_address_list_t;
typedef void const* kth_payment_address_list_const_t;
typedef void* kth_binary_t;
typedef void* kth_stealth_compact_t;
typedef void* kth_stealth_compact_list_t;
typedef void* kth_hash_list_t;
typedef void* kth_raw_output_t;
typedef void* kth_raw_output_list_t;
typedef void* kth_string_list_t;
typedef void* kth_double_list_t;
typedef void* kth_u32_list_t;
typedef void* kth_u64_list_t;

typedef void* kth_wallet_data_t;

typedef void* kth_ec_compressed_list_t;


// VM
typedef void* kth_metrics_t;
typedef void* kth_program_t;

typedef void const* kth_program_const_t;


// helper functions

typedef struct kth_shorthash_t {
    uint8_t hash[KTH_BITCOIN_SHORT_HASH_SIZE];  //kth::hash_size
} kth_shorthash_t;

typedef struct kth_hash_t {
    uint8_t hash[KTH_BITCOIN_HASH_SIZE];        //kth::hash_size
} kth_hash_t;

typedef struct kth_longhash_t {
    uint8_t hash[KTH_BITCOIN_LONG_HASH_SIZE];   //kth::long_hash_size
} kth_longhash_t;

typedef struct kth_encrypted_seed_t {
    uint8_t hash[KTH_BITCOIN_ENCRYPTED_SEED_SIZE];
} kth_encrypted_seed_t;



// Currencies --------------------------------------------------------

typedef enum {
    kth_currency_bitcoin,
    kth_currency_bitcoin_cash,
    kth_currency_litecoin
} kth_currency_t;

// Network -----------------------------------------------------------
typedef enum {
      kth_network_mainnet
    , kth_network_testnet
    , kth_network_regtest
#if defined(KTH_CURRENCY_BCH)
    , kth_network_testnet4
    , kth_network_scalenet
    , kth_network_chipnet
#endif
} kth_network_t;

// Start Modules -----------------------------------------------------
typedef enum {
      kth_start_modules_all
    , kth_start_modules_just_chain
    , kth_start_modules_just_p2p
} kth_start_modules_t;


// DB Modes -----------------------------------------------------------

typedef enum {
    kth_db_mode_pruned = 0,
    kth_db_mode_normal = 1,
    kth_db_mode_full_indexed = 2
} kth_db_mode_t;


// Endorsement type ----------------------------------------------------
typedef enum {
    kth_endorsement_type_ecdsa = 0,
    kth_endorsement_type_schnorr = 1
} kth_endorsement_type_t;


// Callback signatures ------------------------------------------------
typedef void (*kth_run_handler_t)(kth_node_t, void*, kth_error_code_t);
typedef void (*kth_stealth_fetch_handler_t)(kth_chain_t, void*, kth_error_code_t, kth_stealth_compact_list_t);
typedef void (*kth_block_fetch_handler_t)(kth_chain_t, void*, kth_error_code_t, kth_block_t, kth_size_t);
typedef void (*kth_block_header_txs_size_fetch_handler_t)(kth_chain_t, void*, kth_error_code_t, kth_header_t, kth_size_t, kth_hash_list_t, uint64_t);
typedef void (*kth_blockhash_timestamp_fetch_handler_t)(kth_chain_t, void*, kth_error_code_t, kth_hash_t, uint32_t, kth_size_t);
typedef void (*kth_block_height_fetch_handler_t)(kth_chain_t, void*, kth_error_code_t, kth_size_t);
typedef void (*kth_block_header_fetch_handler_t)(kth_chain_t, void*, kth_error_code_t, kth_header_t, kth_size_t);
typedef void (*kth_compact_block_fetch_handler_t)(kth_chain_t, void*, kth_error_code_t, kth_compact_block_t, kth_size_t);
typedef void (*kth_history_fetch_handler_t)(kth_chain_t, void*, kth_error_code_t, kth_history_compact_list_t);
typedef void (*kth_last_height_fetch_handler_t)(kth_chain_t, void*, kth_error_code_t, kth_size_t);
typedef void (*kth_merkleblock_fetch_handler_t)(kth_chain_t, void*, kth_error_code_t, kth_merkleblock_t, kth_size_t);
typedef void (*kth_output_fetch_handler_t)(kth_chain_t, void*, kth_error_code_t, kth_output_t output);
typedef void (*kth_spend_fetch_handler_t)(kth_chain_t, void*, kth_error_code_t, kth_inputpoint_t);
typedef void (*kth_transaction_fetch_handler_t)(kth_chain_t, void*, kth_error_code_t, kth_transaction_t, kth_size_t, kth_size_t);
typedef void (*kth_transaction_index_fetch_handler_t)(kth_chain_t, void*, kth_error_code_t, kth_size_t, kth_size_t);
typedef void (*kth_validate_tx_handler_t)(kth_chain_t, void*, kth_error_code_t, char const*);
typedef void (*kth_block_locator_fetch_handler_t)(kth_chain_t, void*, kth_error_code_t, kth_get_headers_ptr_t);
typedef void (*kth_result_handler_t)(kth_chain_t, void*, kth_error_code_t);
typedef void (*kth_transactions_by_address_fetch_handler_t)(kth_chain_t, void*, kth_error_code_t, kth_hash_list_t);
typedef kth_bool_t (*kth_subscribe_blockchain_handler_t)(kth_node_t, kth_chain_t, void*, kth_error_code_t, kth_size_t, kth_block_list_t, kth_block_list_t);
typedef kth_bool_t (*kth_subscribe_transaction_handler_t)(kth_node_t, kth_chain_t, void*, kth_error_code_t, kth_transaction_t);
typedef kth_bool_t (*kth_subscribe_ds_proof_handler_t)(kth_node_t, kth_chain_t, void*, kth_error_code_t, kth_double_spend_proof_t);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* KTH_CAPI_PRIMITIVES_H_ */
