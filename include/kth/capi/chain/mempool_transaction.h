// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_CAPI_CHAIN_MEMPOOL_TRANSACTION_H_
#define KTH_CAPI_CHAIN_MEMPOOL_TRANSACTION_H_

#include <stdint.h>

#include <kth/capi/primitives.h>
#include <kth/capi/visibility.h>

#ifdef __cplusplus
extern "C" {
#endif

KTH_EXPORT
char const* kth_chain_mempool_transaction_address(mempool_kth_transaction_t tx);

KTH_EXPORT
char const* kth_chain_mempool_transaction_hash(mempool_kth_transaction_t tx);

KTH_EXPORT
uint64_t kth_chain_mempool_transaction_index(mempool_kth_transaction_t tx);

KTH_EXPORT
char const* kth_chain_mempool_transaction_satoshis(mempool_kth_transaction_t tx);

KTH_EXPORT
uint64_t kth_chain_mempool_kth_transaction_timestamp(mempool_kth_transaction_t tx);

KTH_EXPORT
char const* kth_chain_mempool_transaction_prev_output_id(mempool_kth_transaction_t tx);

KTH_EXPORT
char const* kth_chain_mempool_transaction_prev_output_index(mempool_kth_transaction_t tx);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* KTH_CAPI_CHAIN_MEMPOOL_TRANSACTION_H_ */
