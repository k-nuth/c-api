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

#include <bitprim/nodecint/chain/inputv2.h>

#include <bitprim/nodecint/convertions.hpp>
#include <bitprim/nodecint/chain/output_pointv2.h>
#include <bitprim/nodecint/chain/scriptv2.h>


libbitcoin::chainv2::input const& chain_inputv2_const_cpp(inputv2_t input) {
    return *static_cast<libbitcoin::chainv2::input const*>(input);
}

libbitcoin::chainv2::input& chain_inputv2_cpp(inputv2_t input) {
    return *static_cast<libbitcoin::chainv2::input*>(input);
}


extern "C" {

//input();
inputv2_t chain_inputv2_construct_default() {
    return new libbitcoin::chainv2::input();
}

//input(output_point&& previous_output, chainv2::script&& script, uint32_t sequence);
//input(const output_point& previous_output, const chainv2::script& script, uint32_t sequence);
inputv2_t chain_inputv2_construct(output_point_t previous_output, script_t script, uint32_t sequence) {
    return new libbitcoin::chainv2::input(output_point_const_cpp(previous_output), chain_script_const_cpp(script), sequence);
}


void chain_inputv2_destruct(inputv2_t input) {
    delete &chain_inputv2_cpp(input);
}

int /*bool*/ chain_inputv2_is_valid(inputv2_t input) {
    return static_cast<int>(chain_inputv2_const_cpp(input).is_valid());
}

int /*bool*/ chain_inputv2_is_final(inputv2_t input) {
    return static_cast<int>(chain_inputv2_const_cpp(input).is_final());
}

uint64_t /*size_t*/ chain_inputv2_serialized_size(inputv2_t input, int /*bool*/ wire /* = true*/) {
    return chain_inputv2_const_cpp(input).serialized_size(wire != 0);
}

uint32_t chain_inputv2_sequence(inputv2_t input) {
    return chain_inputv2_const_cpp(input).sequence();
}

uint64_t /*size_t*/ chain_inputv2_signature_operations(inputv2_t input, int /*bool*/ bip16_active) {
    return chain_inputv2_const_cpp(input).signature_operations(bip16_active != 0);
}

script_t chain_inputv2_script(inputv2_t input) {
    return &(chain_inputv2_cpp(input).script());
}

output_point_t chain_inputv2_previous_output(inputv2_t input) {
    return &(chain_inputv2_cpp(input).previous_output());
}

//// Serialization.
////-----------------------------------------------------------------------------
//
//data_chunk to_data(bool wire=true) const;
//void to_data(std::ostream& stream, bool wire=true) const;
//void to_data(writer& sink, bool wire=true) const;


uint8_t const* chain_inputv2_to_data(inputv2_t input, int /*bool*/ wire, uint64_t* /*size_t*/ out_size) {
    auto input_data = chain_inputv2_const_cpp(input).to_data(wire);
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
//void set_script(const chainv2::script& value);
//void set_script(chainv2::script&& value);
//
//void set_sequence(uint32_t value);
//
///// The payment address extraxcted from this input as a standard script.
//wallet::payment_address address() const;


} /* extern "C" */
