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

#include <bitprim/nodecint/chain/stealth_compact.h>
#include <bitcoin/bitcoin/chain/stealth.hpp>


libbitcoin::chain::stealth_compact const& stealth_compact_const_cpp(stealth_compact_t stealth){
	return *static_cast<libbitcoin::chain::stealth_compact const*>(stealth);
}

libbitcoin::chain::stealth_compact& stealth_compact_cpp(stealth_compact_t stealth){
	return *static_cast<libbitcoin::chain::stealth_compact*>(stealth);
}

hash_t stealth_compact_get_ephemeral_public_key_hash(stealth_compact_t stealth){
    //return &stealth_compact_cpp(stealth).ephemeral_public_key_hash;

    auto const& hash_cpp = stealth_compact_cpp(stealth).ephemeral_public_key_hash;
    return hash_cpp.data(); //TODO: returning a dangling pointer
}

hash_t stealth_compact_get_transaction_hash(stealth_compact_t stealth){
    //return &stealth_compact_cpp(stealth).transaction_hash;
    auto const& hash_cpp = stealth_compact_cpp(stealth).transaction_hash;
    return hash_cpp.data(); //TODO: returning a dangling pointer

}

short_hash_t stealth_compact_get_public_key_hash(stealth_compact_t stealth){
//    return &stealth_compact_cpp(stealth).public_key_hash;

    uint8_t* ret = (uint8_t*)malloc(stealth_compact_cpp(stealth).public_key_hash.size() * sizeof(uint8_t));
//    printf("wallet_mnemonics_to_seed - ret: %p\n", ret);
    std::copy_n(std::begin(stealth_compact_cpp(stealth).public_key_hash), stealth_compact_cpp(stealth).public_key_hash.size(), ret);
    return ret;
}


/*
    typedef std::vector<stealth_compact> list;

    hash_digest ephemeral_public_key_hash;
    short_hash public_key_hash;
    hash_digest transaction_hash;
*/

