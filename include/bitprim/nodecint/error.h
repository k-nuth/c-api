/**
 * Copyright (c) 2017-2018 Bitprim Inc.
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

#ifndef BITPRIM_NODECINT_ERROR_H_
#define BITPRIM_NODECINT_ERROR_H_

#ifdef __cplusplus
extern "C" {
#endif
 
typedef enum error_code {
    // general codes
    bitprim_ec_success = 0,
    bitprim_ec_deprecated = 6,
    bitprim_ec_unknown = 43,
    bitprim_ec_not_found = 3,
    bitprim_ec_file_system = 42,
    bitprim_ec_non_standard = 17,
    bitprim_ec_not_implemented = 4,
    bitprim_ec_oversubscribed = 71,

    // network
    bitprim_ec_service_stopped = 1,
    bitprim_ec_operation_failed = 2,
    bitprim_ec_resolve_failed = 7,
    bitprim_ec_network_unreachable = 8,
    bitprim_ec_address_in_use = 9,
    bitprim_ec_listen_failed = 10,
    bitprim_ec_accept_failed = 11,
    bitprim_ec_bad_stream = 12,
    bitprim_ec_channel_timeout = 13,
    bitprim_ec_address_blocked = 44,
    bitprim_ec_channel_stopped = 45,
    bitprim_ec_peer_throttling = 73,

    // database
    bitprim_ec_store_block_duplicate = 66,
    bitprim_ec_store_block_invalid_height = 67,
    bitprim_ec_store_block_missing_parent = 68,

    // blockchain
    bitprim_ec_duplicate_block = 51,
    bitprim_ec_orphan_block = 5,
    bitprim_ec_invalid_previous_block = 24,
    bitprim_ec_insufficient_work = 48,
    bitprim_ec_orphan_transaction = 14,
    bitprim_ec_insufficient_fee = 70,
    bitprim_ec_dusty_transaction = 76,
    bitprim_ec_stale_chain = 75,

    // check header
    bitprim_ec_invalid_proof_of_work = 26,
    bitprim_ec_futuristic_timestamp = 27,

    // accept header
    bitprim_ec_checkpoints_failed = 35,
    bitprim_ec_old_version_block = 36,
    bitprim_ec_incorrect_proof_of_work = 32,
    bitprim_ec_timestamp_too_early = 33,

    // check block
    bitprim_ec_block_size_limit = 50,
    bitprim_ec_empty_block = 47,
    bitprim_ec_first_not_coinbase = 28,
    bitprim_ec_extra_coinbases = 29,
    bitprim_ec_internal_duplicate = 49,
    bitprim_ec_block_internal_double_spend = 15,
    bitprim_ec_merkle_mismatch = 31,
    bitprim_ec_block_legacy_sigop_limit = 30,

    // accept block
    bitprim_ec_block_non_final = 34,
    bitprim_ec_coinbase_height_mismatch = 37,
    bitprim_ec_coinbase_value_limit = 41,
    bitprim_ec_block_embedded_sigop_limit = 52,

    // check transaction
    bitprim_ec_empty_transaction = 20,
    bitprim_ec_previous_output_null = 23,
    bitprim_ec_spend_overflow = 21,
    bitprim_ec_invalid_coinbase_script_size = 22,
    bitprim_ec_coinbase_transaction = 16,
    bitprim_ec_transaction_internal_double_spend = 72,
    bitprim_ec_transaction_size_limit = 53,
    bitprim_ec_transaction_legacy_sigop_limit = 54,

    // accept transaction
    bitprim_ec_transaction_non_final = 74,
    bitprim_ec_premature_validation = 69,
    bitprim_ec_unspent_duplicate = 38,
    bitprim_ec_missing_previous_output = 19,
    bitprim_ec_double_spend = 18,
    bitprim_ec_coinbase_maturity = 46,
    bitprim_ec_spend_exceeds_value = 40,
    bitprim_ec_transaction_embedded_sigop_limit = 55,
    bitprim_ec_sequence_locked = 78,

    // connect input
    bitprim_ec_invalid_script = 39,
    bitprim_ec_invalid_script_size = 56,
    bitprim_ec_invalid_push_data_size = 57,
    bitprim_ec_invalid_operation_count = 58,
    bitprim_ec_invalid_stack_size = 59,
    bitprim_ec_invalid_stack_scope = 60,
    bitprim_ec_invalid_script_embed = 61,
    bitprim_ec_invalid_signature_encoding = 62,
    bitprim_ec_invalid_signature_lax_encoding = 63,
    bitprim_ec_incorrect_signature = 64,
    bitprim_ec_stack_false = 65,

    // op eval
    bitprim_ec_op_disabled = 100,
    bitprim_ec_op_reserved,
    bitprim_ec_op_push_size,
    bitprim_ec_op_push_data,
    bitprim_ec_op_if,
    bitprim_ec_op_notif,
    bitprim_ec_op_else,
    bitprim_ec_op_endif,
    bitprim_ec_op_verify1,
    bitprim_ec_op_verify2,
    bitprim_ec_op_return,
    bitprim_ec_op_to_alt_stack,
    bitprim_ec_op_from_alt_stack,
    bitprim_ec_op_drop2,
    bitprim_ec_op_dup2,
    bitprim_ec_op_dup3,
    bitprim_ec_op_over2,
    bitprim_ec_op_rot2,
    bitprim_ec_op_swap2,
    bitprim_ec_op_if_dup,
    bitprim_ec_op_drop,
    bitprim_ec_op_dup,
    bitprim_ec_op_nip,
    bitprim_ec_op_over,
    bitprim_ec_op_pick,
    bitprim_ec_op_roll,
    bitprim_ec_op_rot,
    bitprim_ec_op_swap,
    bitprim_ec_op_tuck,
    bitprim_ec_op_size,
    bitprim_ec_op_equal,
    bitprim_ec_op_equal_verify1,
    bitprim_ec_op_equal_verify2,
    bitprim_ec_op_add1,
    bitprim_ec_op_sub1,
    bitprim_ec_op_negate,
    bitprim_ec_op_abs,
    bitprim_ec_op_not,
    bitprim_ec_op_nonzero,
    bitprim_ec_op_add,
    bitprim_ec_op_sub,
    bitprim_ec_op_bool_and,
    bitprim_ec_op_bool_or,
    bitprim_ec_op_num_equal,
    bitprim_ec_op_num_equal_verify1,
    bitprim_ec_op_num_equal_verify2,
    bitprim_ec_op_num_not_equal,
    bitprim_ec_op_less_than,
    bitprim_ec_op_greater_than,
    bitprim_ec_op_less_than_or_equal,
    bitprim_ec_op_greater_than_or_equal,
    bitprim_ec_op_min,
    bitprim_ec_op_max,
    bitprim_ec_op_within,
    bitprim_ec_op_ripemd160,
    bitprim_ec_op_sha1,
    bitprim_ec_op_sha256,
    bitprim_ec_op_hash160,
    bitprim_ec_op_hash256,
    bitprim_ec_op_code_seperator,
    bitprim_ec_op_check_sig_verify1,
    bitprim_ec_op_check_sig,
    bitprim_ec_op_check_multisig_verify1,
    bitprim_ec_op_check_multisig_verify2,
    bitprim_ec_op_check_multisig_verify3,
    bitprim_ec_op_check_multisig_verify4,
    bitprim_ec_op_check_multisig_verify5,
    bitprim_ec_op_check_multisig_verify6,
    bitprim_ec_op_check_multisig_verify7,
    bitprim_ec_op_check_multisig,
    bitprim_ec_op_check_locktime_verify1,
    bitprim_ec_op_check_locktime_verify2,
    bitprim_ec_op_check_locktime_verify3,
    bitprim_ec_op_check_locktime_verify4,
    bitprim_ec_op_check_locktime_verify5,
    bitprim_ec_op_check_locktime_verify6,
    bitprim_ec_op_check_sequence_verify1,
    bitprim_ec_op_check_sequence_verify2,
    bitprim_ec_op_check_sequence_verify3,
    bitprim_ec_op_check_sequence_verify4,
    bitprim_ec_op_check_sequence_verify5,
    bitprim_ec_op_check_sequence_verify6,
    bitprim_ec_op_check_sequence_verify7
} error_code_t;

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* BITPRIM_NODECINT_ERROR_H_ */
