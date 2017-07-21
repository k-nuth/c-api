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

#include <bitprim/nodecint/chain/input_list.h>

#include <bitprim/nodecint/chain/input.h>
#include <bitcoin/bitcoin/chain/input.hpp>


std::vector<libbitcoin::chain::input> const& chain_input_list_const_cpp(input_list_t list) {
    return *static_cast<libbitcoin::chain::input::list const*>(list);
}

std::vector<libbitcoin::chain::input>& chain_input_list_cpp(input_list_t list) {
    return *static_cast<libbitcoin::chain::input::list*>(list);
}

input_list_t chain_input_list_construct_from_cpp(libbitcoin::chain::input::list& list) {
    return &list;
}

// ----------------------------------------------------------------------------------------
extern "C" {

input_list_t chain_input_list_construct_default() {
    return new libbitcoin::chain::input::list();
}

void chain_input_list_push_back(input_list_t list, input_t input) {
    chain_input_list_cpp(list).push_back(chain_input_const_cpp(input));
}

void input_list_destruct(input_list_t list) {
    delete &chain_input_list_cpp(list);
}

uint64_t /*size_t*/ input_list_count(input_list_t list) {
    return chain_input_list_const_cpp(list).size();
}

input_t input_list_nth(input_list_t list, uint64_t /*size_t*/ n) {
    auto &x = chain_input_list_cpp(list)[n];
    return &x;
}

} /* extern "C" */
// ----------------------------------------------------------------------------------------
