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

#include <bitprim/nodecint/chain/output_list.h>

#include <bitprim/nodecint/chain/output.h>


//namespace {

std::vector<libbitcoin::chain::output> const& chain_output_list_const_cpp(output_list_t list) {
    return *static_cast<libbitcoin::chain::output::list const*>(list);
}

std::vector<libbitcoin::chain::output>& chain_output_list_cpp(output_list_t list) {
    return *static_cast<libbitcoin::chain::output::list*>(list);
}

//} /* end of anonymous namespace */


output_list_t chain_output_list_construct_from_cpp(libbitcoin::chain::output::list& list) {
    return &list;
}

extern "C" {

output_list_t chain_output_list_construct_default() {
    return new libbitcoin::chain::output::list();
}

void chain_output_list_push_back(output_list_t list, output_t output) {
    chain_output_list_cpp(list).push_back(chain_output_const_cpp(output));
}

void output_list_destruct(output_list_t list) {
    delete &chain_output_list_cpp(list);
}

uint64_t /*size_t*/ output_list_count(output_list_t list) {
    return chain_output_list_const_cpp(list).size();
}

output_t output_list_nth(output_list_t list, uint64_t /*size_t*/ n) {
    auto &x = chain_output_list_cpp(list)[n];
    return &x;
}

} /* extern "C" */