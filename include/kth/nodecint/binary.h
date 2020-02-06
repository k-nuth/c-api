// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#ifndef KTH_NODECINT_BINARY_H
#define KTH_NODECINT_BINARY_H

#include <stdint.h>

#include <knuth/nodecint/primitives.h>
#include <knuth/nodecint/visibility.h>

#ifdef __cplusplus
extern "C" {
#endif

KTH_EXPORT
binary_t core_binary_construct(void);

KTH_EXPORT
binary_t core_binary_construct_string(char const* string);

KTH_EXPORT
binary_t core_binary_construct_blocks(uint64_t /*size_t*/ bits_size, uint8_t* blocks, uint64_t /*size_t*/ n);

KTH_EXPORT
void core_binary_destruct(binary_t binary);

KTH_EXPORT
uint8_t const* core_binary_blocks(binary_t binary, uint64_t* /*size_t*/ out_n);

KTH_EXPORT
char* core_binary_encoded(binary_t binary);

//KTH_EXPORT
//void word_list_add_word(word_list_t word_list, char const* word);

//KTH_EXPORT
//void word_list_destruct(word_list_t word_list);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // KTH_NODECINT_BINARY_H
