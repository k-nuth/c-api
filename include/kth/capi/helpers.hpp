// Copyright (c) 2016-2023 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_CAPI_HELPERS_HPP_
#define KTH_CAPI_HELPERS_HPP_

#include <array>
#include <cstddef>
#include <memory>
#include <type_traits>
#include <utility>

#include <kth/domain/config/network.hpp>
#include <kth/infrastructure/math/hash.hpp>
#include <kth/infrastructure/error.hpp>
#include <kth/node/full_node.hpp>

namespace kth {
namespace detail {

// template <typename T>
// using remove_cv_t = typename std::remove_cv<T>::type;

// template <typename T, std::size_t N, std::size_t... I>
// constexpr
// std::array<remove_cv_t<T>, N>
// to_array_impl(T (&x)[N], std::index_sequence<I...> /*unused*/) {
//     return { {x[I]...} };
// }

// template <typename R, typename T, std::size_t N, std::size_t... I>
// constexpr
// R to_c_array_impl(std::array<T, N> const& x, std::index_sequence<I...> /*unused*/) {
//     return { {x[I]...} };
// }

} /* namespace detail */

// template <typename T, std::size_t N>
// constexpr
// std::array<remove_cv_t<T>, N> to_array(T (&x)[N]) {
//     return detail::to_array_impl(x, std::make_index_sequence<N>{});
// }

// template <typename R, typename T, std::size_t N>
// constexpr
// R to_c_array(std::array<T, N> const& x) {
//     return detail::to_c_array_impl<R>(x, std::make_index_sequence<N>{});
// }

#if defined(_WIN32)
using kth_string_t = std::wstring;
#else
using kth_string_t = std::string;
#endif


template <typename T>
constexpr
std::array<std::remove_cv_t<T>, 32> to_array(T (&x)[32]) {
    // return detail::to_array_impl(x, std::make_index_sequence<N>{});
    // return std::array<std::remove_cv_t<T>, 32> {{

    return {{
        x[0],  x[1],  x[2],  x[3],  x[4],  x[5],  x[6], x[7],
        x[8],  x[9],  x[10], x[11], x[12], x[13], x[14], x[15],
        x[16], x[17], x[18], x[19], x[20], x[21], x[22], x[23],
        x[24], x[25], x[26], x[27], x[28], x[29], x[30], x[31]}};
}

inline
kth_hash_t to_hash_t(kth::hash_digest const& x) {
    // return to_c_array<kth_hash_t>(x);
    return { {x[0],  x[1],  x[2],  x[3],  x[4],  x[5],  x[6], x[7],
              x[8],  x[9],  x[10], x[11], x[12], x[13], x[14], x[15],
              x[16], x[17], x[18], x[19], x[20], x[21], x[22], x[23],
              x[24], x[25], x[26], x[27], x[28], x[29], x[30], x[31]} };
}

inline
kth_shorthash_t to_shorthash_t(kth::short_hash const& x) {
    // return to_c_array<kth_shorthash_t>(x);
    return { {x[0],  x[1],  x[2],  x[3],  x[4],  x[5],  x[6], x[7],
              x[8],  x[9],  x[10], x[11], x[12], x[13], x[14], x[15],
              x[16], x[17], x[18], x[19]} };
}

inline
kth_longhash_t to_longhash_t(kth::long_hash const& x) {
    // return to_c_array<kth_longhash_t>(x);

    return { {x[0],  x[1],  x[2],  x[3],  x[4],  x[5],  x[6], x[7],
              x[8],  x[9],  x[10], x[11], x[12], x[13], x[14], x[15],
              x[16], x[17], x[18], x[19], x[20], x[21], x[22], x[23],
              x[24], x[25], x[26], x[27], x[28], x[29], x[30], x[31],
              x[32], x[33], x[34], x[35], x[36], x[37], x[38], x[39],
              x[40], x[41], x[42], x[43], x[44], x[45], x[46], x[47],
              x[48], x[49], x[50], x[51], x[52], x[53], x[54], x[55],
              x[56], x[57], x[58], x[59], x[60], x[61], x[62], x[63]} };

}

// inline
// kth_ec_secret_t to_ec_secret_t(kth::hash_digest const& x) {
//     return { {x[0],  x[1],  x[2],  x[3],  x[4],  x[5],  x[6], x[7],
//               x[8],  x[9],  x[10], x[11], x[12], x[13], x[14], x[15],
//               x[16], x[17], x[18], x[19], x[20], x[21], x[22], x[23],
//               x[24], x[25], x[26], x[27], x[28], x[29], x[30], x[31]} };
// }

// constexpr kth_ec_secret_t null_ec_secret = {
//     {0, 0, 0, 0, 0, 0, 0, 0,
//     0, 0, 0, 0, 0, 0, 0, 0,
//     0, 0, 0, 0, 0, 0, 0, 0,
//     0, 0, 0, 0, 0, 0, 0, 0}};

inline
kth::hash_digest hash_to_cpp(uint8_t const* x) {
    kth::hash_digest ret;
    std::copy_n(x, ret.size(), std::begin(ret));
    return ret;
}


inline
kth::short_hash short_hash_to_cpp(uint8_t const* x) {
    kth::short_hash ret;
    std::copy_n(x, ret.size(), std::begin(ret));
    return ret;
}

template <typename T>
inline
T* mnew(std::size_t n = 1) {
    return static_cast<T*>(malloc(sizeof(T) * n));
}

inline
std::size_t c_str_len(char const* str) {
    return std::strlen(str);
}

inline
std::size_t c_str_len(wchar_t const* str) {
    return std::wcslen(str);
}

inline
char* c_str_cpy(char* dest, char const* src) {
    return strcpy(dest, src);
}

inline
wchar_t* c_str_cpy(wchar_t* dest, wchar_t const* src) {
    return wcscpy(dest, src);
}

template <typename CharT>
inline
CharT* allocate_and_copy_c_str(CharT const* str) {
    auto size = c_str_len(str);
    auto* c_str = mnew<CharT>(size + 1);
    c_str_cpy(c_str, str);
    return c_str;
}

template <typename StrT>
inline
auto* create_c_str(StrT const& str) {
    auto* c_str = mnew<typename StrT::value_type>(str.size() + 1);
    std::copy_n(str.c_str(), str.size() + 1, c_str);
    return c_str;
}

template <typename CharT>
inline
std::basic_string<CharT> create_cpp_str(CharT const* str) {
    return std::basic_string<CharT>(str);
}

template <typename N>
inline
uint8_t* create_c_array(kth::data_chunk const& arr, N& out_size) {
    auto* ret = mnew<uint8_t>(arr.size());
    out_size = arr.size();
    std::copy_n(arr.begin(), arr.size(), ret);
    return ret;
}

inline
kth_error_code_t to_c_err(std::error_code const& ec) {
    return static_cast<kth_error_code_t>(ec.value());
}

template <typename HashCpp, typename HashC>
inline
void copy_c_hash(HashCpp const& in, HashC* out) {
    //precondition: size of out->hash is greater or equal than in.size()
    std::copy_n(in.begin(), in.size(), static_cast<uint8_t*>(out->hash));
}

template <typename T>
std::decay_t<T>* move_or_copy_and_leak(T&& x) {
    return new std::decay_t<T>(std::forward<T>(x));
}

inline
int bool_to_int(bool x) {
    // return static_cast<int>(x);
    return x;
}

inline
bool int_to_bool(int x) {
    // return x != 0;
    return x;
}

inline
bool witness(int x = 1) {
#if defined(KTH_CURRENCY_BCH)
    return false;
#else
    return kth::int_to_bool(x);
#endif
}

inline
kth::domain::config::network network_to_cpp(kth_network_t net) {
    switch (net) {
        case kth_network_testnet:
            return kth::domain::config::network::testnet;
        case kth_network_regtest:
            return kth::domain::config::network::regtest;
#if defined(KTH_CURRENCY_BCH)
        case kth_network_testnet4:
            return kth::domain::config::network::testnet4;
        case kth_network_scalenet:
            return kth::domain::config::network::scalenet;
        case kth_network_chipnet:
            return kth::domain::config::network::chipnet;
#endif
        default:
        case kth_network_mainnet:
            return kth::domain::config::network::mainnet;
    }
}

inline
kth_network_t network_to_c(kth::domain::config::network net) {
    switch (net) {
        case kth::domain::config::network::testnet:
            return kth_network_testnet;
        case kth::domain::config::network::regtest:
            return kth_network_regtest;
#if defined(KTH_CURRENCY_BCH)
        case kth::domain::config::network::testnet4:
            return kth_network_testnet4;
        case kth::domain::config::network::scalenet:
            return kth_network_scalenet;
        case kth::domain::config::network::chipnet:
            return kth_network_chipnet;
#endif
        default:
        case kth::domain::config::network::mainnet:
            return kth_network_mainnet;
    }
}

inline
kth::node::start_modules start_modules_to_cpp(kth_start_modules_t mods) {
    switch (mods) {
        case kth_start_modules_all:
            return kth::node::start_modules::all;
        case kth_start_modules_just_chain:
            return kth::node::start_modules::just_chain;
        case kth_start_modules_just_p2p:
            return kth::node::start_modules::just_p2p;
    }

    return kth::node::start_modules::all;
}

template <typename T>
inline
std::remove_const_t<T>* leak_if_success(std::shared_ptr<T> const& ptr, std::error_code ec) {
    if (ec != kth::error::success) return nullptr;
    using RealT = std::remove_const_t<T>;
    auto leaked = new RealT(*ptr);
    return leaked;
}

template <typename T>
inline
T* leak_if_success(T const& ptr, std::error_code ec) {
    if (ec != kth::error::success) return nullptr;
    auto leaked = new T(ptr);
    return leaked;
}


template <typename T>
inline
std::remove_const_t<T>* leak(std::shared_ptr<T> const& ptr) {
    if (! ptr) return nullptr;
    using RealT = std::remove_const_t<T>;
    auto leaked = new RealT(*ptr);
    return leaked;
}

template <typename T>
inline
T* leak(T const& ptr) {
    auto leaked = new T(ptr);
    return leaked;
}



template <typename T>
inline
std::remove_const_t<T>* leak_if(std::shared_ptr<T> const& ptr, bool leak = true) {
    if (! ptr) return nullptr;

    if (leak) {
        using RealT = std::remove_const_t<T>;
        auto leaked = new RealT(*ptr);
        return leaked;
    }
    return *ptr;
}

} // namespace kth

#endif /* KTH_CAPI_HELPERS_HPP_ */
