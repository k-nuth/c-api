// Copyright (c) 2016-2023 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/capi/platform.h>

#include <cstdlib>

#include <kth/capi/helpers.hpp>

// ---------------------------------------------------------------------------
extern "C" {

void kth_platform_free(void* ptr) {
    free(ptr);
}

char* kth_platform_allocate_string(kth_size_t n) {
    return kth::mnew<char>(n);
}

void kth_platform_allocate_string_at(char** ptr, kth_size_t n) {
    *ptr = kth::mnew<char>(n);
}

char** kth_platform_allocate_array_of_strings(kth_size_t n) {
    return kth::mnew<char*>(n);
}

void kth_platform_print_string(char* str) {
    printf("%s\n", str);
}

char* kth_platform_allocate_and_copy_string_at(char** ptr, kth_size_t offset, char const* str) {
    auto n = strlen(str);
    ptr[offset] = kth::mnew<char>(n);
    std::copy_n(str, n + 1, ptr[offset]);
    return ptr[offset];
}

} //extern "C"