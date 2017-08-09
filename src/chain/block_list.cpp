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

#include <bitprim/nodecint/chain/block_list.h>

#include <bitprim/nodecint/chain/block.h>
#include <bitprim/nodecint/convertions.hpp>

//namespace {

std::vector<libbitcoin::message::block> const& chain_block_list_const_cpp(block_list_t list) {
    return *static_cast<std::vector<libbitcoin::message::block> const*>(list);
}

std::vector<libbitcoin::message::block>& chain_block_list_cpp(block_list_t list) {
    return *static_cast<std::vector<libbitcoin::message::block>*>(list);
}

//} /* end of anonymous namespace */


block_list_t chain_block_list_construct_from_cpp(std::vector<libbitcoin::message::block>& list) {
    return &list;
}

extern "C" {

block_list_t chain_block_list_construct_default() {
    return new std::vector<libbitcoin::message::block>();
}

void chain_block_list_push_back(block_list_t list, block_t block) {
    chain_block_list_cpp(list).push_back(chain_block_const_cpp(block));
}

void chain_block_list_destruct(block_list_t list) {
    delete &chain_block_list_cpp(list);
}

uint64_t /*size_t*/ chain_block_list_count(block_list_t list) {
    return chain_block_list_const_cpp(list).size();
}

block_t chain_block_list_nth(block_list_t list, uint64_t /*size_t*/ n) {
    auto &x = chain_block_list_cpp(list)[n];
    return &x;
}

} /* extern "C" */
