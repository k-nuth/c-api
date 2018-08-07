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

#ifndef BITPRIM_NODECINT_CHAIN_STEALTH_COMPACT_H_
#define BITPRIM_NODECINT_CHAIN_STEALTH_COMPACT_H_

#include <stdint.h>

#include <bitprim/nodecint/primitives.h>
#include <bitprim/nodecint/visibility.h>

#ifdef __cplusplus
extern "C" {
#endif

BITPRIM_EXPORT
hash_t chain_stealth_compact_get_ephemeral_public_key_hash(stealth_compact_t stealth);

BITPRIM_EXPORT
void chain_stealth_compact_get_ephemeral_public_key_hash_out(stealth_compact_t stealth, hash_t* out_epk_hash);

BITPRIM_EXPORT
hash_t chain_stealth_compact_get_transaction_hash(stealth_compact_t stealth);

BITPRIM_EXPORT
void chain_stealth_compact_get_transaction_hash_out(stealth_compact_t stealth, hash_t* out_tx_hash);

BITPRIM_EXPORT
short_hash_t chain_stealth_compact_get_public_key_hash(stealth_compact_t stealth);

BITPRIM_EXPORT
void chain_stealth_compact_get_public_key_hash_out(stealth_compact_t stealth, short_hash_t* out_pk_hash);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // BITPRIM_NODECINT_CHAIN_STEALTH_COMPACT_H_
