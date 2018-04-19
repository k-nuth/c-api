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

#ifndef BITPRIM_NODECINT_CHAIN_INPUTV2_H_
#define BITPRIM_NODECINT_CHAIN_INPUTV2_H_

#include <stdio.h>
#include <stdint.h>

#include <bitprim/nodecint/visibility.h>
#include <bitprim/nodecint/primitives.h>


#ifdef __cplusplus
extern "C" {
#endif

//input(void);
BITPRIM_EXPORT
inputv2_t chain_inputv2_construct_default(void);

//input(output_point&& previous_output, chain::script&& script, uint32_t sequence);
//input(const output_point& previous_output, const chain::script& script, uint32_t sequence);
BITPRIM_EXPORT
inputv2_t chain_inputv2_construct(output_pointv2_t previous_output, scriptv2_t script, uint32_t sequence);

BITPRIM_EXPORT
void chain_inputv2_destruct(inputv2_t input);

BITPRIM_EXPORT
int chain_inputv2_is_valid(inputv2_t input);

BITPRIM_EXPORT
int /*bool*/ chain_inputv2_is_final(inputv2_t input);

BITPRIM_EXPORT
uint64_t /*size_t*/ chain_inputv2_serialized_size(inputv2_t input, int /*bool*/ wire /* = true*/);

BITPRIM_EXPORT
uint32_t chain_inputv2_sequence(inputv2_t input);

BITPRIM_EXPORT
uint64_t /*size_t*/ chain_inputv2_signature_operations(inputv2_t input, int /*bool*/ bip16_active);

BITPRIM_EXPORT
scriptv2_t chain_inputv2_script(inputv2_t input);

BITPRIM_EXPORT
output_pointv2_t chain_inputv2_previous_output(inputv2_t input);

BITPRIM_EXPORT
uint8_t const* chain_inputv2_to_data(inputv2_t input, int /*bool*/ wire, uint64_t* /*size_t*/ out_size);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* BITPRIM_NODECINT_CHAIN_INPUTV2_H_ */
