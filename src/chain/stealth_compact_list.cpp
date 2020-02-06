// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#include <bitcoin/bitcoin/chain/stealth.hpp>

#include <knuth/nodecint/chain/stealth_compact_list.h>
#include <knuth/nodecint/conversions.hpp>
#include <knuth/nodecint/list_creator.h>


KTH_LIST_DEFINE_CONVERTERS(chain, stealth_compact_list_t, kth::chain::stealth_compact, stealth_compact_list)

extern "C" {

KTH_LIST_DEFINE(chain, stealth_compact_list_t, stealth_compact_t, stealth_compact_list, kth::chain::stealth_compact, chain_stealth_compact_cpp)

} // extern "C"

