// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#include <kth/capi/chain/transaction_list.h>

#include <kth/capi/chain/transaction.h>
#include <kth/capi/conversions.hpp>


KTH_LIST_DEFINE_CONVERTERS(chain, transaction_list_t, kth::message::transaction, transaction_list)
KTH_LIST_DEFINE_CONSTRUCT_FROM_CPP(chain, transaction_list_t, kth::message::transaction, transaction_list)

extern "C" {

KTH_LIST_DEFINE(chain, transaction_list_t, transaction_t, transaction_list, kth::message::transaction, chain_transaction_const_cpp)

} // extern "C"
