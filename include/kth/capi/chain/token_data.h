// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_CAPI_CHAIN_TOKEN_DATA_H_
#define KTH_CAPI_CHAIN_TOKEN_DATA_H_

#include <stdint.h>

#include <kth/capi/primitives.h>
#include <kth/capi/visibility.h>

#include <kth/capi/chain/token_capability.h>
#include <kth/capi/chain/token_kind.h>

#ifdef __cplusplus
extern "C" {
#endif

KTH_EXPORT
kth_token_data_t kth_chain_token_data_construct_default(void);

KTH_EXPORT
kth_token_data_t kth_chain_token_data_construct_fungible(kth_hash_t const* token_category, int64_t token_amount);

KTH_EXPORT
kth_token_data_t kth_chain_token_data_construct_non_fungible(kth_hash_t const* token_category, kth_token_capability_t capability, uint8_t* commitment_data, kth_size_t commitment_n);

KTH_EXPORT
kth_token_data_t kth_chain_token_data_construct_both(kth_hash_t const* token_category, int64_t token_amount, kth_token_capability_t capability, uint8_t* commitment_data, kth_size_t commitment_n);

KTH_EXPORT
void kth_chain_token_data_destruct(kth_token_data_t token_data);

KTH_EXPORT
kth_bool_t kth_chain_token_data_is_valid(kth_token_data_t token_data);

KTH_EXPORT
kth_size_t kth_chain_token_data_serialized_size(kth_token_data_t token_data);

KTH_EXPORT
uint8_t const* kth_chain_token_data_to_data(kth_token_data_t token_data, kth_size_t* out_size);

KTH_EXPORT
kth_token_kind_t kth_chain_token_data_kind(kth_token_data_t token_data);

KTH_EXPORT
kth_hash_t kth_chain_token_data_category(kth_token_data_t token_data);

KTH_EXPORT
void kth_chain_token_data_category_out(kth_token_data_t token_data, kth_hash_t* out_category);

KTH_EXPORT
int64_t kth_chain_token_data_fungible_amount(kth_token_data_t token_data);

KTH_EXPORT
kth_token_capability_t kth_chain_token_data_non_fungible_capability(kth_token_data_t token_data);

KTH_EXPORT
uint8_t const* kth_chain_token_data_non_fungible_commitment(kth_token_data_t token_data, kth_size_t* out_size);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* KTH_CAPI_CHAIN_TOKEN_DATA_H_ */
