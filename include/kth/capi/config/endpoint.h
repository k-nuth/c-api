// Copyright (c) 2016-2023 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_CAPI_CONFIG_ENDPOINT_H_
#define KTH_CAPI_CONFIG_ENDPOINT_H_

#include <stddef.h>
#include <stdint.h>

#include <kth/capi/primitives.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    char* scheme;
    char* host;
    uint16_t port;
} kth_endpoint;

KTH_EXPORT
kth_endpoint* kth_config_endpoint_allocate_n(kth_size_t n);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // KTH_CAPI_CONFIG_ENDPOINT_H_
