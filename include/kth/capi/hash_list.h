// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_CAPI_HASH_LIST_H_
#define KTH_CAPI_HASH_LIST_H_

#include <stdint.h>

#include <kth/capi/list_creator.h>
#include <kth/capi/primitives.h>
#include <kth/capi/visibility.h>

#ifdef __cplusplus
extern "C" {
#endif

KTH_LIST_DECLARE(core, kth_hash_list_t, kth_hash_t, hash_list)

KTH_EXPORT
void kth_core_hash_list_nth_out(kth_hash_list_t list, kth_size_t n, kth_hash_t* out_hash);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* KTH_CAPI_HASH_LIST_H_ */
