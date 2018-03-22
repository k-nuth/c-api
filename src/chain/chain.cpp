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

#include <bitprim/nodecint/chain/chain.h>
#include <cstdio>
#include <memory>
#include <boost/thread/latch.hpp>

#include <bitprim/nodecint/convertions.hpp>
#include <bitprim/nodecint/helpers.hpp>

#include <bitprim/nodecint/chain/block_list.h>

#include <bitcoin/bitcoin/message/block.hpp>
#include <bitcoin/bitcoin/message/header.hpp>
#include <bitcoin/bitcoin/message/merkle_block.hpp>
#include <bitcoin/bitcoin/message/transaction.hpp>
#include <bitcoin/blockchain/interface/safe_chain.hpp>
#include <chrono>

namespace {

inline
libbitcoin::blockchain::safe_chain& safe_chain(chain_t chain) {
    return *static_cast<libbitcoin::blockchain::safe_chain*>(chain);
}

inline
libbitcoin::message::transaction::const_ptr tx_shared(transaction_t tx) {
    auto const& tx_ref = *static_cast<libbitcoin::message::transaction const*>(tx);
    auto* tx_new = new libbitcoin::message::transaction(tx_ref);
    return libbitcoin::message::transaction::const_ptr(tx_new);
}

inline
libbitcoin::message::block::const_ptr block_shared(block_t block) {
    auto const& block_ref = *static_cast<libbitcoin::message::block const*>(block);
    auto* block_new = new libbitcoin::message::block(block_ref);
    return libbitcoin::message::block::const_ptr(block_new);
}



//inline
//int char2int(char input) {
//    if (input >= '0' && input <= '9') {
//        return input - '0';
//    }
//    if (input >= 'A' && input <= 'F') {
//        return input - 'A' + 10;
//    }
//    if (input >= 'a' && input <= 'f') {
//        return input - 'a' + 10;
//    }
//    throw std::invalid_argument("Invalid input string");
//}

//inline
//void hex2bin(const char* src, uint8_t* target) {
//    while ((*src != 0) && (src[1] != 0)) {
//        *(target++) = char2int(*src) * 16 + char2int(src[1]);
//        src += 2;
//    }
//}

} /* end of anonymous namespace */


#ifdef __cplusplus
extern "C" {
#endif


void chain_fetch_last_height(chain_t chain, void* ctx, last_height_fetch_handler_t handler) {
    safe_chain(chain).fetch_last_height([chain, ctx, handler](std::error_code const& ec, size_t h) {
        handler(chain, ctx, static_cast<error_code_t>(ec.value()), h);
    });
}

error_code_t chain_get_last_height(chain_t chain, uint64_t* /*size_t*/ out_height) {
    boost::latch latch(2); //Note: workaround to fix an error on some versions of Boost.Threads

    error_code_t res;
    safe_chain(chain).fetch_last_height([&](std::error_code const& ec, size_t h) {
       *out_height = h;
       res = static_cast<error_code_t>(ec.value());
       latch.count_down();
    });

    latch.count_down_and_wait();
    return res;
}

//void chain_fetch_block_height(chain_t chain, void* ctx, hash_t hash, block_height_fetch_handler_t handler) {
//
//    libbitcoin::hash_digest hash_cpp;
//    std::copy_n(hash, hash_cpp.size(), std::begin(hash_cpp));
//
//    safe_chain(chain).fetch_block_height(hash_cpp, [chain, ctx, handler](std::error_code const& ec, size_t h) {
//        handler(chain, ctx, static_cast<error_code_t>(ec.value()), h);
//    });
//}

void chain_fetch_block_height(chain_t chain, void* ctx, hash_t hash, block_height_fetch_handler_t handler) {

    auto hash_cpp = bitprim::to_array(hash.hash);
    // std::cout << "hash_cpp: " << libbitcoin::encode_hash(hash_cpp) << std::endl;
    
    safe_chain(chain).fetch_block_height(hash_cpp, [chain, ctx, handler](std::error_code const& ec, size_t h) {
        handler(chain, ctx, static_cast<error_code_t>(ec.value()), h);
    });
}

error_code_t chain_get_block_height(chain_t chain, hash_t hash, uint64_t* /*size_t*/ out_height) {
    boost::latch latch(2); //Note: workaround to fix an error on some versions of Boost.Threads
    error_code_t res;

//    libbitcoin::hash_digest hash_cpp;
//    std::copy_n(hash, hash_cpp.size(), std::begin(hash_cpp));
    auto hash_cpp = bitprim::to_array(hash.hash);

    safe_chain(chain).fetch_block_height(hash_cpp, [&](std::error_code const& ec, size_t h) {
        *out_height = h;
        res = static_cast<error_code_t>(ec.value());
        latch.count_down();
    });

    latch.count_down_and_wait();
    return res;
}

void chain_fetch_block_header_by_height(chain_t chain, void* ctx, uint64_t /*size_t*/ height, block_header_fetch_handler_t handler) {
    safe_chain(chain).fetch_block_header(height, [chain, ctx, handler](std::error_code const& ec, libbitcoin::message::header::ptr header, size_t h) {
        auto new_header = new libbitcoin::message::header(*header);
//        auto new_header = std::make_unique(*header).release();
        //Note: It is the responsability of the user to release/destruct the object
        handler(chain, ctx, static_cast<error_code_t>(ec.value()), new_header, h);
    });
}

error_code_t chain_get_block_header_by_height(chain_t chain, uint64_t /*size_t*/ height, header_t* out_header, uint64_t* /*size_t*/ out_height) {
    boost::latch latch(2); //Note: workaround to fix an error on some versions of Boost.Threads
    error_code_t res;

    safe_chain(chain).fetch_block_header(height, [&](std::error_code const& ec, libbitcoin::message::header::ptr header, size_t h) {
        *out_header = new libbitcoin::message::header(*header);
        //Note: It is the responsability of the user to release/destruct the object

        *out_height = h;
        res = static_cast<error_code_t>(ec.value());
        latch.count_down();
    });

    latch.count_down_and_wait();
    return res;
}       

void chain_fetch_block_header_by_hash(chain_t chain, void* ctx, hash_t hash, block_header_fetch_handler_t handler) {

//    libbitcoin::hash_digest hash_cpp;
//    std::copy_n(hash, hash_cpp.size(), std::begin(hash_cpp));
    auto hash_cpp = bitprim::to_array(hash.hash);

    safe_chain(chain).fetch_block_header(hash_cpp, [chain, ctx, handler](std::error_code const& ec, libbitcoin::message::header::ptr header, size_t h) {
        auto new_header = new libbitcoin::message::header(*header);
//        auto new_header = std::make_unique(*header).release();
        //Note: It is the responsability of the user to release/destruct the object
        handler(chain, ctx, static_cast<error_code_t>(ec.value()), new_header, h);
    });
}

error_code_t chain_get_block_header_by_hash(chain_t chain, hash_t hash, header_t* out_header, uint64_t* /*size_t*/ out_height) {
    boost::latch latch(2); //Note: workaround to fix an error on some versions of Boost.Threads
    error_code_t res;

//    libbitcoin::hash_digest hash_cpp;
//    std::copy_n(hash, hash_cpp.size(), std::begin(hash_cpp));
    auto hash_cpp = bitprim::to_array(hash.hash);

    safe_chain(chain).fetch_block_header(hash_cpp, [&](std::error_code const& ec, libbitcoin::message::header::ptr header, size_t h) {
        *out_header = new libbitcoin::message::header(*header);
        //Note: It is the responsability of the user to release/destruct the object

        *out_height = h;
        res = static_cast<error_code_t>(ec.value());
        latch.count_down();
    });

    latch.count_down_and_wait();
    return res;
}

void chain_fetch_block_by_height(chain_t chain, void* ctx, uint64_t /*size_t*/ height, block_fetch_handler_t handler) {
    safe_chain(chain).fetch_block(height, [chain, ctx, handler](std::error_code const& ec, libbitcoin::message::block::const_ptr block, size_t h) {
        if (ec == libbitcoin::error::success) {
            auto new_block = new libbitcoin::message::block(*block);
            //Note: It is the responsability of the user to release/destruct the object
            handler(chain, ctx, static_cast<error_code_t>(ec.value()), new_block, h);
        } else {
            handler(chain, ctx, static_cast<error_code_t>(ec.value()), nullptr, h);
        }
    });
}

error_code_t chain_get_block_by_height(chain_t chain, uint64_t /*size_t*/ height, block_t* out_block, uint64_t* /*size_t*/ out_height) {
    boost::latch latch(2); //Note: workaround to fix an error on some versions of Boost.Threads
    error_code_t res;

    safe_chain(chain).fetch_block(height, [&](std::error_code const& ec, libbitcoin::message::block::const_ptr block, size_t h) {
        if (ec == libbitcoin::error::success) {
            //Note: It is the responsability of the user to release/destruct the object
            *out_block = new libbitcoin::message::block(*block);
        } else {
            *out_block = nullptr;
        }

        *out_height = h;
        res = static_cast<error_code_t>(ec.value());
        latch.count_down();
    });

    latch.count_down_and_wait();
    return res;
}

void chain_fetch_block_by_height_timestamp(chain_t chain, void* ctx, uint64_t /*size_t*/ height, block_hash_timestamp_fetch_handler_t handler) {
    safe_chain(chain).fetch_block_hash_timestamp(height, [chain, ctx, handler](std::error_code const& ec, const libbitcoin::hash_digest& hash, uint32_t timestamp, size_t h) {
        if (ec == libbitcoin::error::success) {
            handler(chain, ctx, static_cast<error_code_t>(ec.value()), bitprim::to_hash_t(hash), timestamp, h);
        } else {
            handler(chain, ctx, static_cast<error_code_t>(ec.value()), bitprim::to_hash_t(libbitcoin::null_hash), 0, h);
        }
    });
}

error_code_t chain_get_block_by_height_timestamp(chain_t chain, uint64_t /*size_t*/ height, hash_t* out_hash, uint32_t* out_timestamp) {
    boost::latch latch(2); //Note: workaround to fix an error on some versions of Boost.Threads
    error_code_t res;

    safe_chain(chain).fetch_block_hash_timestamp(height, [&](std::error_code const& ec, const libbitcoin::hash_digest& hash, uint32_t timestamp, size_t h) {
        if (ec == libbitcoin::error::success) {
            //handler(chain, ctx, static_cast<error_code_t>(ec.value()), bitprim::to_hash_t(hash), timestamp, h);
            std::memcpy(out_hash->hash, hash.data(), BITCOIN_HASH_SIZE);
            *out_timestamp = timestamp;
        } else {
            std::memcpy(out_hash->hash, libbitcoin::null_hash.data(), BITCOIN_HASH_SIZE);
            *out_timestamp = 0;
        }

        res = static_cast<error_code_t>(ec.value());
        latch.count_down();
    });

    latch.count_down_and_wait();
    return res;
}

void chain_fetch_block_by_hash(chain_t chain, void* ctx, hash_t hash, block_fetch_handler_t handler) {

//    libbitcoin::hash_digest hash_cpp;
//    std::copy_n(hash, hash_cpp.size(), std::begin(hash_cpp));
    auto hash_cpp = bitprim::to_array(hash.hash);

    safe_chain(chain).fetch_block(hash_cpp, [chain, ctx, handler](std::error_code const& ec, libbitcoin::message::block::const_ptr block, size_t h) {
        if (ec == libbitcoin::error::success) {
            //Note: It is the responsability of the user to release/destruct the object
            auto new_block = new libbitcoin::message::block(*block);
            handler(chain, ctx, static_cast<error_code_t>(ec.value()), new_block, h);
        } else {
            handler(chain, ctx, static_cast<error_code_t>(ec.value()), nullptr, h);
        }
    });
}

error_code_t chain_get_block_by_hash(chain_t chain, hash_t hash, block_t* out_block, uint64_t* /*size_t*/ out_height) {
    boost::latch latch(2); //Note: workaround to fix an error on some versions of Boost.Threads
    error_code_t res;

//    libbitcoin::hash_digest hash_cpp;
//    std::copy_n(hash, hash_cpp.size(), std::begin(hash_cpp));
    auto hash_cpp = bitprim::to_array(hash.hash);

    safe_chain(chain).fetch_block(hash_cpp, [&](std::error_code const& ec, libbitcoin::message::block::const_ptr block, size_t h) {
        if (ec == libbitcoin::error::success) {
            //Note: It is the responsability of the user to release/destruct the object
            *out_block = new libbitcoin::message::block(*block);
        } else {
            *out_block = nullptr;
        }

        *out_height = h;
        res = static_cast<error_code_t>(ec.value());
        latch.count_down();
    });

    latch.count_down_and_wait();
    return res;
}

void chain_fetch_block_header_by_hash_txs_size(chain_t chain, void* ctx, hash_t hash, block_header_txs_size_fetch_handler_t handler) {

//    libbitcoin::hash_digest hash_cpp;
//    std::copy_n(hash, hash_cpp.size(), std::begin(hash_cpp));
    auto hash_cpp = bitprim::to_array(hash.hash);

    safe_chain(chain).fetch_block_header_txs_size(hash_cpp, [chain, ctx, handler](std::error_code const& ec, libbitcoin::message::header::const_ptr header, size_t block_height, const std::shared_ptr<libbitcoin::hash_list> tx_hashes, uint64_t block_serialized_size) {
        if (ec == libbitcoin::error::success) {
            //Note: It is the user's responsability of the user to release/destruct the object
            auto new_header = new libbitcoin::message::header(*header);
            //Note: It is the user's responsability of the user to release/destruct the object
            auto new_tx_hashes = new libbitcoin::hash_list(*tx_hashes);
            handler(chain, ctx, static_cast<error_code_t>(ec.value()), new_header, block_height, new_tx_hashes, block_serialized_size);
        } else {
            handler(chain, ctx, static_cast<error_code_t>(ec.value()), nullptr, 0, nullptr, 0);
        }
    });
}

error_code_t chain_get_block_header_by_hash_txs_size(chain_t chain, hash_t hash, header_t* out_header, uint64_t* out_block_height, hash_list_t* out_tx_hashes, uint64_t* out_serialized_size) {
    boost::latch latch(2); //Note: workaround to fix an error on some versions of Boost.Threads
    error_code_t res;

    auto hash_cpp = bitprim::to_array(hash.hash);

    safe_chain(chain).fetch_block_header_txs_size(hash_cpp, [&](std::error_code const& ec, libbitcoin::message::header::const_ptr header, size_t block_height, const std::shared_ptr<libbitcoin::hash_list> tx_hashes, uint64_t block_serialized_size) {
        if (ec == libbitcoin::error::success) {
            //Note: It is the user's responsability of the user to release/destruct the object
            *out_header = new libbitcoin::message::header(*header);
            *out_block_height = block_height;
            //Note: It is the user's responsability of the user to release/destruct the object
            *out_tx_hashes = new libbitcoin::hash_list(*tx_hashes);
            *out_serialized_size = block_serialized_size;
        } else {
            *out_header = nullptr;
            *out_block_height = 0;
            *out_tx_hashes = nullptr;
            *out_serialized_size = 0;
        }

        res = static_cast<error_code_t>(ec.value());
        latch.count_down();
    });

    latch.count_down_and_wait();
    return res;
}

error_code_t chain_get_block_hash(chain_t chain, uint64_t height, hash_t* out_hash) {
    libbitcoin::hash_digest block_hash;
    bool found_block = safe_chain(chain).get_block_hash(block_hash, height);
    if( ! found_block ) {
        return bitprim_ec_not_found;
    }
    std::memcpy(out_hash->hash, block_hash.data(), BITCOIN_HASH_SIZE);
    return bitprim_ec_success;
}

void chain_fetch_merkle_block_by_height(chain_t chain, void* ctx, uint64_t /*size_t*/ height, merkle_block_fetch_handler_t handler) {

    safe_chain(chain).fetch_merkle_block(height, [chain, ctx, handler](std::error_code const& ec, libbitcoin::message::merkle_block::const_ptr block, size_t h) {
        auto new_block = new libbitcoin::message::merkle_block(*block);
        //Note: It is the responsibility of the user to release/destruct the object
        handler(chain, ctx, static_cast<error_code_t>(ec.value()), new_block, h);
    });
}

error_code_t chain_get_merkle_block_by_height(chain_t chain, uint64_t /*size_t*/ height, merkle_block_t* out_block, uint64_t* /*size_t*/ out_height) {
    boost::latch latch(2); //Note: workaround to fix an error on some versions of Boost.Threads
    error_code_t res;

    safe_chain(chain).fetch_merkle_block(height, [&](std::error_code const& ec, libbitcoin::message::merkle_block::const_ptr block, size_t h) {
        *out_block = new libbitcoin::message::merkle_block(*block);
        //Note: It is the responsability of the user to release/destruct the object

        *out_height = h;
        res = static_cast<error_code_t>(ec.value());
        latch.count_down();
    });

    latch.count_down_and_wait();
    return res;
}

void chain_fetch_merkle_block_by_hash(chain_t chain, void* ctx, hash_t hash, merkle_block_fetch_handler_t handler) {

//    libbitcoin::hash_digest hash_cpp;
//    std::copy_n(hash, hash_cpp.size(), std::begin(hash_cpp));
    auto hash_cpp = bitprim::to_array(hash.hash);

    safe_chain(chain).fetch_merkle_block(hash_cpp, [chain, ctx, handler](std::error_code const& ec, libbitcoin::message::merkle_block::const_ptr block, size_t h) {
        auto new_block = new libbitcoin::message::merkle_block(*block);
        handler(chain, ctx, static_cast<error_code_t>(ec.value()), new_block, h);
    });
}

error_code_t chain_get_merkle_block_by_hash(chain_t chain, hash_t hash, merkle_block_t* out_block, uint64_t* /*size_t*/ out_height) {
    boost::latch latch(2); //Note: workaround to fix an error on some versions of Boost.Threads
    error_code_t res;

//    libbitcoin::hash_digest hash_cpp;
//    std::copy_n(hash, hash_cpp.size(), std::begin(hash_cpp));
    auto hash_cpp = bitprim::to_array(hash.hash);

    safe_chain(chain).fetch_merkle_block(hash_cpp, [&](std::error_code const& ec, libbitcoin::message::merkle_block::const_ptr block, size_t h) {
        //Note: It is the responsability of the user to release/destruct the object
        *out_block = new libbitcoin::message::merkle_block(*block);
        *out_height = h;
        res = static_cast<error_code_t>(ec.value());
        latch.count_down();
    });

    latch.count_down_and_wait();
    return res;
}

void chain_fetch_transaction(chain_t chain, void* ctx, hash_t hash, int require_confirmed, transaction_fetch_handler_t handler) {
    //precondition:  [hash, 32] is a valid range

    auto hash_cpp = bitprim::to_array(hash.hash);

    safe_chain(chain).fetch_transaction(hash_cpp, require_confirmed != 0, [chain, ctx, handler](std::error_code const& ec, libbitcoin::message::transaction::const_ptr transaction, size_t i, size_t h) {
        if (ec == libbitcoin::error::success) {
            auto new_transaction = new libbitcoin::message::transaction(*transaction);
            handler(chain, ctx, static_cast<error_code_t>(ec.value()), new_transaction, i, h);
        } else {
            handler(chain, ctx, static_cast<error_code_t>(ec.value()), nullptr, i, h);
        }
    });
}

error_code_t chain_get_transaction(chain_t chain, hash_t hash, int require_confirmed, transaction_t* out_transaction, uint64_t* /*size_t*/ out_height, uint64_t* /*size_t*/ out_index) {
    boost::latch latch(2); //Note: workaround to fix an error on some versions of Boost.Threads
    error_code_t res;

//    libbitcoin::hash_digest hash_cpp;
//    std::copy_n(hash, hash_cpp.size(), std::begin(hash_cpp));
    auto hash_cpp = bitprim::to_array(hash.hash);

    safe_chain(chain).fetch_transaction(hash_cpp, require_confirmed != 0, [&](std::error_code const& ec, libbitcoin::message::transaction::const_ptr transaction, size_t i, size_t h) {
        if (ec == libbitcoin::error::success) {
            *out_transaction = new libbitcoin::message::transaction(*transaction);
        } else {
            *out_transaction = nullptr;
        }

        *out_height = h;
        *out_index = i;
        res = static_cast<error_code_t>(ec.value());
        latch.count_down();
    });

    latch.count_down_and_wait();
    return res;

}

//Note: Removed on 3.3.0
// void chain_fetch_output(chain_t chain, void* ctx, hash_t hash, uint32_t index, int require_confirmed, output_fetch_handler_t handler) {

// //    libbitcoin::hash_digest hash_cpp;
// //    std::copy_n(hash, hash_cpp.size(), std::begin(hash_cpp));
//     auto hash_cpp = bitprim::to_array(hash.hash);

//     libbitcoin::chain::output_point point(hash_cpp, index);

//     safe_chain(chain).fetch_output(point, require_confirmed != 0, [chain, ctx, handler](std::error_code const& ec, libbitcoin::chain::output const& output) {
//         //It is the user's responsibility to release this memory
//         auto new_output = new libbitcoin::chain::output(output);
//         handler(chain, ctx, static_cast<error_code_t>(ec.value()), new_output);
//     });
// }

// error_code_t chain_get_output(chain_t chain, hash_t hash, uint32_t index, int require_confirmed, output_t* out_output) {
//     boost::latch latch(2); //Note: workaround to fix an error on some versions of Boost.Threads
//     error_code_t res;

// //    libbitcoin::hash_digest hash_cpp;
// //    std::copy_n(hash, hash_cpp.size(), std::begin(hash_cpp));
//     auto hash_cpp = bitprim::to_array(hash.hash);

//     libbitcoin::chain::output_point point(hash_cpp, index);

//     safe_chain(chain).fetch_output(point, require_confirmed != 0, [&](std::error_code const& ec, libbitcoin::chain::output const& output) {
//         *out_output = new libbitcoin::chain::output(output);

//         res = static_cast<error_code_t>(ec.value());
//         latch.count_down();
//     });

//     latch.count_down_and_wait();
//     return res;
// }

void chain_fetch_compact_block_by_height(chain_t chain, void* ctx, uint64_t /*size_t*/ height, compact_block_fetch_handler_t handler) {
    safe_chain(chain).fetch_compact_block(height, [chain, ctx, handler](std::error_code const& ec, libbitcoin::message::compact_block::const_ptr block, size_t h) {
        auto new_block = new libbitcoin::message::compact_block(*block);
        //Note: It is the responsibility of the user to release/destruct the object
        handler(chain, ctx, static_cast<error_code_t>(ec.value()), new_block, h);
    });
}

error_code_t chain_get_compact_block_by_height(chain_t chain, uint64_t /*size_t*/ height, compact_block_t* out_block, uint64_t* /*size_t*/ out_height) {
    boost::latch latch(2); //Note: workaround to fix an error on some versions of Boost.Threads
    error_code_t res;

    safe_chain(chain).fetch_compact_block(height, [&](std::error_code const& ec, libbitcoin::message::compact_block::const_ptr block, size_t h) {
        *out_block = new libbitcoin::message::compact_block(*block);
        //Note: It is the responsability of the user to release/destruct the object

        *out_height = h;
        res = static_cast<error_code_t>(ec.value());
        latch.count_down();
    });

    latch.count_down_and_wait();
    return res;
}

void chain_fetch_compact_block_by_hash(chain_t chain, void* ctx, hash_t hash, compact_block_fetch_handler_t handler) {
//    libbitcoin::hash_digest hash_cpp;
//    std::copy_n(hash, hash_cpp.size(), std::begin(hash_cpp));
    auto hash_cpp = bitprim::to_array(hash.hash);

    safe_chain(chain).fetch_compact_block(hash_cpp, [chain, ctx, handler](std::error_code const& ec, libbitcoin::message::compact_block::const_ptr block, size_t h) {
        auto new_block = new libbitcoin::message::compact_block(*block);
        //Note: It is the responsibility of the user to release/destruct the object
        handler(chain, ctx, static_cast<error_code_t>(ec.value()), new_block, h);
    });
}

error_code_t chain_get_compact_block_by_hash(chain_t chain, hash_t hash, compact_block_t* out_block, uint64_t* /*size_t*/ out_height) {
    boost::latch latch(2); //Note: workaround to fix an error on some versions of Boost.Threads
    error_code_t res;

//    libbitcoin::hash_digest hash_cpp;
//    std::copy_n(hash, hash_cpp.size(), std::begin(hash_cpp));
    auto hash_cpp = bitprim::to_array(hash.hash);

    safe_chain(chain).fetch_compact_block(hash_cpp, [&](std::error_code const& ec, libbitcoin::message::compact_block::const_ptr block, size_t h) {
        //Note: It is the responsability of the user to release/destruct the object
        *out_block = new libbitcoin::message::compact_block(*block);
        *out_height = h;
        res = static_cast<error_code_t>(ec.value());
        latch.count_down();
    });

    latch.count_down_and_wait();
    return res;
}

void chain_fetch_transaction_position(chain_t chain, void* ctx, hash_t hash, int require_confirmed, transaction_index_fetch_handler_t handler) {
//    libbitcoin::hash_digest hash_cpp;
//    std::copy_n(hash, hash_cpp.size(), std::begin(hash_cpp));
    auto hash_cpp = bitprim::to_array(hash.hash);

    safe_chain(chain).fetch_transaction_position(hash_cpp, require_confirmed != 0, [chain, ctx, handler](std::error_code const& ec, size_t position, size_t height) {
        handler(chain, ctx, static_cast<error_code_t>(ec.value()), position, height);
    });
}

error_code_t chain_get_transaction_position(chain_t chain, hash_t hash, int require_confirmed, uint64_t* /*size_t*/ out_position, uint64_t* /*size_t*/ out_height) {
    boost::latch latch(2); //Note: workaround to fix an error on some versions of Boost.Threads
    error_code_t res;

//    libbitcoin::hash_digest hash_cpp;
//    std::copy_n(hash, hash_cpp.size(), std::begin(hash_cpp));
    auto hash_cpp = bitprim::to_array(hash.hash);

    safe_chain(chain).fetch_transaction_position(hash_cpp, require_confirmed != 0, [&](std::error_code const& ec, size_t position, size_t height) {
        *out_height = height;
        *out_position = position;
        res = static_cast<error_code_t>(ec.value());
        latch.count_down();
    });

    latch.count_down_and_wait();
    return res;
}

//It is the user's responsibility to release the input point returned in the callback
void chain_fetch_spend(chain_t chain, void* ctx, output_point_t op, spend_fetch_handler_t handler) {
    auto* outpoint_cpp = static_cast<libbitcoin::chain::output_point*>(op);

    safe_chain(chain).fetch_spend(*outpoint_cpp, [chain, ctx, handler](std::error_code const& ec, libbitcoin::chain::input_point input_point) {
        auto new_input_point = new libbitcoin::chain::input_point(input_point);
        handler(chain, ctx, static_cast<error_code_t>(ec.value()), new_input_point);
    });
}

error_code_t chain_get_spend(chain_t chain, output_point_t op, input_point_t* out_input_point) {
    boost::latch latch(2); //Note: workaround to fix an error on some versions of Boost.Threads
    error_code_t res;

    auto* outpoint_cpp = static_cast<libbitcoin::chain::output_point*>(op);

    safe_chain(chain).fetch_spend(*outpoint_cpp, [&](std::error_code const& ec, libbitcoin::chain::input_point input_point) {
        *out_input_point = new libbitcoin::chain::input_point(input_point);
        res = static_cast<error_code_t>(ec.value());
        latch.count_down();
    });

    latch.count_down_and_wait();
    return res;
}

//It is the user's responsibility to release the history returned in the callback
void chain_fetch_history(chain_t chain, void* ctx, payment_address_t address, uint64_t /*size_t*/ limit, uint64_t /*size_t*/ from_height, history_fetch_handler_t handler) {
    libbitcoin::wallet::payment_address const& address_cpp = *static_cast<const libbitcoin::wallet::payment_address*>(address);

    safe_chain(chain).fetch_history(address_cpp, limit, from_height, [chain, ctx, handler](std::error_code const& ec, libbitcoin::chain::history_compact::list history) {
        auto new_history = new libbitcoin::chain::history_compact::list(history);
        handler(chain, ctx, static_cast<error_code_t>(ec.value()), new_history);
    });
}

//It is the user's responsibility to release the history returned in the callback
error_code_t chain_get_history(chain_t chain, payment_address_t address, uint64_t /*size_t*/ limit, uint64_t /*size_t*/ from_height, history_compact_list_t* out_history) {
    boost::latch latch(2); //Note: workaround to fix an error on some versions of Boost.Threads
    error_code_t res;

    libbitcoin::wallet::payment_address const& address_cpp = *static_cast<const libbitcoin::wallet::payment_address*>(address);

    safe_chain(chain).fetch_history(address_cpp, limit, from_height, [&](std::error_code const& ec, libbitcoin::chain::history_compact::list history) {
        *out_history = new libbitcoin::chain::history_compact::list(history);
        res = static_cast<error_code_t>(ec.value());
        latch.count_down();
    });

    latch.count_down_and_wait();
    return res;
}

void chain_fetch_stealth(chain_t chain, void* ctx, binary_t filter, uint64_t from_height, stealth_fetch_handler_t handler) {
	auto* filter_cpp_ptr = static_cast<const libbitcoin::binary*>(filter);
	libbitcoin::binary const& filter_cpp  = *filter_cpp_ptr;

    safe_chain(chain).fetch_stealth(filter_cpp, from_height, [chain, ctx, handler](std::error_code const& ec, libbitcoin::chain::stealth_compact::list stealth) {
        auto new_stealth = new libbitcoin::chain::stealth_compact::list(stealth);
        handler(chain, ctx, static_cast<error_code_t>(ec.value()), new_stealth);
    });
} 


error_code_t chain_get_stealth(chain_t chain, void* ctx, binary_t filter, uint64_t from_height, stealth_compact_list_t* out_list) {
    boost::latch latch(2); //Note: workaround to fix an error on some versions of Boost.Threads
    error_code_t res;

	auto* filter_cpp_ptr = static_cast<const libbitcoin::binary*>(filter);
	libbitcoin::binary const& filter_cpp  = *filter_cpp_ptr;

    safe_chain(chain).fetch_stealth(filter_cpp, from_height, [&](std::error_code const& ec, libbitcoin::chain::stealth_compact::list stealth) {
        *out_list = new libbitcoin::chain::stealth_compact::list(stealth);
        res = static_cast<error_code_t>(ec.value());
        latch.count_down();
    });
    
    latch.count_down_and_wait();
    return res;
}



// ------------------------------------------------------------------
//virtual void fetch_block_locator(const chain::block::indexes& heights, block_locator_fetch_handler handler) const = 0;

//void chain_fetch_block_locator(chain_t chain, void* ctx, block_indexes_t heights, block_locator_fetch_handler_t handler) {
//    auto const& heights_cpp = chain_block_indexes_const_cpp(heights);
//
//    safe_chain(chain).fetch_block_locator(heights_cpp, [chain, ctx, handler](std::error_code const& ec, libbitcoin::get_headers_ptr headers) {
//        //TODO: check if the pointer is set, before dereferencing
//        auto* new_headers = new libbitcoin::message::get_headers(*headers);
//        handler(chain, ctx, static_cast<error_code_t>(ec.value()), new_headers);
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
//    safe_chain(chain).fetch_block_locator(heights_cpp, [&](std::error_code const& ec, libbitcoin::get_headers_ptr headers) {
//        //TODO: check if the pointer is set, before dereferencing
//        *out_headers = new libbitcoin::message::get_headers(*headers);
//        res = static_cast<error_code_t>(ec.value());
//        latch.count_down();
//    });
//
//    latch.count_down_and_wait();
//    return res;
//}



// ------------------------------------------------------------------
//virtual void fetch_locator_block_hashes(get_blocks_const_ptr locator, const hash_digest& threshold, size_t limit, inventory_fetch_handler handler) const = 0;

//void chain_fetch_locator_block_hashes(chain_t chain, void* ctx, get_blocks_ptr_t locator, hash_t threshold, uint64_t /*size_t*/ limit, inventory_fetch_handler handler) {
//}


//virtual void fetch_locator_block_headers(get_headers_const_ptr locator, const hash_digest& threshold, size_t limit, locator_block_headers_fetch_handler handler) const = 0;
//

//// Transaction Pool.
////-------------------------------------------------------------------------
//
//virtual void fetch_template(merkle_block_fetch_handler handler) const = 0;
//virtual void fetch_mempool(size_t count_limit, uint64_t minimum_fee, inventory_fetch_handler handler) const = 0;
//
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

block_t cast_block(libbitcoin::message::block const& x) {
    return const_cast<libbitcoin::message::block*>(&x);    
}

void chain_subscribe_blockchain(executor_t exec, chain_t chain, void* ctx, subscribe_blockchain_handler_t handler) {
    const auto throttling_interval = std::chrono::seconds(10);
    static auto last_callback_time = std::chrono::steady_clock::now();

    safe_chain(chain).subscribe_blockchain([exec, chain, ctx, handler](std::error_code const& ec, size_t fork_height, libbitcoin::block_const_ptr_list_const_ptr incoming, libbitcoin::block_const_ptr_list_const_ptr replaced_blocks) {

        if (safe_chain(chain).is_stale()) {
            return 1;
        }

        if(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - last_callback_time) < throttling_interval) {
            return 1;
        }
        last_callback_time = std::chrono::steady_clock::now();

        block_list_t incoming_cpp = nullptr;
        if (incoming) {
            incoming_cpp = chain_block_list_construct_default();
            for (auto&& x : *incoming) {
                // auto new_block = new libbitcoin::message::block(*x);
                // chain_block_list_push_back(incoming_cpp, new_block);
                chain_block_list_push_back(incoming_cpp, cast_block(*x));
            }
        }

        block_list_t replaced_blocks_cpp = nullptr;
        if (replaced_blocks) {
            replaced_blocks_cpp = chain_block_list_construct_default();
            for (auto&& x : *replaced_blocks) {
                // auto new_block = new libbitcoin::message::block(*x);
                // chain_block_list_push_back(replaced_blocks_cpp, new_block);
                // chain_block_list_push_back_const(replaced_blocks_cpp, x.get());
                chain_block_list_push_back(replaced_blocks_cpp, cast_block(*x));
            }
        }
       
        auto res = handler(exec, chain, ctx, static_cast<error_code_t>(ec.value()), fork_height, incoming_cpp, replaced_blocks_cpp);
        
        return res;
    });
}

void chain_subscribe_transaction(executor_t exec, chain_t chain, void* ctx, subscribe_transaction_handler_t handler) {
    safe_chain(chain).subscribe_transaction([exec, chain, ctx, handler](std::error_code const& ec, libbitcoin::transaction_const_ptr tx) {
        transaction_t new_tx = nullptr;
        if (tx) {
            new_tx = new libbitcoin::message::transaction(*tx);
        }
        auto res = handler(exec, chain, ctx, static_cast<error_code_t>(ec.value()), new_tx);
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
        handler(chain, ctx, static_cast<error_code_t>(ec.value()));
    });
}

int chain_organize_block_sync(chain_t chain, block_t block) {
    boost::latch latch(2); //Note: workaround to fix an error on some versions of Boost.Threads
    error_code_t res;

    safe_chain(chain).organize(block_shared(block), [&](std::error_code const& ec) {
        res = static_cast<error_code_t>(ec.value());
        latch.count_down();
    });

    latch.count_down_and_wait();
    return res;
}

void chain_organize_transaction(chain_t chain, void* ctx, transaction_t transaction, result_handler_t handler) {
    safe_chain(chain).organize(tx_shared(transaction), [chain, ctx, handler](std::error_code const& ec) {
        handler(chain, ctx, static_cast<error_code_t>(ec.value()));
    });
}

int chain_organize_transaction_sync(chain_t chain, transaction_t transaction) {
    boost::latch latch(2); //Note: workaround to fix an error on some versions of Boost.Threads
    error_code_t res;

    safe_chain(chain).organize(tx_shared(transaction), [&](std::error_code const& ec) {
        res = static_cast<error_code_t>(ec.value());
        latch.count_down();
    });

    latch.count_down_and_wait();
    return res;
}

//-------------------------------------------------------------------------

////It is the user's responsibility to release the transaction returned
//transaction_t chain_hex_to_tx(char const* tx_hex) {
//
//    static auto const version = libbitcoin::message::version::level::canonical;
//
////    auto const tx = std::make_shared<libbitcoin::message::transaction>();
//    auto* tx = new libbitcoin::message::transaction;
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

void chain_validate_tx(chain_t chain, void* ctx, transaction_t tx, validate_tx_handler_t handler) {
    safe_chain(chain).organize(tx_shared(tx), [chain, ctx, handler](std::error_code const& ec) {
//        auto is_error = (bool)ec;
        if (handler != nullptr) {
            if (ec) {
                auto* msg_str = new std::string(ec.message());
                handler(chain, ctx, static_cast<error_code_t>(ec.value()), msg_str->c_str());
            } else {
                handler(chain, ctx, static_cast<error_code_t>(ec.value()), nullptr);
            }
        }
    });
}


// Properties.
//-------------------------------------------------------------------------

/// True if the blockchain is stale based on configured age limit.
int /*bool*/ chain_is_stale(chain_t chain) {
    return static_cast<int>(safe_chain(chain).is_stale());
}


/// Get a reference to the blockchain configuration settings.
// const settings& chain_settings() const;



} /* extern "C" */
