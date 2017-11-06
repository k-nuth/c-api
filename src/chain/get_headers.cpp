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

#include <bitprim/nodecint/chain/header.h>

#include <bitprim/nodecint/convertions.hpp>
#include <bitprim/nodecint/helpers.hpp>

#include <bitcoin/bitcoin/message/get_headers.hpp>


libbitcoin::message::get_headers const& chain_get_headers_const_cpp(get_headers_t get_b) {
    return *static_cast<libbitcoin::message::get_headers const*>(get_b);
}

libbitcoin::message::get_headers& chain_get_headers_cpp(get_headers_t get_b) {
    return *static_cast<libbitcoin::message::get_headers*>(get_b);
}


extern "C" {

//get_headers();
get_headers_t chain_get_headers_construct_default() {
    return new libbitcoin::message::get_headers();
}

//get_headers(const hash_list& start, const hash_digest& stop);
//get_headers(hash_list&& start, hash_digest&& stop);
get_headers_t chain_get_headers_construct(hash_list_t start, hash_t stop) {
    auto const& start_cpp = chain_hash_list_const_cpp(start);
    auto stop_cpp = bitprim::to_array(stop.hash);

    return new libbitcoin::message::get_headers(start_cpp, stop_cpp);
}

void chain_get_headers_destruct(get_headers_t get_b) {
    delete &chain_get_headers_cpp(get_b);
}

//hash_list& start_hashes();
//const hash_list& start_hashes() const;
hash_list_t chain_get_headers_start_hashes(get_headers_t get_b) {
    auto& list = chain_get_headers_cpp(get_b).start_hashes();
    return chain_hash_list_construct_from_cpp(list);
}

//void set_start_hashes(const hash_list& value);
//void set_start_hashes(hash_list&& value);
void chain_get_headers_set_start_hashes(get_headers_t get_b, hash_list_t value) {
    auto const& value_cpp = chain_hash_list_const_cpp(value);
    chain_get_headers_cpp(get_b).set_start_hashes(value_cpp);
}

//hash_digest& stop_hash();
//const hash_digest& stop_hash() const;
hash_t chain_get_headers_stop_hash(get_headers_t get_b) {
    auto& stop = chain_get_headers_cpp(get_b).stop_hash();
    return bitprim::to_hash_t(stop);
}

void chain_get_headers_stop_hash_out(get_headers_t get_b, hash_t* out_stop_hash) {
    auto& stop = chain_get_headers_cpp(get_b).stop_hash();
    std::memcpy(out_stop_hash->hash, stop.data(), bitcoin_hash_size);
}

//void set_stop_hash(const hash_digest& value);
//void set_stop_hash(hash_digest&& value);
void chain_get_headers_set_stop_hash(get_headers_t get_b, hash_t value) {
    auto value_cpp = bitprim::to_array(value.hash);
    chain_get_headers_cpp(get_b).set_stop_hash(value_cpp);
}


//virtual bool from_data(uint32_t version, const data_chunk& data);
//virtual bool from_data(uint32_t version, std::istream& stream);
//virtual bool from_data(uint32_t version, reader& source);
//data_chunk to_data(uint32_t version) const;
//void to_data(uint32_t version, std::ostream& stream) const;
//void to_data(uint32_t version, writer& sink) const;

//bool is_valid() const;
int /*bool*/ chain_get_headers_is_valid(get_headers_t get_b) {
    return static_cast<int>(chain_get_headers_cpp(get_b).is_valid());
}

//void reset();
void chain_get_headers_reset(get_headers_t get_b) {
    chain_get_headers_cpp(get_b).reset();
}

//size_t serialized_size(uint32_t version) const;
uint64_t /*size_t*/ chain_get_headers_serialized_size(get_headers_t get_b, uint32_t version) {
    return chain_get_headers_cpp(get_b).serialized_size(version);
}

} /* extern "C" */
