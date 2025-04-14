// Copyright (c) 2016-2025 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_CAPI_CHAIN_SCRIPT_H_
#define KTH_CAPI_CHAIN_SCRIPT_H_

#include <stdint.h>

#include <kth/capi/primitives.h>
#include <kth/capi/visibility.h>
#include <kth/capi/chain/rule_fork.h>
#include <kth/capi/chain/script_pattern.h>
#include <kth/capi/chain/script_version.h>
#include <kth/capi/wallet/primitives.h>

#ifdef __cplusplus
extern "C" {
#endif

KTH_EXPORT
kth_script_t kth_chain_script_construct_default(void);

KTH_EXPORT
kth_script_t kth_chain_script_construct_from_bytes(uint8_t* encoded, kth_size_t n, kth_bool_t prefix);

KTH_EXPORT
kth_script_t kth_chain_script_construct_from_string(char const* str);

KTH_EXPORT
kth_script_t kth_chain_script_construct_from_operations(kth_operation_list_t operations);

KTH_EXPORT
void kth_chain_script_destruct(kth_script_t script);

KTH_EXPORT
kth_bool_t kth_chain_script_is_valid(kth_script_t script);

KTH_EXPORT
kth_bool_t kth_chain_script_is_valid_operations(kth_script_t script);

KTH_EXPORT
kth_size_t kth_chain_script_satoshi_content_size(kth_script_t script);

KTH_EXPORT
kth_size_t kth_chain_script_serialized_size(kth_script_t script, kth_bool_t prefix);

KTH_EXPORT
char const* kth_chain_script_to_string(kth_script_t script, uint32_t active_forks);

KTH_EXPORT
char const* kth_chain_script_type(kth_script_t script);

KTH_EXPORT
uint8_t const* kth_chain_script_to_data(kth_script_t script, kth_bool_t prefix, kth_size_t* out_size);

// KTH_EXPORT
// kth_size_t kth_chain_script_sigops(kth_script_t script, kth_bool_t embedded);

KTH_EXPORT
kth_operation_list_const_t kth_chain_script_operations(kth_script_t script);

KTH_EXPORT
uint8_t const* kth_chain_script_to_bytes(kth_script_t script, kth_size_t* out_size);

// Static functions

/// Determine if the fork is enabled in the active forks set.
KTH_EXPORT
kth_bool_t kth_chain_script_is_enabled(uint32_t active_forks, kth_rule_fork_t fork);

/// Consensus patterns
KTH_EXPORT
kth_bool_t  kth_chain_script_is_push_only(kth_operation_list_t ops);

KTH_EXPORT
kth_bool_t  kth_chain_script_is_relaxed_push(kth_operation_list_t ops);

KTH_EXPORT
kth_bool_t  kth_chain_script_is_coinbase_pattern(kth_operation_list_t ops, kth_size_t height);

/// Common output patterns (psh and pwsh are also consensus).
KTH_EXPORT
kth_bool_t  kth_chain_script_is_null_data_pattern(kth_operation_list_t ops);

KTH_EXPORT
kth_bool_t  kth_chain_script_is_pay_multisig_pattern(kth_operation_list_t ops);

KTH_EXPORT
kth_bool_t  kth_chain_script_is_pay_public_key_pattern(kth_operation_list_t ops);

KTH_EXPORT
kth_bool_t  kth_chain_script_is_pay_public_key_hash_pattern(kth_operation_list_t ops);

KTH_EXPORT
kth_bool_t  kth_chain_script_is_pay_script_hash_pattern(kth_operation_list_t ops);

KTH_EXPORT
kth_bool_t  kth_chain_script_is_pay_script_hash_32_pattern(kth_operation_list_t ops);

/// Common input patterns (skh is also consensus).
KTH_EXPORT
kth_bool_t  kth_chain_script_is_sign_multisig_pattern(kth_operation_list_t ops);

KTH_EXPORT
kth_bool_t  kth_chain_script_is_sign_public_key_pattern(kth_operation_list_t ops);

KTH_EXPORT
kth_bool_t  kth_chain_script_is_sign_public_key_hash_pattern(kth_operation_list_t ops);

KTH_EXPORT
kth_bool_t  kth_chain_script_is_sign_script_hash_pattern(kth_operation_list_t ops);

/// Stack factories.
KTH_EXPORT
kth_operation_list_const_t kth_chain_script_to_null_data_pattern(uint8_t const* data, kth_size_t n);

KTH_EXPORT
kth_operation_list_const_t kth_chain_script_to_pay_public_key_pattern(uint8_t const* point, kth_size_t n);

KTH_EXPORT
kth_operation_list_const_t kth_chain_script_to_pay_public_key_hash_pattern(kth_shorthash_t const* chash);

KTH_EXPORT
kth_operation_list_const_t kth_chain_script_to_pay_script_hash_pattern(kth_shorthash_t const* hash);

KTH_EXPORT
kth_operation_list_const_t kth_chain_script_to_pay_script_hash_32_pattern(kth_hash_t const* hash);

KTH_EXPORT
kth_operation_list_const_t kth_chain_script_to_pay_multisig_pattern(uint8_t signatures, kth_ec_compressed_list_t points);

// TODO: add this
// KTH_EXPORT
// kth_operation_list_const_t kth_chain_script_to_pay_multisig_pattern(uint8_t signatures, data_stack const& points);


// Utilities (non-static).
//-------------------------------------------------------------------------

/// Common pattern detection.

KTH_EXPORT
kth_script_pattern_t kth_chain_script_pattern(kth_script_t script);

KTH_EXPORT
kth_script_pattern_t kth_chain_script_output_pattern(kth_script_t script);

KTH_EXPORT
kth_script_pattern_t kth_chain_script_input_pattern(kth_script_t script);

/// Consensus computations.
KTH_EXPORT
kth_size_t kth_chain_script_sigops(kth_script_t script, kth_bool_t accurate);

KTH_EXPORT
kth_bool_t kth_chain_script_is_unspendable(kth_script_t script);

KTH_EXPORT
void kth_chain_script_reset(kth_script_t script);


// Signing.
//-------------------------------------------------------------------------

KTH_EXPORT
kth_hash_t generate_signature_hash(
    kth_transaction_t tx,
    uint32_t input_index,
    kth_script_t script_code,
    uint8_t sighash_type,
    uint32_t active_forks,
#if ! defined(KTH_CURRENCY_BCH)
    kth_script_version_t version,
#endif // ! KTH_CURRENCY_BCH
    uint64_t value,
    kth_size_t* out_hashed_bytes
);

KTH_EXPORT
kth_bool_t check_signature(
    kth_ec_signature_t signature,
    uint8_t sighash_type,
    uint8_t const* public_key,
    kth_size_t public_key_size,
    kth_script_t script_code,
    kth_transaction_t tx,
    uint32_t input_index,
    uint32_t active_forks,
#if ! defined(KTH_CURRENCY_BCH)
    kth_script_version_t version,
#endif // ! KTH_CURRENCY_BCH
    uint64_t value,
    kth_size_t* out_hashed_bytes
);

KTH_EXPORT
uint8_t const* kth_chain_script_create_endorsement(
    kth_ec_secret_t const* secret,
    kth_script_t prevout_script,
    kth_transaction_t tx,
    uint32_t input_index,
    uint8_t sighash_type,
    uint32_t active_forks,
#if ! defined(KTH_CURRENCY_BCH)
    kth_script_version_t version,
#endif // ! KTH_CURRENCY_BCH
    uint64_t value,
    kth_endorsement_type_t type,
    kth_size_t* out_size
);

// Validation.
//-----------------------------------------------------------------------------

KTH_EXPORT
kth_error_code_t kth_chain_script_verify(kth_transaction_t tx, uint32_t input_index, uint32_t forks, kth_script_t input_script, kth_script_t prevout_script, uint64_t value);

KTH_EXPORT
kth_error_code_t kth_chain_script_verify_transaction(kth_transaction_t tx, uint32_t input, uint32_t forks);


#if defined(KTH_SEGWIT_ENABLED)
KTH_EXPORT
kth_bool_t  kth_chain_script_is_commitment_pattern(kth_operation_list_t ops);

KTH_EXPORT
kth_bool_t  kth_chain_script_is_witness_program_pattern(kth_operation_list_t ops);

KTH_EXPORT
kth_bool_t  kth_chain_script_is_pay_witness_script_hash_pattern(kth_operation_list_t ops);
#endif

#ifdef __cplusplus
} // extern "C"
#endif

#endif // KTH_CAPI_CHAIN_SCRIPT_H_
