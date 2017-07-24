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


#include <bitprim/nodecint/wallet/wallet.h>

#include <bitprim/nodecint/helpers.hpp>
#include <bitcoin/bitcoin/wallet/mnemonic.hpp>

extern "C" {

//long_hash_t wallet_mnemonics_to_seed(word_list_t mnemonics) {
//    auto const& mnemonics_cpp = *static_cast<const std::vector<std::string>*>(mnemonics);
//    auto hash_cpp = libbitcoin::wallet::decode_mnemonic(mnemonics_cpp);
//
//    uint8_t* ret = (uint8_t*)malloc(hash_cpp.size() * sizeof(uint8_t));
//    std::copy_n(std::begin(hash_cpp), hash_cpp.size(), ret);
//    return ret;
//}

long_hash_t wallet_mnemonics_to_seed(word_list_t mnemonics) {
    auto const& mnemonics_cpp = *static_cast<const std::vector<std::string>*>(mnemonics);
    auto hash_cpp = libbitcoin::wallet::decode_mnemonic(mnemonics_cpp);
    return bitprim::to_long_hash_t(hash_cpp);
}

//void long_hash_destroy(long_hash_t ptr) {
//    free(ptr);
//}

} /* extern "C" */
