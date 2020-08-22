// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_CAPI_WALLET_WORD_LIST_H_
#define KTH_CAPI_WALLET_WORD_LIST_H_

#include <stdint.h>

#include <kth/capi/primitives.h>
#include <kth/capi/visibility.h>

#ifdef __cplusplus
extern "C" {
#endif

KTH_EXPORT
kth_word_list_t kth_wallet_word_list_construct(void);

KTH_EXPORT
void kth_wallet_word_list_add_word(kth_word_list_t word_list, const char* word);

KTH_EXPORT
void kth_wallet_word_list_destruct(kth_word_list_t word_list);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* KTH_CAPI_WALLET_WORD_LIST_H_ */
