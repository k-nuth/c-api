// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_CAPI_WALLET_PAYMENT_ADDRESS_H_
#define KTH_CAPI_WALLET_PAYMENT_ADDRESS_H_

#include <stdint.h>

#include <kth/capi/primitives.h>
#include <kth/capi/visibility.h>

#include <kth/capi/wallet/primitives.h>

#ifdef __cplusplus
extern "C" {
#endif

KTH_EXPORT
kth_payment_address_t kth_wallet_payment_address_construct_from_string(char const* address);

KTH_EXPORT
kth_payment_address_t kth_wallet_payment_address_construct_from_short_hash(kth_shorthash_t const* hash, uint8_t version);

KTH_EXPORT
kth_payment_address_t kth_wallet_payment_address_construct_from_hash(kth_hash_t const* hash, uint8_t version);

KTH_EXPORT
kth_payment_address_t kth_wallet_payment_address_construct_from_public(kth_ec_public_t point, uint8_t version);

KTH_EXPORT
kth_payment_address_t kth_wallet_payment_address_construct_from_script(kth_script_t script, uint8_t version);

KTH_EXPORT
kth_payment_address_t kth_wallet_payment_address_from_pay_public_key_hash_script(kth_script_t script, uint8_t version);

KTH_EXPORT
void kth_wallet_payment_address_destruct(kth_payment_address_t payment_address);

#if defined(KTH_CURRENCY_BCH)
KTH_EXPORT
void kth_wallet_payment_address_set_cashaddr_prefix(char const* prefix);
#endif //KTH_CURRENCY_BCH

KTH_EXPORT
char* kth_wallet_payment_address_encoded_legacy(kth_payment_address_t payment_address);

#if defined(KTH_CURRENCY_BCH)
KTH_EXPORT
char* kth_wallet_payment_address_encoded_cashaddr(kth_payment_address_t payment_address, kth_bool_t token_aware);
#endif //KTH_CURRENCY_BCH

KTH_EXPORT
kth_shorthash_t kth_wallet_payment_address_hash20(kth_payment_address_t payment_address);

KTH_EXPORT
kth_hash_t kth_wallet_payment_address_hash32(kth_payment_address_t payment_address);

KTH_EXPORT
uint8_t kth_wallet_payment_address_version(kth_payment_address_t payment_address);

KTH_EXPORT
kth_bool_t kth_wallet_payment_address_is_valid(kth_payment_address_t payment_address);

KTH_EXPORT
kth_payment_address_list_const_t kth_wallet_payment_address_extract(kth_script_t script, uint8_t p2kh_version, uint8_t p2sh_version);

KTH_EXPORT
kth_payment_address_list_const_t kth_wallet_payment_address_extract_input(kth_script_t script, uint8_t p2kh_version, uint8_t p2sh_version);

KTH_EXPORT
kth_payment_address_list_const_t kth_wallet_payment_address_extract_output(kth_script_t script, uint8_t p2kh_version, uint8_t p2sh_version);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* KTH_CAPI_WALLET_PAYMENT_ADDRESS_H_ */
