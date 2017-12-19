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

#include <bitprim/nodecint/primitives.h>

#include <bitprim/nodecint/helpers.hpp>
#include <bitcoin/bitcoin/math/elliptic_curve.hpp>
#include <bitcoin/bitcoin/wallet/mnemonic.hpp>
#include <bitcoin/bitcoin/wallet/hd_private.hpp>
#include <bitcoin/bitcoin/wallet/ec_public.hpp>
#include <bitcoin/bitcoin/wallet/payment_address.hpp>


libbitcoin::ec_secret new_key(libbitcoin::data_chunk const& seed) {
    libbitcoin::wallet::hd_private const key(seed);
    return key.secret();
}


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


// console_result ec_new::invoke(std::ostream& output, std::ostream& error)
// {
//     // Bound parameters.
//     const data_chunk& seed = get_seed_argument();

//     if (seed.size() < minimum_seed_size)
//     {
//         error << BX_EC_NEW_SHORT_SEED << std::endl;
//         return console_result::failure;
//     }

//     ec_secret secret(new_key(seed));
//     if (secret == null_hash)
//     {
//         error << BX_EC_NEW_INVALID_KEY << std::endl;
//         return console_result::failure;
//     }

//     // We don't use bc::ec_private serialization (WIF) here.
//     output << config::ec_private(secret) << std::endl;
//     return console_result::okay;
// }


// //static header factory_from_data(const uint32_t version, const data_chunk& data);
// header_t chain_header_factory_from_data(uint32_t version, uint8_t* data, uint64_t n) {

// //    libbitcoin::data_chunk data_cpp(data, data + n);
//     libbitcoin::data_chunk data_cpp(data, std::next(data, n));
//     auto header = libbitcoin::message::header::factory_from_data(version, data_cpp);
//     return new libbitcoin::message::header(std::move(header)); // TODO(fernando): revisar todos los "new"'s que hay por todos lados para ver si podemos hacer un move de los recursos...
// }


//TODO(fernando): return error code and use output parameters
ec_secret_t wallet_ec_new(uint8_t* seed, uint64_t n) {

    if (n < BITCOIN_MINIMUM_SEED_SIZE) return bitprim::null_ec_secret;

    libbitcoin::data_chunk seed_cpp(seed, std::next(seed, n));

    // if (seed_cpp.size() < minimum_seed_size)
    // {
    //     error << BX_EC_NEW_SHORT_SEED << std::endl;
    //     return console_result::failure;
    // }

    libbitcoin::ec_secret secret(new_key(seed_cpp));
    // if (secret == null_hash)
    // {
    //     error << BX_EC_NEW_INVALID_KEY << std::endl;
    //     return console_result::failure;
    // }

    // return secret;

    return bitprim::to_ec_secret_t(secret);

}



// // In the case of failure this produces ec_compressed_null.
// console_result ec_to_public::invoke(std::ostream& output, std::ostream& error)
// {
//     const auto& secret = get_ec_private_key_argument();
//     const auto& uncompressed = get_uncompressed_option();

//     ec_compressed point;
//     secret_to_public(point, secret);

//     // Serialize to the original compression state.
//     output << ec_public(point, !uncompressed) << std::endl;
//     return console_result::okay;
// }

ec_public_t wallet_ec_to_public(ec_secret_t secret, int /*bool*/ uncompressed) {
    
    auto secret_cpp = bitprim::to_array(secret.data);
    bool uncompressed_cpp = uncompressed != 0;
    
    libbitcoin::ec_compressed point;
    libbitcoin::secret_to_public(point, secret_cpp);
    return new libbitcoin::wallet::ec_public(point, !uncompressed_cpp);
}


// console_result ec_to_address::invoke(std::ostream& output, std::ostream& error)
// {
//     // Bound parameters.
//     const auto& point = get_ec_public_key_argument();
//     const auto version = get_version_option();

//     output << payment_address(point, version) << std::endl;
//     return console_result::okay;
// }

payment_address_t wallet_ec_to_address(ec_public_t point, uint32_t version) {
    libbitcoin::wallet::ec_public const& point_cpp = *static_cast<libbitcoin::wallet::ec_public const*>(point);
    return new libbitcoin::wallet::payment_address(point_cpp, version);
}

// ec-to-wif

//void long_hash_destroy(long_hash_t ptr) {
//    free(ptr);
//}

} /* extern "C" */
