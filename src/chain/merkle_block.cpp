// Copyright (c) 2016-2023 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/capi/chain/merkle_block.h>

#include <kth/domain/message/merkle_block.hpp>
#include <kth/domain/message/transaction.hpp>

#include <kth/capi/helpers.hpp>
#include <kth/capi/type_conversions.h>

KTH_CONV_DEFINE(chain, kth_merkleblock_t, kth::domain::message::merkle_block, merkle_block)

// ---------------------------------------------------------------------------
extern "C" {

void kth_chain_merkle_block_destruct(kth_merkleblock_t block) {
    delete &kth_chain_merkle_block_cpp(block);
}

kth_hash_t kth_chain_merkle_block_hash_nth(kth_merkleblock_t block, kth_size_t n) {
    //precondition: n >=0 && n < hashes().size()

    auto* blk = &kth_chain_merkle_block_cpp(block);
    auto& hash_n = blk->hashes()[n];
    return kth::to_hash_t(hash_n);
}

void kth_chain_merkle_block_hash_nth_out(kth_merkleblock_t block, kth_size_t n, kth_hash_t* out_hash) {
    //precondition: n >=0 && n < hashes().size()

    auto* blk = &kth_chain_merkle_block_cpp(block);
    auto& hash_n = blk->hashes()[n];
    kth::copy_c_hash(hash_n, out_hash);
}

kth_header_t kth_chain_merkle_block_header(kth_merkleblock_t block) {
    return &kth_chain_merkle_block_cpp(block).header();
}

kth_bool_t kth_chain_merkle_block_is_valid(kth_merkleblock_t block) {
    return kth::bool_to_int(kth_chain_merkle_block_const_cpp(block).is_valid());
}

kth_size_t kth_chain_merkle_block_hash_count(kth_merkleblock_t block) {
    return kth_chain_merkle_block_const_cpp(block).hashes().size();
}

kth_size_t kth_chain_merkle_block_serialized_size(kth_merkleblock_t block, uint32_t version) {
    return kth_chain_merkle_block_const_cpp(block).serialized_size(version);
}

kth_size_t kth_chain_merkle_block_total_transaction_count(kth_merkleblock_t block) {
    return kth_chain_merkle_block_const_cpp(block).total_transactions();
}

void kth_chain_merkle_block_reset(kth_merkleblock_t block) {
    kth_chain_merkle_block_cpp(block).reset();
}

} // extern "C"
