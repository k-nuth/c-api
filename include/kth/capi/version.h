// Copyright (c) 2016-2022 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_CAPI_VERSION_H_
#define KTH_CAPI_VERSION_H_

#ifdef KTH_PROJECT_VERSION
#define KTH_CAPI_VERSION KTH_PROJECT_VERSION
#else
#define KTH_CAPI_VERSION "0.0.0"
#endif

#endif //KTH_CAPI_VERSION_H_


// //! @internal
// //! Transforms a (version, revision, patchlevel) triple into a number of the
// //! form 0xVVRRPPPP to allow comparing versions in a normalized way.
// //!
// //! See http://sourceforge.net/p/predef/wiki/VersionNormalization.
// #define KTH_CAPI_CONFIG_VERSION(version, revision, patch) \
//     (((version) << 24) + ((revision) << 16) + (patch))

// //! @ingroup group-config
// //! Macro expanding to the major version of the library, i.e. the `x` in `x.y.z`.
// #define KTH_CAPI_MAJOR_VERSION 0

// //! @ingroup group-config
// //! Macro expanding to the minor version of the library, i.e. the `y` in `x.y.z`.
// #define KTH_CAPI_MINOR_VERSION 11

// //! @ingroup group-config
// //! Macro expanding to the patch level of the library, i.e. the `z` in `x.y.z`.
// #define KTH_CAPI_PATCH_VERSION 0

// //! @ingroup group-config
// //! Macro expanding to the full version of the library, in hexadecimal
// //! representation.
// //!
// //! Specifically, `KTH_CAPI_VERSION` expands to an hexadecimal number of the
// //! form 0xVVRRPPPP, where `VV` is the major version of the library, `RR` is
// //! the minor version and `PPPP` is the patch level. This allows the version
// //! of the library to be compared:
// //! @snippet example/version.cpp main
// //!
// //!
// //! @note
// //! The major, minor and patch versions of the library are also available
// //! individually with the `KTH_CAPI_{MAJOR,MINOR,PATCH}_VERSION` macros.

// #define KTH_CAPI_VERSION_NUMBER                                          \
//     KTH_CAPI_CONFIG_VERSION(KTH_CAPI_MAJOR_VERSION,              \
//                               KTH_CAPI_MINOR_VERSION,                    \
//                               KTH_CAPI_PATCH_VERSION)                    \

// #define STR_HELPER(x) #x
// #define STR(x) STR_HELPER(x)
// #define KTH_CAPI_VERSION_STR STR(KTH_CAPI_MAJOR_VERSION) "." STR(KTH_CAPI_MINOR_VERSION) "." STR(KTH_CAPI_PATCH_VERSION)
// #undef STR
// #undef STR_HELPER

// #ifdef KTH_BUILD_NUMBER
// #define KTH_CAPI_VERSION KTH_BUILD_NUMBER
// #else
// #define KTH_CAPI_VERSION "v0.0.0"
// #endif