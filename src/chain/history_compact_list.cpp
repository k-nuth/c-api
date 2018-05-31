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

#include <bitprim/nodecint/chain/history_compact_list.h>
#include <bitcoin/bitcoin/chain/output_point.hpp>
#include <bitcoin/bitcoin/chain/history.hpp>

std::vector<libbitcoin::chain::history_compact> const& chain_history_compact_list_const_cpp(history_compact_list_t list) {
    return *static_cast<std::vector<libbitcoin::chain::history_compact> const*>(list);
}

std::vector<libbitcoin::chain::history_compact>& chain_history_compact_list_cpp(history_compact_list_t list) {
    return *static_cast<std::vector<libbitcoin::chain::history_compact>*>(list);
}

void chain_history_compact_list_destruct(history_compact_list_t list) {
    delete &chain_history_compact_list_cpp(list);
}

uint64_t /*size_t*/ chain_history_compact_list_count(history_compact_list_t list) {
    return chain_history_compact_list_const_cpp(list).size();
}

history_compact_t chain_history_compact_list_nth(history_compact_list_t list, uint64_t /*size_t*/ n) {
    auto& x = chain_history_compact_list_cpp(list)[n];
    return &x;
}