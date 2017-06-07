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

#ifndef BITPRIM_NODE_CINT_PRIMITIVES_H_
#define BITPRIM_NODE_CINT_PRIMITIVES_H_

#include <stdio.h>
#include <stdint.h>

#include <bitprim/nodecint/visibility.h>


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


#ifdef __cplusplus
} // extern "C"
#endif

#endif /* BITPRIM_NODE_CINT_PRIMITIVES_H_ */
