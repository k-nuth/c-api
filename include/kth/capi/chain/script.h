// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#ifndef KTH_NODECINT_CHAIN_SCRIPT_H_
#define KTH_NODECINT_CHAIN_SCRIPT_H_

#include <stdint.h>

#include <kth/capi/primitives.h>
#include <kth/capi/visibility.h>

#ifdef __cplusplus
extern "C" {
#endif

KTH_EXPORT
script_t chain_script_construct_default(void);

KTH_EXPORT
script_t chain_script_construct(uint8_t* encoded, uint64_t n, bool_t prefix);

KTH_EXPORT
void chain_script_destruct(script_t script);

KTH_EXPORT
bool_t chain_script_is_valid(script_t script);

KTH_EXPORT
bool_t chain_script_is_valid_operations(script_t script);

KTH_EXPORT
uint64_t /*size_t*/ chain_script_satoshi_content_size(script_t script);

KTH_EXPORT
uint64_t /*size_t*/ chain_script_serialized_size(script_t script, bool_t prefix);

//Note: user of the function has to release the resource (memory) manually
KTH_EXPORT
char* chain_script_to_string(script_t script, uint32_t active_forks);

//Note: user of the function has to release the resource (memory) manually
KTH_EXPORT
char* chain_script_type(script_t script);

//Note: user of the function has to release the resource (memory) manually
KTH_EXPORT
uint8_t* chain_script_to_data(script_t script, bool_t prefix, uint64_t* /*size_t*/ out_size);

KTH_EXPORT
uint64_t /*size_t*/ chain_script_sigops(script_t script, bool_t embedded);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* KTH_NODECINT_CHAIN_SCRIPT_H_ */
