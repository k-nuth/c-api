/**
 * Copyright (c) 2016-2018 Bitprim Inc.
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

#ifndef BITPRIM_NODECINT_CHAIN_SCRIPT_H_
#define BITPRIM_NODECINT_CHAIN_SCRIPT_H_

#include <stdint.h>

#include <bitprim/nodecint/primitives.h>
#include <bitprim/nodecint/visibility.h>

#ifdef __cplusplus
extern "C" {
#endif

BITPRIM_EXPORT
script_t chain_script_construct_default(void);

BITPRIM_EXPORT
script_t chain_script_construct(uint8_t* encoded, uint64_t n, bool_t prefix);

BITPRIM_EXPORT
void chain_script_destruct(script_t script);

BITPRIM_EXPORT
bool_t chain_script_is_valid(script_t script);

BITPRIM_EXPORT
bool_t chain_script_is_valid_operations(script_t script);

BITPRIM_EXPORT
uint64_t /*size_t*/ chain_script_satoshi_content_size(script_t script);

BITPRIM_EXPORT
uint64_t /*size_t*/ chain_script_serialized_size(script_t script, bool_t prefix);

//Note: user of the function has to release the resource (memory) manually
BITPRIM_EXPORT
char* chain_script_to_string(script_t script, uint32_t active_forks);

//Note: user of the function has to release the resource (memory) manually
BITPRIM_EXPORT
char* chain_script_type(script_t script);

//Note: user of the function has to release the resource (memory) manually
BITPRIM_EXPORT
uint8_t* chain_script_to_data(script_t script, bool_t prefix, uint64_t* /*size_t*/ out_size);

BITPRIM_EXPORT
uint64_t /*size_t*/ chain_script_sigops(script_t script, bool_t embedded);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* BITPRIM_NODECINT_CHAIN_SCRIPT_H_ */
