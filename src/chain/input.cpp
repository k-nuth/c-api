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

#include <bitprim/nodecint/chain/input.h>
#include <bitcoin/bitcoin/chain/input.hpp>


libbitcoin::chain::input const& input_const_cpp(input_t input) {
    return *static_cast<libbitcoin::chain::input const*>(input);
}

libbitcoin::chain::input& input_cpp(input_t input) {
    return *static_cast<libbitcoin::chain::input*>(input);
}


extern "C" {

void input_destruct(input_t input) {
    delete &input_cpp(input);
}

int /*bool*/ input_is_valid(input_t input) {
    return input_const_cpp(input).is_valid();
}

int /*bool*/ input_is_final(input_t input) {
    return input_const_cpp(input).is_final();
}

size_t input_serialized_size(input_t input, int wire /* = true*/) {
    return input_const_cpp(input).serialized_size(wire);
}

uint32_t input_sequence(input_t input) {
    return input_const_cpp(input).sequence();
}

size_t input_signature_operations(input_t input, int /*bool*/ bip16_active) {
    return input_const_cpp(input).signature_operations(bip16_active);
}

script_t input_script(input_t input) {
    return &(input_cpp(input).script());
}

output_point_t input_previous_output(input_t input) {
    return &(input_cpp(input).previous_output());
}

//// Serialization.
////-----------------------------------------------------------------------------
//
//data_chunk to_data(bool wire=true) const;
//void to_data(std::ostream& stream, bool wire=true) const;
//void to_data(writer& sink, bool wire=true) const;
//
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
