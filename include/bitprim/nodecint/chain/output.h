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

#ifndef BITPRIM_NODECINT_CHAIN_OUTPUT_H_
#define BITPRIM_NODECINT_CHAIN_OUTPUT_H_

#include <stdio.h>
#include <stdint.h>

#include <bitprim/nodecint/visibility.h>
#include <bitprim/nodecint/primitives.h>

#ifdef __cplusplus
extern "C" {
#endif

BITPRIM_EXPORT
output_t chain_output_construct_default(void);

//output(uint64_t value, chain::script&& script);
//output(uint64_t value, const chain::script& script);
BITPRIM_EXPORT
output_t chain_output_construct(uint64_t value, script_t script);

BITPRIM_EXPORT
void chain_output_destruct(output_t output);

BITPRIM_EXPORT
int chain_output_is_valid(output_t output);

BITPRIM_EXPORT
uint64_t /*size_t*/ chain_output_serialized_size(output_t output, int /*bool*/ wire /*= true*/);

BITPRIM_EXPORT
uint64_t chain_output_value(output_t output);

BITPRIM_EXPORT
uint64_t /*size_t*/ chain_output_signature_operations(output_t output);

BITPRIM_EXPORT
script_t chain_output_script(output_t output);

BITPRIM_EXPORT
hash_t chain_output_get_hash(output_t output);

BITPRIM_EXPORT
uint32_t chain_output_get_index(output_t output);


#ifdef __cplusplus
} // extern "C"
#endif

#endif /* BITPRIM_NODECINT_CHAIN_OUTPUT_H_ */
