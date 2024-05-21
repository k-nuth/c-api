// Copyright (c) 2023 Fernando Pelliccioni.
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt

#pragma once

#include <cassert>
#include <cstddef>
#include <string_view>

namespace ct {

/**
 * @brief A compile-time fixed-length string
 *
 * @tparam N The number of characters in the string (NOT including a null terminator)
 */
template <size_t N>
struct str {
    char _chars[N + 1] = {0};

    str() = default;
    str(str const&) = default;

    constexpr
    str(char const (&arr)[N + 1]) noexcept {
        auto src = arr;
        auto dst = _chars;
        for (auto i = 0u; i < N; ++i) {
            dst[i] = src[i];
        }
    }

    constexpr explicit
    str(std::string_view s) noexcept {
        auto dst = _chars;
        auto const src = s.data();
        assert(s.size() == N);
        for (auto i = 0u; i < N; ++i) {
            dst[i] = src[i];
        }
    }

    constexpr operator std::string_view() const noexcept { return std::string_view(_chars, N); }

    constexpr char*       data() noexcept { return _chars; }
    constexpr char const* data() const noexcept { return _chars; }

    constexpr size_t size() const noexcept { return N; }

    constexpr auto begin() noexcept { return data(); }
    constexpr auto begin() const noexcept { return data(); }
    constexpr auto end() noexcept { return data() + N; }
    constexpr auto end() const noexcept { return data() + N; }

    constexpr bool operator==(str const&) const noexcept = default;

    template <std::convertible_to<std::string_view> S>
    constexpr bool operator==(S&& s) const noexcept {
        return std::string_view(*this) == std::string_view(s);
    }

    template <size_t M>
    constexpr str<M + N> operator+(str<M> const& other) const noexcept {
        str<M + N> ret;
        auto o = ret._chars;
        for (auto i = 0u; i < N; ++i, ++o) {
            *o = this->_chars[i];
        }
        for (auto i = 0u; i < M; ++i, ++o) {
            *o = other._chars[i];
        }
        return ret;
    }

    template <size_t M>
    constexpr str<N + M - 1> operator+(char const (&arr)[M]) const noexcept {
        return *this + str{arr};
    }

    template <size_t M>
    constexpr friend str<N + M - 1> operator+(char const (&arr)[M], str const& self) noexcept {
        return str{arr} + self;
    }

    constexpr char operator[](size_t off) const noexcept { return _chars[off]; }
};

// CTAD
template <size_t N>
str(char const (&)[N]) -> str<N - 1>;

} // namespace ct