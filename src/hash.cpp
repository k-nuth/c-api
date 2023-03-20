// Copyright (c) 2016-2023 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/capi/hash.h>

#include <algorithm>

#include <kth/infrastructure/hash_define.hpp>
#include <kth/capi/helpers.hpp>

namespace {

inline
int char2int(char input) {
    // precondition:
    if (input >= '0' && input <= '9') {
        return input - '0';
    }
    if (input >= 'A' && input <= 'F') {
        return input - 'A' + 10;
    }
    if (input >= 'a' && input <= 'f') {
        return input - 'a' + 10;
    }
    return 0;
    //throw std::invalid_argument("Invalid input string");
}

inline
void hex2bin(char const* src, uint8_t* target) {
    while ((*src != 0) && (src[1] != 0)) {
        *(target++) = char2int(*src) * 16 + char2int(src[1]);
        src += 2;
    }
}

}

// ---------------------------------------------------------------------------
extern "C" {

kth_hash_t kth_str_to_hash(char const* str) {
	kth::hash_digest hash_bytes;
	hex2bin(str, hash_bytes.data());
	std::reverse(hash_bytes.begin(), hash_bytes.end());
    auto res = kth::to_hash_t(hash_bytes);
    return res;
}

char* kth_hash_to_str(kth_hash_t hash) {
    size_t n = std::size(hash.hash);
    auto* ret = kth::mnew<char>(n * 2 + 1);
    ret[n * 2] = 0;

    --n;
    auto* f = ret;
    while (true) {
        auto b = hash.hash[n];
        sprintf(f, "%02x", b);
        f += 2;
        if (n == 0) break;
        --n;
    }

    return ret;
}

// void print_hex(uint8_t const* data, size_t n) {
//     while (n != 0) {
//         printf("%2x", *data);
//         ++data;
//         --n;
//     }
//     printf("\n");
// }



} // extern "C"
