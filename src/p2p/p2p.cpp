// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#include <kth/capi/p2p/p2p.h>

#include <kth/network/p2p.hpp>
#include <kth/capi/helpers.hpp>

namespace {

inline
kth::network::p2p& p2p_cast(p2p_t p2p) {
    return *static_cast<kth::network::p2p*>(p2p);
}

} /* end of anonymous namespace */

// ---------------------------------------------------------------------------
extern "C" {

uint64_t /*size_t*/ p2p_address_count(p2p_t p2p) {
    return p2p_cast(p2p).address_count();
}

void p2p_stop(p2p_t p2p) {
    p2p_cast(p2p).stop();
}

void p2p_close(p2p_t p2p) {
    p2p_cast(p2p).close();
}

bool_t p2p_stopped(p2p_t p2p) {
    return knuth::bool_to_int(p2p_cast(p2p).stopped());
}

} // extern "C"
