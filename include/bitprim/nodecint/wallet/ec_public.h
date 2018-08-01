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

#ifndef BITPRIM_NODECINT_WALLET_EC_PUBLIC_H_
#define BITPRIM_NODECINT_WALLET_EC_PUBLIC_H_

#include <stdint.h>

#include <bitprim/nodecint/primitives.h>
#include <bitprim/nodecint/visibility.h>

#ifdef __cplusplus
extern "C" {
#endif

BITPRIM_EXPORT
ec_public_t wallet_ec_public_construct_default(void);

BITPRIM_EXPORT
uint16_t wallet_ec_public_version(ec_public_t obj);

BITPRIM_EXPORT
uint8_t wallet_ec_public_payment_version(ec_public_t obj);

BITPRIM_EXPORT
uint8_t wallet_ec_public_wif_version(ec_public_t obj);

BITPRIM_EXPORT
bool_t wallet_ec_public_compressed(ec_public_t obj);

// const ec_compressed& point() const;
// const uint16_t version() const;
// const uint8_t payment_version() const;
// const uint8_t wif_version() const;
// const bool compressed() const;

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* BITPRIM_NODECINT_WALLET_EC_PUBLIC_H_ */
