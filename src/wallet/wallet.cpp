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

ec_public_t wallet_ec_to_public(ec_secret_t secret, int /*bool*/ uncompressed) {
    
    auto secret_cpp = bitprim::to_array(secret.data);
    bool uncompressed_cpp = uncompressed != 0;
    
    libbitcoin::ec_compressed point;
    libbitcoin::secret_to_public(point, secret_cpp);
    return new libbitcoin::wallet::ec_public(point, !uncompressed_cpp);
}

payment_address_t wallet_ec_to_address(ec_public_t point, uint32_t version) {
    libbitcoin::wallet::ec_public const& point_cpp = *static_cast<libbitcoin::wallet::ec_public const*>(point);
    return new libbitcoin::wallet::payment_address(point_cpp, version);
}

//TODO(fernando): implement ec-to-wif

// console_result hd_new::invoke(std::ostream& output, std::ostream& error)
// {
//     // Bound parameters.
//     const auto version = get_version_option();
//     const data_chunk& seed = get_seed_argument();

//     if (seed.size() < minimum_seed_size)
//     {
//         error << BX_HD_NEW_SHORT_SEED << std::endl;
//         return console_result::failure;
//     }

//     // We require the private version, but public is unused here.
//     const auto prefixes = bc::wallet::hd_private::to_prefixes(version, 0);
//     const bc::wallet::hd_private private_key(seed, prefixes);

//     if (!private_key)
//     {
//         error << BX_HD_NEW_INVALID_KEY << std::endl;
//         return console_result::failure;
//     }

//     output << private_key << std::endl;
//     return console_result::okay;
// }

//TODO(fernando): return error code and use output parameters
hd_private_t wallet_hd_new(uint8_t* seed, uint64_t n, uint32_t version /* = 76066276*/) {

//     if (seed.size() < minimum_seed_size)
//     {
//         error << BX_HD_NEW_SHORT_SEED << std::endl;
//         return console_result::failure;
//     }

//     // We require the private version, but public is unused here.
//     const auto prefixes = bc::wallet::hd_private::to_prefixes(version, 0);
//     const bc::wallet::hd_private private_key(seed, prefixes);

//     if (!private_key)
//     {
//         error << BX_HD_NEW_INVALID_KEY << std::endl;
//         return console_result::failure;
//     }

//     output << private_key << std::endl;
//     return console_result::okay;

    printf("C++ wallet_hd_new - 1\n");
    if (n < BITCOIN_MINIMUM_SEED_SIZE) return nullptr;

    printf("C++ wallet_hd_new - 2\n");

    libbitcoin::data_chunk seed_cpp(seed, std::next(seed, n));

    printf("C++ wallet_hd_new - 3\n");

    // We require the private version, but public is unused here.
    auto const prefixes = libbitcoin::wallet::hd_private::to_prefixes(version, 0);

    printf("C++ wallet_hd_new - 4\n");

    // libbitcoin::wallet::hd_private const private_key(seed_cpp, prefixes);
    auto* res = new libbitcoin::wallet::hd_private(seed_cpp, prefixes);

    printf("C++ wallet_hd_new - 5\n");

    return res
}


// console_result hd_to_ec::invoke(std::ostream& output, std::ostream& error)
// {
//     // Bound parameters.
//     const auto& key = get_hd_key_argument();
//     const auto private_version = get_secret_version_option();
//     const auto public_version = get_public_version_option();

//     const auto key_version = key.version();
//     if (key_version != private_version && key_version != public_version)
//     {
//         output << "ERROR_VERSION" << std::endl;
//         return console_result::failure;
//     }

//     if (key.version() == private_version)
//     {
//         const auto prefixes = bc::wallet::hd_private::to_prefixes(
//             key.version(), public_version);

//         // Create the private key from hd_key and the public version.
//         const auto private_key = bc::wallet::hd_private(key, prefixes);
//         if (private_key)
//         {
//             output << encode_base16(private_key.secret()) << std::endl;
//             return console_result::okay;
//         }
//     }
//     else
//     {
//         // Create the public key from hd_key and the public version.
//         const auto public_key = bc::wallet::hd_public(key, public_version);
//         if (public_key)
//         {
//             output << bc::wallet::ec_public(public_key) << std::endl;
//             return console_result::okay;
//         }
//     }

//     output << "ERROR_VKEY" << std::endl;
//     return console_result::failure;
// }


//TODO(fernando): return error code and use output parameters
ec_secret_t wallet_hd_private_to_ec(hd_private_t key) {
    auto const& key_cpp = *static_cast<libbitcoin::wallet::hd_private const*>(key);
    libbitcoin::ec_secret secret = key_cpp.secret();
    return bitprim::to_ec_secret_t(secret);
}


//void long_hash_destroy(long_hash_t ptr) {
//    free(ptr);
//}

} /* extern "C" */
