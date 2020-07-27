// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#include <kth/capi/chain/block_list.h>

#include <kth/capi/chain/block.h>
#include <kth/capi/conversions.hpp>


KTH_LIST_DEFINE_CONVERTERS(chain, block_list_t, kth::domain::message::block, block_list)
KTH_LIST_DEFINE_CONSTRUCT_FROM_CPP(chain, block_list_t, kth::domain::message::block, block_list)

extern "C" {

KTH_LIST_DEFINE(chain, block_list_t, block_t, block_list, kth::domain::message::block, chain_block_const_cpp)

} // extern "C"
