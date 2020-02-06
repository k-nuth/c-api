// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#include <kth/capi/chain/mempool_transaction.h>

#include <tuple>

#include <kth/blockchain/interface/safe_chain.hpp>

#include <kth/capi/helpers.hpp>
#include <kth/capi/type_conversions.h>

KTH_CONV_DEFINE(chain, mempool_transaction_t, kth::blockchain::mempool_transaction_summary, mempool_transaction)

// ---------------------------------------------------------------------------
extern "C" {

char const* chain_mempool_transaction_address(mempool_transaction_t tx) {
    auto tx_address_str = chain_mempool_transaction_const_cpp(tx).address();
    return knuth::create_c_str(tx_address_str);
}

char const* chain_mempool_transaction_hash(mempool_transaction_t tx) {
    auto tx_hash_str = chain_mempool_transaction_const_cpp(tx).hash();
    return knuth::create_c_str(tx_hash_str);
}

uint64_t chain_mempool_transaction_index(mempool_transaction_t tx) {
    return chain_mempool_transaction_const_cpp(tx).index();
}

char const* chain_mempool_transaction_satoshis(mempool_transaction_t tx) {
    auto tx_satoshis_str = chain_mempool_transaction_const_cpp(tx).satoshis();
    return knuth::create_c_str(tx_satoshis_str);
}

uint64_t chain_mempool_transaction_timestamp(mempool_transaction_t tx) {
    return chain_mempool_transaction_const_cpp(tx).timestamp();
}

char const* chain_mempool_transaction_prev_output_id(mempool_transaction_t tx) {
    auto tx_prev_output_id_str = chain_mempool_transaction_const_cpp(tx).previous_output_hash();
    return knuth::create_c_str(tx_prev_output_id_str);
}

char const* chain_mempool_transaction_prev_output_index(mempool_transaction_t tx) {
    auto tx_prev_output_index_str = chain_mempool_transaction_const_cpp(tx).previous_output_index();
    return knuth::create_c_str(tx_prev_output_index_str);
}

} // extern "C"



