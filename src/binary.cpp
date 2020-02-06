// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#include <knuth/nodecint/binary.h>

#ifdef KTH_USE_DOMAIN
#include <bitcoin/infrastructure/utility/binary.hpp>
#else
#include <bitcoin/bitcoin/utility/binary.hpp>
#endif // KTH_USE_DOMAIN

#include <knuth/nodecint/helpers.hpp>
#include <knuth/nodecint/type_conversions.h>

KTH_CONV_DEFINE(core, binary_t, kth::binary, binary)

// ---------------------------------------------------------------------------
extern "C" {

binary_t core_binary_construct() {
    return new kth::binary();
}

binary_t core_binary_construct_string(char const* string) {
    return new kth::binary(string);
}

binary_t core_binary_construct_blocks(uint64_t /*size_t*/ bits_size, uint8_t* blocks, uint64_t /*size_t*/ n) {
    kth::data_slice blocks_cpp(blocks, blocks + n); 
    return new kth::binary(bits_size, blocks_cpp);
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
    return knuth::create_c_str(str);
}

} // extern "C"
