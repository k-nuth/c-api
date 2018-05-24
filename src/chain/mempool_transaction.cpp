/**
 * Copyright (c) 2011-2017 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin.
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

#include <bitprim/nodecint/chain/mempool_transaction.h>

#include <bitprim/nodecint/helpers.hpp>
#include <bitcoin/blockchain/interface/safe_chain.hpp>
#include <tuple>


libbitcoin::blockchain::safe_chain::mempool_tx_summary const& chain_mempool_transaction_const_cpp(mempool_transaction_t tx) {
    return *static_cast<libbitcoin::blockchain::safe_chain::mempool_tx_summary const*>(tx);
}

//libbitcoin::chain::point& history_compact_cpp(history_compact_t point) {
//    return *static_cast<libbitcoin::chain::point*>(point);
//}


extern "C" {

char const* chain_mempool_transaction_address(mempool_transaction_t tx) {
    auto tx_cpp = chain_mempool_transaction_const_cpp(tx);
    std::string tx_address_str = std::get<0>(tx_cpp);
    return bitprim::create_c_str(tx_address_str);
}

char const* chain_mempool_transaction_hash(mempool_transaction_t tx) {
    auto tx_cpp = chain_mempool_transaction_const_cpp(tx);
    std::string tx_hash_str = std::get<1>(tx_cpp);
    return bitprim::create_c_str(tx_hash_str);
}

uint64_t chain_mempool_transaction_index(mempool_transaction_t tx) {
    auto tx_cpp = chain_mempool_transaction_const_cpp(tx);
    return std::get<2>(tx_cpp);
}

char const* chain_mempool_transaction_satoshis(mempool_transaction_t tx) {
    auto tx_cpp = chain_mempool_transaction_const_cpp(tx);
    std::string tx_satoshis_str = std::get<3>(tx_cpp);
    return bitprim::create_c_str(tx_satoshis_str);
}

uint64_t chain_mempool_transaction_timestamp(mempool_transaction_t tx) {
    auto tx_cpp = chain_mempool_transaction_const_cpp(tx);
    return std::get<4>(tx_cpp);
}

char const* chain_mempool_transaction_prev_output_id(mempool_transaction_t tx) {
    auto tx_cpp = chain_mempool_transaction_const_cpp(tx);
    std::string tx_prev_output_id_str = std::get<5>(tx_cpp);
    return bitprim::create_c_str(tx_prev_output_id_str);
}

char const* chain_mempool_transaction_prev_output_index(mempool_transaction_t tx) {
    auto tx_cpp = chain_mempool_transaction_const_cpp(tx);
    std::string tx_prev_output_index_str = std::get<6>(tx_cpp);
    return bitprim::create_c_str(tx_prev_output_index_str);
}

} /* extern "C" */



