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

#include <bitprim/nodecint/output_point.h>
#include <bitcoin/bitcoin/chain/output_point.hpp>

libbitcoin::chain::output_point const& output_point_const_cpp(output_point_t outpoint) {
    return *static_cast<libbitcoin::chain::output_point const*>(outpoint);
}

libbitcoin::chain::output_point& output_point_cpp(output_point_t outpoint) {
    return *static_cast<libbitcoin::chain::output_point*>(outpoint);
}

output_point_t output_point_construct(){
    return std::make_unique<libbitcoin::chain::output_point>().release();
}

void output_point_destruct(output_point_t outpoint){
    delete &output_point_cpp(outpoint);
}

hash_t output_point_get_hash(output_point_t outpoint){
    auto const& hash_cpp = output_point_const_cpp(outpoint).hash();
    return hash_cpp.data();
}

uint32_t output_point_get_index(output_point_t outpoint){
    return output_point_const_cpp(outpoint).index();
}