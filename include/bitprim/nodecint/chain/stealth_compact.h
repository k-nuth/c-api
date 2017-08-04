/*struct BC_API stealth_compact
{
    typedef std::vector<stealth_compact> list;

    hash_digest ephemeral_public_key_hash;
    short_hash public_key_hash;
    hash_digest transaction_hash;
};*/


/**
 * Copyright (c) 2011-2017 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin.
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

#include <stdio.h>
#include <stdint.h>

#include <bitprim/nodecint/visibility.h>
#include <bitprim/nodecint/primitives.h>

#ifdef __cplusplus
extern "C" {
#endif

//BITPRIM_EXPORT
//point_kind_t history_compact_get_point_kind(history_compact_t history);

BITPRIM_EXPORT
hash_t stealth_compact_get_ephemeral_public_key_hash(stealth_compact_t stealth);

BITPRIM_EXPORT
hash_t stealth_compact_get_transaction_hash(stealth_compact_t stealth);

BITPRIM_EXPORT
short_hash_t stealth_compact_get_public_key_hash(stealth_compact_t stealth);

/*
    typedef std::vector<stealth_compact> list;

    hash_digest ephemeral_public_key_hash;
    short_hash public_key_hash;
    hash_digest transaction_hash;
*/

#ifdef __cplusplus
} // extern "C"
#endif

#endif // BITPRIM_NODECINT_CHAIN_STEALTH_COMPACT_H_



