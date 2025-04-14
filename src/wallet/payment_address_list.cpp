// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/capi/wallet/payment_address_list.h>

#include <vector>

#include <kth/capi/conversions.hpp>
#include <kth/capi/list_creator.h>

#include <kth/domain/wallet/payment_address.hpp>

KTH_LIST_DEFINE_CONVERTERS(wallet, kth_payment_address_list_t, kth::domain::wallet::payment_address, payment_address_list)
KTH_LIST_DEFINE_CONSTRUCT_FROM_CPP_BOTH(wallet, kth_payment_address_list_t, kth::domain::wallet::payment_address, payment_address_list)

extern "C" {
KTH_LIST_DEFINE(wallet, kth_payment_address_list_t, kth_payment_address_t, payment_address_list, kth::domain::wallet::payment_address, kth_wallet_payment_address_const_cpp)
} // extern "C"