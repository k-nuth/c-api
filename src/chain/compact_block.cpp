// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#include <bitcoin/bitcoin/message/compact_block.hpp>

#include <knuth/nodecint/chain/compact_block.h>
#include <knuth/nodecint/helpers.hpp>
#include <knuth/nodecint/type_conversions.h>

KTH_CONV_DEFINE(chain, compact_block_t, kth::message::compact_block, compact_block)

// ---------------------------------------------------------------------------
extern "C" {

header_t chain_compact_block_header(compact_block_t block) {
    return &chain_compact_block_cpp(block).header();
}

bool_t chain_compact_block_is_valid(compact_block_t block) {
    return knuth::bool_to_int(chain_compact_block_const_cpp(block).is_valid());
}

uint64_t /*size_t*/ chain_compact_block_serialized_size(compact_block_t block, uint32_t version) {
    return chain_compact_block_const_cpp(block).serialized_size(version);
}

uint64_t /*size_t*/ chain_compact_block_transaction_count(compact_block_t block) {
    return chain_compact_block_const_cpp(block).transactions().size();
}

transaction_t chain_compact_block_transaction_nth(compact_block_t block, uint64_t /*size_t*/ n) {
    //precondition: n >=0 && n < transactions().size()

    auto* blk = &chain_compact_block_cpp(block);
    auto& tx_n = blk->transactions()[n];
    return &tx_n;
}

uint64_t chain_compact_block_nonce(compact_block_t block) {
    return chain_compact_block_const_cpp(block).nonce();
}

void chain_compact_block_destruct(compact_block_t block) {
    delete &chain_compact_block_cpp(block);
}

void chain_compact_block_reset(compact_block_t block) {
    chain_compact_block_cpp(block).reset();
}

} // extern "C"
