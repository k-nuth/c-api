// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#include <knuth/nodecint/chain/input_list.h>

#include <bitcoin/bitcoin/chain/input.hpp>
#include <knuth/nodecint/chain/input.h>
#include <knuth/nodecint/conversions.hpp>


KTH_LIST_DEFINE_CONVERTERS(chain, input_list_t, libbitcoin::chain::input, input_list)
KTH_LIST_DEFINE_CONSTRUCT_FROM_CPP(chain, input_list_t, libbitcoin::chain::input, input_list)

extern "C" {

KTH_LIST_DEFINE(chain, input_list_t, input_t, input_list, libbitcoin::chain::input, chain_input_const_cpp)

} // extern "C"
