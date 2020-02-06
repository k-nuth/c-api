// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#include <knuth/nodecint/chain/history_compact_list.h>

#include <bitcoin/bitcoin/chain/history.hpp>
#include <bitcoin/bitcoin/chain/output_point.hpp>

#include <knuth/nodecint/conversions.hpp>

KTH_LIST_DEFINE_CONVERTERS(chain, history_compact_list_t, kth::chain::history_compact, history_compact_list)

extern "C" {

KTH_LIST_DEFINE(chain, history_compact_list_t, history_compact_t, history_compact_list, kth::chain::history_compact, chain_history_compact_const_cpp)

} // extern "C"
