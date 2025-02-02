// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_CAPI_CHAIN_UTXO_H_
#define KTH_CAPI_CHAIN_UTXO_H_

#include <stdint.h>

#include <kth/capi/primitives.h>
#include <kth/capi/visibility.h>

#ifdef __cplusplus
extern "C" {
#endif

KTH_EXPORT
kth_utxo_t kth_chain_utxo_construct(void);

KTH_EXPORT
kth_utxo_t kth_chain_utxo_construct_from_hash_index_amount(kth_hash_t const* hash, uint32_t index, uint64_t amount);

KTH_EXPORT
void kth_chain_utxo_destruct(kth_utxo_t op);

KTH_EXPORT
kth_hash_t kth_chain_utxo_get_hash(kth_utxo_t op);

KTH_EXPORT
void kth_chain_utxo_get_hash_out(kth_utxo_t op, kth_hash_t* out_hash);

KTH_EXPORT
uint32_t kth_chain_utxo_get_index(kth_utxo_t op);

KTH_EXPORT
uint64_t kth_chain_utxo_get_amount(kth_utxo_t op);

KTH_EXPORT
kth_output_t kth_chain_utxo_get_cached_output(kth_utxo_t op);

KTH_EXPORT
void kth_chain_utxo_set_hash(kth_utxo_t op, kth_hash_t const* hash);

KTH_EXPORT
void kth_chain_utxo_set_index(kth_utxo_t op, uint32_t index);

KTH_EXPORT
void kth_chain_utxo_set_amount(kth_utxo_t op, uint64_t amount);

KTH_EXPORT
void kth_chain_utxo_set_cached_output(kth_utxo_t op, kth_output_t output);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // KTH_CAPI_CHAIN_UTXO_H_