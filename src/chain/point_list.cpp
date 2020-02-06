// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#include <kth/domain/chain/point.hpp>

#include <kth/capi/chain/point_list.h>
#include <kth/capi/conversions.hpp>
#include <kth/capi/list_creator.h>

KTH_LIST_DEFINE_CONVERTERS(chain, point_list_t, kth::chain::point, point_list)

// ---------------------------------------------------------------------------
extern "C" {

KTH_LIST_DEFINE(chain, point_list_t, point_t, point_list, kth::chain::point, chain_point_const_cpp)

} // extern "C"