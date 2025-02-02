// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_CAPI_CORE_U64_LIST_H_
#define KTH_CAPI_CORE_U64_LIST_H_

#include <stdint.h>

#include <kth/capi/primitives.h>
#include <kth/capi/visibility.h>

#ifdef __cplusplus
extern "C" {
#endif

KTH_EXPORT
kth_u64_list_t kth_core_u64_list_construct(void);

KTH_EXPORT
void kth_core_u64_list_push_back(kth_u64_list_t u64_list, uint64_t value);

KTH_EXPORT
void kth_core_u64_list_destruct(kth_u64_list_t u64_list);

KTH_EXPORT
uint64_t kth_core_u64_list_nth(kth_u64_list_t u64_list, kth_size_t index);

KTH_EXPORT
kth_size_t kth_core_u64_list_count(kth_u64_list_t u64_list);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* KTH_CAPI_CORE_U64_LIST_H_ */