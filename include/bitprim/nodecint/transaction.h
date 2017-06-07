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

#ifndef BITPRIM_NODE_CINT_TRANSACTION_H_
#define BITPRIM_NODE_CINT_TRANSACTION_H_

#include <stdio.h>
#include <stdint.h>

#include <bitprim/nodecint/visibility.h>
#include <bitprim/nodecint/primitives.h>

#ifdef __cplusplus
extern "C" {
#endif

BITPRIM_EXPORT
void transaction_destruct(transaction_t transaction);

BITPRIM_EXPORT
int transaction_is_valid(transaction_t transaction);

BITPRIM_EXPORT
uint32_t transaction_version(transaction_t transaction);

BITPRIM_EXPORT
void transaction_set_version(transaction_t transaction, uint32_t version);

BITPRIM_EXPORT
hash_t transaction_hash(transaction_t transaction);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* BITPRIM_NODE_CINT_TRANSACTION_H_ */
