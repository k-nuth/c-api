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

#include <bitprim/nodecint/chain/hash_list.h>

#include <bitprim/nodecint/convertions.hpp>
#include <bitprim/nodecint/helpers.hpp>

std::vector<libbitcoin::hash_digest> const& chain_hash_list_const_cpp(hash_list_t list) {
    return *static_cast<std::vector<libbitcoin::hash_digest> const*>(list);
}

std::vector<libbitcoin::hash_digest>& chain_hash_list_cpp(hash_list_t list) {
    return *static_cast<std::vector<libbitcoin::hash_digest>*>(list);
}

hash_list_t chain_hash_list_construct_from_cpp(std::vector<libbitcoin::hash_digest>& list) {
    return &list;
}

extern "C" {

hash_list_t chain_hash_list_construct_default() {
    return new std::vector<libbitcoin::hash_digest>();
}

void chain_hash_list_push_back(hash_list_t list, hash_t hash) {
    auto hash_cpp = bitprim::to_array(hash.hash);
    chain_hash_list_cpp(list).push_back(hash_cpp);
}

void hash_list_destruct(hash_list_t list) {
    delete &chain_hash_list_cpp(list);
}

uint64_t /*size_t*/ hash_list_count(hash_list_t list) {
    return chain_hash_list_const_cpp(list).size();
}

hash_t hash_list_nth(hash_list_t list, uint64_t /*size_t*/ n) {
    auto const& x = chain_hash_list_cpp(list)[n];
    return bitprim::to_hash_t(x);
}

} /* extern "C" */
