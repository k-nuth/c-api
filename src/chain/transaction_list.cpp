/**
 * Copyright (c) 2017 Bitprim developers (see AUTHORS)
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

#include <bitprim/nodecint/chain/transaction_list.h>

#include <bitprim/nodecint/convertions.hpp>
#include <bitprim/nodecint/chain/transaction.h>


//namespace {

std::vector<libbitcoin::message::transaction> const& chain_transaction_list_const_cpp(transaction_list_t list) {
    return *static_cast<std::vector<libbitcoin::message::transaction> const*>(list);
}

std::vector<libbitcoin::message::transaction>& chain_transaction_list_cpp(transaction_list_t list) {
    return *static_cast<std::vector<libbitcoin::message::transaction>*>(list);
}

//} /* end of anonymous namespace */


transaction_list_t chain_transaction_list_construct_from_cpp(std::vector<libbitcoin::message::transaction>& list) {
    return &list;
}

extern "C" {

transaction_list_t chain_transaction_list_construct_default() {
    return new std::vector<libbitcoin::message::transaction>();
}

void chain_transaction_list_push_back(transaction_list_t list, transaction_t transaction) {
    chain_transaction_list_cpp(list).push_back(chain_transaction_const_cpp(transaction));
}

void chain_transaction_list_destruct(transaction_list_t list) {
    delete &chain_transaction_list_cpp(list);
}

uint64_t /*size_t*/ chain_transaction_list_count(transaction_list_t list) {
    return chain_transaction_list_const_cpp(list).size();
}

transaction_t chain_transaction_list_nth(transaction_list_t list, uint64_t /*size_t*/ n) {
    auto &x = chain_transaction_list_cpp(list)[n];
    return &x;
}

} /* extern "C" */
