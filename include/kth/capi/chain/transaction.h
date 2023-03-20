// Copyright (c) 2016-2023 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_CAPI_CHAIN_TRANSACTION_H_
#define KTH_CAPI_CHAIN_TRANSACTION_H_

#include <stdint.h>

#include <kth/capi/primitives.h>
#include <kth/capi/visibility.h>

#ifdef __cplusplus
extern "C" {
#endif

KTH_EXPORT
kth_transaction_t kth_chain_transaction_factory_from_data(uint32_t version, uint8_t* data, kth_size_t n);

KTH_EXPORT
kth_transaction_t kth_chain_transaction_construct_default(void);

KTH_EXPORT
kth_transaction_t kth_chain_transaction_construct(uint32_t version, uint32_t locktime, kth_input_list_t inputs, kth_output_list_t outputs);

KTH_EXPORT
void kth_chain_transaction_destruct(kth_transaction_t transaction);

KTH_EXPORT
kth_bool_t kth_chain_transaction_is_valid(kth_transaction_t transaction);

KTH_EXPORT
uint32_t kth_chain_transaction_version(kth_transaction_t transaction);

KTH_EXPORT
void kth_chain_transaction_set_version(kth_transaction_t transaction, uint32_t version);

KTH_EXPORT
kth_hash_t kth_chain_transaction_hash(kth_transaction_t transaction);

KTH_EXPORT
void kth_chain_transaction_hash_out(kth_transaction_t transaction, kth_hash_t* out_hash);

KTH_EXPORT
kth_hash_t kth_chain_transaction_hash_sighash_type(kth_transaction_t transaction, uint32_t sighash_type);

KTH_EXPORT
void kth_chain_transaction_hash_sighash_type_out(kth_transaction_t transaction, uint32_t sighash_type, kth_hash_t* out_hash);

KTH_EXPORT
uint32_t kth_chain_transaction_locktime(kth_transaction_t transaction);

KTH_EXPORT
kth_size_t kth_chain_transaction_serialized_size(kth_transaction_t transaction, kth_bool_t wire); //wire = true

KTH_EXPORT
uint64_t kth_chain_transaction_fees(kth_transaction_t transaction);

KTH_EXPORT
kth_size_t kth_chain_transaction_signature_operations(kth_transaction_t transaction);

KTH_EXPORT
kth_size_t kth_chain_transaction_signature_operations_bip16_active(kth_transaction_t transaction, kth_bool_t bip16_active);

KTH_EXPORT
uint64_t kth_chain_transaction_total_input_value(kth_transaction_t transaction);

KTH_EXPORT
uint64_t kth_chain_transaction_total_output_value(kth_transaction_t transaction);

KTH_EXPORT
kth_bool_t kth_chain_transaction_is_coinbase(kth_transaction_t transaction);

KTH_EXPORT
kth_bool_t kth_chain_transaction_is_null_non_coinbase(kth_transaction_t transaction);

KTH_EXPORT
kth_bool_t kth_chain_transaction_is_oversized_coinbase(kth_transaction_t transaction);

KTH_EXPORT
kth_bool_t kth_chain_transaction_is_mature(kth_transaction_t transaction, kth_size_t target_height);

KTH_EXPORT
kth_bool_t kth_chain_transaction_is_overspent(kth_transaction_t transaction);

KTH_EXPORT
kth_bool_t kth_chain_transaction_is_double_spend(kth_transaction_t transaction, kth_bool_t include_unconfirmed);

KTH_EXPORT
kth_bool_t kth_chain_transaction_is_missing_previous_outputs(kth_transaction_t transaction);

KTH_EXPORT
kth_bool_t kth_chain_transaction_is_final(kth_transaction_t transaction, kth_size_t block_height, uint32_t kth_block_time);

KTH_EXPORT
kth_bool_t kth_chain_transaction_is_locktime_conflict(kth_transaction_t transaction);

KTH_EXPORT
kth_output_list_t kth_chain_transaction_outputs(kth_transaction_t transaction);

KTH_EXPORT
kth_input_list_t kth_chain_transaction_inputs(kth_transaction_t transaction);

KTH_EXPORT
uint8_t const* kth_chain_transaction_to_data(kth_transaction_t transaction, kth_bool_t wire, kth_size_t* out_size);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* KTH_CAPI_CHAIN_TRANSACTION_H_ */
