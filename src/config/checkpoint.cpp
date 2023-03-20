// Copyright (c) 2016-2023 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/capi/config/checkpoint.h>
#include <kth/capi/helpers.hpp>

// ---------------------------------------------------------------------------
extern "C" {

kth_checkpoint* kth_config_checkpoint_allocate_n(kth_size_t n) {
    return kth::mnew<kth_checkpoint>(n);
}

} // extern "C"
