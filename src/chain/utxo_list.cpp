// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/capi/chain/utxo_list.h>

#include <kth/domain/chain/utxo.hpp>
#include <kth/capi/chain/utxo.h>
#include <kth/capi/conversions.hpp>


KTH_LIST_DEFINE_CONVERTERS(chain, kth_utxo_list_t, kth::domain::chain::utxo, utxo_list)
KTH_LIST_DEFINE_CONSTRUCT_FROM_CPP(chain, kth_utxo_list_t, kth::domain::chain::utxo, utxo_list)

extern "C" {

KTH_LIST_DEFINE(chain, kth_utxo_list_t, kth_utxo_t, utxo_list, kth::domain::chain::utxo, kth_chain_utxo_const_cpp)

} // extern "C"
