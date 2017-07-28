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

#ifndef BITPRIM_NODECINT_PRIMITIVES_H_
#define BITPRIM_NODECINT_PRIMITIVES_H_

#include <stdio.h>
#include <stdint.h>

#include <bitprim/nodecint/visibility.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum point_kind {output = 0, spend = 1} point_kind_t;

typedef struct executor* executor_t;
typedef void* chain_t;
typedef void* p2p_t;

//typedef struct output_point_t {
//    uint8_t* hash;
//    uint32_t index;
//} output_point_t;


// TODO(fernando): check if we can encapsulate the pointer into a struct to make them more "type safe"
typedef void* block_t;
typedef void* block_indexes_t;
typedef void* block_list_t;

typedef void* compact_block_t;
typedef void* header_t;
typedef void* history_compact_t;
typedef void* history_compact_list_t;

typedef void* input_t;
typedef void* input_list_t;
typedef void* input_point_t;

typedef void* merkle_block_t;
typedef void* script_t;

typedef void* output_t;
typedef void* output_list_t;
typedef void* output_point_t;

typedef void* point_t;
typedef void* point_list_t;
typedef void* transaction_t;
typedef void* transaction_list_t;

typedef void* get_blocks_t;
typedef void* get_blocks_ptr_t;
typedef void* get_headers_t;
typedef void* get_headers_ptr_t;


typedef void* payment_address_t;
typedef void* binary_t;
typedef void* stealth_compact_t;
typedef void* stealth_compact_list_t;


typedef void* hash_list_t;



//typedef uint8_t const* hash_t;
//typedef uint8_t* long_hash_t;
//typedef uint8_t* short_hash_t;

//typedef uint8_t const* hash_t;
//typedef uint8_t* long_hash_t;
typedef struct short_hash_t {
//    uint8_t hash[libbitcoin::hash_size];
    uint8_t hash[20];
} short_hash_t;

typedef struct hash_t {
//    uint8_t hash[libbitcoin::hash_size];
    uint8_t hash[32];
} hash_t;

typedef struct long_hash_t {
//    uint8_t hash[libbitcoin::long_hash_size];
    uint8_t hash[64];
} long_hash_t;

//typedef char const* zstring_t;
typedef void* word_list_t;



typedef void (*run_handler_t)(executor_t exec, void* ctx, int error);


typedef void (*stealth_fetch_handler_t)(chain_t chain, void*, int, stealth_compact_list_t stealth);
typedef void (*block_fetch_handler_t)(chain_t, void*, int, block_t block, uint64_t /*size_t*/ h);
typedef void (*block_height_fetch_handler_t)(chain_t, void*, int, uint64_t /*size_t*/ h);
typedef void (*block_header_fetch_handler_t)(chain_t, void*, int, header_t header, uint64_t /*size_t*/ h);
typedef void (*compact_block_fetch_handler_t)(chain_t, void*, int, compact_block_t block, uint64_t /*size_t*/ h);
typedef void (*history_fetch_handler_t)(chain_t, void*, int, history_compact_list_t history);
typedef void (*last_height_fetch_handler_t)(chain_t, void*, int, uint64_t /*size_t*/ h);
typedef void (*merkle_block_fetch_handler_t)(chain_t, void*, int, merkle_block_t block, uint64_t /*size_t*/ h);
typedef void (*output_fetch_handler_t)(chain_t, void*, int, output_t output);
typedef void (*spend_fetch_handler_t)(chain_t, void*, int, input_point_t input_point);
typedef void (*transaction_fetch_handler_t)(chain_t, void*, int, transaction_t transaction, uint64_t /*size_t*/ h, uint64_t /*size_t*/ i);
typedef void (*transaction_index_fetch_handler_t)(chain_t, void*, int, uint64_t /*size_t*/ position, uint64_t /*size_t*/ height);
typedef void (*validate_tx_handler_t)(chain_t, void*, int, char const* message);

//typedef std::function<void(const code&, get_headers_ptr)> block_locator_fetch_handler;
typedef void (*block_locator_fetch_handler_t)(chain_t, void*, int, get_headers_ptr_t);

//typedef std::function<void(const code&, inventory_ptr)> inventory_fetch_handler;


typedef void (*result_handler_t)(chain_t, void*, int);

typedef int (*reorganize_handler_t)(chain_t, void*, int, uint64_t /*size_t*/, block_list_t, block_list_t);
typedef int (*transaction_handler_t)(chain_t, void*, int, transaction_t);



#ifdef __cplusplus
} // extern "C"
#endif


#endif /* BITPRIM_NODECINT_PRIMITIVES_H_ */
