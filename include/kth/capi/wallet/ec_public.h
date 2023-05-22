// Copyright (c) 2016-2023 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_CAPI_WALLET_EC_PUBLIC_H_
#define KTH_CAPI_WALLET_EC_PUBLIC_H_

#include <stdint.h>

#include <kth/capi/primitives.h>
#include <kth/capi/visibility.h>
#include <kth/capi/wallet/primitives.h>

#ifdef __cplusplus
extern "C" {
#endif

KTH_EXPORT
kth_ec_public_t kth_wallet_ec_public_construct_default(void);

KTH_EXPORT
kth_ec_public_t kth_wallet_ec_public_construct(kth_ec_private_t secret);

KTH_EXPORT
kth_ec_public_t kth_wallet_ec_public_construct_from_decoded(uint8_t const* decoded, kth_size_t size);

KTH_EXPORT
kth_ec_public_t kth_wallet_ec_public_construct_from_base16(char const* base16);

KTH_EXPORT
kth_ec_public_t kth_wallet_ec_public_construct_from_point(kth_ec_compressed_t const* point, kth_bool_t compress);

KTH_EXPORT
void kth_wallet_ec_public_destruct(kth_ec_public_t obj);

KTH_EXPORT
kth_bool_t kth_wallet_ec_public_is_valid(kth_ec_public_t obj);

KTH_EXPORT
char* kth_wallet_ec_public_encoded(kth_ec_public_t obj);

KTH_EXPORT
kth_ec_compressed_t kth_wallet_ec_public_point(kth_ec_public_t obj);

// KTH_EXPORT
// uint16_t kth_wallet_ec_public_version(kth_ec_public_t obj);

// KTH_EXPORT
// uint8_t kth_wallet_ec_public_payment_version(kth_ec_public_t obj);

// KTH_EXPORT
// uint8_t kth_wallet_ec_public_wif_version(kth_ec_public_t obj);

KTH_EXPORT
kth_bool_t kth_wallet_ec_public_compressed(kth_ec_public_t obj);

KTH_EXPORT
uint8_t const* kth_wallet_ec_public_to_data(kth_ec_public_t obj, kth_size_t* out_size);

KTH_EXPORT
kth_bool_t kth_wallet_ec_public_to_uncompressed(kth_ec_public_t obj, kth_ec_uncompressed_t* out_data);

KTH_EXPORT
kth_payment_address_t kth_wallet_ec_public_to_payment_address(kth_ec_public_t obj, uint8_t version);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* KTH_CAPI_WALLET_EC_PUBLIC_H_ */
