// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_CAPI_STRING_LIST_H_
#define KTH_CAPI_STRING_LIST_H_

#include <stdint.h>

#include <kth/capi/primitives.h>
#include <kth/capi/visibility.h>

#ifdef __cplusplus
extern "C" {
#endif

KTH_EXPORT
kth_string_list_t kth_core_string_list_construct(void);

KTH_EXPORT
void kth_core_string_list_push_back(kth_string_list_t string_list, char const* string);

KTH_EXPORT
void kth_core_string_list_destruct(kth_string_list_t string_list);

KTH_EXPORT
char const* kth_core_string_list_nth(kth_string_list_t string_list, kth_size_t index);

KTH_EXPORT
kth_size_t kth_core_string_list_count(kth_string_list_t string_list);


#ifdef __cplusplus
} // extern "C"
#endif

#endif /* KTH_CAPI_WALLET_WORD_LIST_H_ */