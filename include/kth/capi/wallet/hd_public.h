// Copyright (c) 2016-2023 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_CAPI_WALLET_HD_PUBLIC_H_
#define KTH_CAPI_WALLET_HD_PUBLIC_H_

#include <stdint.h>

#include <kth/capi/primitives.h>
#include <kth/capi/visibility.h>

#include <kth/capi/wallet/primitives.h>
#include <kth/capi/wallet/hd_lineage.h>

#ifdef __cplusplus
extern "C" {
#endif

KTH_EXPORT
kth_hd_public_t kth_wallet_hd_public_construct_default(void);

KTH_EXPORT
kth_hd_public_t kth_wallet_hd_public_construct_key(kth_hd_key_t const* public_key);

KTH_EXPORT
kth_hd_public_t kth_wallet_hd_public_construct_key_prefix(kth_hd_key_t const* public_key, uint32_t prefix);

KTH_EXPORT
kth_hd_public_t kth_wallet_hd_public_construct_string(char const* encoded);

KTH_EXPORT
kth_hd_public_t kth_wallet_hd_public_construct_string_prefix(char const* encoded, uint32_t prefix);

KTH_EXPORT
void kth_wallet_hd_public_destruct(kth_hd_public_t hd_public);

KTH_EXPORT
kth_bool_t kth_wallet_hd_public_is_valid(kth_hd_public_t hd_public);

KTH_EXPORT
char* kth_wallet_hd_public_encoded(kth_hd_public_t hd_public);

KTH_EXPORT
kth_hd_chain_code_t kth_wallet_hd_public_chain_code(kth_hd_public_t hd_public);

KTH_EXPORT
kth_hd_lineage_t kth_wallet_hd_public_lineage(kth_hd_public_t hd_public);

KTH_EXPORT
kth_ec_compressed_t kth_wallet_hd_public_point(kth_hd_public_t hd_public);

KTH_EXPORT
kth_hd_key_t kth_wallet_hd_public_to_hd_key(kth_hd_public_t hd_public);

KTH_EXPORT
kth_hd_public_t kth_wallet_hd_public_derive_public(kth_hd_public_t hd_public, uint32_t index);

#ifdef __cplusplus
} // extern "C"
#endif


#endif /* KTH_CAPI_WALLET_HD_PUBLIC_H_ */
