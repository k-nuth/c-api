// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_CAPI_CONFIG_HELPERS_HPP_
#define KTH_CAPI_CONFIG_HELPERS_HPP_

#include <filesystem>
#include <type_traits>
#include <vector>

#include <kth/capi/helpers.hpp>
#include <kth/infrastructure/path.hpp>

namespace kth::capi::helpers {

inline
kth_char_t* path_to_c(kth::path const& x) {
    kth_char_t* ret = kth::mnew<kth_char_t>(x.native().size() + 1);
    std::copy_n(x.c_str(), x.native().size() + 1, ret);
    return ret;
}

template <typename Source, typename Transformation>
inline
auto list_to_cpp(Source const* data, size_t n, Transformation transform) {
    using Target = std::invoke_result_t<Transformation, Source const&>;
    // static_assert(std::is_same<decltype(b), double>::value, "");

    std::vector<Target> res;
    res.reserve(n);
    while (n != 0) {
        res.push_back(transform(*data));
        ++data;
        --n;
    }
    return res;
}

template <typename Source, typename Deleter>
inline
auto list_c_delete(Source* data, size_t n, Deleter deleter) {
    for (size_t i = 0; i < n; ++i) {
        auto xxx = data[i];
        deleter(data[i]);
    }
    free(data);
}

template <typename Source, typename UnsignedInt, typename Transformation>
inline
auto* list_to_c(std::vector<Source> const& data, UnsignedInt& out_size, Transformation transform) {
    using Target = std::invoke_result_t<Transformation, Source const&>;

    out_size = data.size();
    // if (out_size == 0) return nullptr;

    auto* ret = kth::mnew<Target>(out_size);
    auto* f = ret;
    for (auto&& x : data) {
        *f = transform(x);
        ++f;
    }
    return ret;
}

}

#endif // KTH_CAPI_CONFIG_HELPERS_HPP_
