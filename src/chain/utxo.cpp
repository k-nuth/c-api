// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/capi/chain/utxo.h>

#include <kth/capi/conversions.hpp>
#include <kth/capi/helpers.hpp>

KTH_CONV_DEFINE(chain, kth_utxo_t, kth::domain::chain::utxo, utxo)

// ---------------------------------------------------------------------------
extern "C" {

kth_utxo_t kth_chain_utxo_construct() {
    // return std::make_unique<kth::domain::chain::utxo>().release();
    return new kth::domain::chain::utxo;
}


kth_utxo_t kth_chain_utxo_construct_from_hash_index_amount(kth_hash_t const* hash, uint32_t index, uint64_t amount) {
    auto hash_cpp = kth::to_array(hash->hash);
    auto ret = new kth::domain::chain::utxo(kth::domain::chain::output_point(hash_cpp, index), amount);
    return ret;
}

void kth_chain_utxo_destruct(kth_utxo_t op) {
    delete &kth_chain_utxo_cpp(op);
}

//kth_hash_t kth_chain_utxo_get_hash(kth_utxo_t op) {
//    auto const& hash_cpp = kth_chain_utxo_const_cpp(op).hash();
//    return hash_cpp.data();
//}

kth_hash_t kth_chain_utxo_get_hash(kth_utxo_t op) {
    auto const& hash_cpp = kth_chain_utxo_const_cpp(op).point().hash();
    return kth::to_hash_t(hash_cpp);
}

void kth_chain_utxo_get_hash_out(kth_utxo_t op, kth_hash_t* out_hash) {
    auto const& hash_cpp = kth_chain_utxo_const_cpp(op).point().hash();
    kth::copy_c_hash(hash_cpp, out_hash);
}

uint32_t kth_chain_utxo_get_index(kth_utxo_t op) {
    return kth_chain_utxo_const_cpp(op).point().index();
}

uint64_t kth_chain_utxo_get_amount(kth_utxo_t op) {
    return kth_chain_utxo_const_cpp(op).amount();
}

kth_output_t kth_chain_utxo_get_cached_output(kth_utxo_t op) {
    auto& output = kth_chain_utxo_const_cpp(op).point().validation.cache;
    return &output;
}

void kth_chain_utxo_set_hash(kth_utxo_t op, kth_hash_t const* hash) {
    auto hash_cpp = kth::to_array(hash->hash);
    kth_chain_utxo_cpp(op).point().set_hash(hash_cpp);
}

void kth_chain_utxo_set_index(kth_utxo_t op, uint32_t index) {
    kth_chain_utxo_cpp(op).point().set_index(index);
}

void kth_chain_utxo_set_amount(kth_utxo_t op, uint64_t amount) {
    kth_chain_utxo_cpp(op).set_amount(amount);
}

void kth_chain_utxo_set_cached_output(kth_utxo_t op, kth_output_t output) {
    kth_chain_utxo_cpp(op).point().validation.cache = kth_chain_output_const_cpp(output);
}

} // extern "C"
