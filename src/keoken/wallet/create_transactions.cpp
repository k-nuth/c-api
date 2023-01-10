// Copyright (c) 2016-2023 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#include <kth/capi/keoken/wallet/create_transactions.h>

#include <kth/domain/wallet/payment_address.hpp>

#include <kth/keoken/wallet/create_transaction.hpp>

#include <kth/capi/conversions.hpp>
#include <kth/capi/helpers.hpp>
#include <kth/capi/primitives.h>

// ---------------------------------------------------------------------------
extern "C" {

kth_error_code_t keoken_wallet_tx_encode_create_asset(
    kth_point_list_t outputs_to_spend,
    kth_payment_address_t asset_owner,
    uint64_t utxo_satoshis,
    char const* asset_name,
    keoken_amount_t asset_amount,
    uint32_t locktime /*= 0*/,
    uint32_t tx_version /*= 1*/,
    uint8_t script_version /*= 5*/,
    kth_transaction_t* out_transaction) {

    auto p = kth::keoken::wallet::tx_encode_create_asset(
                kth_chain_point_list_const_cpp(outputs_to_spend),
                kth_wallet_payment_address_const_cpp(asset_owner),
                utxo_satoshis,
                std::string(asset_name),
                asset_amount,
                locktime,
                tx_version,
                script_version
               );

    if (p.first == kth::error::success) {
        *out_transaction = new kth::domain::message::transaction(std::move(p.second));
    } else {
        *out_transaction = nullptr;
    }

    return kth::to_c_err(p.first);
}

kth_error_code_t keoken_wallet_tx_encode_send_tokens(
    kth_point_list_t outputs_to_spend,
    kth_payment_address_t asset_owner,
    uint64_t utxo_satoshis,
    kth_payment_address_t asset_receiver,
    uint64_t dust,
    keoken_asset_id_t asset_id,
    keoken_amount_t asset_amount,
    uint32_t locktime /*= 0*/,
    uint32_t tx_version /*= 1*/,
    uint8_t script_version /*= 5*/,
    kth_transaction_t* out_transaction) {

    auto p = kth::keoken::wallet::tx_encode_send_token(
                kth_chain_point_list_const_cpp(outputs_to_spend),
                kth_wallet_payment_address_const_cpp(asset_owner),
                utxo_satoshis,
                kth_wallet_payment_address_const_cpp(asset_receiver),
                dust,
                asset_id,
                asset_amount,

                locktime,
                tx_version,
                script_version
               );

    if (p.first == kth::error::success) {
        *out_transaction = new kth::domain::message::transaction(std::move(p.second));
    } else {
        *out_transaction = nullptr;
    }

    return kth::to_c_err(p.first);
}

} // extern "C"
