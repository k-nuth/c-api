// Copyright (c) 2016-2021 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/capi/keoken/get_assets_data.h>

#include <kth/keoken/state_dto.hpp>
#include <kth/capi/conversions.hpp>
#include <kth/capi/helpers.hpp>
#include <kth/capi/type_conversions.h>

KTH_CONV_DEFINE(keoken, keoken_get_assets_data_t, kth::keoken::get_assets_data, get_assets_data)

// ---------------------------------------------------------------------------
extern "C" {

// keoken_get_assets_data_t keoken_get_assets_data_construct_default(void) {
//     return new kth::keoken::get_assets_data();
// }

keoken_get_assets_data_t keoken_get_assets_data_construct(keoken_asset_id_t asset_id, char const* asset_name, kth_payment_address_t asset_creator, keoken_amount_t amount) {
    // auto const& asset_creator_cpp = kth_wallet_payment_address_const_cpp(asset_creator);
    return new kth::keoken::get_assets_data(asset_id, std::string(asset_name), kth_wallet_payment_address_const_cpp(asset_creator), amount);
}

void keoken_get_assets_data_destruct(keoken_get_assets_data_t obj) {
    delete &keoken_get_assets_data_cpp(obj);
}

keoken_asset_id_t keoken_get_assets_data_asset_id(keoken_get_assets_data_t obj) {
    return keoken_get_assets_data_const_cpp(obj).asset_id;
}

char const* keoken_get_assets_data_asset_name(keoken_get_assets_data_t obj) {
    auto const& asset_name = keoken_get_assets_data_const_cpp(obj).asset_name;
    return kth::create_c_str(asset_name);
}

kth_payment_address_t keoken_get_assets_data_asset_creator(keoken_get_assets_data_t obj) {
    return &keoken_get_assets_data_cpp(obj).asset_creator;
}

keoken_amount_t keoken_get_assets_data_amount(keoken_get_assets_data_t obj) {
    return keoken_get_assets_data_const_cpp(obj).amount;
}

} // extern "C"
