// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#ifndef KTH_NODECINT_STRING_LIST_H_
#define KTH_NODECINT_STRING_LIST_H_

#include <stdint.h>

#include <knuth/nodecint/primitives.h>
#include <knuth/nodecint/visibility.h>

#ifdef __cplusplus
extern "C" {
#endif

KTH_EXPORT
string_list_t core_string_list_construct(void);

KTH_EXPORT
void core_string_list_push_back(string_list_t string_list, const char* string);

KTH_EXPORT
void core_string_list_destruct(string_list_t string_list);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* KTH_NODECINT_WALLET_WORD_LIST_H_ */