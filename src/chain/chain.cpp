/**
* Copyright (c) 2016-2020 Knuth Project developers.
*
* This file is part of the Knuth Project.
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

#include <kth/capi/chain/chain.h>
#include <cstdio>
#include <memory>

#include <boost/thread/latch.hpp>

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
kth::blockchain::safe_chain& safe_chain(chain_t chain) {
    return *static_cast<kth::blockchain::safe_chain*>(chain);
}

inline
kth::domain::message::transaction::const_ptr tx_shared(transaction_t tx) {
    auto const& tx_ref = *static_cast<kth::domain::message::transaction const*>(tx);
    auto* tx_new = new kth::domain::message::transaction(tx_ref);
    return kth::domain::message::transaction::const_ptr(tx_new);
}

inline
kth::domain::message::block::const_ptr block_shared(block_t block) {
    auto const& block_ref = *static_cast<kth::domain::message::block const*>(block);
    auto* block_new = new kth::domain::message::block(block_ref);
    return kth::domain::message::block::const_ptr(block_new);
}

} /* end of anonymous namespace */


// ---------------------------------------------------------------------------
extern "C" {

void chain_fetch_last_height(chain_t chain, void* ctx, last_height_fetch_handler_t handler) {
    safe_chain(chain).fetch_last_height([chain, ctx, handler](std::error_code const& ec, size_t h) {
        handler(chain, ctx, kth::to_c_err(ec), h);
    });
}

error_code_t chain_get_last_height(chain_t chain, uint64_t* /*size_t*/ out_height) {
    boost::latch latch(2); //Note: workaround to fix an error on some versions of Boost.Threads

    error_code_t res;
    safe_chain(chain).fetch_last_height([&](std::error_code const& ec, size_t h) {
       *out_height = h;
       res = kth::to_c_err(ec);
       latch.count_down();
    });

    latch.count_down_and_wait();
    return res;
}

//void chain_fetch_block_height(chain_t chain, void* ctx, hash_t hash, block_height_fetch_handler_t handler) {
//
//    kth::hash_digest hash_cpp;
//    std::copy_n(hash, hash_cpp.size(), std::begin(hash_cpp));
//
//    safe_chain(chain).fetch_block_height(hash_cpp, [chain, ctx, handler](std::error_code const& ec, size_t h) {
//        handler(chain, ctx, kth::to_c_err(ec), h);
//    });
//}

void chain_fetch_block_height(chain_t chain, void* ctx, hash_t hash, block_height_fetch_handler_t handler) {

    auto hash_cpp = kth::to_array(hash.hash);
    // std::cout << "hash_cpp: " << kth::encode_hash(hash_cpp) << std::endl;
    
    safe_chain(chain).fetch_block_height(hash_cpp, [chain, ctx, handler](std::error_code const& ec, size_t h) {
        handler(chain, ctx, kth::to_c_err(ec), h);
    });
}

error_code_t chain_get_block_height(chain_t chain, hash_t hash, uint64_t* /*size_t*/ out_height) {
    boost::latch latch(2); //Note: workaround to fix an error on some versions of Boost.Threads
    error_code_t res;

    auto hash_cpp = kth::to_array(hash.hash);

    safe_chain(chain).fetch_block_height(hash_cpp, [&](std::error_code const& ec, size_t h) {
        *out_height = h;
        res = kth::to_c_err(ec);
        latch.count_down();
    });

    latch.count_down_and_wait();
    return res;
}

void chain_fetch_block_header_by_height(chain_t chain, void* ctx, uint64_t /*size_t*/ height, block_header_fetch_handler_t handler) {
    safe_chain(chain).fetch_block_header(height, [chain, ctx, handler](std::error_code const& ec, kth::domain::message::header::ptr header, size_t h) {
        auto new_header = new kth::domain::message::header(*header);
//        auto new_header = std::make_unique(*header).release();
        //Note: It is the responsability of the user to release/destruct the object
        handler(chain, ctx, kth::to_c_err(ec), new_header, h);
    });
}

error_code_t chain_get_block_header_by_height(chain_t chain, uint64_t /*size_t*/ height, header_t* out_header, uint64_t* /*size_t*/ out_height) {
    boost::latch latch(2); //Note: workaround to fix an error on some versions of Boost.Threads
    error_code_t res;

    safe_chain(chain).fetch_block_header(height, [&](std::error_code const& ec, kth::domain::message::header::ptr header, size_t h) {
        *out_header = new kth::domain::message::header(*header);
        //Note: It is the responsability of the user to release/destruct the object

        *out_height = h;
        res = kth::to_c_err(ec);
        latch.count_down();
    });

    latch.count_down_and_wait();
    return res;
}       

void chain_fetch_block_header_by_hash(chain_t chain, void* ctx, hash_t hash, block_header_fetch_handler_t handler) {

    auto hash_cpp = kth::to_array(hash.hash);

    safe_chain(chain).fetch_block_header(hash_cpp, [chain, ctx, handler](std::error_code const& ec, kth::domain::message::header::ptr header, size_t h) {
        auto new_header = new kth::domain::message::header(*header);
        //Note: It is the responsability of the user to release/destruct the object
        handler(chain, ctx, kth::to_c_err(ec), new_header, h);
    });
}

error_code_t chain_get_block_header_by_hash(chain_t chain, hash_t hash, header_t* out_header, uint64_t* /*size_t*/ out_height) {
    boost::latch latch(2); //Note: workaround to fix an error on some versions of Boost.Threads
    error_code_t res;

    auto hash_cpp = kth::to_array(hash.hash);

    safe_chain(chain).fetch_block_header(hash_cpp, [&](std::error_code const& ec, kth::domain::message::header::ptr header, size_t h) {
        *out_header = new kth::domain::message::header(*header);
        //Note: It is the responsability of the user to release/destruct the object

        *out_height = h;
        res = kth::to_c_err(ec);
        latch.count_down();
    });

    latch.count_down_and_wait();
    return res;
}

#if defined(KTH_DB_LEGACY) || defined(KTH_DB_NEW_BLOCKS) || defined(KTH_DB_NEW_FULL)
void chain_fetch_block_by_height(chain_t chain, void* ctx, uint64_t /*size_t*/ height, block_fetch_handler_t handler) {
#ifdef KTH_CURRENCY_BCH
    bool_t witness = 0;
#else
    bool_t witness = 1;
#endif
    safe_chain(chain).fetch_block(height, kth::int_to_bool(witness), [chain, ctx, handler](std::error_code const& ec, kth::domain::message::block::const_ptr block, size_t h) {
        if (ec == kth::error::success) {
            auto new_block = new kth::domain::message::block(*block);
            //Note: It is the responsability of the user to release/destruct the object
            handler(chain, ctx, kth::to_c_err(ec), new_block, h);
        } else {
            handler(chain, ctx, kth::to_c_err(ec), nullptr, h);
        }
    });
}

error_code_t chain_get_block_by_height(chain_t chain, uint64_t /*size_t*/ height, block_t* out_block, uint64_t* /*size_t*/ out_height) {
#ifdef KTH_CURRENCY_BCH
    bool_t witness = 0;
#else
    bool_t witness = 1;
#endif    
    boost::latch latch(2); //Note: workaround to fix an error on some versions of Boost.Threads
    error_code_t res;

    safe_chain(chain).fetch_block(height, kth::int_to_bool(witness), [&](std::error_code const& ec, kth::domain::message::block::const_ptr block, size_t h) {
        if (ec == kth::error::success) {
            //Note: It is the responsability of the user to release/destruct the object
            *out_block = new kth::domain::message::block(*block);
        } else {
            *out_block = nullptr;
        }

        *out_height = h;
        res = kth::to_c_err(ec);
        latch.count_down();
    });

    latch.count_down_and_wait();
    return res;
}

void chain_fetch_block_by_hash(chain_t chain, void* ctx, hash_t hash, block_fetch_handler_t handler) {
#ifdef KTH_CURRENCY_BCH
    bool_t witness = 0;
#else
    bool_t witness = 1;
#endif
    auto hash_cpp = kth::to_array(hash.hash);

    safe_chain(chain).fetch_block(hash_cpp, kth::int_to_bool(witness), [chain, ctx, handler](std::error_code const& ec, kth::domain::message::block::const_ptr block, size_t h) {
        if (ec == kth::error::success) {
            //Note: It is the responsability of the user to release/destruct the object
            auto new_block = new kth::domain::message::block(*block);
            handler(chain, ctx, kth::to_c_err(ec), new_block, h);
        } else {
            handler(chain, ctx, kth::to_c_err(ec), nullptr, h);
        }
    });
}

error_code_t chain_get_block_by_hash(chain_t chain, hash_t hash, block_t* out_block, uint64_t* /*size_t*/ out_height) {
#ifdef KTH_CURRENCY_BCH
    bool_t witness = 0;
#else
    bool_t witness = 1;
#endif    
    boost::latch latch(2); //Note: workaround to fix an error on some versions of Boost.Threads
    error_code_t res;

    auto hash_cpp = kth::to_array(hash.hash);

    safe_chain(chain).fetch_block(hash_cpp, kth::int_to_bool(witness), [&](std::error_code const& ec, kth::domain::message::block::const_ptr block, size_t h) {
        if (ec == kth::error::success) {
            //Note: It is the responsability of the user to release/destruct the object
            *out_block = new kth::domain::message::block(*block);
        } else {
            *out_block = nullptr;
        }

        *out_height = h;
        res = kth::to_c_err(ec);
        latch.count_down();
    });

    latch.count_down_and_wait();
    return res;
}

void chain_fetch_block_header_by_hash_txs_size(chain_t chain, void* ctx, hash_t hash, block_header_txs_size_fetch_handler_t handler) {

    auto hash_cpp = kth::to_array(hash.hash);

    safe_chain(chain).fetch_block_header_txs_size(hash_cpp, [chain, ctx, handler](std::error_code const& ec, kth::domain::message::header::const_ptr header, size_t block_height, const std::shared_ptr<kth::hash_list> tx_hashes, uint64_t block_serialized_size) {
        if (ec == kth::error::success) {
            //Note: It is the user's responsability of the user to release/destruct the object
            auto new_header = new kth::domain::message::header(*header);
            //Note: It is the user's responsability of the user to release/destruct the object
            auto new_tx_hashes = new kth::hash_list(*tx_hashes);
            handler(chain, ctx, kth::to_c_err(ec), new_header, block_height, new_tx_hashes, block_serialized_size);
        } else {
            handler(chain, ctx, kth::to_c_err(ec), nullptr, 0, nullptr, 0);
        }
    });
}

error_code_t chain_get_block_header_by_hash_txs_size(chain_t chain, hash_t hash, header_t* out_header, uint64_t* out_block_height, hash_list_t* out_tx_hashes, uint64_t* out_serialized_size) {
    boost::latch latch(2); //Note: workaround to fix an error on some versions of Boost.Threads
    error_code_t res;

    auto hash_cpp = kth::to_array(hash.hash);

    safe_chain(chain).fetch_block_header_txs_size(hash_cpp, [&](std::error_code const& ec, kth::domain::message::header::const_ptr header, size_t block_height, const std::shared_ptr<kth::hash_list> tx_hashes, uint64_t block_serialized_size) {
        if (ec == kth::error::success) {
            //Note: It is the user's responsability of the user to release/destruct the object
            *out_header = new kth::domain::message::header(*header);
            *out_block_height = block_height;
            //Note: It is the user's responsability of the user to release/destruct the object
            *out_tx_hashes = new kth::hash_list(*tx_hashes);
            *out_serialized_size = block_serialized_size;
        } else {
            *out_header = nullptr;
            *out_block_height = 0;
            *out_tx_hashes = nullptr;
            *out_serialized_size = 0;
        }

        res = kth::to_c_err(ec);
        latch.count_down();
    });

    latch.count_down_and_wait();
    return res;
}

void chain_fetch_merkle_block_by_height(chain_t chain, void* ctx, uint64_t /*size_t*/ height, merkle_block_fetch_handler_t handler) {
    safe_chain(chain).fetch_merkle_block(height, [chain, ctx, handler](std::error_code const& ec, kth::domain::message::merkle_block::const_ptr block, size_t h) {
        auto new_block = new kth::domain::message::merkle_block(*block);
        //Note: It is the responsibility of the user to release/destruct the object
        handler(chain, ctx, kth::to_c_err(ec), new_block, h);
    });
}

error_code_t chain_get_merkle_block_by_height(chain_t chain, uint64_t /*size_t*/ height, merkle_block_t* out_block, uint64_t* /*size_t*/ out_height) {
    boost::latch latch(2); //Note: workaround to fix an error on some versions of Boost.Threads
    error_code_t res;

    safe_chain(chain).fetch_merkle_block(height, [&](std::error_code const& ec, kth::domain::message::merkle_block::const_ptr block, size_t h) {
        *out_block = new kth::domain::message::merkle_block(*block);
        //Note: It is the responsability of the user to release/destruct the object

        *out_height = h;
        res = kth::to_c_err(ec);
        latch.count_down();
    });

    latch.count_down_and_wait();
    return res;
}

void chain_fetch_merkle_block_by_hash(chain_t chain, void* ctx, hash_t hash, merkle_block_fetch_handler_t handler) {
    auto hash_cpp = kth::to_array(hash.hash);

    safe_chain(chain).fetch_merkle_block(hash_cpp, [chain, ctx, handler](std::error_code const& ec, kth::domain::message::merkle_block::const_ptr block, size_t h) {
        auto new_block = new kth::domain::message::merkle_block(*block);
        handler(chain, ctx, kth::to_c_err(ec), new_block, h);
    });
}

error_code_t chain_get_merkle_block_by_hash(chain_t chain, hash_t hash, merkle_block_t* out_block, uint64_t* /*size_t*/ out_height) {
    boost::latch latch(2); //Note: workaround to fix an error on some versions of Boost.Threads
    error_code_t res;

    auto hash_cpp = kth::to_array(hash.hash);

    safe_chain(chain).fetch_merkle_block(hash_cpp, [&](std::error_code const& ec, kth::domain::message::merkle_block::const_ptr block, size_t h) {
        //Note: It is the responsability of the user to release/destruct the object
        *out_block = new kth::domain::message::merkle_block(*block);
        *out_height = h;
        res = kth::to_c_err(ec);
        latch.count_down();
    });

    latch.count_down_and_wait();
    return res;
}


void chain_fetch_compact_block_by_height(chain_t chain, void* ctx, uint64_t /*size_t*/ height, compact_block_fetch_handler_t handler) {
    safe_chain(chain).fetch_compact_block(height, [chain, ctx, handler](std::error_code const& ec, kth::domain::message::compact_block::const_ptr block, size_t h) {
        auto new_block = new kth::domain::message::compact_block(*block);
        //Note: It is the responsibility of the user to release/destruct the object
        handler(chain, ctx, kth::to_c_err(ec), new_block, h);
    });
}

error_code_t chain_get_compact_block_by_height(chain_t chain, uint64_t /*size_t*/ height, compact_block_t* out_block, uint64_t* /*size_t*/ out_height) {
    boost::latch latch(2); //Note: workaround to fix an error on some versions of Boost.Threads
    error_code_t res;

    safe_chain(chain).fetch_compact_block(height, [&](std::error_code const& ec, kth::domain::message::compact_block::const_ptr block, size_t h) {
        *out_block = new kth::domain::message::compact_block(*block);
        //Note: It is the responsability of the user to release/destruct the object

        *out_height = h;
        res = kth::to_c_err(ec);
        latch.count_down();
    });

    latch.count_down_and_wait();
    return res;
}

void chain_fetch_compact_block_by_hash(chain_t chain, void* ctx, hash_t hash, compact_block_fetch_handler_t handler) {
    auto hash_cpp = kth::to_array(hash.hash);

    safe_chain(chain).fetch_compact_block(hash_cpp, [chain, ctx, handler](std::error_code const& ec, kth::domain::message::compact_block::const_ptr block, size_t h) {
        auto new_block = new kth::domain::message::compact_block(*block);
        //Note: It is the responsibility of the user to release/destruct the object
        handler(chain, ctx, kth::to_c_err(ec), new_block, h);
    });
}

error_code_t chain_get_compact_block_by_hash(chain_t chain, hash_t hash, compact_block_t* out_block, uint64_t* /*size_t*/ out_height) {
    boost::latch latch(2); //Note: workaround to fix an error on some versions of Boost.Threads
    error_code_t res;

    auto hash_cpp = kth::to_array(hash.hash);

    safe_chain(chain).fetch_compact_block(hash_cpp, [&](std::error_code const& ec, kth::domain::message::compact_block::const_ptr block, size_t h) {
        //Note: It is the responsability of the user to release/destruct the object
        *out_block = new kth::domain::message::compact_block(*block);
        *out_height = h;
        res = kth::to_c_err(ec);
        latch.count_down();
    });

    latch.count_down_and_wait();
    return res;
}


#endif // defined(KTH_DB_LEGACY) || defined(KTH_DB_NEW_BLOCKS) || defined(KTH_DB_NEW_FULL)


void chain_fetch_block_by_height_timestamp(chain_t chain, void* ctx, uint64_t /*size_t*/ height, block_hash_timestamp_fetch_handler_t handler) {
    safe_chain(chain).fetch_block_hash_timestamp(height, [chain, ctx, handler](std::error_code const& ec, kth::hash_digest const& hash, uint32_t timestamp, size_t h) {
        if (ec == kth::error::success) {
            handler(chain, ctx, kth::to_c_err(ec), kth::to_hash_t(hash), timestamp, h);
        } else {
            handler(chain, ctx, kth::to_c_err(ec), kth::to_hash_t(kth::null_hash), 0, h);
        }
    });
}

error_code_t chain_get_block_by_height_timestamp(chain_t chain, uint64_t /*size_t*/ height, hash_t* out_hash, uint32_t* out_timestamp) {
    boost::latch latch(2); //Note: workaround to fix an error on some versions of Boost.Threads
    error_code_t res;

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

    latch.count_down_and_wait();
    return res;
}



error_code_t chain_get_block_hash(chain_t chain, uint64_t height, hash_t* out_hash) {
    kth::hash_digest block_hash;
    bool found_block = safe_chain(chain).get_block_hash(block_hash, height);
    if( ! found_block ) {
        return kth_ec_not_found;
    }
    kth::copy_c_hash(block_hash, out_hash);
    return kth_ec_success;
}

#if defined(KTH_DB_LEGACY) || defined(KTH_DB_NEW_FULL)

void chain_fetch_transaction(chain_t chain, void* ctx, hash_t hash, bool_t require_confirmed, transaction_fetch_handler_t handler) {
#ifdef KTH_CURRENCY_BCH
    bool_t witness = 0;
#else
    bool_t witness = 1;
#endif    
    //precondition:  [hash, 32] is a valid range

    auto hash_cpp = kth::to_array(hash.hash);

    safe_chain(chain).fetch_transaction(hash_cpp, kth::int_to_bool(require_confirmed), kth::int_to_bool(witness), [chain, ctx, handler](std::error_code const& ec, kth::domain::message::transaction::const_ptr transaction, size_t i, size_t h) {
        if (ec == kth::error::success) {
            auto new_transaction = new kth::domain::message::transaction(*transaction);
            handler(chain, ctx, kth::to_c_err(ec), new_transaction, i, h);
        } else {
            handler(chain, ctx, kth::to_c_err(ec), nullptr, i, h);
        }
    });
}

error_code_t chain_get_transaction(chain_t chain, hash_t hash, int require_confirmed, transaction_t* out_transaction, uint64_t* /*size_t*/ out_height, uint64_t* /*size_t*/ out_index) {
#ifdef KTH_CURRENCY_BCH
    bool_t witness = 0;
#else
    bool_t witness = 1;
#endif    
    boost::latch latch(2); //Note: workaround to fix an error on some versions of Boost.Threads
    error_code_t res;

    auto hash_cpp = kth::to_array(hash.hash);

    safe_chain(chain).fetch_transaction(hash_cpp, kth::int_to_bool(require_confirmed), kth::int_to_bool(witness), [&](std::error_code const& ec, kth::domain::message::transaction::const_ptr transaction, size_t i, size_t h) {
        if (ec == kth::error::success) {
            *out_transaction = new kth::domain::message::transaction(*transaction);
        } else {
            *out_transaction = nullptr;
        }

        *out_height = h;
        *out_index = i;
        res = kth::to_c_err(ec);
        latch.count_down();
    });

    latch.count_down_and_wait();
    return res;

}


void chain_fetch_transaction_position(chain_t chain, void* ctx, hash_t hash, int require_confirmed, transaction_index_fetch_handler_t handler) {
    auto hash_cpp = kth::to_array(hash.hash);

    safe_chain(chain).fetch_transaction_position(hash_cpp, kth::int_to_bool(require_confirmed), [chain, ctx, handler](std::error_code const& ec, size_t position, size_t height) {
        handler(chain, ctx, kth::to_c_err(ec), position, height);
    });
}

error_code_t chain_get_transaction_position(chain_t chain, hash_t hash, int require_confirmed, uint64_t* /*size_t*/ out_position, uint64_t* /*size_t*/ out_height) {
    boost::latch latch(2); //Note: workaround to fix an error on some versions of Boost.Threads
    error_code_t res;

    auto hash_cpp = kth::to_array(hash.hash);

    safe_chain(chain).fetch_transaction_position(hash_cpp, kth::int_to_bool(require_confirmed), [&](std::error_code const& ec, size_t position, size_t height) {
        *out_height = height;
        *out_position = position;
        res = kth::to_c_err(ec);
        latch.count_down();
    });

    latch.count_down_and_wait();
    return res;
}
#endif // defined(KTH_DB_LEGACY) || defined(KTH_DB_NEW_FULL)


#if (defined(KTH_DB_LEGACY) && defined(KTH_DB_SPENDS)) || defined(KTH_DB_NEW_FULL)
//It is the user's responsibility to release the input point returned in the callback
void chain_fetch_spend(chain_t chain, void* ctx, output_point_t op, spend_fetch_handler_t handler) {
    auto* outpoint_cpp = static_cast<kth::domain::chain::output_point*>(op);

    safe_chain(chain).fetch_spend(*outpoint_cpp, [chain, ctx, handler](std::error_code const& ec, kth::domain::chain::input_point input_point) {
        auto new_input_point = new kth::domain::chain::input_point(input_point);
        handler(chain, ctx, kth::to_c_err(ec), new_input_point);
    });
}

error_code_t chain_get_spend(chain_t chain, output_point_t op, input_point_t* out_input_point) {
    boost::latch latch(2); //Note: workaround to fix an error on some versions of Boost.Threads
    error_code_t res;

    auto* outpoint_cpp = static_cast<kth::domain::chain::output_point*>(op);

    safe_chain(chain).fetch_spend(*outpoint_cpp, [&](std::error_code const& ec, kth::domain::chain::input_point input_point) {
        *out_input_point = new kth::domain::chain::input_point(input_point);
        res = kth::to_c_err(ec);
        latch.count_down();
    });

    latch.count_down_and_wait();
    return res;
}
#endif // defined(KTH_DB_LEGACY) && defined(KTH_DB_SPENDS) || defined(KTH_DB_NEW_FULL)

#if (defined(KTH_DB_LEGACY) && defined(KTH_DB_HISTORY)) || defined(KTH_DB_NEW_FULL)
//It is the user's responsibility to release the history returned in the callback
void chain_fetch_history(chain_t chain, void* ctx, payment_address_t address, uint64_t /*size_t*/ limit, uint64_t /*size_t*/ from_height, history_fetch_handler_t handler) {
    // auto const& address_cpp = wallet_payment_address_const_cpp(address);

    safe_chain(chain).fetch_history(wallet_payment_address_const_cpp(address), limit, from_height, [chain, ctx, handler](std::error_code const& ec, kth::domain::chain::history_compact::list history) {
        auto new_history = new kth::domain::chain::history_compact::list(history);
        handler(chain, ctx, kth::to_c_err(ec), new_history);
    });
}

//It is the user's responsibility to release the history returned in the callback
error_code_t chain_get_history(chain_t chain, payment_address_t address, uint64_t /*size_t*/ limit, uint64_t /*size_t*/ from_height, history_compact_list_t* out_history) {
    boost::latch latch(2); //Note: workaround to fix an error on some versions of Boost.Threads
    error_code_t res;

    // auto const& address_cpp = wallet_payment_address_const_cpp(address);

    safe_chain(chain).fetch_history(wallet_payment_address_const_cpp(address), limit, from_height, [&](std::error_code const& ec, kth::domain::chain::history_compact::list history) {
        *out_history = new kth::domain::chain::history_compact::list(history);
        res = kth::to_c_err(ec);
        latch.count_down();
    });

    latch.count_down_and_wait();
    return res;
}
#endif // defined(KTH_DB_LEGACY) && defined(KTH_DB_HISTORY) || defined(KTH_DB_NEW_FULL)


#if defined(KTH_DB_TRANSACTION_UNCONFIRMED) || defined(KTH_DB_NEW_FULL)
void chain_fetch_confirmed_transactions(chain_t chain, void* ctx, payment_address_t address, uint64_t max, uint64_t start_height, transactions_by_addres_fetch_handler_t handler) {
    // auto const& address_cpp = wallet_payment_address_const_cpp(address);

    safe_chain(chain).fetch_confirmed_transactions(wallet_payment_address_const_cpp(address), max, start_height, [chain, ctx, handler](std::error_code const& ec, const std::vector<kth::hash_digest>& txs) {
        //It is the user's responsibility to release this allocated memory
        auto new_txs = new kth::hash_list(txs);
        handler(chain, ctx, kth::to_c_err(ec), new_txs);
    });
}

error_code_t chain_get_confirmed_transactions(chain_t chain, payment_address_t address, uint64_t max, uint64_t start_height, hash_list_t* out_tx_hashes) {
    boost::latch latch(2); //Note: workaround to fix an error on some versions of Boost.Threads
    error_code_t res;

    // auto const& address_cpp = wallet_payment_address_const_cpp(address);

    safe_chain(chain).fetch_confirmed_transactions(wallet_payment_address_const_cpp(address), max, start_height, [&](std::error_code const& ec, const std::vector<kth::hash_digest>& txs) {
        //It is the user's responsibility to release this allocated memory
        *out_tx_hashes = new kth::hash_list(txs);
        res = kth::to_c_err(ec);
        latch.count_down();
    });

    latch.count_down_and_wait();
    return res;
}
#endif // defined(KTH_DB_TRANSACTION_UNCONFIRMED) || defined(KTH_DB_NEW_FULL)


#if defined(KTH_DB_STEALTH)
void chain_fetch_stealth(chain_t chain, void* ctx, binary_t filter, uint64_t from_height, stealth_fetch_handler_t handler) {
	auto* filter_cpp_ptr = static_cast<kth::binary const*>(filter);
	kth::binary const& filter_cpp  = *filter_cpp_ptr;

    safe_chain(chain).fetch_stealth(filter_cpp, from_height, [chain, ctx, handler](std::error_code const& ec, kth::domain::chain::stealth_compact::list stealth) {
        auto new_stealth = new kth::domain::chain::stealth_compact::list(stealth);
        handler(chain, ctx, kth::to_c_err(ec), new_stealth);
    });
} 

error_code_t chain_get_stealth(chain_t chain, binary_t filter, uint64_t from_height, stealth_compact_list_t* out_list) {
    boost::latch latch(2); //Note: workaround to fix an error on some versions of Boost.Threads
    error_code_t res;

	auto* filter_cpp_ptr = static_cast<kth::binary const*>(filter);
	kth::binary const& filter_cpp  = *filter_cpp_ptr;

    safe_chain(chain).fetch_stealth(filter_cpp, from_height, [&](std::error_code const& ec, kth::domain::chain::stealth_compact::list stealth) {
        *out_list = new kth::domain::chain::stealth_compact::list(stealth);
        res = kth::to_c_err(ec);
        latch.count_down();
    });
    
    latch.count_down_and_wait();
    return res;
}
#endif // defined(KTH_DB_STEALTH)

// ------------------------------------------------------------------
//virtual void fetch_block_locator(chain::block::indexes const& heights, block_locator_fetch_handler handler) const = 0;

//void chain_fetch_block_locator(chain_t chain, void* ctx, block_indexes_t heights, block_locator_fetch_handler_t handler) {
//    auto const& heights_cpp = chain_block_indexes_const_cpp(heights);
//
//    safe_chain(chain).fetch_block_locator(heights_cpp, [chain, ctx, handler](std::error_code const& ec, kth::get_headers_ptr headers) {
//        //TODO: check if the pointer is set, before dereferencing
//        auto* new_headers = new kth::domain::message::get_headers(*headers);
//        handler(chain, ctx, kth::to_c_err(ec), new_headers);
//    });
//}
//
////It is the user's responsibility to release the history returned in the callback
//error_code_t chain_get_block_locator(chain_t chain, block_indexes_t heights, get_headers_ptr_t* out_headers) {
//    boost::latch latch(2); //Note: workaround to fix an error on some versions of Boost.Threads
//    error_code_t res;
//
//    auto const& heights_cpp = chain_block_indexes_const_cpp(heights);
//
//    safe_chain(chain).fetch_block_locator(heights_cpp, [&](std::error_code const& ec, kth::get_headers_ptr headers) {
//        //TODO: check if the pointer is set, before dereferencing
//        *out_headers = new kth::domain::message::get_headers(*headers);
//        res = kth::to_c_err(ec);
//        latch.count_down();
//    });
//
//    latch.count_down_and_wait();
//    return res;
//}



// ------------------------------------------------------------------
//virtual void fetch_locator_block_hashes(get_blocks_const_ptr locator, hash_digest const& threshold, size_t limit, inventory_fetch_handler handler) const = 0;

//void chain_fetch_locator_block_hashes(chain_t chain, void* ctx, get_blocks_ptr_t locator, hash_t threshold, uint64_t /*size_t*/ limit, inventory_fetch_handler handler) {
//}


//virtual void fetch_locator_block_headers(get_headers_const_ptr locator, hash_digest const& threshold, size_t limit, locator_block_headers_fetch_handler handler) const = 0;
//

//// Transaction Pool.
////-------------------------------------------------------------------------
//
//virtual void fetch_template(merkle_block_fetch_handler handler) const = 0;
//virtual void fetch_mempool(size_t count_limit, uint64_t minimum_fee, inventory_fetch_handler handler) const = 0;
//

#if defined(KTH_DB_TRANSACTION_UNCONFIRMED) || defined(KTH_DB_NEW_FULL)
mempool_transaction_list_t chain_get_mempool_transactions(chain_t chain, payment_address_t address, bool_t use_testnet_rules) {
#ifdef KTH_CURRENCY_BCH
    bool_t witness = 0;
#else
    bool_t witness = 1;
#endif
    auto const& address_cpp = wallet_payment_address_const_cpp(address);
    if (address_cpp) {
        auto txs = safe_chain(chain).get_mempool_transactions(address_cpp.encoded(), kth::int_to_bool(use_testnet_rules), kth::int_to_bool(witness));
        auto ret_txs = new std::vector<kth::blockchain::mempool_transaction_summary>(txs);
        return static_cast<mempool_transaction_list_t>(ret_txs);
    } 
    auto ret_txs = new std::vector<kth::blockchain::mempool_transaction_summary>();
    return static_cast<mempool_transaction_list_t>(ret_txs);
}

transaction_list_t chain_get_mempool_transactions_from_wallets(chain_t chain, payment_address_list_t addresses, bool_t use_testnet_rules) {
#ifdef KTH_CURRENCY_BCH
    bool_t witness = 0;
#else
    bool_t witness = 1;
#endif
    auto const& addresses_cpp = *static_cast<std::vector<kth::domain::wallet::payment_address> const*>(addresses);
    auto txs = safe_chain(chain).get_mempool_transactions_from_wallets(addresses_cpp, kth::int_to_bool(use_testnet_rules), kth::int_to_bool(witness));
    return kth::move_or_copy_and_leak(std::move(txs));
}
#endif // defined(KTH_DB_TRANSACTION_UNCONFIRMED) || defined(KTH_DB_NEW_FULL)


//// Filters.
////-------------------------------------------------------------------------
//
//virtual void filter_blocks(get_data_ptr message, result_handler handler) const = 0;

//void chain_filter_blocks(chain_t chain, void* ctx, get_data_ptr message, result_handler handler) {
//}


//virtual void filter_transactions(get_data_ptr message, result_handler handler) const = 0;
// ------------------------------------------------------------------


// Subscribers.
//-------------------------------------------------------------------------

block_t cast_block(kth::domain::message::block const& x) {
    return const_cast<kth::domain::message::block*>(&x);    
}

void chain_subscribe_blockchain(executor_t exec, chain_t chain, void* ctx, subscribe_blockchain_handler_t handler) {
    safe_chain(chain).subscribe_blockchain([exec, chain, ctx, handler](std::error_code const& ec, size_t fork_height, kth::block_const_ptr_list_const_ptr incoming, kth::block_const_ptr_list_const_ptr replaced_blocks) {

        if (safe_chain(chain).is_stale()) { // TODO(fernando): Move somewhere else (there should be no logic here)
            return 1;
        }

        block_list_t incoming_cpp = nullptr;
        if (incoming) {
            incoming_cpp = chain_block_list_construct_default();
            for (auto&& x : *incoming) {
                // auto new_block = new kth::domain::message::block(*x);
                // chain_block_list_push_back(incoming_cpp, new_block);
                chain_block_list_push_back(incoming_cpp, cast_block(*x));
            }
        }

        block_list_t replaced_blocks_cpp = nullptr;
        if (replaced_blocks) {
            replaced_blocks_cpp = chain_block_list_construct_default();
            for (auto&& x : *replaced_blocks) {
                // auto new_block = new kth::domain::message::block(*x);
                // chain_block_list_push_back(replaced_blocks_cpp, new_block);
                // chain_block_list_push_back_const(replaced_blocks_cpp, x.get());
                chain_block_list_push_back(replaced_blocks_cpp, cast_block(*x));
            }
        }

        auto res = handler(exec, chain, ctx, kth::to_c_err(ec), fork_height, incoming_cpp, replaced_blocks_cpp);
        return res;
    });
}

void chain_subscribe_transaction(executor_t exec, chain_t chain, void* ctx, subscribe_transaction_handler_t handler) {
    safe_chain(chain).subscribe_transaction([exec, chain, ctx, handler](std::error_code const& ec, kth::transaction_const_ptr tx) {
        transaction_t new_tx = nullptr;
        if (tx) {
            new_tx = new kth::domain::message::transaction(*tx);
        }
        auto res = handler(exec, chain, ctx, kth::to_c_err(ec), new_tx);
        return res;
    });
}

void chain_unsubscribe(chain_t chain) {
    safe_chain(chain).unsubscribe();
}

// Organizers.
//-------------------------------------------------------------------------

//virtual void organize(block_const_ptr block, result_handler handler) = 0;
//virtual void organize(transaction_const_ptr tx, result_handler handler) = 0;

void chain_organize_block(chain_t chain, void* ctx, block_t block, result_handler_t handler) {
    safe_chain(chain).organize(block_shared(block), [chain, ctx, handler](std::error_code const& ec) {
        handler(chain, ctx, kth::to_c_err(ec));
    });
}

int chain_organize_block_sync(chain_t chain, block_t block) {
    boost::latch latch(2); //Note: workaround to fix an error on some versions of Boost.Threads
    error_code_t res;

    safe_chain(chain).organize(block_shared(block), [&](std::error_code const& ec) {
        res = kth::to_c_err(ec);
        latch.count_down();
    });

    latch.count_down_and_wait();
    return res;
}

void chain_organize_transaction(chain_t chain, void* ctx, transaction_t transaction, result_handler_t handler) {
    safe_chain(chain).organize(tx_shared(transaction), [chain, ctx, handler](std::error_code const& ec) {
        handler(chain, ctx, kth::to_c_err(ec));
    });
}

int chain_organize_transaction_sync(chain_t chain, transaction_t transaction) {
    boost::latch latch(2); //Note: workaround to fix an error on some versions of Boost.Threads
    error_code_t res;

    safe_chain(chain).organize(tx_shared(transaction), [&](std::error_code const& ec) {
        res = kth::to_c_err(ec);
        latch.count_down();
    });

    latch.count_down_and_wait();
    return res;
}

//-------------------------------------------------------------------------

////It is the user's responsibility to release the transaction returned
//transaction_t chain_hex_to_tx(char const* tx_hex) {
//
//    static auto const version = kth::domain::message::version::level::canonical;
//
////    auto const tx = std::make_shared<kth::domain::message::transaction>();
//    auto* tx = new kth::domain::message::transaction;
//
//    std::string tx_hex_cpp(tx_hex);
//    std::vector<uint8_t> data(tx_hex_cpp.size() / 2); // (tx_hex_cpp.begin(), tx_hex_cpp.end());
//    //data.reserve(tx_hex_cpp.size() / 2);
//
//    hex2bin(tx_hex_cpp.c_str(), data.data());
//
//    if (!tx->from_data(version, data)) {
//        return nullptr;
//    }
//
//    // Simulate organization into our chain.
//    tx->validation.simulate = true;
//
//    return tx;
//}

void chain_transaction_validate_sequential(chain_t chain, void* ctx, transaction_t tx, validate_tx_handler_t handler) {
    if (handler == nullptr) return;

    auto tx_cpp = tx_shared(tx);
    tx_cpp->validation.simulate = true;

    safe_chain(chain).organize(tx_cpp, [chain, ctx, handler](std::error_code const& ec) {
        if (ec) {
            handler(chain, ctx, kth::to_c_err(ec), ec.message().c_str());
        } else {
            handler(chain, ctx, kth::to_c_err(ec), nullptr);
        }
    });
}

void chain_transaction_validate(chain_t chain, void* ctx, transaction_t tx, validate_tx_handler_t handler) {
    if (handler == nullptr) return;

    safe_chain(chain).transaction_validate(tx_shared(tx), [chain, ctx, handler](std::error_code const& ec) {
        if (ec) {
            handler(chain, ctx, kth::to_c_err(ec), ec.message().c_str());
        } else {
            handler(chain, ctx, kth::to_c_err(ec), nullptr);
        }
    });
}

//Note: deprecated name
void chain_validate_tx(chain_t chain, void* ctx, transaction_t tx, validate_tx_handler_t handler) {
    chain_transaction_validate(chain, ctx, tx, handler);
}


// Properties.
//-------------------------------------------------------------------------

/// True if the blockchain is stale based on configured age limit.
bool_t chain_is_stale(chain_t chain) {
    return kth::bool_to_int(safe_chain(chain).is_stale());
}


/// Get a reference to the blockchain configuration settings.
// const settings& chain_settings() const;


} // extern "C"
