// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#ifndef KTH_NODECINT_CONVERSIONS_HPP_
#define KTH_NODECINT_CONVERSIONS_HPP_

#include <vector>

#include <knuth/nodecint/list_creator.h>
#include <knuth/nodecint/primitives.h>
#include <knuth/nodecint/type_conversions.h>

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

KTH_CONV_DECLARE(chain, block_t, libbitcoin::message::block, block)
KTH_CONV_DECLARE(chain, header_t, libbitcoin::message::header, header)
KTH_CONV_DECLARE(chain, input_t, libbitcoin::chain::input, input)
KTH_CONV_DECLARE(chain, output_t, libbitcoin::chain::output, output)
KTH_CONV_DECLARE(chain, output_point_t, libbitcoin::chain::output_point, output_point)
KTH_CONV_DECLARE(chain, script_t, libbitcoin::chain::script, script)
KTH_CONV_DECLARE(chain, transaction_t, libbitcoin::message::transaction, transaction)
KTH_CONV_DECLARE(chain, point_t, libbitcoin::chain::point, point)
KTH_CONV_DECLARE(chain, mempool_transaction_t, libbitcoin::blockchain::mempool_transaction_summary, mempool_transaction)
KTH_CONV_DECLARE(chain, history_compact_t, libbitcoin::chain::history_compact, history_compact)
KTH_CONV_DECLARE(chain, stealth_compact_t, libbitcoin::chain::stealth_compact, stealth_compact)
KTH_CONV_DECLARE(wallet, payment_address_t, libbitcoin::wallet::payment_address, payment_address)

//Note: block_list_t created with this function has not have to destruct it...
// KTH_LIST_DECLARE_CONSTRUCT_FROM_CPP(chain, block_list_t, libbitcoin::message::block, block_list)
KTH_LIST_DECLARE_CONSTRUCT_FROM_CPP(chain, input_list_t, libbitcoin::chain::input, input_list)
KTH_LIST_DECLARE_CONSTRUCT_FROM_CPP(chain, output_list_t, libbitcoin::chain::output, output_list)
KTH_LIST_DECLARE_CONSTRUCT_FROM_CPP(chain, transaction_list_t, libbitcoin::message::transaction, transaction_list)
KTH_LIST_DECLARE_CONSTRUCT_FROM_CPP(core, hash_list_t, libbitcoin::hash_digest, hash_list)

KTH_LIST_DECLARE_CONVERTERS(chain, block_list_t, libbitcoin::message::block, block_list)
KTH_LIST_DECLARE_CONVERTERS(chain, point_list_t, libbitcoin::chain::point, point_list)
KTH_LIST_DECLARE_CONVERTERS(chain, input_list_t, libbitcoin::chain::input, input_list)
KTH_LIST_DECLARE_CONVERTERS(chain, output_list_t, libbitcoin::chain::output, output_list)
KTH_LIST_DECLARE_CONVERTERS(chain, transaction_list_t, libbitcoin::message::transaction, transaction_list)
KTH_LIST_DECLARE_CONVERTERS(core, hash_list_t, libbitcoin::hash_digest, hash_list)
KTH_LIST_DECLARE_CONVERTERS(chain, block_indexes_t, uint64_t, block_indexes)

// Wallet.
// ------------------------------------------------------------------------------------
// KTH_CONV_DECLARE(wallet, ec_public_t, libbitcoin::wallet::ec_public, ec_public)
KTH_CONV_DECLARE(wallet, raw_output_t, libbitcoin::wallet::raw_output, raw_output)
KTH_LIST_DECLARE_CONVERTERS(wallet, raw_output_list_t, libbitcoin::wallet::raw_output, raw_output_list)


#endif /* KTH_NODECINT_CONVERSIONS_HPP_ */
