// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_CAPI_CONFIG_CHECKPOINT_H_
#define KTH_CAPI_CONFIG_CHECKPOINT_H_

#include <stddef.h>
#include <stdint.h>

#include <kth/capi/primitives.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    kth_hash_t hash;
    size_t height;
} kth_checkpoint;

KTH_EXPORT
kth_checkpoint* kth_config_checkpoint_allocate_n(kth_size_t n);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // KTH_CAPI_CONFIG_CHECKPOINT_H_
