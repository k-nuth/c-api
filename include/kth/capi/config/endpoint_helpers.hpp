// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_CAPI_CONFIG_ENDPOINT_HELPERS_HPP_
#define KTH_CAPI_CONFIG_ENDPOINT_HELPERS_HPP_

#include <kth/capi/config/endpoint.h>

#include <vector>

#include <kth/capi/config/helpers.hpp>
#include <kth/capi/helpers.hpp>

#include <kth/infrastructure/config/endpoint.hpp>

namespace kth::capi::helpers {

using endpoint = kth::infrastructure::config::endpoint;

inline
endpoint endpoint_to_cpp(kth_endpoint const& x) {
    return {x.host, x.port};
}

inline
kth_endpoint endpoint_to_c(endpoint const& x) {
    return {kth::create_c_str(x.scheme()), kth::create_c_str(x.host()), x.port()};
}

inline
void endpoint_delete(kth_endpoint& x) {
    free(x.scheme);
    free(x.host);
}

inline
std::vector<endpoint> endpoint_list_to_cpp(kth_endpoint const* data, size_t n) {
    return kth::capi::helpers::list_to_cpp(data, n, endpoint_to_cpp);
}

inline
kth_endpoint* endpoint_list_to_c(std::vector<endpoint> const& data, size_t& out_size) {
    return kth::capi::helpers::list_to_c(data, out_size, endpoint_to_c);
}

inline
void endpoint_list_delete(kth_endpoint* list, size_t n) {
    list_c_delete(list, n, endpoint_delete);
}

}

#endif // KTH_CAPI_CONFIG_ENDPOINT_HELPERS_HPP_
