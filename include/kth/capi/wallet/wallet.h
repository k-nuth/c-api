// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_CAPI_WALLET_WALLET_H_
#define KTH_CAPI_WALLET_WALLET_H_

#include <kth/capi/primitives.h>
#include <kth/capi/visibility.h>

#ifdef __cplusplus
extern "C" {
#endif

KTH_EXPORT
kth_longhash_t kth_wallet_mnemonics_to_seed(kth_word_list_t mnemonics);

KTH_EXPORT
kth_ec_secret_t kth_wallet_ec_new(uint8_t* seed, uint64_t n);

KTH_EXPORT
kth_ec_public_t kth_wallet_ec_to_public(kth_ec_secret_t secret, kth_bool_t uncompressed);

KTH_EXPORT
kth_payment_address_t kth_wallet_ec_to_address(kth_ec_public_t point, uint32_t version);

KTH_EXPORT
kth_hd_private_t kth_wallet_hd_new(uint8_t* seed, uint64_t n, uint32_t version /* = 76066276*/);

KTH_EXPORT
kth_ec_secret_t kth_wallet_hd_private_to_ec(kth_hd_private_t key);


#ifdef __cplusplus
} // extern "C"
#endif

#endif /* KTH_CAPI_WALLET_WALLET_H_ */
