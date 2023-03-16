// Copyright (c) 2016-2023 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_CAPI_ERROR_H_
#define KTH_CAPI_ERROR_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef enum error_code {
    // general codes
    kth_ec_success = 0,
    kth_ec_deprecated = 6,
    kth_ec_unknown = 43,
    kth_ec_not_found = 3,
    kth_ec_file_system = 42,
    kth_ec_non_standard = 17,
    kth_ec_not_implemented = 4,
    kth_ec_oversubscribed = 71,

    // network
    kth_ec_service_stopped = 1,
    kth_ec_operation_failed = 2,
    kth_ec_resolve_failed = 7,
    kth_ec_network_unreachable = 8,
    kth_ec_address_in_use = 9,
    kth_ec_listen_failed = 10,
    kth_ec_accept_failed = 11,
    kth_ec_bad_stream = 12,
    kth_ec_channel_timeout = 13,
    kth_ec_address_blocked = 44,
    kth_ec_channel_stopped = 45,
    kth_ec_peer_throttling = 73,

    // database
    kth_ec_store_block_duplicate = 66,
    kth_ec_store_block_invalid_height = 67,
    kth_ec_store_block_missing_parent = 68,

    // blockchain
    kth_ec_duplicate_block = 51,
    kth_ec_orphan_block = 5,
    kth_ec_invalid_previous_block = 24,
    kth_ec_insufficient_work = 48,
    kth_ec_orphan_transaction = 14,
    kth_ec_insufficient_fee = 70,
    kth_ec_dusty_transaction = 76,
    kth_ec_stale_chain = 75,

    // check header
    kth_ec_invalid_proof_of_work = 26,
    kth_ec_futuristic_timestamp = 27,

    // accept header
    kth_ec_checkpoints_failed = 35,
    kth_ec_old_version_block = 36,
    kth_ec_incorrect_proof_of_work = 32,
    kth_ec_timestamp_too_early = 33,

    // check block
    kth_ec_block_size_limit = 50,
    kth_ec_empty_block = 47,
    kth_ec_first_not_coinbase = 28,
    kth_ec_extra_coinbases = 29,
    kth_ec_internal_duplicate = 49,
    kth_ec_block_internal_double_spend = 15,
    kth_ec_merkle_mismatch = 31,
    kth_ec_block_legacy_sigop_limit = 30,

#if defined(KTH_CURRENCY_BCH)
    kth_ec_non_canonical_ordered = 84,
    kth_ec_block_sigchecks_limit = 85,
#endif

    // accept block
    kth_ec_block_non_final = 34,
    kth_ec_coinbase_height_mismatch = 37,
    kth_ec_coinbase_value_limit = 41,
    kth_ec_block_embedded_sigop_limit = 52,

    // check transaction
    kth_ec_empty_transaction = 20,
    kth_ec_previous_output_null = 23,
    kth_ec_spend_overflow = 21,
    kth_ec_invalid_coinbase_script_size = 22,
    kth_ec_coinbase_transaction = 16,
    kth_ec_transaction_internal_double_spend = 72,
    kth_ec_transaction_size_limit = 53,
    kth_ec_transaction_legacy_sigop_limit = 54,
#if defined(KTH_CURRENCY_BCH)
    kth_ec_transaction_sigchecks_limit = 86,
#endif

    // accept transaction
    kth_ec_transaction_non_final = 74,
    kth_ec_premature_validation = 69,
    kth_ec_unspent_duplicate = 38,
    kth_ec_missing_previous_output = 19,
    kth_ec_double_spend = 18,
    kth_ec_coinbase_maturity = 46,
    kth_ec_spend_exceeds_value = 40,
    kth_ec_transaction_embedded_sigop_limit = 55,
    kth_ec_sequence_locked = 78,
    kth_ec_transaction_version_out_of_range = 87,

    // connect input
    kth_ec_invalid_script = 39,
    kth_ec_invalid_script_size = 56,
    kth_ec_invalid_push_data_size = 57,
    kth_ec_invalid_operation_count = 58,
    kth_ec_invalid_stack_size = 59,
    kth_ec_invalid_stack_scope = 60,
    kth_ec_invalid_script_embed = 61,
    kth_ec_invalid_signature_encoding = 62,
    kth_ec_invalid_signature_lax_encoding = 63,
    kth_ec_incorrect_signature = 64,
    kth_ec_stack_false = 65,

    // op eval
    kth_ec_op_disabled = 100,
    kth_ec_op_reserved,
    kth_ec_op_push_size,
    kth_ec_op_push_data,
    kth_ec_op_if,
    kth_ec_op_notif,
    kth_ec_op_else,
    kth_ec_op_endif,
    kth_ec_op_verify1,
    kth_ec_op_verify2,
    kth_ec_op_return,
    kth_ec_op_to_alt_stack,
    kth_ec_op_from_alt_stack,
    kth_ec_op_drop2,
    kth_ec_op_dup2,
    kth_ec_op_dup3,
    kth_ec_op_over2,
    kth_ec_op_rot2,
    kth_ec_op_swap2,
    kth_ec_op_if_dup,
    kth_ec_op_drop,
    kth_ec_op_dup,
    kth_ec_op_nip,
    kth_ec_op_over,
    kth_ec_op_pick,
    kth_ec_op_roll,
    kth_ec_op_rot,
    kth_ec_op_swap,
    kth_ec_op_tuck,
    kth_ec_op_size,
    kth_ec_op_equal,
    kth_ec_op_equal_verify1,
    kth_ec_op_equal_verify2,
    kth_ec_op_add1,
    kth_ec_op_sub1,
    kth_ec_op_negate,
    kth_ec_op_abs,
    kth_ec_op_not,
    kth_ec_op_nonzero,
    kth_ec_op_add,
    kth_ec_op_sub,
    kth_ec_op_bool_and,
    kth_ec_op_bool_or,
    kth_ec_op_num_equal,
    kth_ec_op_num_equal_verify1,
    kth_ec_op_num_equal_verify2,
    kth_ec_op_num_not_equal,
    kth_ec_op_less_than,
    kth_ec_op_greater_than,
    kth_ec_op_less_than_or_equal,
    kth_ec_op_greater_than_or_equal,
    kth_ec_op_min,
    kth_ec_op_max,
    kth_ec_op_within,
    kth_ec_op_ripemd160,
    kth_ec_op_sha1,
    kth_ec_op_sha256,
    kth_ec_op_hash160,
    kth_ec_op_hash256,
    kth_ec_op_code_seperator,
    kth_ec_op_check_sig_verify1,
    kth_ec_op_check_sig,
    kth_ec_op_check_multisig_verify1,
    kth_ec_op_check_multisig_verify2,
    kth_ec_op_check_multisig_verify3,
    kth_ec_op_check_multisig_verify4,
    kth_ec_op_check_multisig_verify5,
    kth_ec_op_check_multisig_verify6,
    kth_ec_op_check_multisig_verify7,
    kth_ec_op_check_multisig,
    kth_ec_op_check_locktime_verify1,
    kth_ec_op_check_locktime_verify2,
    kth_ec_op_check_locktime_verify3,
    kth_ec_op_check_locktime_verify4,
    kth_ec_op_check_locktime_verify5,
    kth_ec_op_check_locktime_verify6,
    kth_ec_op_check_sequence_verify1,
    kth_ec_op_check_sequence_verify2,
    kth_ec_op_check_sequence_verify3,
    kth_ec_op_check_sequence_verify4,
    kth_ec_op_check_sequence_verify5,
    kth_ec_op_check_sequence_verify6,
    kth_ec_op_check_sequence_verify7
} kth_error_code_t;

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* KTH_CAPI_ERROR_H_ */
