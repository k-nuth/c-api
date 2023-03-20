// Copyright (c) 2016-2023 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/capi/chain/input_list.h>

#include <kth/domain/chain/input.hpp>
#include <kth/capi/chain/input.h>
#include <kth/capi/conversions.hpp>


KTH_LIST_DEFINE_CONVERTERS(chain, kth_input_list_t, kth::domain::chain::input, input_list)
KTH_LIST_DEFINE_CONSTRUCT_FROM_CPP(chain, kth_input_list_t, kth::domain::chain::input, input_list)

extern "C" {

KTH_LIST_DEFINE(chain, kth_input_list_t, kth_input_t, input_list, kth::domain::chain::input, kth_chain_input_const_cpp)

} // extern "C"
