// Copyright (c) 2016-2023 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_CAPI_HASH_H_
#define KTH_CAPI_HASH_H_

#include <kth/capi/primitives.h>
#include <kth/capi/visibility.h>

#ifdef __cplusplus
extern "C" {
#endif

KTH_EXPORT
kth_hash_t kth_str_to_hash(char const* str);

KTH_EXPORT
char* kth_hash_to_str(kth_hash_t hash);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* KTH_CAPI_HASH_H_ */
