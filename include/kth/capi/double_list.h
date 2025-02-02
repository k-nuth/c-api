// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_CAPI_DOUBLE_LIST_H_
#define KTH_CAPI_DOUBLE_LIST_H_

#include <stdint.h>

#include <kth/capi/primitives.h>
#include <kth/capi/visibility.h>

#ifdef __cplusplus
extern "C" {
#endif

KTH_EXPORT
kth_double_list_t kth_core_double_list_construct(void);

KTH_EXPORT
void kth_core_double_list_push_back(kth_double_list_t double_list, double value);

KTH_EXPORT
void kth_core_double_list_destruct(kth_double_list_t double_list);

KTH_EXPORT
double kth_core_double_list_nth(kth_double_list_t double_list, kth_size_t index);

KTH_EXPORT
kth_size_t kth_core_double_list_count(kth_double_list_t double_list);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* KTH_CAPI_WALLET_WORD_LIST_H_ */