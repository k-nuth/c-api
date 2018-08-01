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

#include <bitprim/nodecint/binary.h>

#include <bitcoin/bitcoin/utility/binary.hpp>

#include <bitprim/nodecint/helpers.hpp>
#include <bitprim/nodecint/type_conversions.h>

BITPRIM_CONV_DEFINE(core, binary_t, libbitcoin::binary, binary)

// ---------------------------------------------------------------------------
extern "C" {

binary_t core_binary_construct() {
    return new libbitcoin::binary();
}

binary_t core_binary_construct_string(char const* string) {
    return new libbitcoin::binary(string);
}

binary_t core_binary_construct_blocks(uint64_t /*size_t*/ bits_size, uint8_t* blocks, uint64_t /*size_t*/ n) {
    libbitcoin::data_slice blocks_cpp(blocks, blocks + n); 
    return new libbitcoin::binary(bits_size, blocks_cpp);
}

void core_binary_destruct(binary_t binary) {
    delete &core_binary_cpp(binary);
}

uint8_t const* core_binary_blocks(binary_t binary, uint64_t* /*size_t*/ out_n) {
    *out_n = core_binary_const_cpp(binary).blocks().size();
    return core_binary_cpp(binary).blocks().data();
}

char* core_binary_encoded(binary_t binary) {
    std::string str = core_binary_const_cpp(binary).encoded();   //TODO(fernando): returns a value or a reference?
    return bitprim::create_c_str(str);
}

} // extern "C"
