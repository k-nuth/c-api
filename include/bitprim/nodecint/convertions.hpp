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

#ifndef BITPRIM_NODECINT_CONVERTIONS_HPP_
#define BITPRIM_NODECINT_CONVERTIONS_HPP_

#include <vector>

#include <bitcoin/bitcoin/chain/input.hpp>
#include <bitcoin/bitcoin/chain/output.hpp>
#include <bitcoin/bitcoin/chain/output_point.hpp>
#include <bitcoin/bitcoin/chain/script.hpp>
#include <bitcoin/bitcoin/message/block.hpp>
#include <bitcoin/bitcoin/message/header.hpp>
#include <bitcoin/bitcoin/message/transaction.hpp>

libbitcoin::message::block const& chain_block_const_cpp(block_t block);
libbitcoin::message::block& chain_block_cpp(block_t block);

std::vector<libbitcoin::message::block> const& chain_block_list_const_cpp(block_list_t list);
std::vector<libbitcoin::message::block>& chain_block_list_cpp(block_list_t list);
//Note: block_list_t created with this function has not have to destruct it...
//block_list_t chain_block_list_construct_from_cpp(libbitcoin::message::block::list& list);

libbitcoin::message::header const& chain_header_const_cpp(header_t header);
libbitcoin::message::header& chain_header_cpp(header_t header);

libbitcoin::chain::input const& chain_input_const_cpp(input_t input);
libbitcoin::chain::input& chain_input_cpp(input_t input);

std::vector<libbitcoin::chain::input> const& chain_input_list_const_cpp(input_list_t list);
std::vector<libbitcoin::chain::input>& chain_input_list_cpp(input_list_t list);
//Note: input_list_t created with this function has not have to destruct it...
input_list_t chain_input_list_construct_from_cpp(libbitcoin::chain::input::list& list);

libbitcoin::chain::output const& chain_output_const_cpp(output_t output);
libbitcoin::chain::output& chain_output_cpp(output_t output);


std::vector<libbitcoin::chain::output> const& chain_output_list_const_cpp(output_list_t list);
std::vector<libbitcoin::chain::output>& chain_output_list_cpp(output_list_t list);
//Note: output_list_t created with this function has not have to destruct it...
output_list_t chain_output_list_construct_from_cpp(libbitcoin::chain::output::list& list);


libbitcoin::chain::output_point const& output_point_const_cpp(output_point_t op);
libbitcoin::chain::output_point& output_point_cpp(output_point_t op);



libbitcoin::chain::script const& chain_script_const_cpp(script_t s);
libbitcoin::chain::script& chain_script_cpp(script_t s);

libbitcoin::message::transaction const& chain_transaction_const_cpp(transaction_t transaction);
libbitcoin::message::transaction& chain_transaction_cpp(transaction_t transaction);



std::vector<libbitcoin::message::transaction> const& chain_transaction_list_const_cpp(transaction_list_t list);
std::vector<libbitcoin::message::transaction>& chain_transaction_list_cpp(transaction_list_t list);
//Note: transaction_list_t created with this function has not have to destruct it...
transaction_list_t chain_transaction_list_construct_from_cpp(libbitcoin::message::transaction::list& list);



std::vector<libbitcoin::hash_digest> const& chain_hash_list_const_cpp(hash_list_t list);
std::vector<libbitcoin::hash_digest>& chain_hash_list_cpp(hash_list_t list);
hash_list_t chain_hash_list_construct_from_cpp(std::vector<libbitcoin::hash_digest>& list);


std::vector<uint64_t /*size_t*/> const& chain_block_indexes_const_cpp(block_indexes_t list);
std::vector<uint64_t /*size_t*/>& chain_block_indexes_cpp(block_indexes_t list);


#endif /* BITPRIM_NODECINT_CONVERTIONS_HPP_ */
