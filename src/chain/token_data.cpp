// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/capi/chain/token_data.h>

#include <kth/capi/conversions.hpp>
#include <kth/capi/helpers.hpp>

#include <kth/domain/chain/token_data_serialization.hpp>

#include <utility>

KTH_CONV_DEFINE(chain, kth_token_data_t, kth::domain::chain::token_data_t, token_data)

// ---------------------------------------------------------------------------
extern "C" {

kth_token_data_t kth_chain_token_data_construct_default() {
    return new kth::domain::chain::token_data_t();
}

kth_token_data_t kth_chain_token_data_construct_fungible(kth_hash_t const* token_category, int64_t token_amount) {
    using kth::domain::chain::amount_t;

    auto token_category_cpp = kth::to_array(token_category->hash);
    return new kth::domain::chain::token_data_t {
        token_category_cpp,
        kth::domain::chain::fungible{amount_t{token_amount}}
    };
}

kth_token_data_t kth_chain_token_data_construct_non_fungible(kth_hash_t const* token_category, kth_token_capability_t capability, uint8_t* commitment_data, kth_size_t commitment_n) {
    auto token_category_cpp = kth::to_array(token_category->hash);
    auto capability_cpp = kth::token_capability_to_cpp(capability);
    kth::data_chunk commitment_cpp(commitment_data, std::next(commitment_data, commitment_n));

    return new kth::domain::chain::token_data_t {
        token_category_cpp,
        kth::domain::chain::non_fungible{capability_cpp, std::move(commitment_cpp)}
    };
}

kth_token_data_t kth_chain_token_data_construct_both(kth_hash_t const* token_category, int64_t token_amount, kth_token_capability_t capability, uint8_t* commitment_data, kth_size_t commitment_n) {
    using kth::domain::chain::amount_t;

    auto token_category_cpp = kth::to_array(token_category->hash);
    auto capability_cpp = kth::token_capability_to_cpp(capability);
    kth::data_chunk commitment_cpp(commitment_data, std::next(commitment_data, commitment_n));

    return new kth::domain::chain::token_data_t {
        token_category_cpp,
        kth::domain::chain::both_kinds{
            kth::domain::chain::fungible{
                amount_t{token_amount}
            },
            kth::domain::chain::non_fungible{
                capability_cpp,
                std::move(commitment_cpp)
            }
        }
    };
}

void kth_chain_token_data_destruct(kth_token_data_t token_data) {
    delete &kth_chain_token_data_cpp(token_data);
}

kth_bool_t kth_chain_token_data_is_valid(kth_token_data_t token_data) {
    return kth::bool_to_int(
        kth::domain::chain::is_valid(
            kth_chain_token_data_const_cpp(token_data)
        )
    );
}

kth_size_t kth_chain_token_data_serialized_size(kth_token_data_t token_data) {
    return kth::domain::chain::token::encoding::serialized_size(
            kth_chain_token_data_const_cpp(token_data)
        );
}

uint8_t const* kth_chain_token_data_to_data(kth_token_data_t token_data, kth_size_t* out_size) {
    auto token_data_data = kth::domain::chain::token::encoding::to_data(kth_chain_token_data_const_cpp(token_data));
    return kth::create_c_array(token_data_data, *out_size);
}

kth_token_kind_t kth_chain_token_data_kind(kth_token_data_t token_data) {
    auto const& token_data_cpp = kth_chain_token_data_const_cpp(token_data);
    if (std::holds_alternative<kth::domain::chain::fungible>(token_data_cpp.data)) {
        return kth_token_kind_fungible;
    }
    if (std::holds_alternative<kth::domain::chain::non_fungible>(token_data_cpp.data)) {
        return kth_token_kind_non_fungible;
    }
    if (std::holds_alternative<kth::domain::chain::both_kinds>(token_data_cpp.data)) {
        return kth_token_kind_both;
    }
    return kth_token_kind_none;
}

kth_hash_t kth_chain_token_data_category(kth_token_data_t token_data) {
    auto const& category_cpp = kth_chain_token_data_const_cpp(token_data).id;
    return kth::to_hash_t(category_cpp);
}

void kth_chain_token_data_category_out(kth_token_data_t token_data, kth_hash_t* out_category) {
    auto const& category_cpp = kth_chain_token_data_const_cpp(token_data).id;
    kth::copy_c_hash(category_cpp, out_category);
}

int64_t kth_chain_token_data_fungible_amount(kth_token_data_t token_data) {
    auto const& token_data_cpp = kth_chain_token_data_const_cpp(token_data);
    if (std::holds_alternative<kth::domain::chain::fungible>(token_data_cpp.data)) {
        auto const& fungible_cpp = std::get<kth::domain::chain::fungible>(token_data_cpp.data);
        return std::to_underlying(fungible_cpp.amount);
    }
    if (std::holds_alternative<kth::domain::chain::both_kinds>(token_data_cpp.data)) {
        auto const& both_kinds_cpp = std::get<kth::domain::chain::both_kinds>(token_data_cpp.data);
        auto const& fungible_cpp = both_kinds_cpp.first;
        return std::to_underlying(fungible_cpp.amount);
    }
    return std::numeric_limits<int64_t>::max();
}

kth_token_capability_t kth_chain_token_data_non_fungible_capability(kth_token_data_t token_data) {
    auto const& token_data_cpp = kth_chain_token_data_const_cpp(token_data);
    if (std::holds_alternative<kth::domain::chain::non_fungible>(token_data_cpp.data)) {
        auto const& non_fungible_cpp = std::get<kth::domain::chain::non_fungible>(token_data_cpp.data);
        return kth::token_capability_to_c(non_fungible_cpp.capability);
    }
    if (std::holds_alternative<kth::domain::chain::both_kinds>(token_data_cpp.data)) {
        auto const& both_kinds_cpp = std::get<kth::domain::chain::both_kinds>(token_data_cpp.data);
        auto const& non_fungible_cpp = both_kinds_cpp.second;
        return kth::token_capability_to_c(non_fungible_cpp.capability);
    }
    return kth_token_capability_none; // TODO: this is not a good way to signal an error
}

uint8_t const* kth_chain_token_data_non_fungible_commitment(kth_token_data_t token_data, kth_size_t* out_size) {
    auto const& token_data_cpp = kth_chain_token_data_const_cpp(token_data);
    if (std::holds_alternative<kth::domain::chain::non_fungible>(token_data_cpp.data)) {
        auto const& non_fungible_cpp = std::get<kth::domain::chain::non_fungible>(token_data_cpp.data);
        return kth::create_c_array(non_fungible_cpp.commitment, *out_size);
    }
    if (std::holds_alternative<kth::domain::chain::both_kinds>(token_data_cpp.data)) {
        auto const& both_kinds_cpp = std::get<kth::domain::chain::both_kinds>(token_data_cpp.data);
        auto const& non_fungible_cpp = both_kinds_cpp.second;
        return kth::create_c_array(non_fungible_cpp.commitment, *out_size);
    }

    *out_size = 0;
    return nullptr;
}

} // extern "C"
