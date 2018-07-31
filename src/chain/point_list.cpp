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

#include <bitcoin/bitcoin/chain/point.hpp>

#include <bitprim/nodecint/chain/point_list.h>
#include <bitprim/nodecint/list_creator.h>

// std::vector<libbitcoin::chain::point> const& point_list_const_cpp(point_list_t point_list) {
//     return *static_cast<std::vector<libbitcoin::chain::point> const*>(point_list);
// }

// std::vector<libbitcoin::chain::point>& point_list_cpp(point_list_t point_list) {
//     return *static_cast<std::vector<libbitcoin::chain::point>*>(point_list);
// }

BITPRIM_LIST_DEFINE_CONVERTERS(chain, point_list_t, libbitcoin::chain::point, point_list)

// ---------------------------------------------------------------------------
extern "C" {

point_t point_list_nth(point_list_t point_list, uint64_t /*size_t*/ n) {
    auto& point_n = chain_point_list_cpp(point_list)[n];
    return &point_n;
}

uint64_t /*size_t*/ point_list_count(point_list_t point_list) {
    return chain_point_list_const_cpp(point_list).size();
}

void point_list_destruct(point_list_t point_list) {
    delete &chain_point_list_cpp(point_list);
}

} // extern "C"