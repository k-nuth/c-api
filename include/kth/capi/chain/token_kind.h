// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_CAPI_CHAIN_TOKEN_KIND_H_
#define KTH_CAPI_CHAIN_TOKEN_KIND_H_

#include <stdint.h>

#include <kth/capi/primitives.h>
#include <kth/capi/visibility.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    kth_token_kind_none = 0x00,
    kth_token_kind_fungible = 0x01,
    kth_token_kind_non_fungible = 0x02,
    kth_token_kind_both = 0x03,
} kth_token_kind_t;

#ifdef __cplusplus
} // extern "C"
#endif

#endif // KTH_CAPI_CHAIN_TOKEN_KIND_H_
