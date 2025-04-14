// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_CAPI_WALLET_WALLET_MANAGER_H_
#define KTH_CAPI_WALLET_WALLET_MANAGER_H_

#include <kth/capi/primitives.h>
#include <kth/capi/visibility.h>

#include <kth/capi/wallet/primitives.h>

#ifdef __cplusplus
extern "C" {
#endif

KTH_EXPORT
kth_error_code_t kth_wallet_create_wallet(
    char const* password,
    char const* normalized_passphrase,
    kth_wallet_data_t* out_wallet_data);

KTH_EXPORT
kth_error_code_t kth_wallet_decrypt_seed(
    char const* password,
    kth_encrypted_seed_t const* encrypted_seed,
    kth_longhash_t** out_decrypted_seed);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* KTH_CAPI_WALLET_WALLET_MANAGER_H_ */
