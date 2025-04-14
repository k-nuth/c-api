// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_CAPI_WALLET_WALLET_DATA_H_
#define KTH_CAPI_WALLET_WALLET_DATA_H_

#include <kth/capi/primitives.h>
#include <kth/capi/visibility.h>

#include <kth/capi/wallet/primitives.h>

#ifdef __cplusplus
extern "C" {
#endif

KTH_EXPORT
void kth_wallet_wallet_data_destruct(kth_wallet_data_t wallet_data);

KTH_EXPORT
kth_string_list_t kth_wallet_wallet_data_mnemonics(kth_wallet_data_t wallet_data);

KTH_EXPORT
kth_hd_public_t kth_wallet_wallet_data_xpub(kth_wallet_data_t wallet_data);

KTH_EXPORT
kth_encrypted_seed_t kth_wallet_wallet_data_encrypted_seed(kth_wallet_data_t wallet_data);

KTH_EXPORT
void kth_wallet_wallet_data_encrypted_seed_out(kth_wallet_data_t wallet_data, kth_encrypted_seed_t* out_encrypted_seed);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* KTH_CAPI_WALLET_WALLET_DATA_H_ */
