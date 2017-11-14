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

template <typename T>
using remove_cv_t = typename std::remove_cv<T>::type;

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

template <typename T>
constexpr
std::array<detail::remove_cv_t<T>, 32> to_array(T (&x)[32]) {
    // return detail::to_array_impl(x, std::make_index_sequence<N>{});
    // return std::array<detail::remove_cv_t<T>, 32> {{
        
    return {{
        x[0],  x[1],  x[2],  x[3],  x[4],  x[5],  x[6], x[7],
        x[8],  x[9],  x[10], x[11], x[12], x[13], x[14], x[15],
        x[16], x[17], x[18], x[19], x[20], x[21], x[22], x[23],
        x[24], x[25], x[26], x[27], x[28], x[29], x[30], x[31]}};
}

inline
hash_t to_hash_t(libbitcoin::hash_digest const& x) {
    // return to_c_array<hash_t>(x);
    return { {x[0],  x[1],  x[2],  x[3],  x[4],  x[5],  x[6], x[7],
              x[8],  x[9],  x[10], x[11], x[12], x[13], x[14], x[15],
              x[16], x[17], x[18], x[19], x[20], x[21], x[22], x[23],
              x[24], x[25], x[26], x[27], x[28], x[29], x[30], x[31]} };
}

inline
short_hash_t to_short_hash_t(libbitcoin::short_hash const& x) {
    // return to_c_array<short_hash_t>(x);
    return { {x[0],  x[1],  x[2],  x[3],  x[4],  x[5],  x[6], x[7],
              x[8],  x[9],  x[10], x[11], x[12], x[13], x[14], x[15]} };
}

inline
long_hash_t to_long_hash_t(libbitcoin::long_hash const& x) {
    // return to_c_array<long_hash_t>(x);

    return { {x[0],  x[1],  x[2],  x[3],  x[4],  x[5],  x[6], x[7],
              x[8],  x[9],  x[10], x[11], x[12], x[13], x[14], x[15],
              x[16], x[17], x[18], x[19], x[20], x[21], x[22], x[23],
              x[24], x[25], x[26], x[27], x[28], x[29], x[30], x[31],
              x[32], x[33], x[34], x[35], x[36], x[37], x[38], x[39],
              x[40], x[41], x[42], x[43], x[44], x[45], x[46], x[47],
              x[48], x[49], x[50], x[51], x[52], x[53], x[54], x[55],
              x[56], x[57], x[58], x[59], x[60], x[61], x[62], x[63]} };              

}

inline
libbitcoin::hash_digest hash_to_cpp(uint8_t* x) {
    libbitcoin::hash_digest ret;        // NOLINT
    std::copy_n(x, ret.size(), std::begin(ret));
    return ret;
}

} /* namespace bitprim */

#endif /* BITPRIM_NODECINT_HELPERS_HPP_ */
