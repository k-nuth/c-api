// Copyright (c) 2016-2023 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/capi/chain/chain_sync.h>
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

kth_error_code_t kth_chain_sync_last_height(kth_chain_t chain, kth_size_t* out_height) {
    std::latch latch(1); //Note: workaround to fix an error on some versions of Boost.Threads

    kth_error_code_t res;
    safe_chain(chain).fetch_last_height([&](std::error_code const& ec, size_t h) {
       *out_height = h;
       res = kth::to_c_err(ec);
       latch.count_down();
    });

    latch.wait();
    return res;
}

kth_error_code_t kth_chain_sync_block_height(kth_chain_t chain, kth_hash_t hash, kth_size_t* out_height) {
    std::latch latch(1); //Note: workaround to fix an error on some versions of Boost.Threads
    kth_error_code_t res;

    auto hash_cpp = kth::to_array(hash.hash);

    safe_chain(chain).fetch_block_height(hash_cpp, [&](std::error_code const& ec, size_t h) {
        *out_height = h;
        res = kth::to_c_err(ec);
        latch.count_down();
    });

    latch.wait();
    return res;
}

kth_error_code_t kth_chain_sync_block_header_by_height(kth_chain_t chain, kth_size_t height, kth_header_t* out_header, kth_size_t* out_height) {
    std::latch latch(1); //Note: workaround to fix an error on some versions of Boost.Threads
    kth_error_code_t res;

    safe_chain(chain).fetch_block_header(height, [&](std::error_code const& ec, kth::domain::message::header::ptr header, size_t h) {
        *out_header = kth::leak_if_success(header, ec);
        *out_height = h;
        res = kth::to_c_err(ec);
        latch.count_down();
    });

    latch.wait();
    return res;
}

kth_error_code_t kth_chain_sync_block_header_by_hash(kth_chain_t chain, kth_hash_t hash, kth_header_t* out_header, kth_size_t* out_height) {
    std::latch latch(1); //Note: workaround to fix an error on some versions of Boost.Threads
    kth_error_code_t res;

    auto hash_cpp = kth::to_array(hash.hash);

    safe_chain(chain).fetch_block_header(hash_cpp, [&](std::error_code const& ec, kth::domain::message::header::ptr header, size_t h) {
        *out_header = kth::leak_if_success(header, ec);
        *out_height = h;
        res = kth::to_c_err(ec);
        latch.count_down();
    });

    latch.wait();
    return res;
}

kth_error_code_t kth_chain_sync_block_by_height(kth_chain_t chain, kth_size_t height, kth_block_t* out_block, kth_size_t* out_height) {
    std::latch latch(1); //Note: workaround to fix an error on some versions of Boost.Threads
    kth_error_code_t res;

    safe_chain(chain).fetch_block(height, kth::witness(), [&](std::error_code const& ec, kth::domain::message::block::const_ptr block, size_t h) {
        if (ec == kth::error::success) {
            *out_block = kth::leak_if_success(block, ec);
        } else {
            *out_block = nullptr;
        }

        *out_height = h;
        res = kth::to_c_err(ec);
        latch.count_down();
    });

    latch.wait();
    return res;
}

kth_error_code_t kth_chain_sync_block_by_hash(kth_chain_t chain, kth_hash_t hash, kth_block_t* out_block, kth_size_t* out_height) {
    std::latch latch(1); //Note: workaround to fix an error on some versions of Boost.Threads
    kth_error_code_t res;

    auto hash_cpp = kth::to_array(hash.hash);

    safe_chain(chain).fetch_block(hash_cpp, kth::witness(), [&](std::error_code const& ec, kth::domain::message::block::const_ptr block, size_t h) {
        if (ec == kth::error::success) {
            *out_block = kth::leak_if_success(block, ec);
        } else {
            *out_block = nullptr;
        }

        *out_height = h;
        res = kth::to_c_err(ec);
        latch.count_down();
    });

    latch.wait();
    return res;
}

kth_error_code_t kth_chain_sync_block_header_byhash_txs_size(kth_chain_t chain, kth_hash_t hash, kth_header_t* out_header, uint64_t* out_block_height, kth_hash_list_t* out_tx_hashes, uint64_t* out_serialized_size) {
    std::latch latch(1); //Note: workaround to fix an error on some versions of Boost.Threads
    kth_error_code_t res;

    auto hash_cpp = kth::to_array(hash.hash);

    safe_chain(chain).fetch_block_header_txs_size(hash_cpp, [&](std::error_code const& ec, kth::domain::message::header::const_ptr header, size_t block_height, std::shared_ptr<kth::hash_list> tx_hashes, uint64_t block_serialized_size) {
        *out_header = kth::leak_if_success(header, ec);
        *out_block_height = block_height;
        *out_tx_hashes = kth::leak_if_success(tx_hashes, ec);
        *out_serialized_size = block_serialized_size;
        res = kth::to_c_err(ec);
        latch.count_down();
    });

    latch.wait();
    return res;
}

kth_error_code_t kth_chain_sync_merkle_block_by_height(kth_chain_t chain, kth_size_t height, kth_merkleblock_t* out_block, kth_size_t* out_height) {
    std::latch latch(1); //Note: workaround to fix an error on some versions of Boost.Threads
    kth_error_code_t res;

    safe_chain(chain).fetch_merkle_block(height, [&](std::error_code const& ec, kth::domain::message::merkle_block::const_ptr block, size_t h) {
        *out_block = kth::leak_if_success(block, ec);
        *out_height = h;
        res = kth::to_c_err(ec);
        latch.count_down();
    });

    latch.wait();
    return res;
}

kth_error_code_t kth_chain_sync_merkle_block_by_hash(kth_chain_t chain, kth_hash_t hash, kth_merkleblock_t* out_block, kth_size_t* out_height) {
    std::latch latch(1); //Note: workaround to fix an error on some versions of Boost.Threads
    kth_error_code_t res;

    auto hash_cpp = kth::to_array(hash.hash);

    safe_chain(chain).fetch_merkle_block(hash_cpp, [&](std::error_code const& ec, kth::domain::message::merkle_block::const_ptr block, size_t h) {
        *out_block = kth::leak_if_success(block, ec);
        *out_height = h;
        res = kth::to_c_err(ec);
        latch.count_down();
    });

    latch.wait();
    return res;
}

kth_error_code_t kth_chain_sync_compact_block_by_height(kth_chain_t chain, kth_size_t height, kth_compact_block_t* out_block, kth_size_t* out_height) {
    std::latch latch(1); //Note: workaround to fix an error on some versions of Boost.Threads
    kth_error_code_t res;

    safe_chain(chain).fetch_compact_block(height, [&](std::error_code const& ec, kth::domain::message::compact_block::const_ptr block, size_t h) {
        *out_block = kth::leak_if_success(block, ec);
        *out_height = h;
        res = kth::to_c_err(ec);
        latch.count_down();
    });

    latch.wait();
    return res;
}

kth_error_code_t kth_chain_sync_compact_block_by_hash(kth_chain_t chain, kth_hash_t hash, kth_compact_block_t* out_block, kth_size_t* out_height) {
    std::latch latch(1); //Note: workaround to fix an error on some versions of Boost.Threads
    kth_error_code_t res;

    auto hash_cpp = kth::to_array(hash.hash);

    safe_chain(chain).fetch_compact_block(hash_cpp, [&](std::error_code const& ec, kth::domain::message::compact_block::const_ptr block, size_t h) {
        *out_block = kth::leak_if_success(block, ec);
        *out_height = h;
        res = kth::to_c_err(ec);
        latch.count_down();
    });

    latch.wait();
    return res;
}

kth_error_code_t kth_chain_sync_block_by_height_timestamp(kth_chain_t chain, kth_size_t height, kth_hash_t* out_hash, uint32_t* out_timestamp) {
    std::latch latch(1); //Note: workaround to fix an error on some versions of Boost.Threads
    kth_error_code_t res;

    safe_chain(chain).fetch_block_hash_timestamp(height, [&](std::error_code const& ec, kth::hash_digest const& hash, uint32_t timestamp, size_t h) {
        if (ec == kth::error::success) {
            kth::copy_c_hash(hash, out_hash);
            *out_timestamp = timestamp;
        } else {
            kth::copy_c_hash(kth::null_hash, out_hash);
            *out_timestamp = 0;
        }

        res = kth::to_c_err(ec);
        latch.count_down();
    });

    latch.wait();
    return res;
}



kth_error_code_t kth_chain_sync_block_hash(kth_chain_t chain, kth_size_t height, kth_hash_t* out_hash) {
    kth::hash_digest block_hash;
    bool found_block = safe_chain(chain).get_block_hash(block_hash, height);
    if( ! found_block ) {
        return kth_ec_not_found;
    }
    kth::copy_c_hash(block_hash, out_hash);
    return kth_ec_success;
}

kth_error_code_t kth_chain_sync_transaction(kth_chain_t chain, kth_hash_t hash, int require_confirmed, kth_transaction_t* out_transaction, kth_size_t* out_height, kth_size_t* out_index) {
    std::latch latch(1); //Note: workaround to fix an error on some versions of Boost.Threads
    kth_error_code_t res;

    auto hash_cpp = kth::to_array(hash.hash);

    safe_chain(chain).fetch_transaction(hash_cpp, kth::int_to_bool(require_confirmed), kth::witness(), [&](std::error_code const& ec, kth::domain::message::transaction::const_ptr transaction, size_t i, size_t h) {
        *out_transaction = kth::leak_if_success(transaction, ec);
        *out_height = h;
        *out_index = i;
        res = kth::to_c_err(ec);
        latch.count_down();
    });

    latch.wait();
    return res;
}

kth_error_code_t kth_chain_sync_transaction_position(kth_chain_t chain, kth_hash_t hash, int require_confirmed, kth_size_t* out_position, kth_size_t* out_height) {
    std::latch latch(1); //Note: workaround to fix an error on some versions of Boost.Threads
    kth_error_code_t res;

    auto hash_cpp = kth::to_array(hash.hash);

    safe_chain(chain).fetch_transaction_position(hash_cpp, kth::int_to_bool(require_confirmed), [&](std::error_code const& ec, size_t position, size_t height) {
        *out_height = height;
        *out_position = position;
        res = kth::to_c_err(ec);
        latch.count_down();
    });

    latch.wait();
    return res;
}

kth_error_code_t kth_chain_sync_spend(kth_chain_t chain, kth_outputpoint_t op, kth_inputpoint_t* out_input_point) {
    std::latch latch(1); //Note: workaround to fix an error on some versions of Boost.Threads
    kth_error_code_t res;

    auto* outpoint_cpp = static_cast<kth::domain::chain::output_point*>(op);

    safe_chain(chain).fetch_spend(*outpoint_cpp, [&](std::error_code const& ec, kth::domain::chain::input_point input_point) {
        *out_input_point = kth::leak_if_success(input_point, ec);
        res = kth::to_c_err(ec);
        latch.count_down();
    });

    latch.wait();
    return res;
}

kth_error_code_t kth_chain_sync_history(kth_chain_t chain, kth_payment_address_t address, kth_size_t limit, kth_size_t from_height, kth_history_compact_list_t* out_history) {
    std::latch latch(1); //Note: workaround to fix an error on some versions of Boost.Threads
    kth_error_code_t res;

    safe_chain(chain).fetch_history(kth_wallet_payment_address_const_cpp(address).hash20(), limit, from_height, [&](std::error_code const& ec, kth::domain::chain::history_compact::list history) {
        *out_history = kth::leak_if_success(history, ec);
        res = kth::to_c_err(ec);
        latch.count_down();
    });

    latch.wait();
    return res;
}

kth_error_code_t kth_chain_sync_confirmed_transactions(kth_chain_t chain, kth_payment_address_t address, uint64_t max, uint64_t start_height, kth_hash_list_t* out_tx_hashes) {
    std::latch latch(1); //Note: workaround to fix an error on some versions of Boost.Threads
    kth_error_code_t res;

    safe_chain(chain).fetch_confirmed_transactions(kth_wallet_payment_address_const_cpp(address).hash20(), max, start_height, [&](std::error_code const& ec, const std::vector<kth::hash_digest>& txs) {
        *out_tx_hashes = kth::leak_if_success(txs, ec);
        res = kth::to_c_err(ec);
        latch.count_down();
    });

    latch.wait();
    return res;
}

// kth_error_code_t kth_chain_sync_stealth(kth_chain_t chain, kth_binary_t filter, uint64_t from_height, kth_stealth_compact_list_t* out_list) {
//     std::latch latch(1); //Note: workaround to fix an error on some versions of Boost.Threads
//     kth_error_code_t res;

// 	auto* filter_cpp_ptr = static_cast<kth::binary const*>(filter);
// 	kth::binary const& filter_cpp  = *filter_cpp_ptr;

//     safe_chain(chain).fetch_stealth(filter_cpp, from_height, [&](std::error_code const& ec, kth::domain::chain::stealth_compact::list stealth) {
//         *out_list = kth::leak_if_success(stealth, ec);
//         res = kth::to_c_err(ec);
//         latch.count_down();
//     });

//     latch.wait();
//     return res;
// }

// ------------------------------------------------------------------

kth_mempool_transaction_list_t kth_chain_sync_mempool_transactions(kth_chain_t chain, kth_payment_address_t address, kth_bool_t use_testnet_rules) {
    auto const& address_cpp = kth_wallet_payment_address_const_cpp(address);
    if (address_cpp) {
        auto txs = safe_chain(chain).get_mempool_transactions(address_cpp.encoded_cashaddr(false), kth::int_to_bool(use_testnet_rules), kth::witness());
        auto ret_txs = kth::leak(txs);
        return static_cast<kth_mempool_transaction_list_t>(ret_txs);
    }
    auto ret_txs = new std::vector<kth::blockchain::mempool_transaction_summary>();
    return static_cast<kth_mempool_transaction_list_t>(ret_txs);
}

kth_transaction_list_t kth_chain_sync_mempool_transactions_from_wallets(kth_chain_t chain, kth_payment_address_list_t addresses, kth_bool_t use_testnet_rules) {
    auto const& addresses_cpp = *static_cast<std::vector<kth::domain::wallet::payment_address> const*>(addresses);
    auto txs = safe_chain(chain).get_mempool_transactions_from_wallets(addresses_cpp, kth::int_to_bool(use_testnet_rules), kth::witness());
    return kth::move_or_copy_and_leak(std::move(txs));
}

// Organizers.
//-------------------------------------------------------------------------

int kth_chain_sync_organize_block(kth_chain_t chain, kth_block_t block) {
    std::latch latch(1); //Note: workaround to fix an error on some versions of Boost.Threads
    kth_error_code_t res;

    safe_chain(chain).organize(block_shared(block), [&](std::error_code const& ec) {
        res = kth::to_c_err(ec);
        latch.count_down();
    });

    latch.wait();
    return res;
}

int kth_chain_sync_organize_transaction(kth_chain_t chain, kth_transaction_t transaction) {
    std::latch latch(1); //Note: workaround to fix an error on some versions of Boost.Threads
    kth_error_code_t res;

    safe_chain(chain).organize(tx_shared(transaction), [&](std::error_code const& ec) {
        res = kth::to_c_err(ec);
        latch.count_down();
    });

    latch.wait();
    return res;
}

//-------------------------------------------------------------------------

} // extern "C"
