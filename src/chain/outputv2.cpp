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

#include <bitprim/nodecint/chain/outputv2.h>

#include <bitprim/nodecint/convertions.hpp>
#include <bitprim/nodecint/chain/scriptv2.h>

libbitcoin::chainv2::output const& chain_outputv2_const_cpp(outputv2_t output) {
    return *static_cast<libbitcoin::chainv2::output const*>(output);
}

libbitcoin::chainv2::output& chain_outputv2_cpp(outputv2_t output) {
    return *static_cast<libbitcoin::chainv2::output*>(output);
}

extern "C" {


//output();
outputv2_t chain_outputv2_construct_default() {
    return new libbitcoin::chainv2::output();
}

//output(uint64_t value, chainv2::script&& script);
//output(uint64_t value, const chainv2::script& script);
outputv2_t chain_outputv2_construct(uint64_t value, scriptv2_t script) {
    return new libbitcoin::chainv2::output(value, chain_scriptv2_const_cpp(script));
}

void chain_outputv2_destruct(outputv2_t output) {
    delete &chain_outputv2_cpp(output);
}

int chain_outputv2_is_valid(outputv2_t output) {
    return static_cast<int>(chain_outputv2_const_cpp(output).is_valid());
}

uint64_t /*size_t*/ chain_outputv2_serialized_size(outputv2_t output, int /* bool */ wire /* = true */) {
    return chain_outputv2_const_cpp(output).serialized_size(wire != 0);
}

uint64_t chain_outputv2_value(outputv2_t output) {
    return chain_outputv2_const_cpp(output).value();
}

uint64_t /*size_t*/ chain_outputv2_signature_operations(outputv2_t output) {
    return chain_outputv2_const_cpp(output).signature_operations();
}

scriptv2_t chain_outputv2_script(outputv2_t output) {
    return &(chain_outputv2_cpp(output).script());
}

payment_address_t chain_outputv2_payment_address(outputv2_t output, int /*bool*/ use_testnet_rules){
    auto payment_address = chain_outputv2_cpp(output).address(use_testnet_rules != 0);
    return new libbitcoin::wallet::payment_address(payment_address);
}

//const chainv2::script& script() const;

//// Serialization.
////-----------------------------------------------------------------------------
//
//data_chunk to_data(bool wire=true) const;
//void to_data(std::ostream& stream, bool wire=true) const;
//void to_data(writer& sink, bool wire=true) const;


uint8_t const* chain_outputv2_to_data(outputv2_t output, int /*bool*/ wire, uint64_t* /*size_t*/ out_size) {
    auto output_data = chain_outputv2_const_cpp(output).to_data(wire);
    auto* ret = (uint8_t*)malloc((output_data.size()) * sizeof(uint8_t)); // NOLINT
    std::copy_n(output_data.begin(), output_data.size(), ret);
    *out_size = output_data.size();
    return ret;
}


//// Properties (size, accessors, cache).
////-----------------------------------------------------------------------------
//
//
//void set_value(uint64_t value);
//
//const chainv2::script& script() const;
//void set_script(const chainv2::script& value);
//void set_script(chainv2::script&& value);
//
///// The payment address extracted from this output as a standard script.
//wallet::payment_address address() const;



} /* extern "C" */
