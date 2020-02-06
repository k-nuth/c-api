/**
* Copyright (c) 2016-2020 Knuth Project developers.
*
* This file is part of the Knuth Project.
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU Affero General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU Affero General Public License for more details.
*
* You should have received a copy of the GNU Affero General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <kth/capi/wallet/payment_address_list.h>

#include <vector>

#include <kth/capi/conversions.hpp>
#include <kth/capi/list_creator.h>

#include <kth/bitcoin/wallet/payment_address.hpp>

KTH_LIST_DEFINE_CONVERTERS(wallet, payment_address_list_t, kth::wallet::payment_address, payment_address_list)
KTH_LIST_DEFINE_CONSTRUCT_FROM_CPP(wallet, payment_address_list_t, kth::wallet::payment_address, payment_address_list)

extern "C" {
KTH_LIST_DEFINE(wallet, payment_address_list_t, payment_address_t, payment_address_list, kth::wallet::payment_address, wallet_payment_address_const_cpp)
} // extern "C"