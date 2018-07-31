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

#include <bitprim/nodecint/keoken/manager.h>

#include <bitprim/nodecint/helpers.hpp>
#include <bitprim/nodecint/type_convertions.h>

#include <bitprim/keoken/manager.hpp>
#include <bitprim/keoken/state.hpp>
#include <bitprim/keoken/state_dto.hpp>

namespace {
BITPRIM_CONV_DEFINE(keoken, keoken_manager_t, bitprim::keoken::manager, manager)
} /* end of anonymous namespace */

// ---------------------------------------------------------------------------
extern "C" {

void keoken_manager_initialize_from_blockchain(keoken_manager_t manager) {
    keoken_manager_cpp(manager).initialize_from_blockchain();
}

bool_t keoken_manager_initialized(keoken_manager_t manager) {
    return bitprim::bool_to_int(keoken_manager_const_cpp(manager).initialized());
}

get_assets_by_address_list_t keoken_manager_get_assets_by_address(keoken_manager_t manager, payment_address_t address) {
    libbitcoin::wallet::payment_address const& address_cpp = *static_cast<const libbitcoin::wallet::payment_address*>(address);
    auto result = keoken_manager_const_cpp(manager).get_assets_by_address(address_cpp);
    return bitprim::move_or_copy_and_leak(std::move(result));         //Must be released by caller
}

get_assets_list_t keoken_manager_get_assets(keoken_manager_t manager) {
    auto result = keoken_manager_const_cpp(manager).get_assets();
    return bitprim::move_or_copy_and_leak(std::move(result));         //Must be released by caller
}

get_all_asset_addresses_list_t keoken_manager_get_all_asset_addresses(keoken_manager_t manager) {
    auto result = keoken_manager_const_cpp(manager).get_all_asset_addresses();
    return bitprim::move_or_copy_and_leak(std::move(result));         //Must be released by caller
}

} // extern "C"
