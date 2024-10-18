// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/capi/chain/operation.h>

#include <kth/capi/conversions.hpp>
#include <kth/capi/helpers.hpp>

#include <kth/domain/common.hpp>

KTH_CONV_DEFINE(chain, kth_operation_t, kth::domain::machine::operation, operation)

// ---------------------------------------------------------------------------
extern "C" {

kth_operation_t kth_chain_operation_construct_default() {
    return new kth::domain::machine::operation();
}

kth_operation_t kth_chain_operation_construct_from_bytes(uint8_t* uncoded, kth_size_t n, kth_bool_t minimal) {
    kth::data_chunk uncoded_cpp(uncoded, std::next(uncoded, n));
    return new kth::domain::machine::operation(uncoded_cpp, kth::int_to_bool(minimal));
}

kth_operation_t kth_chain_operation_construct_from_opcode(kth_opcode_t opcode) {
    return new kth::domain::machine::operation(kth::opcode_to_cpp(opcode));
}

kth_operation_t kth_chain_operation_construct_from_string(char const* value) {
    auto op = new kth::domain::machine::operation();
    op->from_string(std::string(value));
    return op;
}

void kth_chain_operation_destruct(kth_operation_t operation) {
    delete &kth_chain_operation_cpp(operation);
}

char const* kth_chain_operation_to_string(kth_operation_t operation, uint32_t active_forks) {
    return kth::create_c_str(kth_chain_operation_cpp(operation).to_string(active_forks));
}

uint8_t const* kth_chain_operation_to_data(kth_operation_t operation, kth_size_t* out_size) {
    auto operation_data = kth_chain_operation_cpp(operation).to_data();
    return kth::create_c_array(operation_data, *out_size);
}

// kth_bool_t kth_chain_operation_from_data_mutable(kth_operation_t operation, uint8_t const* data, kth_size_t n) {
//     kth::data_chunk data_cpp(data, std::next(data, n));
//     auto& op_cpp = kth_chain_operation_cpp(operation);
//     auto const res = kth::domain::entity_from_data(op_cpp, data_cpp);
//     return kth::bool_to_int(res);
// }

kth_bool_t kth_chain_operation_from_string_mutable(kth_operation_t operation, char const* value) {
    auto& op_cpp = kth_chain_operation_cpp(operation);
    auto const res = op_cpp.from_string(std::string(value));
    return kth::bool_to_int(res);
}

kth_bool_t kth_chain_operation_is_valid(kth_operation_t operation) {
    return kth::bool_to_int(kth_chain_operation_cpp(operation).is_valid());
}

kth_size_t kth_chain_operation_serialized_size(kth_operation_t operation) {
    return kth_chain_operation_cpp(operation).serialized_size();
}

kth_opcode_t kth_chain_operation_code(kth_operation_t operation) {
    return kth::opcode_to_c(kth_chain_operation_cpp(operation).code());
}

uint8_t const* kth_chain_operation_data(kth_operation_t operation, kth_size_t* out_size) {
    auto data = kth_chain_operation_cpp(operation).data();
    return kth::create_c_array(data, *out_size);
}

// ******************************************
// Categories of operations
// ******************************************

kth_bool_t kth_chain_operation_is_push(kth_operation_t operation) {
    return kth::bool_to_int(kth_chain_operation_cpp(operation).is_push());
}

kth_bool_t kth_chain_operation_is_counted(kth_operation_t operation) {
    return kth::bool_to_int(kth_chain_operation_cpp(operation).is_counted());
}

kth_bool_t kth_chain_operation_is_version(kth_operation_t operation) {
    return kth::bool_to_int(kth_chain_operation_cpp(operation).is_version());
}

kth_bool_t kth_chain_operation_is_positive(kth_operation_t operation) {
    return kth::bool_to_int(kth_chain_operation_cpp(operation).is_positive());
}

kth_bool_t kth_chain_operation_is_disabled(kth_operation_t operation, uint32_t active_forks) {
    return kth::bool_to_int(kth_chain_operation_cpp(operation).is_disabled(active_forks));
}

kth_bool_t kth_chain_operation_is_conditional(kth_operation_t operation) {
    return kth::bool_to_int(kth_chain_operation_cpp(operation).is_conditional());
}

kth_bool_t kth_chain_operation_is_relaxed_push(kth_operation_t operation) {
    return kth::bool_to_int(kth_chain_operation_cpp(operation).is_relaxed_push());
}

kth_bool_t kth_chain_operation_is_oversized(kth_operation_t operation, kth_size_t max_size) {
    return kth::bool_to_int(kth_chain_operation_cpp(operation).is_oversized(max_size));
}

kth_bool_t kth_chain_operation_is_minimal_push(kth_operation_t operation) {
    return kth::bool_to_int(kth_chain_operation_cpp(operation).is_minimal_push());
}

kth_bool_t kth_chain_operation_is_nominal_push(kth_operation_t operation) {
    return kth::bool_to_int(kth_chain_operation_cpp(operation).is_nominal_push());
}

// ******************************************
// static functions
// ******************************************

kth_opcode_t kth_chain_operation_opcode_from_size(kth_size_t size) {
    return kth::opcode_to_c(kth::domain::machine::operation::opcode_from_size(size));
}

kth_opcode_t kth_chain_operation_minimal_opcode_from_data(uint8_t const* data, kth_size_t n) {
    kth::data_chunk data_cpp(data, std::next(data, n));
    return kth::opcode_to_c(kth::domain::machine::operation::minimal_opcode_from_data(data_cpp));
}

kth_opcode_t kth_chain_operation_nominal_opcode_from_data(uint8_t const* data, kth_size_t n) {
    kth::data_chunk data_cpp(data, std::next(data, n));
    return kth::opcode_to_c(kth::domain::machine::operation::nominal_opcode_from_data(data_cpp));
}

kth_opcode_t kth_chain_operation_opcode_from_positive(uint8_t value) {
    return kth::opcode_to_c(kth::domain::machine::operation::opcode_from_positive(value));
}

uint8_t kth_chain_operation_opcode_to_positive(kth_opcode_t code) {
    auto code_c = kth::opcode_to_cpp(code);
    return kth::domain::machine::operation::opcode_to_positive(code_c);
}

kth_bool_t kth_chain_operation_opcode_is_push(kth_opcode_t code) {
    auto code_c = kth::opcode_to_cpp(code);
    return kth::bool_to_int(kth::domain::machine::operation::is_push(code_c));
}

kth_bool_t kth_chain_operation_opcode_is_payload(kth_opcode_t code) {
    auto code_c = kth::opcode_to_cpp(code);
    return kth::bool_to_int(kth::domain::machine::operation::is_payload(code_c));
}

kth_bool_t kth_chain_operation_opcode_is_counted(kth_opcode_t code) {
    auto code_c = kth::opcode_to_cpp(code);
    return kth::bool_to_int(kth::domain::machine::operation::is_counted(code_c));
}

kth_bool_t kth_chain_operation_opcode_is_version(kth_opcode_t code) {
    auto code_c = kth::opcode_to_cpp(code);
    return kth::bool_to_int(kth::domain::machine::operation::is_version(code_c));
}

kth_bool_t kth_chain_operation_opcode_is_numeric(kth_opcode_t code) {
    auto code_c = kth::opcode_to_cpp(code);
    return kth::bool_to_int(kth::domain::machine::operation::is_numeric(code_c));
}

kth_bool_t kth_chain_operation_opcode_is_positive(kth_opcode_t code) {
    auto code_c = kth::opcode_to_cpp(code);
    return kth::bool_to_int(kth::domain::machine::operation::is_positive(code_c));
}

kth_bool_t kth_chain_operation_opcode_is_reserved(kth_opcode_t code) {
    auto code_c = kth::opcode_to_cpp(code);
    return kth::bool_to_int(kth::domain::machine::operation::is_reserved(code_c));
}

kth_bool_t kth_chain_operation_opcode_is_disabled(kth_opcode_t code, uint32_t active_forks) {
    auto code_c = kth::opcode_to_cpp(code);
    return kth::bool_to_int(kth::domain::machine::operation::is_disabled(code_c, active_forks));
}

kth_bool_t kth_chain_operation_opcode_is_conditional(kth_opcode_t code) {
    auto code_c = kth::opcode_to_cpp(code);
    return kth::bool_to_int(kth::domain::machine::operation::is_conditional(code_c));
}

kth_bool_t kth_chain_operation_opcode_is_relaxed_push(kth_opcode_t code) {
    auto code_c = kth::opcode_to_cpp(code);
    return kth::bool_to_int(kth::domain::machine::operation::is_relaxed_push(code_c));
}

} // extern "C"
