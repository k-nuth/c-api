// Copyright (c) 2016-2023 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_CAPI_WALLET_HD_PRIVATE_H_
#define KTH_CAPI_WALLET_HD_PRIVATE_H_

#include <stdint.h>

#include <kth/capi/primitives.h>
#include <kth/capi/visibility.h>

#include <kth/capi/wallet/primitives.h>

#ifdef __cplusplus
extern "C" {
#endif

KTH_EXPORT
kth_hd_private_t kth_wallet_hd_private_construct_default(void);

KTH_EXPORT
kth_hd_private_t kth_wallet_hd_private_construct(kth_hd_key_t const* private_key);

KTH_EXPORT
kth_hd_private_t kth_wallet_hd_private_construct_with_prefix(kth_hd_key_t const* private_key, uint32_t prefix);

KTH_EXPORT
kth_hd_private_t kth_wallet_hd_private_construct_with_prefixes(kth_hd_key_t const* private_key, uint64_t prefixes);

KTH_EXPORT
kth_hd_private_t kth_wallet_hd_private_construct_with_seed(uint8_t const* seed, kth_size_t size, uint64_t prefixes);

KTH_EXPORT
kth_hd_private_t kth_wallet_hd_private_construct_string(char const* encoded);

KTH_EXPORT
kth_hd_private_t kth_wallet_hd_private_construct_string_with_prefix(char const* encoded, uint32_t prefix);

KTH_EXPORT
kth_hd_private_t kth_wallet_hd_private_construct_string_with_prefixes(char const* encoded, uint64_t prefixes);

KTH_EXPORT
void kth_wallet_hd_private_destruct(kth_hd_private_t hd_private);

KTH_EXPORT
char* kth_wallet_hd_private_encoded(kth_hd_private_t hd_private);

KTH_EXPORT
kth_ec_secret_t kth_wallet_hd_private_secret(kth_hd_private_t hd_private);

KTH_EXPORT
kth_hd_key_t kth_wallet_hd_private_to_hd_key(kth_hd_private_t hd_private);

KTH_EXPORT
kth_hd_public_t kth_wallet_hd_private_to_public(kth_hd_private_t hd_private);

KTH_EXPORT
kth_hd_private_t kth_wallet_hd_private_derive_private(kth_hd_private_t hd_private, uint32_t index);

KTH_EXPORT
kth_hd_public_t kth_wallet_hd_private_derive_public(kth_hd_private_t hd_private, uint32_t index);

#ifdef __cplusplus
} // extern "C"
#endif


#endif /* KTH_CAPI_WALLET_HD_PRIVATE_H_ */