// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#ifndef KTH_CAPI_CHAIN_OUTPUT_H_
#define KTH_CAPI_CHAIN_OUTPUT_H_

#include <stdint.h>

#include <kth/capi/primitives.h>
#include <kth/capi/visibility.h>

#ifdef __cplusplus
extern "C" {
#endif

KTH_EXPORT
output_t chain_output_construct_default(void);

KTH_EXPORT
output_t chain_output_construct(uint64_t value, script_t script);

KTH_EXPORT
void chain_output_destruct(output_t output);

KTH_EXPORT
int chain_output_is_valid(output_t output);

KTH_EXPORT
uint64_t /*size_t*/ chain_output_serialized_size(output_t output, bool_t wire /*= true*/);

KTH_EXPORT
uint64_t chain_output_value(output_t output);

KTH_EXPORT
uint64_t /*size_t*/ chain_output_signature_operations(output_t output);

KTH_EXPORT
script_t chain_output_script(output_t output);

KTH_EXPORT
payment_address_t chain_output_payment_address(output_t output, bool_t use_testnet_rules);

KTH_EXPORT
uint8_t* chain_output_to_data(output_t output, bool_t wire, uint64_t* /*size_t*/ out_size);

//KTH_EXPORT
//uint32_t chain_output_get_index(output_t output);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* KTH_CAPI_CHAIN_OUTPUT_H_ */
