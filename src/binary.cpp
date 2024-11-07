// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/capi/binary.h>

#include <kth/infrastructure/utility/binary.hpp>

#include <kth/capi/helpers.hpp>
#include <kth/capi/type_conversions.h>

KTH_CONV_DEFINE(core, kth_binary_t, kth::binary, binary)

// ---------------------------------------------------------------------------
extern "C" {

kth_binary_t kth_core_binary_construct() {
    return new kth::binary();
}

kth_binary_t kth_core_binary_construct_string(char const* string) {
    return new kth::binary(string);
}

kth_binary_t kth_core_binary_construct_blocks(kth_size_t bits_size, uint8_t* blocks, kth_size_t n) {
    kth::data_slice blocks_cpp(blocks, blocks + n);
    return new kth::binary(bits_size, blocks_cpp);
}

void kth_core_binary_destruct(kth_binary_t binary) {
    delete &kth_core_binary_cpp(binary);
}

uint8_t const* kth_core_binary_blocks(kth_binary_t binary, kth_size_t* out_n) {
    *out_n = kth_core_binary_const_cpp(binary).blocks().size();
    return kth_core_binary_cpp(binary).blocks().data();
}

char* kth_core_binary_encoded(kth_binary_t binary) {
    std::string str = kth_core_binary_const_cpp(binary).encoded();   //TODO(fernando): returns a value or a reference?
    return kth::create_c_str(str);
}

} // extern "C"
