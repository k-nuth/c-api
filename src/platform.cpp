// Copyright (c) 2016-2020 Knuth Project developers.
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

char** kth_platform_allocate_array_of_strings(kth_size_t n) {
    return kth::mnew<char*>(n);
}

} //extern "C"