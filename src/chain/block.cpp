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

#include <bitprim/nodecint/chain/block.h>

#include <bitprim/nodecint/convertions.hpp>
#include <bitprim/nodecint/helpers.hpp>

#include <bitcoin/bitcoin/message/transaction.hpp>


// libbitcoin::message::block const& chain_block_const_cpp(block_t block) {
//     return *static_cast<libbitcoin::message::block const*>(block);
// }

// libbitcoin::message::block& chain_block_cpp(block_t block) {
//     return *static_cast<libbitcoin::message::block*>(block);
// }
BITPRIM_CONV_DEFINE(chain, block_t, libbitcoin::message::block, block)


// inline                                                         
// libbitcoin::message::block const& chain_block_const_cpp(block_t o) {       
//     return *static_cast<libbitcoin::message::block const*>(o);                   
// }                                                              
// inline                                                         
// libbitcoin::message::block& chain_block_cpp(block_t o) {       
//     return *static_cast<libbitcoin::message::block*>(o);       
// }


// ---------------------------------------------------------------------------
extern "C" {

block_t chain_block_construct_default() {
    return new libbitcoin::message::block();
}

block_t chain_block_construct(header_t header, transaction_list_t transactions) {

    auto const& header_cpp = *static_cast<libbitcoin::chain::header const*>(header);
    auto const& txs_cpp = *static_cast<libbitcoin::chain::transaction::list const*>(transactions);

    return new libbitcoin::message::block(header_cpp, txs_cpp);
}

void chain_block_destruct(block_t block) {
    delete &chain_block_cpp(block);
}

bool_t chain_block_is_valid(block_t block) {
    return bitprim::bool_to_int(chain_block_const_cpp(block).is_valid());
}

header_t chain_block_header(block_t block) {
    return &chain_block_cpp(block).header();
}

hash_t chain_block_hash(block_t block) {
    auto const& hash_cpp = chain_block_const_cpp(block).hash();
    return bitprim::to_hash_t(hash_cpp);
}

void chain_block_hash_out(block_t block, hash_t* out_hash) {
    auto const& hash_cpp = chain_block_const_cpp(block).hash();
    // std::memcpy(static_cast<void*>(out_hash->hash), hash_cpp.data(), BITCOIN_HASH_SIZE);
    bitprim::copy_c_hash(hash_cpp, out_hash);
}

//deprecated
char const* chain_block_proof(block_t block) {
    auto proof_str = chain_block_const_cpp(block).proof().str();
    auto* proof_c_str = static_cast<char*>(malloc((proof_str.size() + 1) * sizeof(char)));
    std::copy_n(proof_str.begin(), proof_str.size() + 1, proof_c_str);
    return proof_c_str;
}

char const* chain_block_proof_str(block_t block) {
    auto proof_str = chain_block_const_cpp(block).proof().str();
    return bitprim::create_c_str(proof_str);
}

// Warning: breaking change
uint64_t /*size_t*/ chain_block_transaction_count(block_t block) {
    return chain_block_const_cpp(block).transactions().size();
}

// Warning: breaking change
transaction_t chain_block_transaction_nth(block_t block, uint64_t /*size_t*/ n) {
    //precondition: n >=0 && n < transactions().size()

    auto* blk = &chain_block_cpp(block);
    auto& tx_n = blk->transactions()[n];
    return &tx_n;
}

// // Warning: breaking change
// transaction_list_t chain_block_transactions(block_t block) {
//     auto& block_cpp = chain_block_cpp(block);
//     return chain_transaction_list_construct_from_cpp(block_cpp.transactions()); // TODO(fernando): block::transactions() is deprecated... check how to do it better...
// }

// -----------------------

uint64_t /*size_t*/ chain_block_serialized_size(block_t block, uint32_t version) {
    return chain_block_const_cpp(block).serialized_size(version);
}

/*static*/
uint64_t chain_block_subsidy(uint64_t /*size_t*/ height) {
    return libbitcoin::message::block::subsidy(height);
}

//static uint256_t chain_block_proof(uint32_t bits) {}

///*static*/
//uint256_t chain_block_proof(uint64_t /*size_t*/ height) {
//    return libbitcoin::message::block::proof(height);
//}

uint64_t chain_block_fees(block_t block) {
    return chain_block_const_cpp(block).fees();
}

uint64_t chain_block_claim(block_t block) {
    return chain_block_const_cpp(block).claim();
}

uint64_t chain_block_reward(block_t block, uint64_t /*size_t*/ height) {
    return chain_block_const_cpp(block).reward(height);
}

//uint256_t chain_block_proof(block_t block) {}
//hash_digest chain_block_generate_merkle_root(block_t block) {}

////Note: The user is responsible for the resource release
//hash_t chain_block_generate_merkle_root(block_t block) {
//    auto hash_cpp = chain_block_const_cpp(block).generate_merkle_root();
//    uint8_t* ret = (uint8_t*)malloc(hash_cpp.size() * sizeof(uint8_t));
//    std::copy_n(std::begin(hash_cpp), hash_cpp.size(), ret);
//    return ret;
//}

hash_t chain_block_generate_merkle_root(block_t block) {
    auto hash_cpp = chain_block_const_cpp(block).generate_merkle_root();
    return bitprim::to_hash_t(hash_cpp);
}

void chain_block_generate_merkle_root_out(block_t block, hash_t* out_merkle) {
    auto hash_cpp = chain_block_const_cpp(block).generate_merkle_root();
    // std::memcpy(static_cast<void*>(out_merkle->hash), hash_cpp.data(), BITCOIN_HASH_SIZE);
    bitprim::copy_c_hash(hash_cpp, out_merkle);
}

uint64_t /*size_t*/ chain_block_signature_operations(block_t block) {
    return chain_block_const_cpp(block).signature_operations();
}

uint64_t /*size_t*/ chain_block_signature_operations_bip16_active(block_t block, bool_t bip16_active) {
#ifdef BITPRIM_CURRENCY_BCH
    bool_t bip141_active = 0;
#else
    bool_t bip141_active = 1;
#endif

    return chain_block_const_cpp(block).signature_operations(bitprim::int_to_bool(bip16_active), bitprim::int_to_bool(bip141_active));
}

uint64_t /*size_t*/ chain_block_total_inputs(block_t block, bool_t with_coinbase=1) {
    return chain_block_const_cpp(block).total_inputs(bitprim::int_to_bool(with_coinbase));
}

bool_t chain_block_is_extra_coinbases(block_t block) {
    return bitprim::bool_to_int(chain_block_const_cpp(block).is_extra_coinbases());
}

bool_t chain_block_is_final(block_t block, uint64_t /*size_t*/ height, uint32_t block_time) {
    return bitprim::bool_to_int(chain_block_const_cpp(block).is_final(height, block_time));
}

bool_t chain_block_is_distinct_transaction_set(block_t block) {
    return bitprim::bool_to_int(chain_block_const_cpp(block).is_distinct_transaction_set());
}

bool_t chain_block_is_valid_coinbase_claim(block_t block, uint64_t /*size_t*/ height) {
    return bitprim::bool_to_int(chain_block_const_cpp(block).is_valid_coinbase_claim(height));
}

bool_t chain_block_is_valid_coinbase_script(block_t block, uint64_t /*size_t*/ height) {
    return bitprim::bool_to_int(chain_block_const_cpp(block).is_valid_coinbase_script(height));
}

bool_t chain_block_is_internal_double_spend(block_t block) {
    return bitprim::bool_to_int(chain_block_const_cpp(block).is_internal_double_spend());
}

bool_t chain_block_is_valid_merkle_root(block_t block) {
    return bitprim::bool_to_int(chain_block_const_cpp(block).is_valid_merkle_root());
}

uint8_t const* chain_block_to_data(block_t block, bool_t wire, uint64_t* /*size_t*/ out_size) {
    auto block_data = chain_block_const_cpp(block).to_data(wire);
    return bitprim::create_c_array(block_data, *out_size);
}

} // extern "C"
