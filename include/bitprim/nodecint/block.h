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

#ifndef BITPRIM_NODE_CINT_BLOCK_H_
#define BITPRIM_NODE_CINT_BLOCK_H_

#include <stdio.h>
#include <stdint.h>

#include <bitprim/nodecint/visibility.h>
#include <bitprim/nodecint/primitives.h>

#ifdef __cplusplus
extern "C" {
#endif


BITPRIM_EXPORT
void block_destruct(block_t block);

BITPRIM_EXPORT
int block_is_valid(block_t block);

BITPRIM_EXPORT
header_t block_header(block_t block);

BITPRIM_EXPORT
hash_t block_hash(block_t block);

BITPRIM_EXPORT
size_t block_transaction_count(block_t block);

BITPRIM_EXPORT
transaction_t block_transactions(block_t block, size_t* n);

BITPRIM_EXPORT
transaction_t block_transaction_next(transaction_t transaction);

BITPRIM_EXPORT
transaction_t block_transaction_nth(block_t block, size_t n);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* BITPRIM_NODE_CINT_BLOCK_H_ */
