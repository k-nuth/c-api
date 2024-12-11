// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/capi/config/authority.h>

// #include <kth/infrastructure/config/authority.hpp>

#include <kth/capi/helpers.hpp>

// ---------------------------------------------------------------------------
extern "C" {

kth_authority* kth_config_authority_allocate_n(kth_size_t n) {
    return kth::mnew<kth_authority>(n);
}

} // extern "C"
