// Copyright (c) 2016-2023 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_CAPI_PLATFORM_H
#define KTH_CAPI_PLATFORM_H

#include <kth/capi/primitives.h>
#include <kth/capi/visibility.h>

#ifdef __cplusplus
extern "C" {
#endif

KTH_EXPORT
void kth_platform_free(void* ptr);

KTH_EXPORT
char* kth_platform_allocate_string(kth_size_t n);

KTH_EXPORT
void kth_platform_allocate_string_at(char** ptr, kth_size_t n);

KTH_EXPORT
char** kth_platform_allocate_array_of_strings(kth_size_t n);

KTH_EXPORT
void kth_platform_print_string(char* str);

KTH_EXPORT
char* kth_platform_allocate_and_copy_string_at(char** ptr, kth_size_t offset, char const* str);

#ifdef __cplusplus
} // extern "C"
#endif

#endif //KTH_CAPI_PLATFORM_H
