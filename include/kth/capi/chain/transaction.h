// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#ifndef KTH_NODECINT_CHAIN_TRANSACTION_H_
#define KTH_NODECINT_CHAIN_TRANSACTION_H_

#include <stdint.h>

#include <knuth/nodecint/primitives.h>
#include <knuth/nodecint/visibility.h>

#ifdef __cplusplus
extern "C" {
#endif

KTH_EXPORT
transaction_t chain_transaction_factory_from_data(uint32_t version, uint8_t* data, uint64_t n);

KTH_EXPORT
transaction_t chain_transaction_construct_default(void);

KTH_EXPORT
transaction_t chain_transaction_construct(uint32_t version, uint32_t locktime, input_list_t inputs, output_list_t outputs);

KTH_EXPORT
void chain_transaction_destruct(transaction_t transaction);

KTH_EXPORT
int chain_transaction_is_valid(transaction_t transaction);

KTH_EXPORT
uint32_t chain_transaction_version(transaction_t transaction);

KTH_EXPORT
void chain_transaction_set_version(transaction_t transaction, uint32_t version);

KTH_EXPORT
hash_t chain_transaction_hash(transaction_t transaction);

KTH_EXPORT
void chain_transaction_hash_out(transaction_t transaction, hash_t* out_hash);

KTH_EXPORT
hash_t chain_transaction_hash_sighash_type(transaction_t transaction, uint32_t sighash_type);

KTH_EXPORT
void chain_transaction_hash_sighash_type_out(transaction_t transaction, uint32_t sighash_type, hash_t* out_hash);

KTH_EXPORT
uint32_t chain_transaction_locktime(transaction_t transaction);

KTH_EXPORT
uint64_t /*size_t*/ chain_transaction_serialized_size(transaction_t transaction, int wire /*= true*/);

KTH_EXPORT
uint64_t chain_transaction_fees(transaction_t transaction);

KTH_EXPORT
uint64_t /*size_t*/ chain_transaction_signature_operations(transaction_t transaction);

KTH_EXPORT
uint64_t /*size_t*/ chain_transaction_signature_operations_bip16_active(transaction_t transaction, bool_t bip16_active);

KTH_EXPORT
uint64_t chain_transaction_total_input_value(transaction_t transaction);

KTH_EXPORT
uint64_t chain_transaction_total_output_value(transaction_t transaction);

KTH_EXPORT
bool_t chain_transaction_is_coinbase(transaction_t transaction);

KTH_EXPORT
bool_t chain_transaction_is_null_non_coinbase(transaction_t transaction);

KTH_EXPORT
bool_t chain_transaction_is_oversized_coinbase(transaction_t transaction);

KTH_EXPORT
bool_t chain_transaction_is_mature(transaction_t transaction, uint64_t /*size_t*/ target_height);

KTH_EXPORT
bool_t chain_transaction_is_overspent(transaction_t transaction);

KTH_EXPORT
bool_t chain_transaction_is_double_spend(transaction_t transaction, bool_t include_unconfirmed);

KTH_EXPORT
bool_t chain_transaction_is_missing_previous_outputs(transaction_t transaction);

KTH_EXPORT
bool_t chain_transaction_is_final(transaction_t transaction, uint64_t /*size_t*/ block_height, uint32_t block_time);

KTH_EXPORT
bool_t chain_transaction_is_locktime_conflict(transaction_t transaction);

KTH_EXPORT
output_list_t chain_transaction_outputs(transaction_t transaction);

KTH_EXPORT
input_list_t chain_transaction_inputs(transaction_t transaction);

KTH_EXPORT
uint8_t* chain_transaction_to_data(transaction_t transaction, bool_t wire, uint64_t* /*size_t*/ out_size);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* KTH_NODECINT_CHAIN_TRANSACTION_H_ */
