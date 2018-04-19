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

#include <bitprim/nodecint/chain/inputv2_list.h>

#include <bitprim/nodecint/convertions.hpp>
#include <bitprim/nodecint/chain/inputv2.h>
#include <bitcoin/bitcoin/chainv2/input.hpp>


std::vector<libbitcoin::chainv2::input> const& chain_inputv2_list_const_cpp(inputv2_list_t list) {
    return *static_cast<libbitcoin::chainv2::input::list const*>(list);
}

std::vector<libbitcoin::chainv2::input>& chain_inputv2_list_cpp(inputv2_list_t list) {
    return *static_cast<libbitcoin::chainv2::input::list*>(list);
}

inputv2_list_t chain_inputv2_list_construct_from_cpp(libbitcoin::chainv2::input::list& list) {
    return &list;
}

// ----------------------------------------------------------------------------------------
extern "C" {

inputv2_list_t chain_inputv2_list_construct_default() {
    return new libbitcoin::chainv2::input::list();
}

void chain_inputv2_list_push_back(inputv2_list_t list, inputv2_t input) {
    chain_inputv2_list_cpp(list).push_back(chain_inputv2_const_cpp(input));
}

void chain_inputv2_list_destruct(inputv2_list_t list) {
    delete &chain_inputv2_list_cpp(list);
}

uint64_t /*size_t*/ chain_inputv2_list_count(inputv2_list_t list) {
    return chain_inputv2_list_const_cpp(list).size();
}

inputv2_t chain_inputv2_list_nth(inputv2_list_t list, uint64_t /*size_t*/ n) {
    auto& x = chain_inputv2_list_cpp(list)[n];
    return &x;
}

} /* extern "C" */
// ----------------------------------------------------------------------------------------
