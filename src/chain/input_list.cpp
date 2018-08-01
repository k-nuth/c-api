/**
 * Copyright (c) 2016-2018 Bitprim Inc.
 *
 * This file is part of Bitprim.
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

#include <bitprim/nodecint/chain/input_list.h>

#include <bitcoin/bitcoin/chain/input.hpp>
#include <bitprim/nodecint/chain/input.h>
#include <bitprim/nodecint/conversions.hpp>


BITPRIM_LIST_DEFINE_CONVERTERS(chain, input_list_t, libbitcoin::chain::input, input_list)
BITPRIM_LIST_DEFINE_CONSTRUCT_FROM_CPP(chain, input_list_t, libbitcoin::chain::input, input_list)

extern "C" {

BITPRIM_LIST_DEFINE(chain, input_list_t, input_t, input_list, libbitcoin::chain::input, chain_input_const_cpp)

} // extern "C"
