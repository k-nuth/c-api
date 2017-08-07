/**
 * Copyright (c) 2011-2017 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin.
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

#include <bitprim/nodecint/chain/point.h>

#include <bitprim/nodecint/helpers.hpp>
#include <bitcoin/bitcoin/chain/point.hpp>


libbitcoin::chain::point const& chain_point_const_cpp(point_t point) {
    return *static_cast<libbitcoin::chain::point const*>(point);
}

//libbitcoin::chain::point& history_compact_cpp(history_compact_t point) {
//    return *static_cast<libbitcoin::chain::point*>(point);
//}


extern "C" {

hash_t chain_point_get_hash(point_t point) {
    auto const& hash_cpp = chain_point_const_cpp(point).hash();
    return bitprim::to_hash_t(hash_cpp);
}

int /*bool*/ chain_point_is_valid(point_t point) {
    return static_cast<int>(chain_point_const_cpp(point).is_valid());
}

uint32_t chain_point_get_index(point_t point) {
    return chain_point_const_cpp(point).index();
}

uint64_t chain_point_get_checksum(point_t point) {
    return chain_point_const_cpp(point).checksum();
}

} /* extern "C" */

