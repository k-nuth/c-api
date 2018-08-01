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

#ifndef BITPRIM_NODECINT_CONVERSIONS_HPP_
#define BITPRIM_NODECINT_CONVERSIONS_HPP_

#include <vector>

#include <bitprim/nodecint/list_creator.h>
#include <bitprim/nodecint/primitives.h>
#include <bitprim/nodecint/type_conversions.h>

#include <bitcoin/bitcoin/chain/input.hpp>
#include <bitcoin/bitcoin/chain/output.hpp>
#include <bitcoin/bitcoin/chain/output_point.hpp>
#include <bitcoin/bitcoin/chain/script.hpp>
#include <bitcoin/bitcoin/message/block.hpp>
#include <bitcoin/bitcoin/message/header.hpp>
#include <bitcoin/bitcoin/message/transaction.hpp>
// #include <bitcoin/bitcoin/wallet/ec_public.hpp>
#include <bitcoin/bitcoin/wallet/transaction_functions.hpp>
#include <bitcoin/blockchain/interface/safe_chain.hpp>

BITPRIM_CONV_DECLARE(chain, block_t, libbitcoin::message::block, block)
BITPRIM_CONV_DECLARE(chain, header_t, libbitcoin::message::header, header)
BITPRIM_CONV_DECLARE(chain, input_t, libbitcoin::chain::input, input)
BITPRIM_CONV_DECLARE(chain, output_t, libbitcoin::chain::output, output)
BITPRIM_CONV_DECLARE(chain, output_point_t, libbitcoin::chain::output_point, output_point)
BITPRIM_CONV_DECLARE(chain, script_t, libbitcoin::chain::script, script)
BITPRIM_CONV_DECLARE(chain, transaction_t, libbitcoin::message::transaction, transaction)
BITPRIM_CONV_DECLARE(chain, point_t, libbitcoin::chain::point, point)
BITPRIM_CONV_DECLARE(chain, mempool_transaction_t, libbitcoin::blockchain::mempool_transaction_summary, mempool_transaction)
BITPRIM_CONV_DECLARE(chain, history_compact_t, libbitcoin::chain::history_compact, history_compact)
BITPRIM_CONV_DECLARE(chain, stealth_compact_t, libbitcoin::chain::stealth_compact, stealth_compact)
BITPRIM_CONV_DECLARE(wallet, payment_address_t, libbitcoin::wallet::payment_address, payment_address)

//Note: block_list_t created with this function has not have to destruct it...
// BITPRIM_LIST_DECLARE_CONSTRUCT_FROM_CPP(chain, block_list_t, libbitcoin::message::block, block_list)
BITPRIM_LIST_DECLARE_CONSTRUCT_FROM_CPP(chain, input_list_t, libbitcoin::chain::input, input_list)
BITPRIM_LIST_DECLARE_CONSTRUCT_FROM_CPP(chain, output_list_t, libbitcoin::chain::output, output_list)
BITPRIM_LIST_DECLARE_CONSTRUCT_FROM_CPP(chain, transaction_list_t, libbitcoin::message::transaction, transaction_list)
BITPRIM_LIST_DECLARE_CONSTRUCT_FROM_CPP(core, hash_list_t, libbitcoin::hash_digest, hash_list)

BITPRIM_LIST_DECLARE_CONVERTERS(chain, block_list_t, libbitcoin::message::block, block_list)
BITPRIM_LIST_DECLARE_CONVERTERS(chain, point_list_t, libbitcoin::chain::point, point_list)
BITPRIM_LIST_DECLARE_CONVERTERS(chain, input_list_t, libbitcoin::chain::input, input_list)
BITPRIM_LIST_DECLARE_CONVERTERS(chain, output_list_t, libbitcoin::chain::output, output_list)
BITPRIM_LIST_DECLARE_CONVERTERS(chain, transaction_list_t, libbitcoin::message::transaction, transaction_list)
BITPRIM_LIST_DECLARE_CONVERTERS(core, hash_list_t, libbitcoin::hash_digest, hash_list)
BITPRIM_LIST_DECLARE_CONVERTERS(chain, block_indexes_t, uint64_t, block_indexes)

// Wallet.
// ------------------------------------------------------------------------------------
// BITPRIM_CONV_DECLARE(wallet, ec_public_t, libbitcoin::wallet::ec_public, ec_public)
BITPRIM_CONV_DECLARE(wallet, raw_output_t, libbitcoin::wallet::raw_output, raw_output)
BITPRIM_LIST_DECLARE_CONVERTERS(wallet, raw_output_list_t, libbitcoin::wallet::raw_output, raw_output_list)


#endif /* BITPRIM_NODECINT_CONVERSIONS_HPP_ */
