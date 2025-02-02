// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_CAPI_CHAIN_OPERATION_H_
#define KTH_CAPI_CHAIN_OPERATION_H_

#include <stdint.h>

#include <kth/capi/primitives.h>
#include <kth/capi/visibility.h>

#include <kth/capi/chain/opcode.h>

#ifdef __cplusplus
extern "C" {
#endif

KTH_EXPORT
kth_operation_t kth_chain_operation_construct_default();

KTH_EXPORT
kth_operation_t kth_chain_operation_construct_from_bytes(uint8_t* uncoded, kth_size_t n, kth_bool_t minimal);

KTH_EXPORT
kth_operation_t kth_chain_operation_construct_from_opcode(kth_opcode_t opcode);

KTH_EXPORT
kth_operation_t kth_chain_operation_construct_from_string(char const* value);

KTH_EXPORT
void kth_chain_operation_destruct(kth_operation_t operation);

KTH_EXPORT
char const* kth_chain_operation_to_string(kth_operation_t operation, uint32_t active_forks);

KTH_EXPORT
uint8_t const* kth_chain_operation_to_data(kth_operation_t operation, kth_size_t* out_size);

KTH_EXPORT
kth_bool_t kth_chain_operation_from_data_mutable(kth_operation_t operation, uint8_t const* data, kth_size_t n);

KTH_EXPORT
kth_bool_t kth_chain_operation_from_string_mutable(kth_operation_t operation, char const* value);

KTH_EXPORT
kth_bool_t kth_chain_operation_is_valid(kth_operation_t operation);

KTH_EXPORT
kth_size_t kth_chain_operation_serialized_size(kth_operation_t operation);

KTH_EXPORT
kth_opcode_t kth_chain_operation_code(kth_operation_t operation);

KTH_EXPORT
uint8_t const* kth_chain_operation_data(kth_operation_t operation, kth_size_t* out_size);

// ******************************************
// Categories of operations
// ******************************************

KTH_EXPORT
kth_bool_t kth_chain_operation_is_push(kth_operation_t operation);

KTH_EXPORT
kth_bool_t kth_chain_operation_is_counted(kth_operation_t operation);

KTH_EXPORT
kth_bool_t kth_chain_operation_is_version(kth_operation_t operation);

KTH_EXPORT
kth_bool_t kth_chain_operation_is_positive(kth_operation_t operation);

KTH_EXPORT
kth_bool_t kth_chain_operation_is_disabled(kth_operation_t operation, uint32_t active_forks);

KTH_EXPORT
kth_bool_t kth_chain_operation_is_conditional(kth_operation_t operation);

KTH_EXPORT
kth_bool_t kth_chain_operation_is_relaxed_push(kth_operation_t operation);

KTH_EXPORT
kth_bool_t kth_chain_operation_is_oversized(kth_operation_t operation, kth_size_t max_size);

KTH_EXPORT
kth_bool_t kth_chain_operation_is_minimal_push(kth_operation_t operation);

KTH_EXPORT
kth_bool_t kth_chain_operation_is_nominal_push(kth_operation_t operation);


// ******************************************
// static functions
// ******************************************

KTH_EXPORT
kth_opcode_t kth_chain_operation_opcode_from_size(kth_size_t size);

KTH_EXPORT
kth_opcode_t kth_chain_operation_minimal_opcode_from_data(uint8_t const* data, kth_size_t n);

KTH_EXPORT
kth_opcode_t kth_chain_operation_nominal_opcode_from_data(uint8_t const* data, kth_size_t n);

KTH_EXPORT
kth_opcode_t kth_chain_operation_opcode_from_positive(uint8_t value);

KTH_EXPORT
uint8_t kth_chain_operation_opcode_to_positive(kth_opcode_t code);

KTH_EXPORT
kth_bool_t kth_chain_operation_opcode_is_push(kth_opcode_t code);

KTH_EXPORT
kth_bool_t kth_chain_operation_opcode_is_payload(kth_opcode_t code);

KTH_EXPORT
kth_bool_t kth_chain_operation_opcode_is_counted(kth_opcode_t code);

KTH_EXPORT
kth_bool_t kth_chain_operation_opcode_is_version(kth_opcode_t code);

KTH_EXPORT
kth_bool_t kth_chain_operation_opcode_is_numeric(kth_opcode_t code);

KTH_EXPORT
kth_bool_t kth_chain_operation_opcode_is_positive(kth_opcode_t code);

KTH_EXPORT
kth_bool_t kth_chain_operation_opcode_is_reserved(kth_opcode_t code);

KTH_EXPORT
kth_bool_t kth_chain_operation_opcode_is_disabled(kth_opcode_t code, uint32_t active_forks);

KTH_EXPORT
kth_bool_t kth_chain_operation_opcode_is_conditional(kth_opcode_t code);

KTH_EXPORT
kth_bool_t kth_chain_operation_opcode_is_relaxed_push(kth_opcode_t code);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* KTH_CAPI_CHAIN_OPERATION_H_ */
