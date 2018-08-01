/**
 * Copyright (c) 2016-2018 Bitprim Inc.
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

#include <bitcoin/bitcoin/chain/stealth.hpp>
#include <bitprim/nodecint/chain/stealth_compact.h>
#include <bitprim/nodecint/helpers.hpp>

libbitcoin::chain::stealth_compact const& stealth_compact_const_cpp(stealth_compact_t stealth) {
	return *static_cast<libbitcoin::chain::stealth_compact const*>(stealth);
}

libbitcoin::chain::stealth_compact& stealth_compact_cpp(stealth_compact_t stealth) {
	return *static_cast<libbitcoin::chain::stealth_compact*>(stealth);
}

hash_t stealth_compact_get_ephemeral_public_key_hash(stealth_compact_t stealth) {
    auto const& hash_cpp = stealth_compact_cpp(stealth).ephemeral_public_key_hash;
    return bitprim::to_hash_t(hash_cpp); 
}

void stealth_compact_get_ephemeral_public_key_hash_out(stealth_compact_t stealth, hash_t* out_epk_hash) {
    auto const& hash_cpp = stealth_compact_cpp(stealth).ephemeral_public_key_hash;
    // std::memcpy(static_cast<void*>(out_epk_hash->hash), hash_cpp.data(), BITCOIN_HASH_SIZE);
    bitprim::copy_c_hash(hash_cpp, out_epk_hash);
}

hash_t stealth_compact_get_transaction_hash(stealth_compact_t stealth) {
    auto const& hash_cpp = stealth_compact_cpp(stealth).transaction_hash;
    return bitprim::to_hash_t(hash_cpp);
}

void stealth_compact_get_transaction_hash_out(stealth_compact_t stealth, hash_t* out_tx_hash) {
    auto const& hash_cpp = stealth_compact_cpp(stealth).transaction_hash;
    // std::memcpy(static_cast<void*>(out_tx_hash->hash), hash_cpp.data(), BITCOIN_HASH_SIZE);
    bitprim::copy_c_hash(hash_cpp, out_tx_hash);
}

short_hash_t stealth_compact_get_public_key_hash(stealth_compact_t stealth) {
    auto const& hash_cpp = stealth_compact_cpp(stealth).public_key_hash;
    return bitprim::to_short_hash_t(hash_cpp);
}

void stealth_compact_get_public_key_hash_out(stealth_compact_t stealth, short_hash_t* out_pk_hash) {
    auto const& hash_cpp = stealth_compact_cpp(stealth).public_key_hash;
    // std::memcpy(static_cast<void*>(out_pk_hash->hash), hash_cpp.data(), BITCOIN_SHORT_HASH_SIZE);
    bitprim::copy_c_hash(hash_cpp, out_pk_hash);
}

/*
    typedef std::vector<stealth_compact> list;

    hash_digest ephemeral_public_key_hash;
    short_hash public_key_hash;
    hash_digest transaction_hash;
*/

