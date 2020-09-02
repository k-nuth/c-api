// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_CAPI_CONFIG_AUTHORITY_H_
#define KTH_CAPI_CONFIG_AUTHORITY_H_

#include <stddef.h>
#include <stdint.h>

typedef struct {
    char* ip;
    uint16_t port;
} kth_authority;

#endif // KTH_CAPI_CONFIG_AUTHORITY_H_
