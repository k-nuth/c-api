/**
 * Copyright (c) 2016-2018 Bitprim Inc.
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

#include <bitcoin/bitcoin/message/compact_block.hpp>

#include <bitprim/nodecint/chain/compact_block.h>
#include <bitprim/nodecint/helpers.hpp>
#include <bitprim/nodecint/type_conversions.h>

BITPRIM_CONV_DEFINE(chain, compact_block_t, libbitcoin::message::compact_block, compact_block)

// ---------------------------------------------------------------------------
extern "C" {

header_t chain_compact_block_header(compact_block_t block) {
    return &chain_compact_block_cpp(block).header();
}

bool_t chain_compact_block_is_valid(compact_block_t block) {
    return bitprim::bool_to_int(chain_compact_block_const_cpp(block).is_valid());
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
