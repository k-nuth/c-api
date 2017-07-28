/**
 * Copyright (c) 2017 Bitprim developers (see AUTHORS)
 *
 * This file is part of Bitprim.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef BITPRIM_NODECINT_HELPERS_HPP_
#define BITPRIM_NODECINT_HELPERS_HPP_

#include <array>
#include <cstddef>
#include <utility>

#include <bitcoin/bitcoin/math/hash.hpp>

namespace bitprim {
namespace detail {

template <typename T, std::size_t N, std::size_t... I>
constexpr
std::array<std::remove_cv_t<T>, N>
to_array_impl(T (&x)[N], std::index_sequence<I...> /*unused*/) {
    return { {x[I]...} };
}

template <typename R, typename T, std::size_t N, std::size_t... I>
constexpr
R to_c_array_impl(std::array<T, N> const& x, std::index_sequence<I...> /*unused*/) {
    return { {x[I]...} };
}

} /* namespace detail */

template <typename T, std::size_t N>
constexpr
std::array<std::remove_cv_t<T>, N> to_array(T (&x)[N]) {
    return detail::to_array_impl(x, std::make_index_sequence<N>{});
}

template <typename R, typename T, std::size_t N>
constexpr
R to_c_array(std::array<T, N> const& x) {
    return detail::to_c_array_impl<R>(x, std::make_index_sequence<N>{});
}

inline
hash_t to_hash_t(libbitcoin::hash_digest const& x) {
    return to_c_array<hash_t>(x);
}

inline
short_hash_t to_short_hash_t(libbitcoin::short_hash const& x) {
    return to_c_array<short_hash_t>(x);
}

inline
long_hash_t to_long_hash_t(libbitcoin::long_hash const& x) {
    return to_c_array<long_hash_t>(x);
}


inline
libbitcoin::hash_digest hash_to_cpp(uint8_t* x) {
    libbitcoin::hash_digest ret;        // NOLINT
    std::copy_n(x, ret.size(), std::begin(ret));
    return ret;
}




} /* namespace bitprim */

#endif /* BITPRIM_NODECINT_HELPERS_HPP_ */
