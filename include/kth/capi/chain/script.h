// Copyright (c) 2016-2023 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_CAPI_CHAIN_SCRIPT_H_
#define KTH_CAPI_CHAIN_SCRIPT_H_

#include <stdint.h>

#include <kth/capi/primitives.h>
#include <kth/capi/visibility.h>

#ifdef __cplusplus
extern "C" {
#endif

KTH_EXPORT
kth_script_t kth_chain_script_construct_default(void);

KTH_EXPORT
kth_script_t kth_chain_script_construct(uint8_t* encoded, kth_size_t n, kth_bool_t prefix);

KTH_EXPORT
void kth_chain_script_destruct(kth_script_t script);

KTH_EXPORT
kth_bool_t kth_chain_script_is_valid(kth_script_t script);

KTH_EXPORT
kth_bool_t kth_chain_script_is_valid_operations(kth_script_t script);

KTH_EXPORT
kth_size_t kth_chain_script_satoshi_content_size(kth_script_t script);

KTH_EXPORT
kth_size_t kth_chain_script_serialized_size(kth_script_t script, kth_bool_t prefix);

KTH_EXPORT
char const* kth_chain_script_to_string(kth_script_t script, uint32_t active_forks);

KTH_EXPORT
char const* kth_chain_script_type(kth_script_t script);

KTH_EXPORT
uint8_t const* kth_chain_script_to_data(kth_script_t script, kth_bool_t prefix, kth_size_t* out_size);

KTH_EXPORT
kth_size_t kth_chain_script_sigops(kth_script_t script, kth_bool_t embedded);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* KTH_CAPI_CHAIN_SCRIPT_H_ */
