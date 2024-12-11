// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/capi/chain/output_list.h>

#include <kth/capi/chain/output.h>
#include <kth/capi/conversions.hpp>

KTH_LIST_DEFINE_CONVERTERS(chain, kth_output_list_t, kth::domain::chain::output, output_list)
KTH_LIST_DEFINE_CONSTRUCT_FROM_CPP(chain, kth_output_list_t, kth::domain::chain::output, output_list)

extern "C" {

KTH_LIST_DEFINE(chain, kth_output_list_t, kth_output_t, output_list, kth::domain::chain::output, kth_chain_output_const_cpp)

} // extern "C"
