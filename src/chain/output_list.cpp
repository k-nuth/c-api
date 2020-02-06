// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#include <knuth/nodecint/chain/output_list.h>

#include <knuth/nodecint/chain/output.h>
#include <knuth/nodecint/conversions.hpp>

KTH_LIST_DEFINE_CONVERTERS(chain, output_list_t, libbitcoin::chain::output, output_list)
KTH_LIST_DEFINE_CONSTRUCT_FROM_CPP(chain, output_list_t, libbitcoin::chain::output, output_list)

extern "C" {

KTH_LIST_DEFINE(chain, output_list_t, output_t, output_list, libbitcoin::chain::output, chain_output_const_cpp)

} // extern "C"
