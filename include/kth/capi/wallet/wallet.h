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
long_kth_hash_t kth_wallet_mnemonics_to_seed(word_list_t mnemonics);

KTH_EXPORT
ec_secret_t kth_wallet_ec_new(uint8_t* seed, uint64_t n);

KTH_EXPORT
ec_public_t kth_wallet_ec_to_public(ec_secret_t secret, bool_t uncompressed);

KTH_EXPORT
kth_payment_address_t kth_wallet_ec_to_address(ec_public_t point, uint32_t version);

KTH_EXPORT
hd_private_t kth_wallet_hd_new(uint8_t* seed, uint64_t n, uint32_t version /* = 76066276*/);

KTH_EXPORT
ec_secret_t kth_wallet_hd_private_to_ec(hd_private_t key);


#ifdef __cplusplus
} // extern "C"
#endif

#endif /* KTH_CAPI_WALLET_WALLET_H_ */
