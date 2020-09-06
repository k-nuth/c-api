// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_CAPI_CONFIG_AUTHORITY_HELPERS_HPP_
#define KTH_CAPI_CONFIG_AUTHORITY_HELPERS_HPP_

#include <kth/capi/config/authority.h>

#include <vector>

#include <kth/capi/config/helpers.hpp>
#include <kth/capi/helpers.hpp>

#include <kth/infrastructure/config/authority.hpp>

namespace kth::capi::helpers {

using authority = kth::infrastructure::config::authority;

inline
authority authority_to_cpp(kth_authority const& x) {
    return {x.ip, x.port};
}

inline
kth_authority authority_to_c(authority const& x) {
    return {kth::create_c_str(x.to_hostname()), x.port()};
}

inline
std::vector<authority> authority_list_to_cpp(kth_authority const* data, size_t n) {
    return kth::capi::helpers::list_to_cpp(data, n, authority_to_cpp);
}

inline
kth_authority* authority_list_to_c(std::vector<authority> const& data, size_t& out_size) {
    return kth::capi::helpers::list_to_c(data, out_size, authority_to_c);
}

}

#endif // KTH_CAPI_CONFIG_AUTHORITY_HELPERS_HPP_
