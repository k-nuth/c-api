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

#include <knuth/nodecint/wallet/raw_output_list.h>

#include <vector>

#include <bitcoin/bitcoin/wallet/transaction_functions.hpp>

#include <knuth/nodecint/conversions.hpp>
#include <knuth/nodecint/list_creator.h>

KTH_LIST_DEFINE_CONVERTERS(wallet, raw_output_list_t, libbitcoin::wallet::raw_output, raw_output_list)
KTH_LIST_DEFINE_CONSTRUCT_FROM_CPP(wallet, raw_output_list_t, libbitcoin::wallet::raw_output, raw_output_list)

extern "C" {
KTH_LIST_DEFINE(wallet, raw_output_list_t, raw_output_t, raw_output_list, libbitcoin::wallet::raw_output, wallet_raw_output_const_cpp)
} // extern "C"
