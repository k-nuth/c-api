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

libbitcoin::wallet::payment_address const& payment_address_const_cpp(payment_address_t payment_address) {
    return *static_cast<libbitcoin::wallet::payment_address const*>(payment_address);
}

libbitcoin::wallet::payment_address& payment_address_cpp(payment_address_t payment_address) {
    return *static_cast<libbitcoin::wallet::payment_address*>(payment_address);
}

extern "C" {

//User is responsible for releasing return value memory
char const* payment_address_encoded(payment_address_t payment_address) {
    std::string encoded_string = payment_address_const_cpp(payment_address).encoded();
    char* ret = (char*)malloc((encoded_string.size() + 1) * sizeof(char));
    std::strcpy(ret, encoded_string.c_str());
    return ret;
}

payment_address_t payment_address_construct_from_string(char const* address) {
    std::string addr_cpp(address);
    return std::make_unique<libbitcoin::wallet::payment_address>(addr_cpp).release();
}

uint8_t payment_address_version(payment_address_t payment_address) {
    return payment_address_cpp(payment_address).version();
}

void payment_address_destruct(payment_address_t payment_address) {
    delete &payment_address_cpp(payment_address);
}

} /* extern "C" */
