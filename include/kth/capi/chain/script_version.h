// Copyright (c) 2016-2025 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_CAPI_CHAIN_SCRIPT_VERSION_H_
#define KTH_CAPI_CHAIN_SCRIPT_VERSION_H_

#include <stdint.h>

#include <kth/capi/primitives.h>
#include <kth/capi/visibility.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
/// Defined by bip141.
    kth_script_version_zero,

/// All reserved script versions (1..16).
    kth_script_version_reserved,

    kth_script_version_unversioned
} kth_script_version_t;


#ifdef __cplusplus
} // extern "C"
#endif

#endif // KTH_CAPI_CHAIN_SCRIPT_VERSION_H_
