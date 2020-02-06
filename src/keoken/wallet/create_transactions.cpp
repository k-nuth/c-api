// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.



#include <knuth/nodecint/keoken/wallet/create_transactions.h>

#include <bitcoin/bitcoin/wallet/payment_address.hpp>

#include <knuth/keoken/wallet/create_transaction.hpp>

#include <knuth/nodecint/conversions.hpp>
#include <knuth/nodecint/helpers.hpp>
#include <knuth/nodecint/primitives.h>

// ---------------------------------------------------------------------------
extern "C" {

error_code_t keoken_wallet_tx_encode_create_asset(
    point_list_t outputs_to_spend,
    payment_address_t asset_owner,
    uint64_t utxo_satoshis,
    char const* asset_name,
    keoken_amount_t asset_amount,
    uint32_t locktime /*= 0*/,
    uint32_t tx_version /*= 1*/,
    uint8_t script_version /*= 5*/,
    transaction_t* out_transaction) {

    auto p = knuth::keoken::wallet::tx_encode_create_asset(
                chain_point_list_const_cpp(outputs_to_spend),
                wallet_payment_address_const_cpp(asset_owner),
                utxo_satoshis,
                std::string(asset_name),
                asset_amount,
                locktime,
                tx_version,
                script_version
               );

    if (p.first == libbitcoin::error::success) {
        *out_transaction = new libbitcoin::message::transaction(std::move(p.second));
    } else {
        *out_transaction = nullptr;
    }

    return knuth::to_c_err(p.first);
}

error_code_t keoken_wallet_tx_encode_send_tokens(
    point_list_t outputs_to_spend,
    payment_address_t asset_owner,
    uint64_t utxo_satoshis,
    payment_address_t asset_receiver,
    uint64_t dust,
    keoken_asset_id_t asset_id,
    keoken_amount_t asset_amount,
    uint32_t locktime /*= 0*/,
    uint32_t tx_version /*= 1*/,
    uint8_t script_version /*= 5*/,
    transaction_t* out_transaction) {

    auto p = knuth::keoken::wallet::tx_encode_send_token(
                chain_point_list_const_cpp(outputs_to_spend),
                wallet_payment_address_const_cpp(asset_owner),
                utxo_satoshis,
                wallet_payment_address_const_cpp(asset_receiver),
                dust,
                asset_id,
                asset_amount,

                locktime,
                tx_version,
                script_version
               );

    if (p.first == libbitcoin::error::success) {
        *out_transaction = new libbitcoin::message::transaction(std::move(p.second));
    } else {
        *out_transaction = nullptr;
    }

    return knuth::to_c_err(p.first);
}

} // extern "C"
