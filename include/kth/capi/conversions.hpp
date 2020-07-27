// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#ifndef KTH_CAPI_CONVERSIONS_HPP_
#define KTH_CAPI_CONVERSIONS_HPP_

#include <vector>

#include <kth/capi/list_creator.h>
#include <kth/capi/primitives.h>
#include <kth/capi/type_conversions.h>

#include <kth/domain/chain/input.hpp>
#include <kth/domain/chain/output.hpp>
#include <kth/domain/chain/output_point.hpp>
#include <kth/domain/chain/script.hpp>
#include <kth/domain/message/block.hpp>
#include <kth/domain/message/header.hpp>
#include <kth/domain/message/transaction.hpp>
// #include <kth/domain/wallet/ec_public.hpp>
#include <kth/domain/wallet/transaction_functions.hpp>
#include <kth/blockchain/interface/safe_chain.hpp>

KTH_CONV_DECLARE(chain, block_t, kth::domain::message::block, block)
KTH_CONV_DECLARE(chain, header_t, kth::domain::message::header, header)
KTH_CONV_DECLARE(chain, input_t, kth::domain::chain::input, input)
KTH_CONV_DECLARE(chain, output_t, kth::domain::chain::output, output)
KTH_CONV_DECLARE(chain, output_point_t, kth::domain::chain::output_point, output_point)
KTH_CONV_DECLARE(chain, script_t, kth::domain::chain::script, script)
KTH_CONV_DECLARE(chain, transaction_t, kth::domain::message::transaction, transaction)
KTH_CONV_DECLARE(chain, point_t, kth::domain::chain::point, point)
KTH_CONV_DECLARE(chain, mempool_transaction_t, kth::blockchain::mempool_transaction_summary, mempool_transaction)
KTH_CONV_DECLARE(chain, history_compact_t, kth::domain::chain::history_compact, history_compact)
KTH_CONV_DECLARE(chain, stealth_compact_t, kth::domain::chain::stealth_compact, stealth_compact)
KTH_CONV_DECLARE(wallet, payment_address_t, kth::domain::wallet::payment_address, payment_address)

//Note: block_list_t created with this function has not have to destruct it...
// KTH_LIST_DECLARE_CONSTRUCT_FROM_CPP(chain, block_list_t, kth::domain::message::block, block_list)
KTH_LIST_DECLARE_CONSTRUCT_FROM_CPP(chain, input_list_t, kth::domain::chain::input, input_list)
KTH_LIST_DECLARE_CONSTRUCT_FROM_CPP(chain, output_list_t, kth::domain::chain::output, output_list)
KTH_LIST_DECLARE_CONSTRUCT_FROM_CPP(chain, transaction_list_t, kth::domain::message::transaction, transaction_list)
KTH_LIST_DECLARE_CONSTRUCT_FROM_CPP(core, hash_list_t, kth::hash_digest, hash_list)

KTH_LIST_DECLARE_CONVERTERS(chain, block_list_t, kth::domain::message::block, block_list)
KTH_LIST_DECLARE_CONVERTERS(chain, point_list_t, kth::domain::chain::point, point_list)
KTH_LIST_DECLARE_CONVERTERS(chain, input_list_t, kth::domain::chain::input, input_list)
KTH_LIST_DECLARE_CONVERTERS(chain, output_list_t, kth::domain::chain::output, output_list)
KTH_LIST_DECLARE_CONVERTERS(chain, transaction_list_t, kth::domain::message::transaction, transaction_list)
KTH_LIST_DECLARE_CONVERTERS(core, hash_list_t, kth::hash_digest, hash_list)
KTH_LIST_DECLARE_CONVERTERS(chain, block_indexes_t, uint64_t, block_indexes)

// Wallet.
// ------------------------------------------------------------------------------------
// KTH_CONV_DECLARE(wallet, ec_public_t, kth::domain::wallet::ec_public, ec_public)
KTH_CONV_DECLARE(wallet, raw_output_t, kth::domain::wallet::raw_output, raw_output)
KTH_LIST_DECLARE_CONVERTERS(wallet, raw_output_list_t, kth::domain::wallet::raw_output, raw_output_list)


#endif /* KTH_CAPI_CONVERSIONS_HPP_ */
