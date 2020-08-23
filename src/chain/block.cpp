// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/capi/chain/block.h>

#include <kth/capi/conversions.hpp>
#include <kth/capi/helpers.hpp>

#include <kth/domain/message/transaction.hpp>


KTH_CONV_DEFINE(chain, kth_block_t, kth::domain::message::block, block)

// ---------------------------------------------------------------------------
extern "C" {

kth_block_t kth_chain_block_construct_default() {
    return new kth::domain::message::block();
}

kth_block_t kth_chain_block_construct(kth_header_t header, kth_transaction_list_t transactions) {
    auto const& header_cpp = kth_chain_header_const_cpp(header);
    auto const& txs_cpp = *static_cast<kth::domain::chain::transaction::list const*>(transactions);
    // auto const& txs_cpp = kth_chain_transaction_list_const_cpp(transactions);
    return new kth::domain::message::block(header_cpp, txs_cpp);
}

kth_block_t kth_chain_block_factory_from_data(uint32_t version, uint8_t* data, uint64_t n) {
    kth::data_chunk data_cpp(data, std::next(data, n));
    auto block = kth::domain::create<kth::domain::message::block>(version, data_cpp);
    return kth::move_or_copy_and_leak(std::move(block));
}

void kth_chain_block_destruct(kth_block_t block) {
    delete &kth_chain_block_cpp(block);
}

kth_bool_t kth_chain_block_is_valid(kth_block_t block) {
    return kth::bool_to_int(kth_chain_block_const_cpp(block).is_valid());
}

kth_header_t kth_chain_block_header(kth_block_t block) {
    return &kth_chain_block_cpp(block).header();
}

kth_hash_t kth_chain_block_hash(kth_block_t block) {
    auto const& hash_cpp = kth_chain_block_const_cpp(block).hash();
    return kth::to_hash_t(hash_cpp);
}

void kth_chain_block_hash_out(kth_block_t block, kth_hash_t* out_hash) {
    auto const& hash_cpp = kth_chain_block_const_cpp(block).hash();
    kth::copy_c_hash(hash_cpp, out_hash);
}

//deprecated
char const* kth_chain_block_proof(kth_block_t block) {
    auto proof_str = kth_chain_block_const_cpp(block).proof().str();
    auto* proof_c_str = static_cast<char*>(malloc((proof_str.size() + 1) * sizeof(char)));
    std::copy_n(proof_str.begin(), proof_str.size() + 1, proof_c_str);
    return proof_c_str;
}

char const* kth_chain_block_proof_str(kth_block_t block) {
    auto proof_str = kth_chain_block_const_cpp(block).proof().str();
    return kth::create_c_str(proof_str);
}

// Warning: breaking change
kth_size_t kth_chain_block_transaction_count(kth_block_t block) {
    return kth_chain_block_const_cpp(block).transactions().size();
}

// Warning: breaking change
 kth_transaction_t kth_chain_block_transaction_nth(kth_block_t block, kth_size_t n) {
    //precondition: n >=0 && n < transactions().size()

    auto* blk = &kth_chain_block_cpp(block);
    auto& tx_n = blk->transactions()[n];
    return &tx_n;
}

// // Warning: breaking change
// kth_transaction_list_t kth_chain_block_transactions(kth_block_t block) {
//     auto& block_cpp = kth_chain_block_cpp(block);
//     return kth_chain_transaction_list_construct_from_cpp(block_cpp.transactions()); // TODO(fernando): block::transactions() is deprecated... check how to do it better...
// }

// -----------------------

kth_size_t kth_chain_block_serialized_size(kth_block_t block, uint32_t version) {
    return kth_chain_block_const_cpp(block).serialized_size(version);
}

/*static*/
uint64_t kth_chain_block_subsidy(kth_size_t height) {
    return kth::domain::message::block::subsidy(height);
}

//static uint256_t kth_chain_block_proof(uint32_t bits) {}

///*static*/
//uint256_t kth_chain_block_proof(kth_size_t height) {
//    return kth::domain::message::block::proof(height);
//}

uint64_t kth_chain_block_fees(kth_block_t block) {
    return kth_chain_block_const_cpp(block).fees();
}

uint64_t kth_chain_block_claim(kth_block_t block) {
    return kth_chain_block_const_cpp(block).claim();
}

uint64_t kth_chain_block_reward(kth_block_t block, kth_size_t height) {
    return kth_chain_block_const_cpp(block).reward(height);
}

//uint256_t kth_chain_block_proof(kth_block_t block) {}
//hash_digest kth_chain_block_generate_merkle_root(kth_block_t block) {}

////Note: The user is responsible for the resource release
//kth_hash_t kth_chain_block_generate_merkle_root(kth_block_t block) {
//    auto hash_cpp = kth_chain_block_const_cpp(block).generate_merkle_root();
//    uint8_t* ret = (uint8_t*)malloc(hash_cpp.size() * sizeof(uint8_t));
//    std::copy_n(std::begin(hash_cpp), hash_cpp.size(), ret);
//    return ret;
//}

kth_hash_t kth_chain_block_generate_merkle_root(kth_block_t block) {
    auto hash_cpp = kth_chain_block_const_cpp(block).generate_merkle_root();
    return kth::to_hash_t(hash_cpp);
}

void kth_chain_block_generate_merkle_root_out(kth_block_t block, kth_hash_t* out_merkle) {
    auto hash_cpp = kth_chain_block_const_cpp(block).generate_merkle_root();
    kth::copy_c_hash(hash_cpp, out_merkle);
}

kth_size_t kth_chain_block_signature_operations(kth_block_t block) {
    return kth_chain_block_const_cpp(block).signature_operations();
}

kth_size_t kth_chain_block_signature_operations_bip16_active(kth_block_t block, kth_bool_t bip16_active) {
#if defined(KTH_CURRENCY_BCH)
    kth_bool_t bip141_active = 0;
#else
    kth_bool_t bip141_active = 1;
#endif

    return kth_chain_block_const_cpp(block).signature_operations(kth::int_to_bool(bip16_active), kth::int_to_bool(bip141_active));
}

kth_size_t kth_chain_block_total_inputs(kth_block_t block, kth_bool_t with_coinbase=1) {
    return kth_chain_block_const_cpp(block).total_inputs(kth::int_to_bool(with_coinbase));
}

kth_bool_t kth_chain_block_is_extra_coinbases(kth_block_t block) {
    return kth::bool_to_int(kth_chain_block_const_cpp(block).is_extra_coinbases());
}

kth_bool_t kth_chain_block_is_final(kth_block_t block, kth_size_t height, uint32_t kth_block_time) {
    return kth::bool_to_int(kth_chain_block_const_cpp(block).is_final(height, kth_block_time));
}

kth_bool_t kth_chain_block_is_distinct_transaction_set(kth_block_t block) {
    return kth::bool_to_int(kth_chain_block_const_cpp(block).is_distinct_transaction_set());
}

kth_bool_t kth_chain_block_is_valid_coinbase_claim(kth_block_t block, kth_size_t height) {
    return kth::bool_to_int(kth_chain_block_const_cpp(block).is_valid_coinbase_claim(height));
}

kth_bool_t kth_chain_block_is_valid_coinbase_script(kth_block_t block, kth_size_t height) {
    return kth::bool_to_int(kth_chain_block_const_cpp(block).is_valid_coinbase_script(height));
}

kth_bool_t kth_chain_block_is_internal_double_spend(kth_block_t block) {
    return kth::bool_to_int(kth_chain_block_const_cpp(block).is_internal_double_spend());
}

kth_bool_t kth_chain_block_is_valid_merkle_root(kth_block_t block) {
    return kth::bool_to_int(kth_chain_block_const_cpp(block).is_valid_merkle_root());
}

uint8_t const* kth_chain_block_to_data(kth_block_t block, kth_bool_t wire, kth_size_t* out_size) {
    auto block_data = kth_chain_block_const_cpp(block).to_data(wire);
    return kth::create_c_array(block_data, *out_size);
}

} // extern "C"
