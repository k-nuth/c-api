// Copyright (c) 2016-2024 Knuth Project developers.
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
kth_input_t kth_chain_input_construct_default(void);

KTH_EXPORT
kth_input_t kth_chain_input_construct(kth_outputpoint_t previous_output, kth_script_t script, uint32_t sequence);

KTH_EXPORT
void kth_chain_input_destruct(kth_input_t input);

KTH_EXPORT
kth_input_t kth_chain_input_factory_from_data(uint8_t* data, kth_size_t n);

KTH_EXPORT
kth_bool_t kth_chain_input_is_valid(kth_input_t input);

KTH_EXPORT
kth_bool_t kth_chain_input_is_final(kth_input_t input);

KTH_EXPORT
kth_size_t kth_chain_input_serialized_size(kth_input_t input, kth_bool_t wire); //wire = true

KTH_EXPORT
uint32_t kth_chain_input_sequence(kth_input_t input);

KTH_EXPORT
kth_size_t kth_chain_input_signature_operations(kth_input_t input, kth_bool_t bip16_active);

KTH_EXPORT
kth_script_t kth_chain_input_script(kth_input_t input);

KTH_EXPORT
kth_outputpoint_t kth_chain_input_previous_output(kth_input_t input);

KTH_EXPORT
uint8_t const* kth_chain_input_to_data(kth_input_t input, kth_bool_t wire, kth_size_t* out_size);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* KTH_CAPI_CHAIN_INPUT_H_ */
