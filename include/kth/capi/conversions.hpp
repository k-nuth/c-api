// Copyright (c) 2016-2023 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_CAPI_CONVERSIONS_HPP_
#define KTH_CAPI_CONVERSIONS_HPP_

#include <vector>

#include <kth/capi/list_creator.h>
#include <kth/capi/primitives.h>
#include <kth/capi/type_conversions.h>
#include <kth/capi/wallet/primitives.h>


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

KTH_CONV_DECLARE(chain, kth_block_t, kth::domain::message::block, block)
KTH_CONV_DECLARE(chain, kth_header_t, kth::domain::message::header, header)
KTH_CONV_DECLARE(chain, kth_input_t, kth::domain::chain::input, input)
KTH_CONV_DECLARE(chain, kth_output_t, kth::domain::chain::output, output)
KTH_CONV_DECLARE(chain, kth_outputpoint_t, kth::domain::chain::output_point, output_point)
KTH_CONV_DECLARE(chain, kth_script_t, kth::domain::chain::script, script)
KTH_CONV_DECLARE(chain, kth_transaction_t, kth::domain::message::transaction, transaction)
// KTH_CONV_DECLARE(chain, kth_transaction_t, kth::domain::chain::transaction, transaction)
KTH_CONV_DECLARE(chain, kth_point_t, kth::domain::chain::point, point)
KTH_CONV_DECLARE(chain, kth_mempool_transaction_t, kth::blockchain::mempool_transaction_summary, mempool_transaction)
KTH_CONV_DECLARE(chain, kth_history_compact_t, kth::domain::chain::history_compact, history_compact)
KTH_CONV_DECLARE(chain, kth_stealth_compact_t, kth::domain::chain::stealth_compact, stealth_compact)

//Note: kth_block_list_t created with this function has not have to destruct it...
// KTH_LIST_DECLARE_CONSTRUCT_FROM_CPP(chain, kth_block_list_t, kth::domain::message::block, block_list)
KTH_LIST_DECLARE_CONSTRUCT_FROM_CPP(chain, kth_input_list_t, kth::domain::chain::input, input_list)
KTH_LIST_DECLARE_CONSTRUCT_FROM_CPP(chain, kth_output_list_t, kth::domain::chain::output, output_list)
// KTH_LIST_DECLARE_CONSTRUCT_FROM_CPP(chain, kth_transaction_list_t, kth::domain::message::transaction, transaction_list)
KTH_LIST_DECLARE_CONSTRUCT_FROM_CPP(chain, kth_transaction_list_t, kth::domain::chain::transaction, transaction_list)
KTH_LIST_DECLARE_CONSTRUCT_FROM_CPP(core, kth_hash_list_t, kth::hash_digest, hash_list)


KTH_LIST_DECLARE_CONVERTERS(chain, kth_block_list_t, kth::domain::message::block, block_list)
KTH_LIST_DECLARE_CONVERTERS(chain, kth_point_list_t, kth::domain::chain::point, point_list)
KTH_LIST_DECLARE_CONVERTERS(chain, kth_input_list_t, kth::domain::chain::input, input_list)
KTH_LIST_DECLARE_CONVERTERS(chain, kth_output_list_t, kth::domain::chain::output, output_list)
// KTH_LIST_DECLARE_CONVERTERS(chain, kth_transaction_list_t, kth::domain::message::transaction, transaction_list)
KTH_LIST_DECLARE_CONVERTERS(chain, kth_transaction_list_t, kth::domain::chain::transaction, transaction_list)
KTH_LIST_DECLARE_CONVERTERS(core, kth_hash_list_t, kth::hash_digest, hash_list)
KTH_LIST_DECLARE_CONVERTERS(chain, kth_block_indexes_t, kth_size_t, block_indexes)

// Wallet.
// ------------------------------------------------------------------------------------
KTH_CONV_DECLARE(wallet, kth_raw_output_t, kth::domain::wallet::raw_output, raw_output)
KTH_CONV_DECLARE(wallet, kth_payment_address_t, kth::domain::wallet::payment_address, payment_address)
KTH_CONV_DECLARE(wallet, kth_ec_private_t, kth::domain::wallet::ec_private, ec_private)
KTH_CONV_DECLARE(wallet, kth_ec_public_t, kth::domain::wallet::ec_public, ec_public)

KTH_LIST_DECLARE_CONVERTERS(wallet, kth_raw_output_list_t, kth::domain::wallet::raw_output, raw_output_list)

#endif /* KTH_CAPI_CONVERSIONS_HPP_ */
