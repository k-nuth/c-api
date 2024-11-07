// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_CAPI_WALLET_EC_PRIVATE_H_
#define KTH_CAPI_WALLET_EC_PRIVATE_H_

#include <stdint.h>

#include <kth/capi/primitives.h>
#include <kth/capi/visibility.h>
#include <kth/capi/wallet/primitives.h>

#ifdef __cplusplus
extern "C" {
#endif

KTH_EXPORT
kth_ec_private_t kth_wallet_ec_private_construct_default(void);

KTH_EXPORT
kth_ec_private_t kth_wallet_ec_private_construct_string(char const* wif, uint8_t version);

KTH_EXPORT
kth_ec_private_t kth_wallet_ec_private_construct_compressed(kth_wif_compressed_t const* wif, uint8_t version);

KTH_EXPORT
kth_ec_private_t kth_wallet_ec_private_construct_uncompressed(kth_wif_uncompressed_t const* wif, uint8_t version);

KTH_EXPORT
kth_ec_private_t kth_wallet_ec_private_construct_secret(kth_ec_secret_t const* secret, uint16_t version, kth_bool_t compress);

KTH_EXPORT
void kth_wallet_ec_private_destruct(kth_ec_private_t obj);

KTH_EXPORT
kth_bool_t kth_wallet_ec_private_is_valid(kth_ec_private_t obj);

KTH_EXPORT
char* kth_wallet_ec_private_encoded(kth_ec_private_t obj);

KTH_EXPORT
kth_ec_secret_t kth_wallet_ec_private_secret(kth_ec_private_t obj);

KTH_EXPORT
uint16_t kth_wallet_ec_private_version(kth_ec_private_t obj);

KTH_EXPORT
uint8_t kth_wallet_ec_private_payment_version(kth_ec_private_t obj);

KTH_EXPORT
uint8_t kth_wallet_ec_private_wif_version(kth_ec_private_t obj);

KTH_EXPORT
kth_bool_t kth_wallet_ec_private_compressed(kth_ec_private_t obj);

KTH_EXPORT
kth_ec_public_t kth_wallet_ec_private_to_public(kth_ec_private_t obj);

KTH_EXPORT
kth_payment_address_t kth_wallet_ec_private_to_payment_address(kth_ec_private_t obj);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* KTH_CAPI_WALLET_EC_PRIVATE_H_ */
