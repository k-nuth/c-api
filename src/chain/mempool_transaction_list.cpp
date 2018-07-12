/**
 * Copyright (c) 2018 Bitprim developers (see AUTHORS)
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

#include <bitprim/nodecint/chain/mempool_transaction_list.h>

#include <bitcoin/blockchain/interface/safe_chain.hpp>
#include <bitprim/nodecint/convertions.hpp>


std::vector<libbitcoin::blockchain::mempool_transaction_summary> const& chain_mempool_transaction_list_const_cpp(mempool_transaction_list_t list) {
    return *static_cast<std::vector<libbitcoin::blockchain::mempool_transaction_summary> const*>(list);
}

std::vector<libbitcoin::blockchain::mempool_transaction_summary>& chain_mempool_transaction_list_cpp(mempool_transaction_list_t list) {
    return *static_cast<std::vector<libbitcoin::blockchain::mempool_transaction_summary> *>(list);
}

mempool_transaction_list_t chain_mempool_transaction_list_construct_from_cpp(std::vector<libbitcoin::blockchain::mempool_transaction_summary>& list) {
    return &list;
}

// ---------------------------------------------------------------------------
extern "C" {

mempool_transaction_list_t chain_mempool_transaction_list_construct_default() {
    return new std::vector<libbitcoin::blockchain::mempool_transaction_summary>();
}

void chain_mempool_transaction_list_destruct(mempool_transaction_list_t list) {
    delete &chain_mempool_transaction_list_cpp(list);
}

uint64_t /*size_t*/ chain_mempool_transaction_list_count(mempool_transaction_list_t list) {
    return chain_mempool_transaction_list_const_cpp(list).size();
}

mempool_transaction_t chain_mempool_transaction_list_nth(mempool_transaction_list_t list, uint64_t /*size_t*/ n) {
    auto& x = chain_mempool_transaction_list_cpp(list)[n];
    return &x;
}

} // extern "C"
