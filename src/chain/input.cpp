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

#include <bitprim/nodecint/chain/input.h>

#include <bitprim/nodecint/chain/output_point.h>
#include <bitprim/nodecint/chain/script.h>
#include <bitprim/nodecint/conversions.hpp>
#include <bitprim/nodecint/helpers.hpp>


BITPRIM_CONV_DEFINE(chain, input_t, libbitcoin::chain::input, input)

// ---------------------------------------------------------------------------
extern "C" {

input_t chain_input_construct_default() {
    return new libbitcoin::chain::input();
}

input_t chain_input_construct(output_point_t previous_output, script_t script, uint32_t sequence) {
    return new libbitcoin::chain::input(chain_output_point_const_cpp(previous_output), chain_script_const_cpp(script), sequence);
}

void chain_input_destruct(input_t input) {
    delete &chain_input_cpp(input);
}

bool_t chain_input_is_valid(input_t input) {
    return bitprim::bool_to_int(chain_input_const_cpp(input).is_valid());
}

bool_t chain_input_is_final(input_t input) {
    return bitprim::bool_to_int(chain_input_const_cpp(input).is_final());
}

uint64_t /*size_t*/ chain_input_serialized_size(input_t input, bool_t wire /* = true*/) {
    return chain_input_const_cpp(input).serialized_size(bitprim::int_to_bool(wire));
}

uint32_t chain_input_sequence(input_t input) {
    return chain_input_const_cpp(input).sequence();
}

uint64_t /*size_t*/ chain_input_signature_operations(input_t input, bool_t bip16_active) {
#ifdef BITPRIM_CURRENCY_BCH
    bool_t bip141_active = 0;
#else
    bool_t bip141_active = 1;
#endif
    return chain_input_const_cpp(input).signature_operations(bitprim::int_to_bool(bip16_active), bitprim::int_to_bool(bip141_active));
}

script_t chain_input_script(input_t input) {
    return &(chain_input_cpp(input).script());
}

output_point_t chain_input_previous_output(input_t input) {
    return &(chain_input_cpp(input).previous_output());
}

uint8_t* chain_input_to_data(input_t input, bool_t wire, uint64_t* /*size_t*/ out_size) {
    auto input_data = chain_input_const_cpp(input).to_data(bitprim::int_to_bool(wire));
    return bitprim::create_c_array(input_data, *out_size);
}

} // extern "C"
