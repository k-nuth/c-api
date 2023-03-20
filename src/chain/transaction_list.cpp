// Copyright (c) 2016-2023 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/capi/chain/transaction_list.h>

#include <kth/capi/chain/transaction.h>
#include <kth/capi/conversions.hpp>

KTH_LIST_DEFINE_CONVERTERS(chain, kth_transaction_list_t, kth::domain::chain::transaction, transaction_list)
KTH_LIST_DEFINE_CONSTRUCT_FROM_CPP(chain, kth_transaction_list_t, kth::domain::chain::transaction, transaction_list)

extern "C" {

KTH_LIST_DEFINE(chain, kth_transaction_list_t, kth_transaction_t, transaction_list, kth::domain::chain::transaction, kth_chain_transaction_const_cpp)

} // extern "C"


// KTH_LIST_DEFINE_CONVERTERS(chain, kth_transaction_list_t, kth::domain::message::transaction, transaction_list)
// KTH_LIST_DEFINE_CONSTRUCT_FROM_CPP(chain, kth_transaction_list_t, kth::domain::message::transaction, transaction_list)

// extern "C" {

// KTH_LIST_DEFINE(chain, kth_transaction_list_t, kth_transaction_t, transaction_list, kth::domain::message::transaction, kth_chain_transaction_const_cpp)

// } // extern "C"
