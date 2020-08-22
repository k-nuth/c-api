// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/capi/platform.h>
#include <cstdlib>

// ---------------------------------------------------------------------------
extern "C" {

void platform_free(void* ptr) {
    free(ptr);
}

} //extern "C"