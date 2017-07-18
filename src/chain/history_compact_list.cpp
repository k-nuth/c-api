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

#include <bitprim/nodecint/chain/history_compact_list.h>
#include <bitcoin/bitcoin/chain/output_point.hpp>
#include <bitcoin/bitcoin/chain/history.hpp>

std::vector<libbitcoin::chain::history_compact> const& history_compact_list_const_cpp(history_compact_list_t history_list) {
    return *static_cast<std::vector<libbitcoin::chain::history_compact> const*>(history_list);
}

std::vector<libbitcoin::chain::history_compact>& history_compact_list_cpp(history_compact_list_t history_list) {
    return *static_cast<std::vector<libbitcoin::chain::history_compact>*>(history_list);
}

void history_compact_list_destruct(history_compact_list_t history_list) {
    delete &history_compact_list_cpp(history_list);
}

uint64_t /*size_t*/ history_compact_list_count(history_compact_list_t history_list) {
    return history_compact_list_const_cpp(history_list).size();
}

history_compact_t history_compact_list_nth(history_compact_list_t history_list, uint64_t /*size_t*/ n) {
    auto& x = history_compact_list_cpp(history_list)[n];
    return &x;
}