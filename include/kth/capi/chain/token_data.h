// Copyright (c) 2016-2023 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_CAPI_CHAIN_TOKEN_DATA_H_
#define KTH_CAPI_CHAIN_TOKEN_DATA_H_

#include <stdint.h>

#include <kth/capi/primitives.h>
#include <kth/capi/visibility.h>

#ifdef __cplusplus
extern "C" {
#endif

KTH_EXPORT
kth_token_data_t kth_chain_token_data_construct_default(void);

// KTH_EXPORT
// kth_token_data_t kth_chain_token_data_construct();

KTH_EXPORT
void kth_chain_token_data_destruct(kth_token_data_t token_data);

KTH_EXPORT
kth_bool_t kth_chain_token_data_is_valid(kth_token_data_t token_data);

KTH_EXPORT
kth_size_t kth_chain_token_data_serialized_size(kth_token_data_t token_data);

KTH_EXPORT
uint8_t const* kth_chain_token_data_to_data(kth_token_data_t token_data, kth_size_t* out_size);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* KTH_CAPI_CHAIN_TOKEN_DATA_H_ */
