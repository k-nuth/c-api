// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#ifndef KTH_NODECINT_HASH_LIST_H_
#define KTH_NODECINT_HASH_LIST_H_

#include <stdint.h>

#include <kth/capi/list_creator.h>
#include <kth/capi/primitives.h>
#include <kth/capi/visibility.h>

#ifdef __cplusplus
extern "C" {
#endif

KTH_LIST_DECLARE(core, hash_list_t, hash_t, hash_list)

KTH_EXPORT
void core_hash_list_nth_out(hash_list_t list, uint64_t /*size_t*/ n, hash_t* out_hash);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* KTH_NODECINT_HASH_LIST_H_ */
