// Copyright (c) 2016-2023 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/capi/chain/stealth_compact.h>

#include <kth/domain/chain/stealth.hpp>

#include <kth/capi/helpers.hpp>
#include <kth/capi/type_conversions.h>


KTH_CONV_DEFINE(chain, kth_stealth_compact_t, kth::domain::chain::stealth_compact, stealth_compact)

// ---------------------------------------------------------------------------
extern "C" {

kth_hash_t kth_chain_stealth_compact_get_ephemeral_public_key_hash(kth_stealth_compact_t stealth) {
    auto const& hash_cpp = kth_chain_stealth_compact_cpp(stealth).ephemeral_public_key_hash;
    return kth::to_hash_t(hash_cpp);
}

void kth_chain_stealth_compact_get_ephemeral_public_key_hash_out(kth_stealth_compact_t stealth, kth_hash_t* out_epk_hash) {
    auto const& hash_cpp = kth_chain_stealth_compact_cpp(stealth).ephemeral_public_key_hash;
    kth::copy_c_hash(hash_cpp, out_epk_hash);
}

kth_hash_t kth_chain_stealth_compact_get_transaction_hash(kth_stealth_compact_t stealth) {
    auto const& hash_cpp = kth_chain_stealth_compact_cpp(stealth).transaction_hash;
    return kth::to_hash_t(hash_cpp);
}

void kth_chain_stealth_compact_get_transaction_hash_out(kth_stealth_compact_t stealth, kth_hash_t* out_tx_hash) {
    auto const& hash_cpp = kth_chain_stealth_compact_cpp(stealth).transaction_hash;
    kth::copy_c_hash(hash_cpp, out_tx_hash);
}

kth_shorthash_t kth_chain_stealth_compact_get_public_key_hash(kth_stealth_compact_t stealth) {
    auto const& hash_cpp = kth_chain_stealth_compact_cpp(stealth).public_key_hash;
    return kth::to_shorthash_t(hash_cpp);
}

void kth_chain_stealth_compact_get_public_key_hash_out(kth_stealth_compact_t stealth, kth_shorthash_t* out_pk_hash) {
    auto const& hash_cpp = kth_chain_stealth_compact_cpp(stealth).public_key_hash;
    kth::copy_c_hash(hash_cpp, out_pk_hash);
}

/*
    typedef std::vector<stealth_compact> list;

    hash_digest ephemeral_public_key_hash;
    short_hash public_key_hash;
    hash_digest transaction_hash;
*/


} // extern "C"
