// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#include <knuth/nodecint/chain/transaction_list.h>

#include <knuth/nodecint/chain/transaction.h>
#include <knuth/nodecint/conversions.hpp>


KTH_LIST_DEFINE_CONVERTERS(chain, transaction_list_t, libbitcoin::message::transaction, transaction_list)
KTH_LIST_DEFINE_CONSTRUCT_FROM_CPP(chain, transaction_list_t, libbitcoin::message::transaction, transaction_list)

extern "C" {

KTH_LIST_DEFINE(chain, transaction_list_t, transaction_t, transaction_list, libbitcoin::message::transaction, chain_transaction_const_cpp)

} // extern "C"
