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

#ifndef BITPRIM_NODECINT_CHAIN_GET_HEADERS_H_
#define BITPRIM_NODECINT_CHAIN_GET_HEADERS_H_

#include <stdio.h>
#include <stdint.h>

#include <bitprim/nodecint/visibility.h>
#include <bitprim/nodecint/primitives.h>


#ifdef __cplusplus
extern "C" {
#endif

BITPRIM_EXPORT
get_headers_t chain_get_headers_construct_default(void);

BITPRIM_EXPORT
get_headers_t chain_get_headers_construct(hash_list_t start, hash_t stop);

BITPRIM_EXPORT
void chain_get_headers_destruct(get_headers_t get_b);

BITPRIM_EXPORT
hash_list_t chain_get_headers_start_hashes(get_headers_t get_b);

BITPRIM_EXPORT
void chain_get_headers_set_start_hashes(get_headers_t get_b, hash_list_t value);

BITPRIM_EXPORT
hash_t chain_get_headers_stop_hash(get_headers_t get_b);

BITPRIM_EXPORT
void chain_get_headers_set_stop_hash(get_headers_t get_b, hash_t value);

//virtual bool from_data(uint32_t version, const data_chunk& data);
//virtual bool from_data(uint32_t version, std::istream& stream);
//virtual bool from_data(uint32_t version, reader& source);
//data_chunk to_data(uint32_t version) const;
//void to_data(uint32_t version, std::ostream& stream) const;
//void to_data(uint32_t version, writer& sink) const;

BITPRIM_EXPORT
int /*bool*/ chain_get_headers_is_valid(get_headers_t get_b);

BITPRIM_EXPORT
void chain_get_headers_reset(get_headers_t get_b);

BITPRIM_EXPORT
uint64_t /*size_t*/ chain_get_headers_serialized_size(get_headers_t get_b, uint32_t version);


#ifdef __cplusplus
} // extern "C"
#endif

#endif /* BITPRIM_NODECINT_CHAIN_GET_HEADERS_H_ */
