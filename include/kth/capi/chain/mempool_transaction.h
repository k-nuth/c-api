// Copyright (c) 2016-2024 Knuth Project developers.
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
char const* kth_chain_mempool_transaction_address(kth_mempool_transaction_t tx);

KTH_EXPORT
char const* kth_chain_mempool_transaction_hash(kth_mempool_transaction_t tx);

KTH_EXPORT
uint64_t kth_chain_mempool_transaction_index(kth_mempool_transaction_t tx);

KTH_EXPORT
char const* kth_chain_mempool_transaction_satoshis(kth_mempool_transaction_t tx);

KTH_EXPORT
uint64_t kth_chain_mempool_transaction_timestamp(kth_mempool_transaction_t tx);

KTH_EXPORT
char const* kth_chain_mempool_transaction_prev_output_id(kth_mempool_transaction_t tx);

KTH_EXPORT
char const* kth_chain_mempool_transaction_prev_output_index(kth_mempool_transaction_t tx);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* KTH_CAPI_CHAIN_MEMPOOL_TRANSACTION_H_ */
