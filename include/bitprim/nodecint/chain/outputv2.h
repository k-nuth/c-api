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

#ifndef BITPRIM_NODECINT_CHAIN_OUTPUTV2_H_
#define BITPRIM_NODECINT_CHAIN_OUTPUTV2_H_

#include <stdio.h>
#include <stdint.h>

#include <bitprim/nodecint/visibility.h>
#include <bitprim/nodecint/primitives.h>

#ifdef __cplusplus
extern "C" {
#endif

BITPRIM_EXPORT
outputv2_t chain_outputv2_construct_default(void);

//output(uint64_t value, chain::script&& script);
//output(uint64_t value, const chain::script& script);
BITPRIM_EXPORT
outputv2_t chain_outputv2_construct(uint64_t value, script_t script);

BITPRIM_EXPORT
void chain_outputv2_destruct(outputv2_t output);

BITPRIM_EXPORT
int chain_outputv2_is_valid(outputv2_t output);

BITPRIM_EXPORT
uint64_t /*size_t*/ chain_outputv2_serialized_size(outputv2_t output, int /*bool*/ wire /*= true*/);

BITPRIM_EXPORT
uint64_t chain_outputv2_value(outputv2_t output);

BITPRIM_EXPORT
uint64_t /*size_t*/ chain_outputv2_signature_operations(outputv2_t output);

BITPRIM_EXPORT
script_t chain_outputv2_script(outputv2_t output);

BITPRIM_EXPORT
payment_address_t chain_outputv2_payment_address(outputv2_t output, int /*bool*/ use_testnet_rules);

BITPRIM_EXPORT
uint8_t const* chain_outputv2_to_data(outputv2_t output, int /*bool*/ wire, uint64_t* /*size_t*/ out_size);

//BITPRIM_EXPORT
//uint32_t chain_outputv2_get_index(outputv2_t output);


#ifdef __cplusplus
} // extern "C"
#endif

#endif /* BITPRIM_NODECINT_CHAIN_OUTPUTV2_H_ */
