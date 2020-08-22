// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/domain/message/compact_block.hpp>

#include <kth/capi/chain/compact_block.h>
#include <kth/capi/helpers.hpp>
#include <kth/capi/type_conversions.h>

KTH_CONV_DEFINE(chain, compact_kth_block_t, kth::domain::message::compact_block, compact_block)

// ---------------------------------------------------------------------------
extern "C" {

header_t kth_chain_compact_block_header(compact_kth_block_t block) {
    return &chain_compact_block_cpp(block).header();
}

bool_t kth_chain_compact_block_is_valid(compact_kth_block_t block) {
    return kth::bool_to_int(chain_compact_block_const_cpp(block).is_valid());
}

uint64_t /*size_t*/ kth_chain_compact_block_serialized_size(compact_kth_block_t block, uint32_t version) {
    return kth_chain_compact_block_const_cpp(block).serialized_size(version);
}

uint64_t /*size_t*/ kth_chain_compact_kth_block_transaction_count(compact_kth_block_t block) {
    return kth_chain_compact_block_const_cpp(block).transactions().size();
}

 kth_transaction_t kth_chain_compact_kth_block_transaction_nth(compact_kth_block_t block, uint64_t /*size_t*/ n) {
    //precondition: n >=0 && n < transactions().size()

    auto* blk = &chain_compact_block_cpp(block);
    auto& tx_n = blk->transactions()[n];
    return &tx_n;
}

uint64_t kth_chain_compact_block_nonce(compact_kth_block_t block) {
    return kth_chain_compact_block_const_cpp(block).nonce();
}

void kth_chain_compact_block_destruct(compact_kth_block_t block) {
    delete &chain_compact_block_cpp(block);
}

void kth_chain_compact_block_reset(compact_kth_block_t block) {
    kth_chain_compact_block_cpp(block).reset();
}

} // extern "C"
