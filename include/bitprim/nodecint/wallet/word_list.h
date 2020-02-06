// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#ifndef KTH_NODECINT_WALLET_WORD_LIST_H_
#define KTH_NODECINT_WALLET_WORD_LIST_H_

#include <stdint.h>

#include <knuth/nodecint/primitives.h>
#include <knuth/nodecint/visibility.h>

#ifdef __cplusplus
extern "C" {
#endif

KTH_EXPORT
word_list_t wallet_word_list_construct(void);

KTH_EXPORT
void wallet_word_list_add_word(word_list_t word_list, const char* word);

KTH_EXPORT
void wallet_word_list_destruct(word_list_t word_list);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* KTH_NODECINT_WALLET_WORD_LIST_H_ */
