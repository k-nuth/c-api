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

#include <bitprim/nodecint/chain/outputv2_list.h>

#include <bitprim/nodecint/convertions.hpp>
#include <bitprim/nodecint/chain/outputv2.h>


//namespace {

std::vector<libbitcoin::chainv2::output> const& chain_outputv2_list_const_cpp(outputv2_list_t list) {
    return *static_cast<libbitcoin::chainv2::output::list const*>(list);
}

std::vector<libbitcoin::chainv2::output>& chain_outputv2_list_cpp(outputv2_list_t list) {
    return *static_cast<libbitcoin::chainv2::output::list*>(list);
}

//} /* end of anonymous namespace */


outputv2_list_t chain_outputv2_list_construct_from_cpp(libbitcoin::chainv2::output::list& list) {
    return &list;
}

extern "C" {

outputv2_list_t chain_outputv2_list_construct_default() {
    return new libbitcoin::chainv2::output::list();
}

void chain_outputv2_list_push_back(outputv2_list_t list, output_t output) {
    chain_outputv2_list_cpp(list).push_back(chain_output_const_cpp(output));
}

void chain_outputv2_list_destruct(outputv2_list_t list) {
    delete &chain_outputv2_list_cpp(list);
}

uint64_t /*size_t*/ chain_outputv2_list_count(outputv2_list_t list) {
    return chain_outputv2_list_const_cpp(list).size();
}

output_t chain_outputv2_list_nth(outputv2_list_t list, uint64_t /*size_t*/ n) {
    auto &x = chain_outputv2_list_cpp(list)[n];
    return &x;
}

} /* extern "C" */
