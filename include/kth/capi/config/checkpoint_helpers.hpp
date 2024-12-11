// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_CAPI_CONFIG_CHECKPOINT_HELPERS_HPP_
#define KTH_CAPI_CONFIG_CHECKPOINT_HELPERS_HPP_

#include <kth/capi/config/checkpoint.h>

#include <vector>

#include <kth/capi/config/helpers.hpp>
#include <kth/capi/helpers.hpp>

#include <kth/infrastructure/config/checkpoint.hpp>

namespace kth::capi::helpers {

using checkpoint = kth::infrastructure::config::checkpoint;

inline
checkpoint checkpoint_to_cpp(kth_checkpoint const& x) {
    return {kth::hash_to_cpp(x.hash.hash), x.height};
}

inline
kth_checkpoint checkpoint_to_c(checkpoint const& x) {
    return {kth::to_hash_t(x.hash()), x.height()};
}

inline
void checkpoint_delete(kth_checkpoint&) {
    //do nothing
}


inline
std::vector<checkpoint> checkpoint_list_to_cpp(kth_checkpoint const* data, size_t n) {
    return kth::capi::helpers::list_to_cpp(data, n, checkpoint_to_cpp);
}

inline
kth_checkpoint* checkpoint_list_to_c(std::vector<checkpoint> const& data, kth_size_t& out_size) {
    return kth::capi::helpers::list_to_c(data, out_size, checkpoint_to_c);
}

inline
void checkpoint_list_delete(kth_checkpoint* list, size_t n) {
    list_c_delete(list, n, checkpoint_delete);
}

}

#endif // KTH_CAPI_CONFIG_CHECKPOINT_HELPERS_HPP_
