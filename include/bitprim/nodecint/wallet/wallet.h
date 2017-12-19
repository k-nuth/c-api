/**
 * Copyright (c) 2017 Bitprim developers (see AUTHORS)
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

#ifndef BITPRIM_NODECINT_WALLET_WALLET_H_
#define BITPRIM_NODECINT_WALLET_WALLET_H_

#include <bitprim/nodecint/visibility.h>
#include <bitprim/nodecint/primitives.h>

#ifdef __cplusplus
extern "C" {
#endif

BITPRIM_EXPORT
long_hash_t wallet_mnemonics_to_seed(word_list_t mnemonics);

BITPRIM_EXPORT
ec_secret_t wallet_ec_new(uint8_t* seed, uint64_t n);

BITPRIM_EXPORT
ec_public_t wallet_ec_to_public(ec_secret_t secret, int /*bool*/ uncompressed);

BITPRIM_EXPORT
payment_address_t wallet_ec_to_address(ec_public_t point, uint32_t version);


//BITPRIM_EXPORT
//void long_hash_destroy(long_hash_t ptr);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* BITPRIM_NODECINT_WALLET_WALLET_H_ */
