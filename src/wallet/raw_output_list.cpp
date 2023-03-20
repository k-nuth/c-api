// Copyright (c) 2016-2023 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/capi/wallet/raw_output_list.h>

#include <vector>

#include <kth/domain/wallet/transaction_functions.hpp>

#include <kth/capi/conversions.hpp>
#include <kth/capi/list_creator.h>

KTH_LIST_DEFINE_CONVERTERS(wallet, kth_raw_output_list_t, kth::domain::wallet::raw_output, raw_output_list)
KTH_LIST_DEFINE_CONSTRUCT_FROM_CPP(wallet, kth_raw_output_list_t, kth::domain::wallet::raw_output, raw_output_list)

extern "C" {
KTH_LIST_DEFINE(wallet, kth_raw_output_list_t, kth_raw_output_t, raw_output_list, kth::domain::wallet::raw_output, kth_wallet_raw_output_const_cpp)
} // extern "C"
