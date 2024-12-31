// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_CAPI_WALLET_EC_COMPRESSED_LIST_H_
#define KTH_CAPI_WALLET_EC_COMPRESSED_LIST_H_

#include <stdint.h>

#include <kth/capi/list_creator.h>
#include <kth/capi/primitives.h>
#include <kth/capi/visibility.h>
#include <kth/capi/wallet/primitives.h>

#ifdef __cplusplus
extern "C" {
#endif

// KTH_LIST_DECLARE(wallet, kth_ec_compressed_list_t, kth_ec_compressed_t, ec_compressed_list)

KTH_EXPORT
kth_ec_compressed_list_t kth_wallet_ec_compressed_list_construct_default();

KTH_EXPORT
void kth_wallet_ec_compressed_list_push_back(kth_ec_compressed_list_t l, kth_ec_compressed_t e);

KTH_EXPORT
void kth_wallet_ec_compressed_list_destruct(kth_ec_compressed_list_t l);

KTH_EXPORT
kth_size_t kth_wallet_ec_compressed_list_count(kth_ec_compressed_list_t l);

KTH_EXPORT
kth_ec_compressed_t kth_wallet_ec_compressed_list_nth(kth_ec_compressed_list_t l, kth_size_t n);

KTH_EXPORT
void kth_wallet_ec_compressed_list_nth_out(kth_ec_compressed_list_t l, kth_size_t n, kth_ec_compressed_t* out_elem);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* KTH_CAPI_WALLET_EC_COMPRESSED_LIST_H_ */
