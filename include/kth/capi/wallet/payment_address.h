// Copyright (c) 2016-2023 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_CAPI_WALLET_PAYMENT_ADDRESS_H_
#define KTH_CAPI_WALLET_PAYMENT_ADDRESS_H_

#include <stdint.h>

#include <kth/capi/primitives.h>
#include <kth/capi/visibility.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(KTH_CURRENCY_BCH)
KTH_EXPORT
void kth_wallet_payment_address_set_cashaddr_prefix(char const* prefix);
#endif //KTH_CURRENCY_BCH

KTH_EXPORT
char* kth_wallet_payment_address_encoded(kth_payment_address_t payment_address);

#if defined(KTH_CURRENCY_BCH)
KTH_EXPORT
char* kth_wallet_payment_address_encoded_cashaddr(kth_payment_address_t payment_address);
#endif //KTH_CURRENCY_BCH

KTH_EXPORT
kth_payment_address_t kth_wallet_payment_address_construct_from_string(char const* address);

KTH_EXPORT
kth_shorthash_t kth_wallet_payment_address_hash(kth_payment_address_t payment_address);

KTH_EXPORT
uint8_t kth_wallet_payment_address_version(kth_payment_address_t payment_address);

KTH_EXPORT
kth_bool_t kth_wallet_payment_address_is_valid(kth_payment_address_t payment_address);

KTH_EXPORT
void kth_wallet_payment_address_destruct(kth_payment_address_t payment_address);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* KTH_CAPI_WALLET_PAYMENT_ADDRESS_H_ */
