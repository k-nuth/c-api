// Copyright (c) 2016-2023 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/capi/chain/chain_async.h>
#include <cstdio>
#include <latch>
#include <memory>

// #include <boost/thread/latch.hpp>

#include <kth/domain/message/block.hpp>
#include <kth/domain/message/header.hpp>
#include <kth/domain/message/merkle_block.hpp>
#include <kth/domain/message/transaction.hpp>
#include <kth/blockchain/interface/safe_chain.hpp>

#include <kth/capi/chain/block_list.h>
#include <kth/capi/conversions.hpp>
#include <kth/capi/helpers.hpp>

namespace {

inline
kth::blockchain::safe_chain& safe_chain(kth_chain_t chain) {
    return *static_cast<kth::blockchain::safe_chain*>(chain);
}

inline
kth::domain::message::transaction::const_ptr tx_shared(kth_transaction_t tx) {
    auto const& tx_ref = *static_cast<kth::domain::message::transaction const*>(tx);
    auto* tx_new = new kth::domain::message::transaction(tx_ref);
    return kth::domain::message::transaction::const_ptr(tx_new);
}

// inline
// kth::domain::chain::transaction::const_ptr tx_shared(kth_transaction_t tx) {
//     auto const& tx_ref = *static_cast<kth::domain::chain::transaction const*>(tx);
//     auto* tx_new = new kth::domain::chain::transaction(tx_ref);
//     return kth::domain::chain::transaction::const_ptr(tx_new);
// }

inline
kth::domain::message::block::const_ptr block_shared(kth_block_t block) {
    auto const& block_ref = *static_cast<kth::domain::message::block const*>(block);
    auto* block_new = new kth::domain::message::block(block_ref);
    return kth::domain::message::block::const_ptr(block_new);
}

} /* end of anonymous namespace */


// ---------------------------------------------------------------------------
extern "C" {

void kth_chain_async_last_height(kth_chain_t chain, void* ctx, kth_last_height_fetch_handler_t handler) {
    safe_chain(chain).fetch_last_height([chain, ctx, handler](std::error_code const& ec, size_t h) {
        handler(chain, ctx, kth::to_c_err(ec), h);
    });
}

void kth_chain_async_block_height(kth_chain_t chain, void* ctx, kth_hash_t hash, kth_block_height_fetch_handler_t handler) {
    auto hash_cpp = kth::to_array(hash.hash);
    safe_chain(chain).fetch_block_height(hash_cpp, [chain, ctx, handler](std::error_code const& ec, size_t h) {
        handler(chain, ctx, kth::to_c_err(ec), h);
    });
}

void kth_chain_async_block_header_by_height(kth_chain_t chain, void* ctx, kth_size_t height, kth_block_header_fetch_handler_t handler) {
    safe_chain(chain).fetch_block_header(height, [chain, ctx, handler](std::error_code const& ec, kth::domain::message::header::ptr header, size_t h) {
        handler(chain, ctx, kth::to_c_err(ec), kth::leak_if_success(header, ec), h);
    });
}

void kth_chain_async_block_header_by_hash(kth_chain_t chain, void* ctx, kth_hash_t hash, kth_block_header_fetch_handler_t handler) {
    auto hash_cpp = kth::to_array(hash.hash);
    safe_chain(chain).fetch_block_header(hash_cpp, [chain, ctx, handler](std::error_code const& ec, kth::domain::message::header::ptr header, size_t h) {
        handler(chain, ctx, kth::to_c_err(ec), kth::leak_if_success(header, ec), h);
    });
}

void kth_chain_async_block_by_height(kth_chain_t chain, void* ctx, kth_size_t height, kth_block_fetch_handler_t handler) {
    safe_chain(chain).fetch_block(height, kth::witness(), [chain, ctx, handler](std::error_code const& ec, kth::domain::message::block::const_ptr block, size_t h) {
        handler(chain, ctx, kth::to_c_err(ec), kth::leak_if_success(block, ec), h);
    });
}

void kth_chain_async_block_by_hash(kth_chain_t chain, void* ctx, kth_hash_t hash, kth_block_fetch_handler_t handler) {
    auto hash_cpp = kth::to_array(hash.hash);
    safe_chain(chain).fetch_block(hash_cpp, kth::witness(), [chain, ctx, handler](std::error_code const& ec, kth::domain::message::block::const_ptr block, size_t h) {
        handler(chain, ctx, kth::to_c_err(ec), kth::leak_if_success(block, ec), h);
    });
}

void kth_chain_async_block_header_by_hash_txs_size(kth_chain_t chain, void* ctx, kth_hash_t hash, kth_block_header_txs_size_fetch_handler_t handler) {
    auto hash_cpp = kth::to_array(hash.hash);

    safe_chain(chain).fetch_block_header_txs_size(hash_cpp, [chain, ctx, handler](std::error_code const& ec, kth::domain::message::header::const_ptr header, size_t block_height, std::shared_ptr<kth::hash_list> tx_hashes, uint64_t block_serialized_size) {
        handler(chain, ctx, kth::to_c_err(ec), kth::leak_if_success(header, ec), block_height, kth::leak_if_success(tx_hashes, ec), block_serialized_size);
    });
}

void kth_chain_async_merkle_block_by_height(kth_chain_t chain, void* ctx, kth_size_t height, kth_merkleblock_fetch_handler_t handler) {
    safe_chain(chain).fetch_merkle_block(height, [chain, ctx, handler](std::error_code const& ec, kth::domain::message::merkle_block::const_ptr block, size_t h) {
        handler(chain, ctx, kth::to_c_err(ec), kth::leak_if_success(block, ec), h);
    });
}

void kth_chain_async_merkle_block_by_hash(kth_chain_t chain, void* ctx, kth_hash_t hash, kth_merkleblock_fetch_handler_t handler) {
    auto hash_cpp = kth::to_array(hash.hash);
    safe_chain(chain).fetch_merkle_block(hash_cpp, [chain, ctx, handler](std::error_code const& ec, kth::domain::message::merkle_block::const_ptr block, size_t h) {
        handler(chain, ctx, kth::to_c_err(ec), kth::leak_if_success(block, ec), h);
    });
}

void kth_chain_async_compact_block_by_height(kth_chain_t chain, void* ctx, kth_size_t height, kth_compact_block_fetch_handler_t handler) {
    safe_chain(chain).fetch_compact_block(height, [chain, ctx, handler](std::error_code const& ec, kth::domain::message::compact_block::const_ptr block, size_t h) {
        handler(chain, ctx, kth::to_c_err(ec), kth::leak_if_success(block, ec), h);
    });
}

void kth_chain_async_compact_block_by_hash(kth_chain_t chain, void* ctx, kth_hash_t hash, kth_compact_block_fetch_handler_t handler) {
    auto hash_cpp = kth::to_array(hash.hash);

    safe_chain(chain).fetch_compact_block(hash_cpp, [chain, ctx, handler](std::error_code const& ec, kth::domain::message::compact_block::const_ptr block, size_t h) {
        handler(chain, ctx, kth::to_c_err(ec), kth::leak_if_success(block, ec), h);
    });
}

void kth_chain_async_block_by_height_timestamp(kth_chain_t chain, void* ctx, kth_size_t height, kth_blockhash_timestamp_fetch_handler_t handler) {
    safe_chain(chain).fetch_block_hash_timestamp(height, [chain, ctx, handler](std::error_code const& ec, kth::hash_digest const& hash, uint32_t timestamp, size_t h) {
        if (ec == kth::error::success) {
            handler(chain, ctx, kth::to_c_err(ec), kth::to_hash_t(hash), timestamp, h);
        } else {
            handler(chain, ctx, kth::to_c_err(ec), kth::to_hash_t(kth::null_hash), 0, h);
        }
    });
}

void kth_chain_async_transaction(kth_chain_t chain, void* ctx, kth_hash_t hash, kth_bool_t require_confirmed, kth_transaction_fetch_handler_t handler) {
    //precondition:  [hash, 32] is a valid range
    auto hash_cpp = kth::to_array(hash.hash);
    safe_chain(chain).fetch_transaction(hash_cpp, kth::int_to_bool(require_confirmed), kth::witness(), [chain, ctx, handler](std::error_code const& ec, kth::domain::message::transaction::const_ptr transaction, size_t i, size_t h) {
        handler(chain, ctx, kth::to_c_err(ec), kth::leak_if_success(transaction, ec), i, h);
    });
}

void kth_chain_async_transaction_position(kth_chain_t chain, void* ctx, kth_hash_t hash, int require_confirmed, kth_transaction_index_fetch_handler_t handler) {
    auto hash_cpp = kth::to_array(hash.hash);

    safe_chain(chain).fetch_transaction_position(hash_cpp, kth::int_to_bool(require_confirmed), [chain, ctx, handler](std::error_code const& ec, size_t position, size_t height) {
        handler(chain, ctx, kth::to_c_err(ec), position, height);
    });
}

void kth_chain_async_spend(kth_chain_t chain, void* ctx, kth_outputpoint_t op, kth_spend_fetch_handler_t handler) {
    auto* outpoint_cpp = static_cast<kth::domain::chain::output_point*>(op);

    safe_chain(chain).fetch_spend(*outpoint_cpp, [chain, ctx, handler](std::error_code const& ec, kth::domain::chain::input_point input_point) {
        handler(chain, ctx, kth::to_c_err(ec), kth::leak_if_success(input_point, ec));
    });
}

void kth_chain_async_history(kth_chain_t chain, void* ctx, kth_payment_address_t address, kth_size_t limit, kth_size_t from_height, kth_history_fetch_handler_t handler) {
    safe_chain(chain).fetch_history(kth_wallet_payment_address_const_cpp(address).hash20(), limit, from_height, [chain, ctx, handler](std::error_code const& ec, kth::domain::chain::history_compact::list history) {
        handler(chain, ctx, kth::to_c_err(ec), kth::leak_if_success(history, ec));
    });
}

void kth_chain_async_confirmed_transactions(kth_chain_t chain, void* ctx, kth_payment_address_t address, uint64_t max, uint64_t start_height, kth_transactions_by_address_fetch_handler_t handler) {
    safe_chain(chain).fetch_confirmed_transactions(kth_wallet_payment_address_const_cpp(address).hash20(), max, start_height, [chain, ctx, handler](std::error_code const& ec, const std::vector<kth::hash_digest>& txs) {
        handler(chain, ctx, kth::to_c_err(ec), kth::leak_if_success(txs, ec));
    });
}

// void kth_chain_async_stealth(kth_chain_t chain, void* ctx, kth_binary_t filter, uint64_t from_height, kth_stealth_fetch_handler_t handler) {
// 	auto* filter_cpp_ptr = static_cast<kth::binary const*>(filter);
// 	kth::binary const& filter_cpp = *filter_cpp_ptr;

//     safe_chain(chain).fetch_stealth(filter_cpp, from_height, [chain, ctx, handler](std::error_code const& ec, kth::domain::chain::stealth_compact::list stealth) {
//         handler(chain, ctx, kth::to_c_err(ec), kth::leak_if_success(stealth, ec));
//     });
// }

// Organizers.
//-------------------------------------------------------------------------

void kth_chain_async_organize_block(kth_chain_t chain, void* ctx, kth_block_t block, kth_result_handler_t handler) {
    safe_chain(chain).organize(block_shared(block), [chain, ctx, handler](std::error_code const& ec) {
        handler(chain, ctx, kth::to_c_err(ec));
    });
}

void kth_chain_async_organize_transaction(kth_chain_t chain, void* ctx, kth_transaction_t transaction, kth_result_handler_t handler) {
    safe_chain(chain).organize(tx_shared(transaction), [chain, ctx, handler](std::error_code const& ec) {
        handler(chain, ctx, kth::to_c_err(ec));
    });
}

} // extern "C"
