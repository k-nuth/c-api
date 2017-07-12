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

#include <bitprim/nodecint/binary.h>
#include <bitcoin/bitcoin/utility/binary.hpp>
//#include <string>
#include <vector>
#include <iostream>

extern "C" {

binary_t binary_construct(const char* string) {
    return new libbitcoin::binary(string);
}


/*
binary::binary(const binary& other)
  : blocks_(other.blocks_), final_block_excess_(other.final_block_excess_)
{
}

binary::binary(const std::string& bit_string)
  : binary()
{
    std::stringstream(bit_string) >> *this;
}

binary::binary(size_type size, data_slice blocks)
  : binary()
{
    // Copy blocks
    blocks_.resize(blocks.size());

    if (blocks_.empty())
        return;

    std::copy_n(blocks.begin(), blocks.size(), blocks_.begin());

    // Pad with 00 for safety.
    while (blocks_.size() * bits_per_block < size)
        blocks_.push_back(0x00);

    resize(size);
}
*/




//void word_list_destruct(word_list_t word_list) {
//    delete &word_list_cpp(word_list);
//}

//void word_list_add_word(word_list_t word_list, char const* word) {
//    word_list_cpp(word_list).push_back(std::string(word));
//    for (auto const& x : word_list_cpp(word_list)) {
//        std::cout << x << std::endl;
//    }
//}

} /* extern "C" */
