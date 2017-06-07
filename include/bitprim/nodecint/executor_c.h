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

#ifndef BITPRIM_NODE_CINT_EXECUTOR_H_
#define BITPRIM_NODE_CINT_EXECUTOR_H_

#include <stdio.h>
#include <stdint.h>

#include <bitprim/nodecint/visibility.h>
// #include <bitcoin/bitcoin/message/header.hpp>


#ifdef __cplusplus
extern "C" {
#endif

typedef struct executor* executor_t;
// typedef struct header* header_t;

typedef void* header_t;
typedef void* block_t;
typedef void* transaction_t;
typedef uint8_t* hash_t;

typedef void (*last_height_fetch_handler_t)(int error, size_t h);
typedef void (*block_height_fetch_handler_t)(int error, size_t h);
typedef void (*block_header_fetch_handler_t)(int error, header_t header, size_t h);
// typedef std::function<void(const code&, block_ptr, size_t)> block_fetch_handler;
typedef void (*block_fetch_handler_t)(int error, block_t block, size_t h);

//typedef std::function<void(const code&, transaction_ptr, size_t, size_t)> transaction_fetch_handler;
typedef void (*transaction_fetch_handler_t)(int error, transaction_t transaction, size_t h, size_t i);





BITPRIM_EXPORT
executor_t executor_construct(char const* path, FILE* sin, FILE* sout, FILE* serr);

BITPRIM_EXPORT
executor_t executor_construct_fd(char const* path, int sin_fd, int sout_fd, int serr_fd);

BITPRIM_EXPORT
void executor_destruct(executor_t exec);

BITPRIM_EXPORT
int executor_run(executor_t exec);

BITPRIM_EXPORT
int executor_run_wait(executor_t exec);

BITPRIM_EXPORT
int executor_initchain(executor_t exec);

BITPRIM_EXPORT
void executor_stop(executor_t exec);


// ------------------------------------------------
// ????
// ------------------------------------------------

BITPRIM_EXPORT
void fetch_last_height(executor_t exec, last_height_fetch_handler_t handler);

BITPRIM_EXPORT
void fetch_block_height(executor_t exec, hash_t hash, block_height_fetch_handler_t handler);

BITPRIM_EXPORT
void fetch_block_header(executor_t exec, size_t height, block_header_fetch_handler_t handler);

BITPRIM_EXPORT
void fetch_block_header_by_hash(executor_t exec, hash_t hash, block_header_fetch_handler_t handler);

BITPRIM_EXPORT
void fetch_block(executor_t exec, size_t height, block_fetch_handler_t handler);

BITPRIM_EXPORT
void fetch_block_by_hash(executor_t exec, hash_t hash, block_fetch_handler_t handler);

BITPRIM_EXPORT
void fetch_transaction(executor_t exec, hash_t hash, int require_confirmed, transaction_fetch_handler_t handler);


// ------------------------------------------------
// Header
// ------------------------------------------------

BITPRIM_EXPORT
void header_destruct(header_t header);

BITPRIM_EXPORT
int header_is_valid(header_t header);

BITPRIM_EXPORT
uint32_t header_version(header_t header);

BITPRIM_EXPORT
void header_set_version(header_t header, uint32_t version);


BITPRIM_EXPORT
uint32_t header_timestamp(header_t header);

BITPRIM_EXPORT
void header_set_timestamp(header_t header, uint32_t timestamp);

BITPRIM_EXPORT
uint32_t header_bits(header_t header);

BITPRIM_EXPORT
void header_set_bits(header_t header, uint32_t bits);

BITPRIM_EXPORT
uint32_t header_nonce(header_t header);

BITPRIM_EXPORT
void header_set_nonce(header_t header, uint32_t nonce);

BITPRIM_EXPORT
hash_t header_previous_block_hash(header_t header);

BITPRIM_EXPORT
hash_t header_merkle(header_t header);

BITPRIM_EXPORT
hash_t header_hash(header_t header);



// ------------------------------------------------
// Block
// ------------------------------------------------

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

// ------------------------------------------------
// Transaction
// ------------------------------------------------

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

#endif /* BITPRIM_NODE_CINT_EXECUTOR_H_ */
