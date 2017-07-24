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

#include <bitprim/nodecint/chain/output.h>

#include <bitprim/nodecint/convertions.hpp>
#include <bitprim/nodecint/chain/script.h>

libbitcoin::chain::output const& chain_output_const_cpp(output_t output) {
    return *static_cast<libbitcoin::chain::output const*>(output);
}

libbitcoin::chain::output& chain_output_cpp(output_t output) {
    return *static_cast<libbitcoin::chain::output*>(output);
}

extern "C" {


//output();
output_t chain_output_construct_default() {
    return new libbitcoin::chain::output();
}

//output(uint64_t value, chain::script&& script);
//output(uint64_t value, const chain::script& script);
output_t chain_output_construct(uint64_t value, script_t script) {
    return new libbitcoin::chain::output(value, script_const_cpp(script));
}

void chain_output_destruct(output_t output) {
    delete &chain_output_const_cpp(output);
}

int chain_output_is_valid(output_t output) {
    return chain_output_const_cpp(output).is_valid();
}

uint64_t /*size_t*/ chain_output_serialized_size(output_t output, int /* bool */ wire /* = true */) {
    return chain_output_const_cpp(output).serialized_size(wire);
}

uint64_t chain_output_value(output_t output) {
    return chain_output_const_cpp(output).value();
}

uint64_t /*size_t*/ chain_output_signature_operations(output_t output) {
    return chain_output_const_cpp(output).signature_operations();
}

script_t chain_output_script(output_t output) {
    return &(chain_output_cpp(output).script());
}

//const chain::script& script() const;

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
//
//void set_value(uint64_t value);
//
//const chain::script& script() const;
//void set_script(const chain::script& value);
//void set_script(chain::script&& value);
//
///// The payment address extracted from this output as a standard script.
//wallet::payment_address address() const;



} /* extern "C" */
