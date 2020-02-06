// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#ifndef KTH_CAPI_WALLET_EC_PUBLIC_H_
#define KTH_CAPI_WALLET_EC_PUBLIC_H_

#include <stdint.h>

#include <kth/capi/primitives.h>
#include <kth/capi/visibility.h>

#ifdef __cplusplus
extern "C" {
#endif

KTH_EXPORT
ec_public_t wallet_ec_public_construct_default(void);

KTH_EXPORT
uint16_t wallet_ec_public_version(ec_public_t obj);

KTH_EXPORT
uint8_t wallet_ec_public_payment_version(ec_public_t obj);

KTH_EXPORT
uint8_t wallet_ec_public_wif_version(ec_public_t obj);

KTH_EXPORT
bool_t wallet_ec_public_compressed(ec_public_t obj);

// const ec_compressed& point() const;
// const uint16_t version() const;
// uint8_t const payment_version() const;
// uint8_t const wif_version() const;
// const bool compressed() const;

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* KTH_CAPI_WALLET_EC_PUBLIC_H_ */
