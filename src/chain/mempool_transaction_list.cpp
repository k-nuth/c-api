// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#include <knuth/nodecint/chain/mempool_transaction_list.h>

#include <kth/blockchain/interface/safe_chain.hpp>
#include <knuth/nodecint/conversions.hpp>


KTH_LIST_DEFINE_CONVERTERS(chain, mempool_transaction_list_t, kth::blockchain::mempool_transaction_summary, mempool_transaction_list)
KTH_LIST_DEFINE_CONSTRUCT_FROM_CPP(chain, mempool_transaction_list_t, kth::blockchain::mempool_transaction_summary, mempool_transaction_list)

extern "C" {

KTH_LIST_DEFINE(chain, mempool_transaction_list_t, mempool_transaction_t, mempool_transaction_list, kth::blockchain::mempool_transaction_summary, chain_mempool_transaction_const_cpp)

} // extern "C"
