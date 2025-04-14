// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/capi/chain/utxo.h>

#include <kth/capi/conversions.hpp>
#include <kth/capi/helpers.hpp>

KTH_CONV_DEFINE(chain, kth_utxo_t, kth::domain::chain::utxo, utxo)

// ---------------------------------------------------------------------------
extern "C" {

kth_utxo_t kth_chain_utxo_construct() {
    // return std::make_unique<kth::domain::chain::utxo>().release();
    return new kth::domain::chain::utxo;
}

kth_utxo_t kth_chain_utxo_construct_from_hash_index_amount(kth_hash_t const* hash, uint32_t index, uint64_t amount) {
    auto hash_cpp = kth::to_array(hash->hash);
    auto ret = new kth::domain::chain::utxo(kth::domain::chain::output_point(hash_cpp, index), amount, std::nullopt);
    return ret;
}

kth_utxo_t kth_chain_utxo_construct_from_hash_index_amount_fungible(kth_hash_t const* hash, uint32_t index, uint64_t amount, kth_hash_t const* token_category, uint64_t token_amount) {
    auto hash_cpp = kth::to_array(hash->hash);
    auto token_category_cpp = kth::to_array(token_category->hash);

    kth::domain::chain::token_data_t token_data {
        .id = token_category_cpp,
        .data = kth::domain::chain::fungible {
            .amount = kth::domain::chain::amount_t{int64_t(token_amount)}
        }
    };
    auto ret = new kth::domain::chain::utxo(
        kth::domain::chain::output_point(hash_cpp, index),
        amount,
        token_data);
    return ret;
}

kth_utxo_t kth_chain_utxo_construct_from_hash_index_amount_non_fungible(kth_hash_t const* hash, uint32_t index, uint64_t amount, kth_hash_t const* token_category, kth_token_capability_t capability, uint8_t* commitment_data, kth_size_t commitment_n) {
    auto hash_cpp = kth::to_array(hash->hash);
    auto token_category_cpp = kth::to_array(token_category->hash);
    auto capability_cpp = kth::token_capability_to_cpp(capability);
    kth::data_chunk commitment_cpp(commitment_data, std::next(commitment_data, commitment_n));

    kth::domain::chain::token_data_t token_data {
        token_category_cpp,
        kth::domain::chain::non_fungible{capability_cpp, std::move(commitment_cpp)}
    };

    auto ret = new kth::domain::chain::utxo(
        kth::domain::chain::output_point(hash_cpp, index),
        amount,
        token_data);
    return ret;
}

kth_utxo_t kth_chain_utxo_construct_from_hash_index_amount_both(kth_hash_t const* hash, uint32_t index, uint64_t amount, kth_hash_t const* token_category, uint64_t token_amount, kth_token_capability_t capability, uint8_t* commitment_data, kth_size_t commitment_n) {
    auto hash_cpp = kth::to_array(hash->hash);
    auto token_category_cpp = kth::to_array(token_category->hash);
    auto capability_cpp = kth::token_capability_to_cpp(capability);
    kth::data_chunk commitment_cpp(commitment_data, std::next(commitment_data, commitment_n));


    kth::domain::chain::token_data_t token_data {
        token_category_cpp,
        kth::domain::chain::both_kinds{
            kth::domain::chain::fungible{
                kth::domain::chain::amount_t{int64_t(token_amount)}
            },
            kth::domain::chain::non_fungible{
                capability_cpp,
                std::move(commitment_cpp)
            }
        }
    };

    auto ret = new kth::domain::chain::utxo(
        kth::domain::chain::output_point(hash_cpp, index),
        amount,
        token_data);
    return ret;
}



void kth_chain_utxo_destruct(kth_utxo_t utxo) {
    delete &kth_chain_utxo_cpp(utxo);
}

// Getters

kth_hash_t kth_chain_utxo_get_hash(kth_utxo_t utxo) {
    auto const& hash_cpp = kth_chain_utxo_const_cpp(utxo).point().hash();
    return kth::to_hash_t(hash_cpp);
}

void kth_chain_utxo_get_hash_out(kth_utxo_t utxo, kth_hash_t* out_hash) {
    auto const& hash_cpp = kth_chain_utxo_const_cpp(utxo).point().hash();
    kth::copy_c_hash(hash_cpp, out_hash);
}

uint32_t kth_chain_utxo_get_index(kth_utxo_t utxo) {
    return kth_chain_utxo_const_cpp(utxo).point().index();
}

uint64_t kth_chain_utxo_get_amount(kth_utxo_t utxo) {
    return kth_chain_utxo_const_cpp(utxo).amount();
}

kth_output_t kth_chain_utxo_get_cached_output(kth_utxo_t utxo) {
    auto& output = kth_chain_utxo_const_cpp(utxo).point().validation.cache;
    return &output;
}

kth_bool_t kth_chain_utxo_has_token_data(kth_utxo_t utxo) {
    return kth_chain_utxo_const_cpp(utxo).token_data() ?
        kth::bool_to_int(true) :
        kth::bool_to_int(false);
}

kth_token_data_t kth_chain_utxo_get_token_data(kth_utxo_t utxo) {
    auto& utxo_cpp = kth_chain_utxo_cpp(utxo);
    if ( ! utxo_cpp.token_data()) {
        return nullptr;
    }
    return &utxo_cpp.token_data().value();
}

kth_hash_t kth_chain_utxo_get_token_category(kth_utxo_t utxo) {
    auto const& token_data = kth_chain_utxo_const_cpp(utxo).token_data();
    if ( ! token_data) {
        return kth::to_hash_t(kth::null_hash);
    }
    auto const& token_category_cpp = token_data->id;
    return kth::to_hash_t(token_category_cpp);
}

void kth_chain_utxo_get_token_category_out(kth_utxo_t utxo, kth_hash_t* out_token_category) {
    auto const& token_data = kth_chain_utxo_const_cpp(utxo).token_data();
    if ( ! token_data) {
        kth::copy_c_hash(kth::null_hash, out_token_category);
        return;
    }
    auto const& token_category_cpp = token_data->id;
    kth::copy_c_hash(token_category_cpp, out_token_category);
}

uint64_t kth_chain_utxo_get_token_amount(kth_utxo_t utxo) {
    auto const& token_data = kth_chain_utxo_const_cpp(utxo).token_data();
    if ( ! token_data) {
        return kth::max_uint64;
    }
    if (std::holds_alternative<kth::domain::chain::fungible>(token_data->data)) {
        return uint64_t(std::get<kth::domain::chain::fungible>(token_data->data).amount);
    }
    if (std::holds_alternative<kth::domain::chain::both_kinds>(token_data->data)) {
        return uint64_t(std::get<kth::domain::chain::both_kinds>(token_data->data).first.amount);
    }
    return kth::max_uint64;
}

kth_token_capability_t kth_chain_utxo_get_token_capability(kth_utxo_t utxo) {
    auto const& token_data_opt = kth_chain_utxo_const_cpp(utxo).token_data();
    if ( ! token_data_opt) {
        return kth_token_capability_none;
    }
    auto const& token_data = *token_data_opt;
    if (std::holds_alternative<kth::domain::chain::non_fungible>(token_data.data)) {
        auto const& non_fungible_cpp = std::get<kth::domain::chain::non_fungible>(token_data.data);
        return kth::token_capability_to_c(non_fungible_cpp.capability);
    }
    if (std::holds_alternative<kth::domain::chain::both_kinds>(token_data.data)) {
        auto const& both_kinds_cpp = std::get<kth::domain::chain::both_kinds>(token_data.data);
        auto const& non_fungible_cpp = both_kinds_cpp.second;
        return kth::token_capability_to_c(non_fungible_cpp.capability);
    }
    return kth_token_capability_none; // TODO: this is not a good way to signal an error
}

uint8_t const* kth_chain_utxo_get_token_commitment(kth_utxo_t utxo, kth_size_t* out_size) {
    auto const& token_data_opt = kth_chain_utxo_const_cpp(utxo).token_data();
    if ( ! token_data_opt) {
        *out_size = 0;
        return nullptr;
    }
    auto const& token_data = *token_data_opt;
    if (std::holds_alternative<kth::domain::chain::non_fungible>(token_data.data)) {
        auto const& non_fungible_cpp = std::get<kth::domain::chain::non_fungible>(token_data.data);
        return kth::create_c_array(non_fungible_cpp.commitment, *out_size);
    }
    if (std::holds_alternative<kth::domain::chain::both_kinds>(token_data.data)) {
        auto const& both_kinds_cpp = std::get<kth::domain::chain::both_kinds>(token_data.data);
        auto const& non_fungible_cpp = both_kinds_cpp.second;
        return kth::create_c_array(non_fungible_cpp.commitment, *out_size);
    }

    *out_size = 0;
    return nullptr;
}

// Setters

void kth_chain_utxo_set_hash(kth_utxo_t utxo, kth_hash_t const* hash) {
    auto hash_cpp = kth::to_array(hash->hash);
    kth_chain_utxo_cpp(utxo).point().set_hash(hash_cpp);
}

void kth_chain_utxo_set_index(kth_utxo_t utxo, uint32_t index) {
    kth_chain_utxo_cpp(utxo).point().set_index(index);
}

void kth_chain_utxo_set_amount(kth_utxo_t utxo, uint64_t amount) {
    kth_chain_utxo_cpp(utxo).set_amount(amount);
}

void kth_chain_utxo_set_cached_output(kth_utxo_t utxo, kth_output_t output) {
    kth_chain_utxo_cpp(utxo).point().validation.cache = kth_chain_output_const_cpp(output);
}

void kth_chain_utxo_set_token_data(kth_utxo_t utxo, kth_token_data_t token_data) {
    auto const& token_data_cpp = kth_chain_token_data_const_cpp(token_data);
    kth_chain_utxo_cpp(utxo).set_token_data(token_data_cpp);
}

void kth_chain_utxo_set_fungible_token_data(kth_utxo_t utxo, kth_hash_t const* token_category, int64_t token_amount) {
    auto token_category_cpp = kth::to_array(token_category->hash);

    kth::domain::chain::token_data_t token_data {
        .id = token_category_cpp,
        .data = kth::domain::chain::fungible {
            .amount = kth::domain::chain::amount_t{int64_t(token_amount)}
        }
    };
    kth_chain_utxo_cpp(utxo).set_token_data(token_data);
}

void kth_chain_utxo_set_token_category(kth_utxo_t utxo, kth_hash_t const* token_category) {
    auto token_category_cpp = kth::to_array(token_category->hash);
    auto& utxo_cpp = kth_chain_utxo_cpp(utxo);
    if (utxo_cpp.token_data()) {
        utxo_cpp.token_data()->id = token_category_cpp;
    } else {
        kth::domain::chain::token_data_t token_data {
            .id = token_category_cpp,
        };
        utxo_cpp.set_token_data(token_data);
    }
}

void kth_chain_utxo_set_token_amount(kth_utxo_t utxo, int64_t token_amount) {
    auto& utxo_cpp = kth_chain_utxo_cpp(utxo);
    if (utxo_cpp.token_data()) {
        if (std::holds_alternative<kth::domain::chain::fungible>(utxo_cpp.token_data()->data)) {
            std::get<kth::domain::chain::fungible>(utxo_cpp.token_data()->data).amount = kth::domain::chain::amount_t{int64_t(token_amount)};
        } else if (std::holds_alternative<kth::domain::chain::both_kinds>(utxo_cpp.token_data()->data)) {
            std::get<kth::domain::chain::both_kinds>(utxo_cpp.token_data()->data).first.amount = kth::domain::chain::amount_t{int64_t(token_amount)};
        }
    } else {
        kth::domain::chain::token_data_t token_data {
            .id = kth::null_hash,
            .data = kth::domain::chain::fungible {
                .amount = kth::domain::chain::amount_t{int64_t(token_amount)}
            }
        };
        utxo_cpp.set_token_data(token_data);
    }
}

} // extern "C"
