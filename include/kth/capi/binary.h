// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_CAPI_BINARY_H
#define KTH_CAPI_BINARY_H

#include <stdint.h>

#include <kth/capi/primitives.h>
#include <kth/capi/visibility.h>

#ifdef __cplusplus
extern "C" {
#endif

KTH_EXPORT
kth_binary_t kth_core_binary_construct(void);

KTH_EXPORT
kth_binary_t kth_core_binary_construct_string(char const* string);

KTH_EXPORT
kth_binary_t kth_core_binary_construct_blocks(kth_size_t bits_size, uint8_t* blocks, kth_size_t n);

KTH_EXPORT
void kth_core_binary_destruct(kth_binary_t binary);

KTH_EXPORT
uint8_t const* kth_core_binary_blocks(kth_binary_t binary, kth_size_t* out_n);

KTH_EXPORT
char* kth_core_binary_encoded(kth_binary_t binary);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // KTH_CAPI_BINARY_H
