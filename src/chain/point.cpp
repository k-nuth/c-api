// Copyright (c) 2016-2023 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/capi/chain/point.h>

#include <kth/domain/chain/point.hpp>

#include <kth/capi/helpers.hpp>
#include <kth/capi/type_conversions.h>


KTH_CONV_DEFINE(chain, kth_point_t, kth::domain::chain::point, point)

// ---------------------------------------------------------------------------
extern "C" {

kth_hash_t kth_chain_point_get_hash(kth_point_t point) {
    auto const& hash_cpp = kth_chain_point_const_cpp(point).hash();
    return kth::to_hash_t(hash_cpp);
}

void kth_chain_point_get_hash_out(kth_point_t point, kth_hash_t* out_hash) {
    auto const& hash_cpp = kth_chain_point_const_cpp(point).hash();
    kth::copy_c_hash(hash_cpp, out_hash);
}

kth_bool_t kth_chain_point_is_valid(kth_point_t point) {
    return kth::bool_to_int(kth_chain_point_const_cpp(point).is_valid());
}

uint32_t kth_chain_point_get_index(kth_point_t point) {
    return kth_chain_point_const_cpp(point).index();
}

uint64_t kth_chain_point_get_checksum(kth_point_t point) {
    return kth_chain_point_const_cpp(point).checksum();
}

} // extern "C"

