// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/capi/p2p/p2p.h>

#include <kth/network/p2p.hpp>
#include <kth/capi/helpers.hpp>

namespace {

inline
kth::network::p2p& p2p_cast(kth_p2p_t p2p) {
    return *static_cast<kth::network::p2p*>(p2p);
}

} /* end of anonymous namespace */

// ---------------------------------------------------------------------------
extern "C" {

kth_size_t kth_p2p_address_count(kth_p2p_t p2p) {
    return p2p_cast(p2p).address_count();
}

void kth_p2p_stop(kth_p2p_t p2p) {
    p2p_cast(p2p).stop();
}

void kth_p2p_close(kth_p2p_t p2p) {
    p2p_cast(p2p).close();
}

kth_bool_t kth_p2p_stopped(kth_p2p_t p2p) {
    return kth::bool_to_int(p2p_cast(p2p).stopped());
}

} // extern "C"
