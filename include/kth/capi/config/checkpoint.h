// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_CAPI_CONFIG_CHECKPOINT_H_
#define KTH_CAPI_CONFIG_CHECKPOINT_H_

#include <stddef.h>
#include <stdint.h>

#include <kth/capi/primitives.h>

typedef struct {
    kth_hash_t hash;
    size_t height;
} kth_checkpoint;

#endif // KTH_CAPI_CONFIG_CHECKPOINT_H_
