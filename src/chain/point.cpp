// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#include <kth/capi/chain/point.h>

#include <kth/domain/chain/point.hpp>

#include <kth/capi/helpers.hpp>
#include <kth/capi/type_conversions.h>


KTH_CONV_DEFINE(chain, point_t, kth::chain::point, point)

// ---------------------------------------------------------------------------
extern "C" {

hash_t chain_point_get_hash(point_t point) {
    auto const& hash_cpp = chain_point_const_cpp(point).hash();
    return kth::to_hash_t(hash_cpp);
}

void chain_point_get_hash_out(point_t point, hash_t* out_hash) {
    auto const& hash_cpp = chain_point_const_cpp(point).hash();
    kth::copy_c_hash(hash_cpp, out_hash);
}

bool_t chain_point_is_valid(point_t point) {
    return kth::bool_to_int(chain_point_const_cpp(point).is_valid());
}

uint32_t chain_point_get_index(point_t point) {
    return chain_point_const_cpp(point).index();
}

uint64_t chain_point_get_checksum(point_t point) {
    return chain_point_const_cpp(point).checksum();
}

} // extern "C"

