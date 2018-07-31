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

#include <bitprim/nodecint/keoken/get_all_asset_addresses_data.h>

#include <bitprim/keoken/state_dto.hpp>
#include <bitprim/nodecint/helpers.hpp>
#include <bitprim/nodecint/type_convertions.h>

BITPRIM_CONV_DEFINE(keoken, get_all_asset_addresses_data_t, bitprim::keoken::get_all_asset_addresses_data, get_all_asset_addresses_data)

// ---------------------------------------------------------------------------
extern "C" {

// get_all_asset_addresses_data_t keoken_get_all_asset_addresses_data_construct_default(void) {
//     return new bitprim::keoken::get_all_asset_addresses_data();
// }

get_all_asset_addresses_data_t keoken_get_all_asset_addresses_data_construct(keoken_asset_id_t asset_id, char const* asset_name, payment_address_t asset_creator, keoken_amount_t amount, payment_address_t amount_owner) {
    libbitcoin::wallet::payment_address const& asset_creator_cpp = *static_cast<const libbitcoin::wallet::payment_address*>(asset_creator);
    libbitcoin::wallet::payment_address const& amount_owner_cpp = *static_cast<const libbitcoin::wallet::payment_address*>(amount_owner);
    return new bitprim::keoken::get_all_asset_addresses_data(asset_id, std::string(asset_name), asset_creator_cpp, amount, amount_owner_cpp);
}

void keoken_get_all_asset_addresses_data_destruct(get_all_asset_addresses_data_t obj) {
    auto obj_cpp = &keoken_get_all_asset_addresses_data_cpp(obj);
    delete obj_cpp;
}

keoken_asset_id_t keoken_get_all_asset_addresses_data_asset_id(get_all_asset_addresses_data_t obj) {
    return keoken_get_all_asset_addresses_data_const_cpp(obj).asset_id;
}

char const* keoken_get_all_asset_addresses_data_asset_name(get_all_asset_addresses_data_t obj) {
    auto const& asset_name = keoken_get_all_asset_addresses_data_const_cpp(obj).asset_name;
    return bitprim::create_c_str(asset_name);
}

payment_address_t keoken_get_all_asset_addresses_data_asset_creator(get_all_asset_addresses_data_t obj) {
    auto asset_creator = keoken_get_all_asset_addresses_data_const_cpp(obj).asset_creator;
    return new libbitcoin::wallet::payment_address(asset_creator);
}

keoken_amount_t keoken_get_all_asset_addresses_data_amount(get_all_asset_addresses_data_t obj) {
    return keoken_get_all_asset_addresses_data_const_cpp(obj).amount;
}

payment_address_t keoken_get_all_asset_addresses_data_amount_owner(get_all_asset_addresses_data_t obj) {
    auto amount_owner = keoken_get_all_asset_addresses_data_const_cpp(obj).amount_owner;
    return new libbitcoin::wallet::payment_address(amount_owner);
}

} // extern "C"
