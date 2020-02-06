/**
* Copyright (c) 2016-2020 Knuth Project developers.
*
* This file is part of the Knuth Project.
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

#include <knuth/nodecint/keoken/get_assets_by_address_data.h>

#include <knuth/keoken/state_dto.hpp>
#include <knuth/nodecint/conversions.hpp>
#include <knuth/nodecint/helpers.hpp>
#include <knuth/nodecint/type_conversions.h>

KTH_CONV_DEFINE(keoken, get_assets_by_address_data_t, knuth::keoken::get_assets_by_address_data, get_assets_by_address_data)

// ---------------------------------------------------------------------------
extern "C" {

// get_assets_by_address_data_t keoken_get_assets_by_address_data_construct_default(void) {
//     return new knuth::keoken::get_assets_by_address_data();
// }

get_assets_by_address_data_t keoken_get_assets_by_address_data_construct(keoken_asset_id_t asset_id, char const* asset_name, payment_address_t asset_creator, keoken_amount_t amount) {
    return new knuth::keoken::get_assets_by_address_data(asset_id, std::string(asset_name), wallet_payment_address_const_cpp(asset_creator), amount);
}

void keoken_get_assets_by_address_data_destruct(get_assets_by_address_data_t obj) {
    delete &keoken_get_assets_by_address_data_cpp(obj);
}

keoken_asset_id_t keoken_get_assets_by_address_data_asset_id(get_assets_by_address_data_t obj) {
    return keoken_get_assets_by_address_data_const_cpp(obj).asset_id;
}

char const* keoken_get_assets_by_address_data_asset_name(get_assets_by_address_data_t obj) {
    auto const& asset_name = keoken_get_assets_by_address_data_const_cpp(obj).asset_name;
    return knuth::create_c_str(asset_name);
}

payment_address_t keoken_get_assets_by_address_data_asset_creator(get_assets_by_address_data_t obj) {
    return &keoken_get_assets_by_address_data_cpp(obj).asset_creator;
}

keoken_amount_t keoken_get_assets_by_address_data_amount(get_assets_by_address_data_t obj) {
    return keoken_get_assets_by_address_data_const_cpp(obj).amount;
}

} // extern "C"
