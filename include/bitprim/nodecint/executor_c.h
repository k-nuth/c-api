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
#include <bitprim/nodecint/primitives.h>

#ifdef __cplusplus
extern "C" {
#endif


//BITPRIM_EXPORT
//executor_t executor_construct_devnull(char const* path);

BITPRIM_EXPORT
executor_t executor_construct(char const* path, FILE* sout, FILE* serr);

BITPRIM_EXPORT
executor_t executor_construct_fd(char const* path, int sout_fd, int serr_fd);


#if defined(_WIN32)

BITPRIM_EXPORT
executor_t executor_construct_handles(char const* path, void* sout, void* serr);

#endif /* defined(_WIN32) */



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

//BITPRIM_EXPORT
//void fetch_block(executor_t exec, size_t height, block_fetch_handler_t handler);
//
//BITPRIM_EXPORT
//void fetch_block_by_hash(executor_t exec, hash_t hash, block_fetch_handler_t handler);

BITPRIM_EXPORT
void fetch_last_height(executor_t exec, last_height_fetch_handler_t handler);

BITPRIM_EXPORT
int get_last_height(executor_t exec, size_t* height);

BITPRIM_EXPORT
void fetch_block_height(executor_t exec, hash_t hash, block_height_fetch_handler_t handler);

BITPRIM_EXPORT
int get_block_height(executor_t exec, hash_t hash, size_t* height);


// Block Header ---------------------------------------------------------------------
BITPRIM_EXPORT
void fetch_block_header_by_height(executor_t exec, size_t height, block_header_fetch_handler_t handler);

BITPRIM_EXPORT
int get_block_header_by_height(executor_t exec, size_t height, header_t* header, size_t* ret_height);

BITPRIM_EXPORT
void fetch_block_header_by_hash(executor_t exec, hash_t hash, block_header_fetch_handler_t handler);

BITPRIM_EXPORT
int get_block_header_by_hash(executor_t exec, hash_t hash, header_t* header, size_t* ret_height);


// Block ---------------------------------------------------------------------
BITPRIM_EXPORT
void fetch_block_by_height(executor_t exec, size_t height, block_fetch_handler_t handler);

BITPRIM_EXPORT
int get_block_by_height(executor_t exec, size_t height, block_t* block, size_t* ret_height);

BITPRIM_EXPORT
void fetch_block_by_hash(executor_t exec, hash_t hash, block_fetch_handler_t handler);

BITPRIM_EXPORT
int get_block_by_hash(executor_t exec, hash_t hash, block_t* block, size_t* ret_height);


// Merkle Block ---------------------------------------------------------------------
BITPRIM_EXPORT
void fetch_merkle_block_by_height(executor_t exec, size_t height, merkle_block_fetch_handler_t handler);

BITPRIM_EXPORT
void fetch_merkle_block_by_hash(executor_t exec, hash_t hash, merkle_block_fetch_handler_t handler);

// Compact Block ---------------------------------------------------------------------
BITPRIM_EXPORT
void fetch_compact_block_by_height(executor_t exec, size_t height, compact_block_fetch_handler_t handler);

BITPRIM_EXPORT
void fetch_compact_block_by_hash(executor_t exec, hash_t hash, compact_block_fetch_handler_t handler);


// Transaction ---------------------------------------------------------------------
BITPRIM_EXPORT
void fetch_transaction(executor_t exec, hash_t hash, int require_confirmed, transaction_fetch_handler_t handler);

BITPRIM_EXPORT
int get_transaction(executor_t exec, hash_t hash, int require_confirmed, transaction_t* transaction, size_t* ret_height, size_t* index);

BITPRIM_EXPORT
void fetch_transaction_position(executor_t exec, hash_t hash, int require_confirmed, transaction_index_fetch_handler_t handler);


// Output  ---------------------------------------------------------------------
BITPRIM_EXPORT
void fetch_output(executor_t exec, hash_t hash, uint32_t index, int require_confirmed, output_fetch_handler_t handler);

BITPRIM_EXPORT
int get_output(executor_t exec, hash_t hash, uint32_t index, int require_confirmed, output_t* output);

// Spend ---------------------------------------------------------------------
BITPRIM_EXPORT
void fetch_spend(executor_t exec, output_point_t outpoint, spend_fetch_handler_t handler);

// History ---------------------------------------------------------------------
BITPRIM_EXPORT
void fetch_history(executor_t exec, payment_address_t address, size_t limit, size_t from_height, history_fetch_handler_t handler);

//BITPRIM_EXPORT
//void fetch_history(executor_t exec, zstring_t address, size_t limit, size_t from_height, history_fetch_handler_t handler);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* BITPRIM_NODE_CINT_EXECUTOR_H_ */
