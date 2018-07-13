/**
 * Copyright (c) 2017-2018 Bitprim Inc.
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

#include <bitprim/nodecint/chain/block_indexes.h>

#include <bitprim/nodecint/convertions.hpp>

std::vector<uint64_t /*size_t*/> const& chain_block_indexes_const_cpp(block_indexes_t list) {
    return *static_cast<std::vector<uint64_t /*size_t*/> const*>(list);
}

std::vector<uint64_t /*size_t*/>& chain_block_indexes_cpp(block_indexes_t list) {
    return *static_cast<std::vector<uint64_t /*size_t*/>*>(list);
}

block_indexes_t chain_block_indexes_construct_from_cpp(std::vector<uint64_t /*size_t*/>& list) {
    return &list;
}

// ---------------------------------------------------------------------------
extern "C" {

block_indexes_t chain_block_indexes_construct_default() {
    return new std::vector<uint64_t /*size_t*/>();
}

void chain_block_indexes_push_back(block_indexes_t list, uint64_t /*size_t*/ index) {
    chain_block_indexes_cpp(list).push_back(index);
}

void block_indexes_destruct(block_indexes_t list) {
    delete &chain_block_indexes_cpp(list);
}

uint64_t /*size_t*/ block_indexes_count(block_indexes_t list) {
    return chain_block_indexes_const_cpp(list).size();
}

uint64_t /*size_t*/ block_indexes_nth(block_indexes_t list, uint64_t /*size_t*/ n) {
    return chain_block_indexes_cpp(list)[n];
}

} // extern "C"