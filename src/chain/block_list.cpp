// Copyright (c) 2016-2023 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/capi/chain/block_list.h>

#include <kth/capi/chain/block.h>
#include <kth/capi/conversions.hpp>


KTH_LIST_DEFINE_CONVERTERS(chain, kth_block_list_t, kth::domain::message::block, block_list)
KTH_LIST_DEFINE_CONSTRUCT_FROM_CPP(chain, kth_block_list_t, kth::domain::message::block, block_list)

extern "C" {

KTH_LIST_DEFINE(chain, kth_block_list_t, kth_block_t, block_list, kth::domain::message::block, kth_chain_block_const_cpp)

} // extern "C"
