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

#ifndef BITPRIM_NODECINT_CHAIN_HEADER_H_
#define BITPRIM_NODECINT_CHAIN_HEADER_H_

#include <stdio.h>
#include <stdint.h>

#include <bitprim/nodecint/visibility.h>
#include <bitprim/nodecint/primitives.h>



#ifdef __cplusplus
extern "C" {
#endif

//static header factory_from_data(const uint32_t version, const data_chunk& data);
BITPRIM_EXPORT
header_t chain_header_factory_from_data(uint32_t version, uint8_t* data, uint64_t n);

//static size_t satoshi_fixed_size(const uint32_t version);
BITPRIM_EXPORT
uint64_t /*size_t*/ chain_header_satoshi_fixed_size(uint32_t version);

//void reset(void);
BITPRIM_EXPORT
void chain_header_reset(header_t header);

//size_t serialized_size(const uint32_t version) const;
BITPRIM_EXPORT
uint64_t /*size_t*/ chain_header_serialized_size(header_t header, uint32_t version);

//data_chunk to_data(const uint32_t version) const;
BITPRIM_EXPORT
uint8_t* chain_header_to_data(header_t header, uint32_t version);

//header(void);
BITPRIM_EXPORT
header_t chain_header_construct_default(void);

//header(uint32_t version, const hash_digest& previous_block_hash, const hash_digest& merkle, uint32_t timestamp, uint32_t bits, uint32_t nonce);
BITPRIM_EXPORT
header_t chain_header_construct(uint32_t version, uint8_t* previous_block_hash, uint8_t* merkle, uint32_t timestamp, uint32_t bits, uint32_t nonce);

BITPRIM_EXPORT
void chain_header_destruct(header_t header);

BITPRIM_EXPORT
int chain_header_is_valid(header_t header);

BITPRIM_EXPORT
uint32_t chain_header_version(header_t header);

BITPRIM_EXPORT
void chain_header_set_version(header_t header, uint32_t version);

BITPRIM_EXPORT
uint32_t chain_header_timestamp(header_t header);

BITPRIM_EXPORT
void chain_header_set_timestamp(header_t header, uint32_t timestamp);

BITPRIM_EXPORT
uint32_t chain_header_bits(header_t header);

BITPRIM_EXPORT
void chain_header_set_bits(header_t header, uint32_t bits);

BITPRIM_EXPORT
uint32_t chain_header_nonce(header_t header);

BITPRIM_EXPORT
void chain_header_set_nonce(header_t header, uint32_t nonce);

BITPRIM_EXPORT
hash_t chain_header_previous_block_hash(header_t header);

BITPRIM_EXPORT
hash_t chain_header_merkle(header_t header);

BITPRIM_EXPORT
hash_t chain_header_hash(header_t header);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* BITPRIM_NODECINT_CHAIN_HEADER_H_ */
