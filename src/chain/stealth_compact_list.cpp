// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/domain/chain/stealth.hpp>

#include <kth/capi/chain/stealth_compact_list.h>
#include <kth/capi/conversions.hpp>
#include <kth/capi/list_creator.h>


KTH_LIST_DEFINE_CONVERTERS(chain, kth_stealth_compact_list_t, kth::domain::chain::stealth_compact, stealth_compact_list)

extern "C" {

KTH_LIST_DEFINE(chain, kth_stealth_compact_list_t, kth_stealth_compact_t, stealth_compact_list, kth::domain::chain::stealth_compact, kth_chain_stealth_compact_cpp)

} // extern "C"

