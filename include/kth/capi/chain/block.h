// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_CAPI_CHAIN_BLOCK_H_
#define KTH_CAPI_CHAIN_BLOCK_H_

#include <stdint.h>

#include <kth/capi/primitives.h>
#include <kth/capi/visibility.h>

#ifdef __cplusplus
extern "C" {
#endif

KTH_EXPORT
kth_block_t kth_chain_block_construct_default(void);

KTH_EXPORT
kth_block_t kth_chain_block_construct(kth_header_t header, kth_transaction_list_t transactions);

KTH_EXPORT
kth_block_t kth_chain_block_factory_from_data(uint8_t* data, kth_size_t n);

KTH_EXPORT
void kth_chain_block_destruct(kth_block_t block);

KTH_EXPORT
kth_bool_t kth_chain_block_is_valid(kth_block_t block);

KTH_EXPORT
kth_header_t kth_chain_block_header(kth_block_t block);

KTH_EXPORT
kth_hash_t kth_chain_block_hash(kth_block_t block);

KTH_EXPORT
void kth_chain_block_hash_out(kth_block_t block, kth_hash_t* out_hash);

KTH_EXPORT
char const* kth_chain_block_proof_str(kth_block_t block);

KTH_EXPORT
kth_transaction_list_t kth_chain_block_transactions(kth_block_t block);

KTH_EXPORT
kth_size_t kth_chain_block_serialized_size(kth_block_t block);

/*static*/
KTH_EXPORT
uint64_t kth_chain_block_subsidy(kth_size_t height);

KTH_EXPORT
uint64_t kth_chain_block_fees(kth_block_t block);

KTH_EXPORT
uint64_t kth_chain_block_claim(kth_block_t block);

KTH_EXPORT
uint64_t kth_chain_block_reward(kth_block_t block, kth_size_t height);

KTH_EXPORT
kth_hash_t kth_chain_block_generate_merkle_root(kth_block_t block);

KTH_EXPORT
void kth_chain_block_generate_merkle_root_out(kth_block_t block, kth_hash_t* out_merkle);

KTH_EXPORT
kth_size_t kth_chain_block_signature_operations(kth_block_t block);

KTH_EXPORT
kth_size_t kth_chain_block_signature_operations_bip16_active(kth_block_t block, kth_bool_t bip16_active);

KTH_EXPORT
kth_size_t kth_chain_block_total_inputs(kth_block_t block, kth_bool_t with_coinbase); //with_coinbase = true

KTH_EXPORT
kth_bool_t kth_chain_block_is_extra_coinbases(kth_block_t block);

KTH_EXPORT
kth_bool_t kth_chain_block_is_final(kth_block_t block, kth_size_t height, uint32_t kth_block_time);

KTH_EXPORT
kth_bool_t kth_chain_block_is_distinct_transaction_set(kth_block_t block);

KTH_EXPORT
kth_bool_t kth_chain_block_is_valid_coinbase_claim(kth_block_t block, kth_size_t height);

KTH_EXPORT
kth_bool_t kth_chain_block_is_valid_coinbase_script(kth_block_t block, kth_size_t height);

KTH_EXPORT
kth_bool_t kth_chain_block_is_internal_double_spend(kth_block_t block);

KTH_EXPORT
kth_bool_t kth_chain_block_is_valid_merkle_root(kth_block_t block);

KTH_EXPORT
uint8_t const* kth_chain_block_to_data(kth_block_t block, kth_bool_t wire, kth_size_t* out_size);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* KTH_CAPI_CHAIN_BLOCK_H_ */
