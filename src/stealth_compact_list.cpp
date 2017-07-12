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

#include <bitprim/nodecint/stealth_compact_list.h>
//#include <bitcoin/bitcoin/chain/output_point.hpp>
#include <bitcoin/bitcoin/chain/stealth.hpp>

std::vector<libbitcoin::chain::stealth_compact> const& stealth_compact_list_const_cpp(stealth_compact_list_t stealth_list) {
    return *static_cast<std::vector<libbitcoin::chain::stealth_compact> const*>(stealth_list);
}

std::vector<libbitcoin::chain::stealth_compact>& stealth_compact_list_cpp(stealth_compact_list_t stealth_list) {
    return *static_cast<std::vector<libbitcoin::chain::stealth_compact>*>(stealth_list);
}

void stealth_compact_list_destruct(stealth_compact_list_t stealth_list) {
    delete &stealth_compact_list_cpp(stealth_list);
}

size_t stealth_compact_list_count(stealth_compact_list_t stealth_list) {
    return stealth_compact_list_const_cpp(stealth_list).size();
}

stealth_compact_t stealth_compact_list_nth(stealth_compact_list_t stealth_list, size_t n) {
    auto& x = stealth_compact_list_cpp(stealth_list)[n];
    return &x;
}
