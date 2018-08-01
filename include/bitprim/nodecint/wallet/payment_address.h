/**
 * Copyright (c) 2016-2018 Bitprim Inc.
 *
 * This file is part of Bitprim.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef BITPRIM_NODECINT_WALLET_PAYMENT_ADDRESS_H_
#define BITPRIM_NODECINT_WALLET_PAYMENT_ADDRESS_H_

#include <stdint.h>

#include <bitprim/nodecint/primitives.h>
#include <bitprim/nodecint/visibility.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef BITPRIM_CURRENCY_BCH
BITPRIM_EXPORT
void wallet_payment_address_set_cashaddr_prefix(char const* prefix);
#endif //BITPRIM_CURRENCY_BCH

BITPRIM_EXPORT
char* wallet_payment_address_encoded(payment_address_t payment_address);

#ifdef BITPRIM_CURRENCY_BCH
BITPRIM_EXPORT
char* wallet_payment_address_encoded_cashaddr(payment_address_t payment_address);
#endif //BITPRIM_CURRENCY_BCH

BITPRIM_EXPORT
payment_address_t wallet_payment_address_construct_from_string(char const* address);

BITPRIM_EXPORT
short_hash_t wallet_payment_address_hash(payment_address_t payment_address);

BITPRIM_EXPORT
uint8_t wallet_payment_address_version(payment_address_t payment_address);

BITPRIM_EXPORT
bool_t wallet_payment_address_is_valid(payment_address_t payment_address);

BITPRIM_EXPORT
void wallet_payment_address_destruct(payment_address_t payment_address);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* BITPRIM_NODECINT_WALLET_PAYMENT_ADDRESS_H_ */
