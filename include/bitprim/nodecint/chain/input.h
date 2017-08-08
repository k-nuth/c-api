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

#ifndef BITPRIM_NODECINT_CHAIN_INPUT_H_
#define BITPRIM_NODECINT_CHAIN_INPUT_H_

#include <stdio.h>
#include <stdint.h>

#include <bitprim/nodecint/visibility.h>
#include <bitprim/nodecint/primitives.h>


#ifdef __cplusplus
extern "C" {
#endif

//input(void);
BITPRIM_EXPORT
input_t chain_input_construct_default(void);

//input(output_point&& previous_output, chain::script&& script, uint32_t sequence);
//input(const output_point& previous_output, const chain::script& script, uint32_t sequence);
BITPRIM_EXPORT
input_t chain_input_construct(output_point_t previous_output, script_t script, uint32_t sequence);

BITPRIM_EXPORT
void chain_input_destruct(input_t input);

BITPRIM_EXPORT
int chain_input_is_valid(input_t input);

BITPRIM_EXPORT
int /*bool*/ chain_input_is_final(input_t input);

BITPRIM_EXPORT
uint64_t /*size_t*/ chain_input_serialized_size(input_t input, int /*bool*/ wire /* = true*/);

BITPRIM_EXPORT
uint32_t chain_input_sequence(input_t input);

BITPRIM_EXPORT
uint64_t /*size_t*/ chain_input_signature_operations(input_t input, int /*bool*/ bip16_active);

BITPRIM_EXPORT
script_t chain_input_script(input_t input);

BITPRIM_EXPORT
output_point_t chain_input_previous_output(input_t input);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* BITPRIM_NODECINT_CHAIN_INPUT_H_ */
