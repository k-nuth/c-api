// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/capi/config/endpoint.h>

#include <kth/infrastructure/config/endpoint.hpp>

#include <kth/capi/helpers.hpp>

kth::infrastructure::config::endpoint endpoint_to_cpp(kth_endpoint const& x) {
    return {x.host, x.port};
}

// ---------------------------------------------------------------------------
extern "C" {

kth_endpoint* kth_config_endpoint_allocate_n(kth_size_t n) {
    return kth::mnew<kth_endpoint>(n);
}

} // extern "C"
