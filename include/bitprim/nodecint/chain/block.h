// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#ifndef KTH_NODECINT_CHAIN_BLOCK_H_
#define KTH_NODECINT_CHAIN_BLOCK_H_

#include <stdint.h>

#include <knuth/nodecint/primitives.h>
#include <knuth/nodecint/visibility.h>

#ifdef __cplusplus
extern "C" {
#endif

KTH_EXPORT
block_t chain_block_construct_default(void);

KTH_EXPORT
block_t chain_block_construct(header_t header, transaction_list_t transactions);

KTH_EXPORT
block_t chain_block_factory_from_data(uint32_t version, uint8_t* data, uint64_t n);

KTH_EXPORT
void chain_block_destruct(block_t block);

KTH_EXPORT
int chain_block_is_valid(block_t block);

KTH_EXPORT
header_t chain_block_header(block_t block);

KTH_EXPORT
hash_t chain_block_hash(block_t block);

KTH_EXPORT
void chain_block_hash_out(block_t block, hash_t* out_hash);

//deprecated
KTH_EXPORT
char const* chain_block_proof(block_t block);

KTH_EXPORT
char const* chain_block_proof_str(block_t block);

KTH_EXPORT
uint64_t /*size_t*/ chain_block_transaction_count(block_t block);

KTH_EXPORT
transaction_t chain_block_transaction_nth(block_t block, uint64_t /*size_t*/ n);

//KTH_EXPORT
//transaction_t chain_block_transactions(block_t block, uint64_t* /*size_t*/ n);
//
//KTH_EXPORT
//transaction_t chain_block_transaction_next(transaction_t transaction);

KTH_EXPORT
uint64_t /*size_t*/ chain_block_serialized_size(block_t block, uint32_t version);

KTH_EXPORT
/*static*/
uint64_t chain_block_subsidy(uint64_t /*size_t*/ height);

KTH_EXPORT
uint64_t chain_block_fees(block_t block);

KTH_EXPORT
uint64_t chain_block_claim(block_t block);

KTH_EXPORT
uint64_t chain_block_reward(block_t block, uint64_t /*size_t*/ height);

//Note: The user is responsible for the resource release
KTH_EXPORT
hash_t chain_block_generate_merkle_root(block_t block);

KTH_EXPORT
void chain_block_generate_merkle_root_out(block_t block, hash_t* out_merkle);

KTH_EXPORT
uint64_t /*size_t*/ chain_block_signature_operations(block_t block);

KTH_EXPORT
uint64_t /*size_t*/ chain_block_signature_operations_bip16_active(block_t block, bool_t bip16_active);

KTH_EXPORT
uint64_t /*size_t*/ chain_block_total_inputs(block_t block, bool_t with_coinbase /*= true*/);

KTH_EXPORT
bool_t chain_block_is_extra_coinbases(block_t block);

KTH_EXPORT
bool_t chain_block_is_final(block_t block, uint64_t /*size_t*/ height, uint32_t block_time);

KTH_EXPORT
bool_t chain_block_is_distinct_transaction_set(block_t block);

KTH_EXPORT
bool_t chain_block_is_valid_coinbase_claim(block_t block, uint64_t /*size_t*/ height);

KTH_EXPORT
bool_t chain_block_is_valid_coinbase_script(block_t block, uint64_t /*size_t*/ height);

KTH_EXPORT
bool_t chain_block_is_internal_double_spend(block_t block);

KTH_EXPORT
bool_t chain_block_is_valid_merkle_root(block_t block);

KTH_EXPORT
uint8_t const* chain_block_to_data(block_t block, bool_t wire, uint64_t* /*size_t*/ out_size);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* KTH_NODECINT_CHAIN_BLOCK_H_ */
