// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#ifndef KTH_CAPI_CHAIN_INPUT_H_
#define KTH_CAPI_CHAIN_INPUT_H_

#include <stdint.h>

#include <kth/capi/primitives.h>
#include <kth/capi/visibility.h>

#ifdef __cplusplus
extern "C" {
#endif

KTH_EXPORT
input_t chain_input_construct_default(void);

KTH_EXPORT
input_t chain_input_construct(output_point_t previous_output, script_t script, uint32_t sequence);

KTH_EXPORT
void chain_input_destruct(input_t input);

KTH_EXPORT
int chain_input_is_valid(input_t input);

KTH_EXPORT
bool_t chain_input_is_final(input_t input);

KTH_EXPORT
uint64_t /*size_t*/ chain_input_serialized_size(input_t input, bool_t wire /* = true*/);

KTH_EXPORT
uint32_t chain_input_sequence(input_t input);

KTH_EXPORT
uint64_t /*size_t*/ chain_input_signature_operations(input_t input, bool_t bip16_active);

KTH_EXPORT
script_t chain_input_script(input_t input);

KTH_EXPORT
output_point_t chain_input_previous_output(input_t input);

KTH_EXPORT
uint8_t* chain_input_to_data(input_t input, bool_t wire, uint64_t* /*size_t*/ out_size);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* KTH_CAPI_CHAIN_INPUT_H_ */
