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

#include <bitprim/nodecint/wallet/word_list.h>

// #include <iostream>
#include <string>
#include <vector>

#include <bitprim/nodecint/list_creator.h>

BITPRIM_LIST_DEFINE_CONVERTERS(wallet, word_list_t, std::string, word_list)

// ---------------------------------------------------------------------------
extern "C" {

word_list_t wallet_word_list_construct() {
    return new std::vector<std::string>();
}

void wallet_word_list_destruct(word_list_t word_list) {
    delete &wallet_word_list_cpp(word_list);
}

void wallet_word_list_add_word(word_list_t word_list, char const* word) {
    wallet_word_list_cpp(word_list).emplace_back(std::string(word));
}

} // extern "C"