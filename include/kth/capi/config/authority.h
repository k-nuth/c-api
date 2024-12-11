// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_CAPI_CONFIG_AUTHORITY_H_
#define KTH_CAPI_CONFIG_AUTHORITY_H_

#include <stddef.h>
#include <stdint.h>

#include <kth/capi/primitives.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    char* ip;
    uint16_t port;
} kth_authority;

KTH_EXPORT
kth_authority* kth_config_authority_allocate_n(kth_size_t n);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // KTH_CAPI_CONFIG_AUTHORITY_H_
