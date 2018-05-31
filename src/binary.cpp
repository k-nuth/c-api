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

#include <bitprim/nodecint/binary.h>
#include <bitcoin/bitcoin/utility/binary.hpp>

libbitcoin::binary const& binary_const_cpp(binary_t binary) {
    return *static_cast<libbitcoin::binary const*>(binary);
}

libbitcoin::binary& binary_cpp(binary_t binary) {
    return *static_cast<libbitcoin::binary*>(binary);
}

extern "C" {

binary_t binary_construct() {
    return new libbitcoin::binary();
}

binary_t binary_construct_string(char const* string) {
    return new libbitcoin::binary(string);
}

binary_t binary_construct_blocks(uint64_t /*size_t*/ bits_size, uint8_t* blocks, uint64_t /*size_t*/ n) {
    libbitcoin::data_slice blocks_cpp(blocks, blocks + n); // NOLINT
    return new libbitcoin::binary(bits_size, blocks_cpp);
}

//uint8_t* binary_blocks(binary_t binary) {
//    auto* ret = (uint8_t*)malloc(binary_const_cpp(binary).blocks().size() * sizeof(uint8_t));
//    std::copy_n(std::begin(binary_const_cpp(binary).blocks()), binary_const_cpp(binary).blocks().size(), ret);
//    return ret;
//}

void binary_destruct(binary_t binary) {
    // delete binary;
    delete &binary_cpp(binary);
}

uint8_t const* binary_blocks(binary_t binary, uint64_t* /*size_t*/ out_n) {
    *out_n = binary_const_cpp(binary).blocks().size();
    return binary_cpp(binary).blocks().data();
}

char* binary_encoded(binary_t binary) {
    std::string str = binary_const_cpp(binary).encoded();
    auto* ret = (char*)malloc((str.size() + 1) * sizeof(char)); // NOLINT

//    std::strcpy(ret, str.c_str());
    std::copy_n(str.begin(), str.size() + 1, ret);

    return ret;
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
