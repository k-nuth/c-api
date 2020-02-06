// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#include <knuth/nodecint/chain/stealth_compact.h>

#include <kth/bitcoin/chain/stealth.hpp>

#include <knuth/nodecint/helpers.hpp>
#include <knuth/nodecint/type_conversions.h>


KTH_CONV_DEFINE(chain, stealth_compact_t, kth::chain::stealth_compact, stealth_compact)

// ---------------------------------------------------------------------------
extern "C" {

hash_t chain_stealth_compact_get_ephemeral_public_key_hash(stealth_compact_t stealth) {
    auto const& hash_cpp = chain_stealth_compact_cpp(stealth).ephemeral_public_key_hash;
    return knuth::to_hash_t(hash_cpp); 
}

void chain_stealth_compact_get_ephemeral_public_key_hash_out(stealth_compact_t stealth, hash_t* out_epk_hash) {
    auto const& hash_cpp = chain_stealth_compact_cpp(stealth).ephemeral_public_key_hash;
    knuth::copy_c_hash(hash_cpp, out_epk_hash);
}

hash_t chain_stealth_compact_get_transaction_hash(stealth_compact_t stealth) {
    auto const& hash_cpp = chain_stealth_compact_cpp(stealth).transaction_hash;
    return knuth::to_hash_t(hash_cpp);
}

void chain_stealth_compact_get_transaction_hash_out(stealth_compact_t stealth, hash_t* out_tx_hash) {
    auto const& hash_cpp = chain_stealth_compact_cpp(stealth).transaction_hash;
    knuth::copy_c_hash(hash_cpp, out_tx_hash);
}

short_hash_t chain_stealth_compact_get_public_key_hash(stealth_compact_t stealth) {
    auto const& hash_cpp = chain_stealth_compact_cpp(stealth).public_key_hash;
    return knuth::to_short_hash_t(hash_cpp);
}

void chain_stealth_compact_get_public_key_hash_out(stealth_compact_t stealth, short_hash_t* out_pk_hash) {
    auto const& hash_cpp = chain_stealth_compact_cpp(stealth).public_key_hash;
    knuth::copy_c_hash(hash_cpp, out_pk_hash);
}

/*
    typedef std::vector<stealth_compact> list;

    hash_digest ephemeral_public_key_hash;
    short_hash public_key_hash;
    hash_digest transaction_hash;
*/


} // extern "C"
