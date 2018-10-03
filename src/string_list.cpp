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

#include <bitprim/nodecint/string_list.h>

#include <string>
#include <vector>

#include <bitprim/nodecint/list_creator.h>

BITPRIM_LIST_DEFINE_CONVERTERS(core, string_list_t, std::string, string_list)

// ---------------------------------------------------------------------------
extern "C" {

string_list_t core_string_list_construct() {
    return new std::vector<std::string>();
}

void core_string_list_destruct(string_list_t string_list) {
    delete &core_string_list_cpp(string_list);
}

void core_string_list_push_back(string_list_t string_list, char const* string) {
    core_string_list_cpp(string_list).emplace_back(std::string(string));
}

} // extern "C"