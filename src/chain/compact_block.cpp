// Copyright (c) 2016-2023 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/domain/message/compact_block.hpp>

#include <kth/capi/chain/compact_block.h>
#include <kth/capi/helpers.hpp>
#include <kth/capi/type_conversions.h>

KTH_CONV_DEFINE(chain, kth_compact_block_t, kth::domain::message::compact_block, compact_block)

// ---------------------------------------------------------------------------
extern "C" {

kth_header_t kth_chain_compact_block_header(kth_compact_block_t block) {
    return &kth_chain_compact_block_cpp(block).header();
}

kth_bool_t kth_chain_compact_block_is_valid(kth_compact_block_t block) {
    return kth::bool_to_int(kth_chain_compact_block_const_cpp(block).is_valid());
}

kth_size_t kth_chain_compact_block_serialized_size(kth_compact_block_t block, uint32_t version) {
    return kth_chain_compact_block_const_cpp(block).serialized_size(version);
}

kth_size_t kth_chain_compact_block_transaction_count(kth_compact_block_t block) {
    return kth_chain_compact_block_const_cpp(block).transactions().size();
}

 kth_transaction_t kth_chain_compact_block_transaction_nth(kth_compact_block_t block, kth_size_t n) {
    //precondition: n >=0 && n < transactions().size()

    auto* blk = &kth_chain_compact_block_cpp(block);
    auto& tx_n = blk->transactions()[n];
    return &tx_n;
}

uint64_t kth_chain_compact_block_nonce(kth_compact_block_t block) {
    return kth_chain_compact_block_const_cpp(block).nonce();
}

void kth_chain_compact_block_destruct(kth_compact_block_t block) {
    delete &kth_chain_compact_block_cpp(block);
}

void kth_chain_compact_block_reset(kth_compact_block_t block) {
    kth_chain_compact_block_cpp(block).reset();
}

} // extern "C"
