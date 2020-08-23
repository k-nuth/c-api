// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/capi/keoken/get_all_asset_addresses_data.h>

#include <kth/keoken/state_dto.hpp>
#include <kth/capi/conversions.hpp>
#include <kth/capi/helpers.hpp>
#include <kth/capi/type_conversions.h>

KTH_CONV_DEFINE(keoken, keoken_get_all_asset_addresses_data_t, kth::keoken::get_all_asset_addresses_data, get_all_asset_addresses_data)

// ---------------------------------------------------------------------------
extern "C" {

// keoken_get_all_asset_addresses_data_t keoken_get_all_asset_addresses_data_construct_default(void) {
//     return new kth::keoken::get_all_asset_addresses_data();
// }

keoken_get_all_asset_addresses_data_t keoken_get_all_asset_addresses_data_construct(keoken_asset_id_t asset_id, char const* asset_name, kth_payment_address_t asset_creator, keoken_amount_t amount, kth_payment_address_t amount_owner) {
    auto result = kth::keoken::get_all_asset_addresses_data(
        asset_id, 
        std::string(asset_name), 
        kth_wallet_payment_address_const_cpp(asset_creator), 
        amount, 
        kth_wallet_payment_address_const_cpp(amount_owner))
    ;
    return kth::move_or_copy_and_leak(std::move(result));         //Must be released by caller
}

void keoken_get_all_asset_addresses_data_destruct(keoken_get_all_asset_addresses_data_t obj) {
    delete &keoken_get_all_asset_addresses_data_cpp(obj);
}

keoken_asset_id_t keoken_get_all_asset_addresses_data_asset_id(keoken_get_all_asset_addresses_data_t obj) {
    return keoken_get_all_asset_addresses_data_const_cpp(obj).asset_id;
}

char const* keoken_get_all_asset_addresses_data_asset_name(keoken_get_all_asset_addresses_data_t obj) {
    auto const& asset_name = keoken_get_all_asset_addresses_data_const_cpp(obj).asset_name;
    return kth::create_c_str(asset_name);
}

kth_payment_address_t keoken_get_all_asset_addresses_data_asset_creator(keoken_get_all_asset_addresses_data_t obj) {
    return &keoken_get_all_asset_addresses_data_cpp(obj).asset_creator;
}

keoken_amount_t keoken_get_all_asset_addresses_data_amount(keoken_get_all_asset_addresses_data_t obj) {
    return keoken_get_all_asset_addresses_data_const_cpp(obj).amount;
}

kth_payment_address_t keoken_get_all_asset_addresses_data_amount_owner(keoken_get_all_asset_addresses_data_t obj) {
    return &keoken_get_all_asset_addresses_data_cpp(obj).amount_owner;
}

} // extern "C"
