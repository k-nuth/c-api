// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_CAPI_CHAIN_TOKEN_CAPABILITY_H_
#define KTH_CAPI_CHAIN_TOKEN_CAPABILITY_H_

#include <stdint.h>

#include <kth/capi/primitives.h>
#include <kth/capi/visibility.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    kth_token_capability_none = 0x00, // The token lacks any capability or permission and is either a pure-fungible token or an immutable non-fungible token.
    kth_token_capability_mut = 0x01,  // If the mutable capability is present, it means that the encoded token is a non-fungible token that can be altered.
    kth_token_capability_minting = 0x02, // If the minting capability is present, it indicates that the encoded token is a non-fungible token used for minting.
} kth_token_capability_t;

#ifdef __cplusplus
} // extern "C"
#endif

#endif // KTH_CAPI_CHAIN_TOKEN_CAPABILITY_H_
