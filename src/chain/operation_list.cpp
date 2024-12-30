// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/capi/chain/operation_list.h>

#include <kth/capi/chain/output.h>
#include <kth/capi/conversions.hpp>

KTH_LIST_DEFINE_CONVERTERS(chain, kth_operation_list_t, kth::domain::machine::operation, operation_list)
KTH_LIST_DEFINE_CONSTRUCT_FROM_CPP_CONST(chain, kth_operation_list_t, kth::domain::machine::operation, operation_list)

extern "C" {

KTH_LIST_DEFINE(chain, kth_operation_list_t, kth_operation_t, operation_list, kth::domain::machine::operation, kth_chain_operation_const_cpp)

} // extern "C"
