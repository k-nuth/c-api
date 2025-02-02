// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/capi/chain/script.h>

#include <kth/capi/conversions.hpp>
#include <kth/capi/helpers.hpp>

KTH_CONV_DEFINE(chain, kth_script_t, kth::domain::chain::script, script)

// ---------------------------------------------------------------------------
extern "C" {

kth_script_t kth_chain_script_construct_default() {
    return new kth::domain::chain::script();
}

// script::script(const data_chunk& encoded, bool prefix)
kth_script_t kth_chain_script_construct_from_bytes(uint8_t* encoded, kth_size_t n, kth_bool_t prefix) {
    kth::data_chunk encoded_cpp(encoded, std::next(encoded, n));
    return new kth::domain::chain::script(encoded_cpp, kth::int_to_bool(prefix));
}

kth_script_t kth_chain_script_construct_from_string(char const* str) {
    kth::domain::chain::script script;
    auto const res = script.from_string(std::string(str));
    if ( ! res) {
        return new kth::domain::chain::script();
    }
    return kth::move_or_copy_and_leak(std::move(script));
}

kth_script_t kth_chain_script_construct_from_operations(kth_operation_list_t operations) {
    auto const& ops_cpp = kth_chain_operation_list_const_cpp(operations);
    return new kth::domain::chain::script(ops_cpp);
}

void kth_chain_script_destruct(kth_script_t script) {
    delete &kth_chain_script_cpp(script);
}

kth_bool_t kth_chain_script_is_valid(kth_script_t script) {
    return kth::bool_to_int(kth_chain_script_const_cpp(script).is_valid());
}

kth_bool_t kth_chain_script_is_valid_operations(kth_script_t script) {
    return kth::bool_to_int(kth_chain_script_const_cpp(script).is_valid_operations());
}

kth_size_t kth_chain_script_satoshi_content_size(kth_script_t script) {
    return kth_chain_script_const_cpp(script).serialized_size(false);
}

kth_size_t kth_chain_script_serialized_size(kth_script_t script, kth_bool_t prefix) {
    return kth_chain_script_const_cpp(script).serialized_size(kth::int_to_bool(prefix));
}

char const* kth_chain_script_to_string(kth_script_t script, uint32_t active_forks) {
    auto str = kth_chain_script_const_cpp(script).to_string(active_forks);
    return kth::create_c_str(str);
}

// TODO(fernando): Move this logic elsewhere (this does not go in a wrapper like c-api)
char const* kth_chain_script_type(kth_script_t script) {
    auto script_pattern = kth_chain_script_const_cpp(script).pattern();
    std::string type = "non_standard";
    switch(script_pattern) {
        case kth::infrastructure::machine::script_pattern::null_data: type = "nulldata"; break;
        case kth::infrastructure::machine::script_pattern::pay_multisig: type = "pay_multisig"; break;
        case kth::infrastructure::machine::script_pattern::pay_public_key: type = "pay_public_key"; break;
        case kth::infrastructure::machine::script_pattern::pay_key_hash: type = "pay_key_hash"; break;
        case kth::infrastructure::machine::script_pattern::pay_script_hash: type = "pay_script_hash"; break;
        case kth::infrastructure::machine::script_pattern::sign_multisig: type = "sign_multisig"; break;
        case kth::infrastructure::machine::script_pattern::sign_public_key: type = "sign_public_key"; break;
        case kth::infrastructure::machine::script_pattern::sign_key_hash: type = "sign_key_hash"; break;
        case kth::infrastructure::machine::script_pattern::sign_script_hash: type = "sign_script_hash"; break;
        default: type = "non_standard"; break;
    }

    return kth::create_c_str(type);
}

uint8_t const* kth_chain_script_to_data(kth_script_t script, kth_bool_t prefix, kth_size_t* out_size) {
    auto script_data = kth_chain_script_const_cpp(script).to_data(kth::int_to_bool(prefix));
    return kth::create_c_array(script_data, *out_size);
}

kth_size_t kth_chain_script_sigops(kth_script_t script, kth_bool_t embedded) {
    return kth_chain_script_const_cpp(script).sigops(kth::int_to_bool(embedded));
}

kth_operation_list_const_t kth_chain_script_operations(kth_script_t script) {
    auto& script_cpp = kth_chain_script_cpp(script);
    return kth_chain_operation_list_construct_from_cpp(script_cpp.operations());
}

uint8_t const* kth_chain_script_to_bytes(kth_script_t script, kth_size_t* out_size) {
    auto script_data = kth_chain_script_const_cpp(script).bytes();
    return kth::create_c_array(script_data, *out_size);
}

kth_bool_t kth_chain_script_is_enabled(uint32_t active_forks, kth_rule_fork_t fork) {
    auto fork_cpp = kth::rule_fork_to_cpp(fork);
    return kth::bool_to_int(kth::domain::chain::script::is_enabled(active_forks, fork_cpp));
}

kth_bool_t  kth_chain_script_is_push_only(kth_operation_list_t ops) {
    auto const& ops_cpp = kth_chain_operation_list_const_cpp(ops);
    return kth::bool_to_int(kth::domain::chain::script::is_push_only(ops_cpp));
}

kth_bool_t  kth_chain_script_is_relaxed_push(kth_operation_list_t ops) {
    auto const& ops_cpp = kth_chain_operation_list_const_cpp(ops);
    return kth::bool_to_int(kth::domain::chain::script::is_relaxed_push(ops_cpp));
}

kth_bool_t  kth_chain_script_is_coinbase_pattern(kth_operation_list_t ops, kth_size_t height) {
    auto const& ops_cpp = kth_chain_operation_list_const_cpp(ops);
    return kth::bool_to_int(kth::domain::chain::script::is_coinbase_pattern(ops_cpp, height));
}

kth_bool_t  kth_chain_script_is_null_data_pattern(kth_operation_list_t ops) {
    auto const& ops_cpp = kth_chain_operation_list_const_cpp(ops);
    return kth::bool_to_int(kth::domain::chain::script::is_null_data_pattern(ops_cpp));
}

kth_bool_t  kth_chain_script_is_pay_multisig_pattern(kth_operation_list_t ops) {
    auto const& ops_cpp = kth_chain_operation_list_const_cpp(ops);
    return kth::bool_to_int(kth::domain::chain::script::is_pay_multisig_pattern(ops_cpp));
}

kth_bool_t  kth_chain_script_is_pay_public_key_pattern(kth_operation_list_t ops) {
    auto const& ops_cpp = kth_chain_operation_list_const_cpp(ops);
    return kth::bool_to_int(kth::domain::chain::script::is_pay_public_key_pattern(ops_cpp));
}

kth_bool_t  kth_chain_script_is_pay_key_hash_pattern(kth_operation_list_t ops) {
    auto const& ops_cpp = kth_chain_operation_list_const_cpp(ops);
    return kth::bool_to_int(kth::domain::chain::script::is_pay_key_hash_pattern(ops_cpp));
}

kth_bool_t  kth_chain_script_is_pay_script_hash_pattern(kth_operation_list_t ops) {
    auto const& ops_cpp = kth_chain_operation_list_const_cpp(ops);
    return kth::bool_to_int(kth::domain::chain::script::is_pay_script_hash_pattern(ops_cpp));
}

kth_bool_t  kth_chain_script_is_sign_multisig_pattern(kth_operation_list_t ops) {
    auto const& ops_cpp = kth_chain_operation_list_const_cpp(ops);
    return kth::bool_to_int(kth::domain::chain::script::is_sign_multisig_pattern(ops_cpp));
}

kth_bool_t  kth_chain_script_is_sign_public_key_pattern(kth_operation_list_t ops) {
    auto const& ops_cpp = kth_chain_operation_list_const_cpp(ops);
    return kth::bool_to_int(kth::domain::chain::script::is_sign_public_key_pattern(ops_cpp));
}

kth_bool_t  kth_chain_script_is_sign_key_hash_pattern(kth_operation_list_t ops) {
    auto const& ops_cpp = kth_chain_operation_list_const_cpp(ops);
    return kth::bool_to_int(kth::domain::chain::script::is_sign_key_hash_pattern(ops_cpp));
}

kth_bool_t  kth_chain_script_is_sign_script_hash_pattern(kth_operation_list_t ops) {
    auto const& ops_cpp = kth_chain_operation_list_const_cpp(ops);
    return kth::bool_to_int(kth::domain::chain::script::is_sign_script_hash_pattern(ops_cpp));
}

kth_operation_list_const_t kth_chain_script_to_null_data_pattern(uint8_t const* data, kth_size_t n) {
    // printf("kth_chain_script_to_null_data_pattern: data: %p, n: %u\n", data, n);
    kth::data_slice data_cpp(data, data + n);
    auto res = kth::domain::chain::script::to_null_data_pattern(data_cpp);
    return kth::move_or_copy_and_leak(std::move(res));
}

kth_operation_list_const_t kth_chain_script_to_pay_public_key_pattern(uint8_t const* point, kth_size_t n) {
    kth::data_slice point_cpp(point, point + n);
    auto res = kth::domain::chain::script::to_pay_public_key_pattern(point_cpp);
    return kth::move_or_copy_and_leak(std::move(res));
}

kth_operation_list_const_t kth_chain_script_to_pay_key_hash_pattern(kth_shorthash_t const* hash) {
    auto const hash_cpp = kth::short_hash_to_cpp(hash->hash);
    auto res = kth::domain::chain::script::to_pay_key_hash_pattern(hash_cpp);
    return kth::move_or_copy_and_leak(std::move(res));
}

kth_operation_list_const_t kth_chain_script_to_pay_script_hash_pattern(kth_shorthash_t const* hash) {
    auto const hash_cpp = kth::short_hash_to_cpp(hash->hash);
    auto res = kth::domain::chain::script::to_pay_script_hash_pattern(hash_cpp);
    return kth::move_or_copy_and_leak(std::move(res));
}

kth_operation_list_const_t kth_chain_script_to_pay_multisig_pattern(uint8_t signatures, kth_ec_compressed_list_t points) {
    auto const& points_cpp = kth_wallet_ec_compressed_list_const_cpp(points);
    auto res = kth::domain::chain::script::to_pay_multisig_pattern(signatures, points_cpp);
    return kth::move_or_copy_and_leak(std::move(res));
}

// TODO: add this
// kth_operation_list_const_t kth_chain_script_to_pay_multisig_pattern(uint8_t signatures, data_stack const& points) {
//     auto res = kth::domain::chain::script::to_pay_multisig_pattern(signatures, points);
//     return kth::move_or_copy_and_leak(std::move(res));
// }

#if defined(KTH_SEGWIT_ENABLED)
kth_bool_t  kth_chain_script_is_commitment_pattern(kth_operation_list_t ops) {
    auto const& ops_cpp = kth_chain_operation_list_const_cpp(ops);
    return kth::bool_to_int(kth::domain::chain::script::is_commitment_pattern(ops_cpp));
}

kth_bool_t  kth_chain_script_is_witness_program_pattern(kth_operation_list_t ops) {
    auto const& ops_cpp = kth_chain_operation_list_const_cpp(ops);
    return kth::bool_to_int(kth::domain::chain::script::is_witness_program_pattern(ops_cpp));
}

kth_bool_t  kth_chain_script_is_pay_witness_script_hash_pattern(kth_operation_list_t ops) {
    auto const& ops_cpp = kth_chain_operation_list_const_cpp(ops);
    return kth::bool_to_int(kth::domain::chain::script::is_pay_witness_script_hash_pattern(ops_cpp));
}
#endif




// // Signing.
// //-------------------------------------------------------------------------

// static
// hash_digest generate_signature_hash(transaction const& tx,
//                                     uint32_t input_index,
//                                     script const& script_code,
//                                     uint8_t sighash_type,
//                                     script_version version = script_version::unversioned,
//                                     uint64_t value = max_uint64);

// static
// bool check_signature(ec_signature const& signature,
//                         uint8_t sighash_type,
//                         data_chunk const& public_key,
//                         script const& script_code,
//                         transaction const& tx,
//                         uint32_t input_index,
//                         script_version version = script_version::unversioned,
//                         uint64_t value = max_uint64);

// static
// bool create_endorsement(endorsement& out, ec_secret const& secret, script const& prevout_script, transaction const& tx, uint32_t input_index, uint8_t sighash_type, script_version version = script_version::unversioned, uint64_t value = max_uint64);


} // extern "C"
