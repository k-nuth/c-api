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

#include <bitprim/nodecint/chain/point_list.h>
#include <bitcoin/bitcoin/chain/point.hpp>

std::vector<libbitcoin::chain::point> const& point_list_const_cpp(point_list_t point_list) {
    return *static_cast<std::vector<libbitcoin::chain::point> const*>(point_list);
}

std::vector<libbitcoin::chain::point>& point_list_cpp(point_list_t point_list) {
    return *static_cast<std::vector<libbitcoin::chain::point>*>(point_list);
}

point_t point_list_nth(point_list_t point_list, size_t n){
    auto& point_n = point_list_cpp(point_list)[n];
    return &point_n;
}

size_t point_list_count(point_list_t point_list){
    return point_list_const_cpp(point_list).size();
}

void point_list_destruct(point_list_t point_list){
    delete &point_list_cpp(point_list);
}