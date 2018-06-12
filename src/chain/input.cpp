/**
 * Copyright (c) 2017-2018 Bitprim Inc.
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

#include <bitprim/nodecint/convertions.hpp>
#include <bitprim/nodecint/chain/output_point.h>
#include <bitprim/nodecint/chain/script.h>


libbitcoin::chain::input const& chain_input_const_cpp(input_t input) {
    return *static_cast<libbitcoin::chain::input const*>(input);
}

libbitcoin::chain::input& chain_input_cpp(input_t input) {
    return *static_cast<libbitcoin::chain::input*>(input);
}


extern "C" {

//input();
input_t chain_input_construct_default() {
    return new libbitcoin::chain::input();
}

//input(output_point&& previous_output, chain::script&& script, uint32_t sequence);
//input(const output_point& previous_output, const chain::script& script, uint32_t sequence);
input_t chain_input_construct(output_point_t previous_output, script_t script, uint32_t sequence) {
    return new libbitcoin::chain::input(output_point_const_cpp(previous_output), chain_script_const_cpp(script), sequence);
}


void chain_input_destruct(input_t input) {
    delete &chain_input_cpp(input);
}

int /*bool*/ chain_input_is_valid(input_t input) {
    return static_cast<int>(chain_input_const_cpp(input).is_valid());
}

int /*bool*/ chain_input_is_final(input_t input) {
    return static_cast<int>(chain_input_const_cpp(input).is_final());
}

uint64_t /*size_t*/ chain_input_serialized_size(input_t input, int /*bool*/ wire /* = true*/) {
    return chain_input_const_cpp(input).serialized_size(wire != 0);
}

uint32_t chain_input_sequence(input_t input) {
    return chain_input_const_cpp(input).sequence();
}

uint64_t /*size_t*/ chain_input_signature_operations(input_t input, int /*bool*/ bip16_active) {
#ifdef BITPRIM_CURRENCY_BCH
    int /*bool*/ bip141_active = 0;
#else
    int /*bool*/ bip141_active = 1;
#endif
    return chain_input_const_cpp(input).signature_operations(bip16_active != 0, bip141_active!=0);
}

script_t chain_input_script(input_t input) {
    return &(chain_input_cpp(input).script());
}

output_point_t chain_input_previous_output(input_t input) {
    return &(chain_input_cpp(input).previous_output());
}

//// Serialization.
////-----------------------------------------------------------------------------
//
//data_chunk to_data(bool wire=true) const;
//void to_data(std::ostream& stream, bool wire=true) const;
//void to_data(writer& sink, bool wire=true) const;


uint8_t* chain_input_to_data(input_t input, int /*bool*/ wire, uint64_t* /*size_t*/ out_size) {
    auto input_data = chain_input_const_cpp(input).to_data(wire);
    auto* ret = (uint8_t*)malloc((input_data.size()) * sizeof(uint8_t)); // NOLINT
    std::copy_n(input_data.begin(), input_data.size(), ret);
    *out_size = input_data.size();
    return ret;
}


//// Properties (size, accessors, cache).
////-----------------------------------------------------------------------------
//
//const output_point& previous_output() const;
//void set_previous_output(const output_point& value);
//void set_previous_output(output_point&& value);
//
//void set_script(const chain::script& value);
//void set_script(chain::script&& value);
//
//void set_sequence(uint32_t value);
//
///// The payment address extraxcted from this input as a standard script.
//wallet::payment_address address() const;


} /* extern "C" */
