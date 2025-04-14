// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_CAPI_CHAIN_UTXO_H_
#define KTH_CAPI_CHAIN_UTXO_H_

#include <stdint.h>

#include <kth/capi/primitives.h>
#include <kth/capi/visibility.h>

#include <kth/capi/chain/token_capability.h>
#include <kth/capi/chain/token_kind.h>

#ifdef __cplusplus
extern "C" {
#endif

KTH_EXPORT
kth_utxo_t kth_chain_utxo_construct(void);

KTH_EXPORT
kth_utxo_t kth_chain_utxo_construct_from_hash_index_amount(kth_hash_t const* hash, uint32_t index, uint64_t amount);

KTH_EXPORT
kth_utxo_t kth_chain_utxo_construct_from_hash_index_amount_fungible(kth_hash_t const* hash, uint32_t index, uint64_t amount, kth_hash_t const* token_category, uint64_t token_amount);

KTH_EXPORT
kth_utxo_t kth_chain_utxo_construct_from_hash_index_amount_non_fungible(kth_hash_t const* hash, uint32_t index, uint64_t amount, kth_hash_t const* token_category, kth_token_capability_t capability, uint8_t* commitment_data, kth_size_t commitment_n);

KTH_EXPORT
kth_utxo_t kth_chain_utxo_construct_from_hash_index_amount_both(kth_hash_t const* hash, uint32_t index, uint64_t amount, kth_hash_t const* token_category, uint64_t token_amount, kth_token_capability_t capability, uint8_t* commitment_data, kth_size_t commitment_n);

KTH_EXPORT
void kth_chain_utxo_destruct(kth_utxo_t utxo);

// Getters
KTH_EXPORT
kth_hash_t kth_chain_utxo_get_hash(kth_utxo_t utxo);

KTH_EXPORT
void kth_chain_utxo_get_hash_out(kth_utxo_t utxo, kth_hash_t* out_hash);

KTH_EXPORT
uint32_t kth_chain_utxo_get_index(kth_utxo_t utxo);

KTH_EXPORT
uint64_t kth_chain_utxo_get_amount(kth_utxo_t utxo);

KTH_EXPORT
kth_output_t kth_chain_utxo_get_cached_output(kth_utxo_t utxo);

KTH_EXPORT
kth_bool_t kth_chain_utxo_has_token_data(kth_utxo_t utxo);

KTH_EXPORT
kth_token_data_t kth_chain_utxo_get_token_data(kth_utxo_t utxo);

KTH_EXPORT
kth_hash_t kth_chain_utxo_get_token_category(kth_utxo_t utxo);

KTH_EXPORT
void kth_chain_utxo_get_token_category_out(kth_utxo_t utxo, kth_hash_t* out_token_category);

KTH_EXPORT
uint64_t kth_chain_utxo_get_token_amount(kth_utxo_t utxo);

KTH_EXPORT
kth_token_capability_t kth_chain_utxo_get_token_capability(kth_utxo_t utxo);

KTH_EXPORT
uint8_t const* kth_chain_utxo_get_token_commitment(kth_utxo_t utxo, kth_size_t* out_size);

// Setters
KTH_EXPORT
void kth_chain_utxo_set_hash(kth_utxo_t utxo, kth_hash_t const* hash);

KTH_EXPORT
void kth_chain_utxo_set_index(kth_utxo_t utxo, uint32_t index);

KTH_EXPORT
void kth_chain_utxo_set_amount(kth_utxo_t utxo, uint64_t amount);

KTH_EXPORT
void kth_chain_utxo_set_cached_output(kth_utxo_t utxo, kth_output_t output);

KTH_EXPORT
void kth_chain_utxo_set_token_data(kth_utxo_t utxo, kth_token_data_t token_data);

KTH_EXPORT
void kth_chain_utxo_set_fungible_token_data(kth_utxo_t utxo, kth_hash_t const* token_category, int64_t token_amount);

KTH_EXPORT
void kth_chain_utxo_set_token_category(kth_utxo_t utxo, kth_hash_t const* token_category);

KTH_EXPORT
void kth_chain_utxo_set_token_amount(kth_utxo_t utxo, int64_t token_amount);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // KTH_CAPI_CHAIN_UTXO_H_