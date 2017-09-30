/**
 * Copyright (c) 2017 Bitprim developers (see AUTHORS)
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

#include <bitprim/nodecint/chain/payment_address.h>
#include <bitcoin/bitcoin/wallet/payment_address.hpp>

libbitcoin::wallet::payment_address const& chain_payment_address_const_cpp(payment_address_t payment_address) {
    return *static_cast<libbitcoin::wallet::payment_address const*>(payment_address);
}

libbitcoin::wallet::payment_address& chain_payment_address_cpp(payment_address_t payment_address) {
    return *static_cast<libbitcoin::wallet::payment_address*>(payment_address);
}

extern "C" {

//User is responsible for releasing return value memory
char const* chain_payment_address_encoded(payment_address_t payment_address) {
    std::string str = chain_payment_address_const_cpp(payment_address).encoded();
    auto* ret = (char*)malloc((str.size() + 1) * sizeof(char)); // NOLINT

//    std::strcpy(ret, str.c_str());
    std::copy_n(str.begin(), str.size() + 1, ret);

    return ret;
}

payment_address_t chain_payment_address_construct_from_string(char const* address) {
    std::string addr_cpp(address);
    // return std::make_unique<libbitcoin::wallet::payment_address>(addr_cpp).release();
    return new libbitcoin::wallet::payment_address(addr_cpp);
}

uint8_t chain_payment_address_version(payment_address_t payment_address) {
    return chain_payment_address_cpp(payment_address).version();
}

void chain_payment_address_destruct(payment_address_t payment_address) {
    delete &chain_payment_address_cpp(payment_address);
}

} /* extern "C" */
