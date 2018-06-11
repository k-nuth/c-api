/**
 * Copyright (c) 2017-2018 Bitprim Inc.
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
#include <bitprim/nodecint/helpers.hpp>

#include <bitcoin/bitcoin/wallet/payment_address.hpp>
#include <bitcoin/bitcoin/multi_crypto_support.hpp>

libbitcoin::wallet::payment_address const& chain_payment_address_const_cpp(payment_address_t payment_address) {
    return *static_cast<libbitcoin::wallet::payment_address const*>(payment_address);
}

libbitcoin::wallet::payment_address& chain_payment_address_cpp(payment_address_t payment_address) {
    return *static_cast<libbitcoin::wallet::payment_address*>(payment_address);
}

extern "C" {

#ifdef BITPRIM_CURRENCY_BCH
void chain_payment_address_set_cashaddr_prefix(char const* prefix) {
    std::string prefix_cpp(prefix);
    libbitcoin::set_cashaddr_prefix(prefix_cpp);
}
#endif //BITPRIM_CURRENCY_BCH

payment_address_t chain_payment_address_construct_from_string(char const* address) {
    std::string addr_cpp(address);
    // return std::make_unique<libbitcoin::wallet::payment_address>(addr_cpp).release();
    return new libbitcoin::wallet::payment_address(addr_cpp);
}

//User is responsible for releasing return value memory
char* chain_payment_address_encoded(payment_address_t payment_address) {
    std::string str = chain_payment_address_const_cpp(payment_address).encoded();
    auto* ret = static_cast<char*>(malloc((str.size() + 1) * sizeof(char))); // NOLINT
    std::copy_n(str.begin(), str.size() + 1, ret);
    return ret;
}

#ifdef BITPRIM_CURRENCY_BCH
//User is responsible for releasing return value memory
char* chain_payment_address_encoded_cashaddr(payment_address_t payment_address) {
    std::string str = chain_payment_address_const_cpp(payment_address).encoded_cashaddr();
    auto* ret = static_cast<char*>(malloc((str.size() + 1) * sizeof(char))); // NOLINT
    std::copy_n(str.begin(), str.size() + 1, ret);
    return ret;
}
#endif //BITPRIM_CURRENCY_BCH

short_hash_t chain_payment_address_hash(payment_address_t payment_address) {
    auto const& hash_cpp = chain_payment_address_const_cpp(payment_address).hash();
    return bitprim::to_short_hash_t(hash_cpp);
}

uint8_t chain_payment_address_version(payment_address_t payment_address) {
    return chain_payment_address_const_cpp(payment_address).version();
}

int /*bool*/ chain_payment_address_is_valid(payment_address_t payment_address) {
    return static_cast<bool>(chain_payment_address_const_cpp(payment_address));
}

void chain_payment_address_destruct(payment_address_t payment_address) {
    delete &chain_payment_address_cpp(payment_address);
}

} /* extern "C" */
