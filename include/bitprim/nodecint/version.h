/**
 * Copyright (c) 2016-2018 Bitprim Inc.
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

#ifndef BITPRIM_NODECINT_VERSION_H_
#define BITPRIM_NODECINT_VERSION_H_

#ifdef BITPRIM_PROJECT_VERSION
#define BITPRIM_NODECINT_VERSION BITPRIM_PROJECT_VERSION
#else
#define BITPRIM_NODECINT_VERSION "0.0.0"
#endif

#endif //BITPRIM_NODECINT_VERSION_H_


// //! @internal
// //! Transforms a (version, revision, patchlevel) triple into a number of the
// //! form 0xVVRRPPPP to allow comparing versions in a normalized way.
// //!
// //! See http://sourceforge.net/p/predef/wiki/VersionNormalization.
// #define BITPRIM_NODECINT_CONFIG_VERSION(version, revision, patch) \
//     (((version) << 24) + ((revision) << 16) + (patch))

// //! @ingroup group-config
// //! Macro expanding to the major version of the library, i.e. the `x` in `x.y.z`.
// #define BITPRIM_NODECINT_MAJOR_VERSION 0

// //! @ingroup group-config
// //! Macro expanding to the minor version of the library, i.e. the `y` in `x.y.z`.
// #define BITPRIM_NODECINT_MINOR_VERSION 11

// //! @ingroup group-config
// //! Macro expanding to the patch level of the library, i.e. the `z` in `x.y.z`.
// #define BITPRIM_NODECINT_PATCH_VERSION 0

// //! @ingroup group-config
// //! Macro expanding to the full version of the library, in hexadecimal
// //! representation.
// //!
// //! Specifically, `BITPRIM_NODECINT_VERSION` expands to an hexadecimal number of the
// //! form 0xVVRRPPPP, where `VV` is the major version of the library, `RR` is
// //! the minor version and `PPPP` is the patch level. This allows the version
// //! of the library to be compared:
// //! @snippet example/version.cpp main
// //!
// //!
// //! @note
// //! The major, minor and patch versions of the library are also available
// //! individually with the `BITPRIM_NODECINT_{MAJOR,MINOR,PATCH}_VERSION` macros.

// #define BITPRIM_NODECINT_VERSION_NUMBER                                          \
//     BITPRIM_NODECINT_CONFIG_VERSION(BITPRIM_NODECINT_MAJOR_VERSION,              \
//                               BITPRIM_NODECINT_MINOR_VERSION,                    \
//                               BITPRIM_NODECINT_PATCH_VERSION)                    \

// #define STR_HELPER(x) #x
// #define STR(x) STR_HELPER(x)
// #define BITPRIM_NODECINT_VERSION_STR STR(BITPRIM_NODECINT_MAJOR_VERSION) "." STR(BITPRIM_NODECINT_MINOR_VERSION) "." STR(BITPRIM_NODECINT_PATCH_VERSION)
// #undef STR
// #undef STR_HELPER

// #ifdef BITPRIM_BUILD_NUMBER
// #define BITPRIM_NODECINT_VERSION BITPRIM_BUILD_NUMBER
// #else
// #define BITPRIM_NODECINT_VERSION "v0.0.0"
// #endif