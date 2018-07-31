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

#include <bitprim/nodecint/chain/output.h>

#include <bitprim/nodecint/chain/script.h>
#include <bitprim/nodecint/convertions.hpp>
#include <bitprim/nodecint/helpers.hpp>

// libbitcoin::chain::output const& chain_output_const_cpp(output_t output) {
//     return *static_cast<libbitcoin::chain::output const*>(output);
// }

// libbitcoin::chain::output& chain_output_cpp(output_t output) {
//     return *static_cast<libbitcoin::chain::output*>(output);
// }
BITPRIM_CONV_DEFINE(chain, output_t, libbitcoin::chain::output, output)

// ---------------------------------------------------------------------------
extern "C" {

output_t chain_output_construct_default() {
    return new libbitcoin::chain::output();
}

output_t chain_output_construct(uint64_t value, script_t script) {
    return new libbitcoin::chain::output(value, chain_script_const_cpp(script));
}

void chain_output_destruct(output_t output) {
    delete &chain_output_cpp(output);
}

int chain_output_is_valid(output_t output) {
    return bitprim::bool_to_int(chain_output_const_cpp(output).is_valid());
}

uint64_t /*size_t*/ chain_output_serialized_size(output_t output, bool_t wire /* = true */) {
    return chain_output_const_cpp(output).serialized_size(bitprim::int_to_bool(wire));
}

uint64_t chain_output_value(output_t output) {
    return chain_output_const_cpp(output).value();
}

uint64_t /*size_t*/ chain_output_signature_operations(output_t output) {
#ifdef BITPRIM_CURRENCY_BCH
    bool_t bip141_active = 0;
#else
    bool_t bip141_active = 1;
#endif   
    return chain_output_const_cpp(output).signature_operations(bitprim::int_to_bool(bip141_active));
}

script_t chain_output_script(output_t output) {
    return &(chain_output_cpp(output).script());
}

payment_address_t chain_output_payment_address(output_t output, bool_t use_testnet_rules) {
    auto payment_address = chain_output_cpp(output).address(bitprim::int_to_bool(use_testnet_rules));
    return new libbitcoin::wallet::payment_address(payment_address);
}

uint8_t* chain_output_to_data(output_t output, bool_t wire, uint64_t* /*size_t*/ out_size) {
    auto output_data = chain_output_const_cpp(output).to_data(bitprim::int_to_bool(wire));
    return bitprim::create_c_array(output_data, *out_size);
}

} // extern "C"
