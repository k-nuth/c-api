// Copyright (c) 2016-2023 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/capi/chain/mempool_transaction.h>

#include <tuple>

#include <kth/blockchain/interface/safe_chain.hpp>

#include <kth/capi/helpers.hpp>
#include <kth/capi/type_conversions.h>

KTH_CONV_DEFINE(chain, kth_mempool_transaction_t, kth::blockchain::mempool_transaction_summary, mempool_transaction)

// ---------------------------------------------------------------------------
extern "C" {

char const* kth_chain_mempool_transaction_address(kth_mempool_transaction_t tx) {
    auto tx_address_str = kth_chain_mempool_transaction_const_cpp(tx).address();
    return kth::create_c_str(tx_address_str);
}

char const* kth_chain_mempool_transaction_hash(kth_mempool_transaction_t tx) {
    auto tx_hash_str = kth_chain_mempool_transaction_const_cpp(tx).hash();
    return kth::create_c_str(tx_hash_str);
}

uint64_t kth_chain_mempool_transaction_index(kth_mempool_transaction_t tx) {
    return kth_chain_mempool_transaction_const_cpp(tx).index();
}

char const* kth_chain_mempool_transaction_satoshis(kth_mempool_transaction_t tx) {
    auto tx_satoshis_str = kth_chain_mempool_transaction_const_cpp(tx).satoshis();
    return kth::create_c_str(tx_satoshis_str);
}

uint64_t kth_chain_kth_mempool_transaction_timestamp(kth_mempool_transaction_t tx) {
    return kth_chain_mempool_transaction_const_cpp(tx).timestamp();
}

char const* kth_chain_mempool_transaction_prev_output_id(kth_mempool_transaction_t tx) {
    auto tx_prev_output_id_str = kth_chain_mempool_transaction_const_cpp(tx).previous_output_hash();
    return kth::create_c_str(tx_prev_output_id_str);
}

char const* kth_chain_mempool_transaction_prev_output_index(kth_mempool_transaction_t tx) {
    auto tx_prev_output_index_str = kth_chain_mempool_transaction_const_cpp(tx).previous_output_index();
    return kth::create_c_str(tx_prev_output_index_str);
}

} // extern "C"



