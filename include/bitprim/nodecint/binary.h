/**
 * Copyright (c) 2017 Bitprim developers (see AUTHORS)
 *
 * This file is part of Bitprim.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef BITPRIM_NODECINT_BINARY_H
#define BITPRIM_NODECINT_BINARY_H

#include <stdio.h>
#include <stdint.h>

#include <bitprim/nodecint/visibility.h>
#include <bitprim/nodecint/primitives.h>

#ifdef __cplusplus
extern "C" {
#endif

BITPRIM_EXPORT
binary_t binary_construct(void);

BITPRIM_EXPORT
binary_t binary_construct_string(char const* string);

BITPRIM_EXPORT
binary_t binary_construct_blocks(uint64_t /*size_t*/ bits_size, uint8_t* blocks, uint64_t /*size_t*/ n);

BITPRIM_EXPORT
//uint8_t* binary_blocks(binary_t binary);
uint8_t const* binary_blocks(binary_t binary, uint64_t* /*size_t*/ out_n);

BITPRIM_EXPORT
char* binary_encoded(binary_t binary);

//BITPRIM_EXPORT
//void word_list_add_word(word_list_t word_list, char const* word);

//BITPRIM_EXPORT
//void word_list_destruct(word_list_t word_list);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // BITPRIM_NODECINT_BINARY_H
