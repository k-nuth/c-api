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

#include <tuple>

#include <bitcoin/blockchain/interface/safe_chain.hpp>
#include <bitprim/nodecint/helpers.hpp>


libbitcoin::blockchain::mempool_transaction_summary const& chain_mempool_transaction_const_cpp(mempool_transaction_t tx) {
    return *static_cast<libbitcoin::blockchain::mempool_transaction_summary const*>(tx);
}

//libbitcoin::chain::point& history_compact_cpp(history_compact_t point) {
//    return *static_cast<libbitcoin::chain::point*>(point);
//}


// ---------------------------------------------------------------------------
extern "C" {

char const* chain_mempool_transaction_address(mempool_transaction_t tx) {
    auto tx_address_str = chain_mempool_transaction_const_cpp(tx).address();
    return bitprim::create_c_str(tx_address_str);
}

char const* chain_mempool_transaction_hash(mempool_transaction_t tx) {
    auto tx_hash_str = chain_mempool_transaction_const_cpp(tx).hash();
    return bitprim::create_c_str(tx_hash_str);
}

uint64_t chain_mempool_transaction_index(mempool_transaction_t tx) {
    return chain_mempool_transaction_const_cpp(tx).index();
}

char const* chain_mempool_transaction_satoshis(mempool_transaction_t tx) {
    auto tx_satoshis_str = chain_mempool_transaction_const_cpp(tx).satoshis();
    return bitprim::create_c_str(tx_satoshis_str);
}

uint64_t chain_mempool_transaction_timestamp(mempool_transaction_t tx) {
    return chain_mempool_transaction_const_cpp(tx).timestamp();
}

char const* chain_mempool_transaction_prev_output_id(mempool_transaction_t tx) {
    auto tx_prev_output_id_str = chain_mempool_transaction_const_cpp(tx).previous_output_hash();
    return bitprim::create_c_str(tx_prev_output_id_str);
}

char const* chain_mempool_transaction_prev_output_index(mempool_transaction_t tx) {
    auto tx_prev_output_index_str = chain_mempool_transaction_const_cpp(tx).previous_output_index();
    return bitprim::create_c_str(tx_prev_output_index_str);
}

} // extern "C"



