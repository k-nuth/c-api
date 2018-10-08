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

#include <bitprim/nodecint/chain/utxo.h>

#include <bitprim/nodecint/helpers.hpp>
#include <bitprim/nodecint/type_conversions.h>


BITPRIM_CONV_DEFINE(chain, utxo_t, libbitcoin::chain::utxo, utxo)

// ---------------------------------------------------------------------------
extern "C" {

//User is responsible for releasing return value memory
char* chain_utxo_get_address(utxo_t utxo) {
    std::string address_str = chain_utxo_const_cpp(utxo).address;
    return bitprim::create_c_str(address_str);
}

void chain_utxo_get_tx_hash_out(utxo_t utxo, hash_t* out_hash) {
    auto const& hash_cpp = chain_utxo_const_cpp(utxo).tx_hash;
    bitprim::copy_c_hash(hash_cpp, out_hash);
}

uint32_t chain_utxo_get_index(utxo_t utxo) {
    return chain_utxo_const_cpp(utxo).index;
}

uint64_t chain_utxo_get_amount(utxo_t utxo) {
    return chain_utxo_const_cpp(utxo).amount;
}

script_t chain_utxo_get_script(utxo_t utxo) {
    return &(chain_utxo_cpp(utxo).script);
}

uint64_t chain_utxo_get_block_height(utxo_t utxo) {
    return chain_utxo_const_cpp(utxo).block_height;
}

} // extern "C"
