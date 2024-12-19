// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/capi/chain/block_indexes.h>

#include <kth/capi/conversions.hpp>

KTH_LIST_DEFINE_CONVERTERS(chain, kth_block_indexes_t, kth_size_t, block_indexes)

KTH_LIST_DEFINE_CONSTRUCT_FROM_CPP(chain, kth_block_indexes_t, kth_size_t, block_indexes)

extern "C" {

KTH_LIST_DEFINE_VALUE(chain, kth_block_indexes_t, kth_size_t, block_indexes, kth_size_t, kth_size_t)

} // extern "C"
