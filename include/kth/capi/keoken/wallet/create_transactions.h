// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_CAPI_KEOKEN_WALLET_CREATE_TRANSACTION_H_
#define KTH_CAPI_KEOKEN_WALLET_CREATE_TRANSACTION_H_

#include <kth/capi/primitives.h>
#include <kth/capi/visibility.h>

#ifdef __cplusplus
extern "C" {
#endif

KTH_EXPORT
error_code_t keoken_wallet_tx_encode_create_asset(
    kth_point_list_t outputs_to_spend,
    kth_payment_address_t asset_owner,
    uint64_t utxo_satoshis,
    char const* asset_name,
    keoken_amount_t asset_amount,
    uint32_t locktime /*= 0*/,
    uint32_t tx_version /*= 1*/,
    uint8_t script_version /*= 5*/,
   kth_transaction_t* out_transaction);

KTH_EXPORT
error_code_t keoken_wallet_tx_encode_send_tokens(
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
   kth_transaction_t* out_transaction);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* KTH_CAPI_KEOKEN_WALLET_CREATE_TRANSACTION_H_ */
