// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.



#include <kth/capi/wallet/wallet.h>

#include <kth/capi/primitives.h>

#include <kth/infrastructure/math/elliptic_curve.hpp>
#include <kth/domain/wallet/ec_public.hpp>
#include <kth/infrastructure/wallet/hd_private.hpp>
#include <kth/infrastructure/wallet/mnemonic.hpp>  //Warning, put it after boost headers

#include <kth/domain/wallet/payment_address.hpp>
#include <kth/capi/helpers.hpp>


kth::ec_secret new_key(kth::data_chunk const& seed) {
    kth::infrastructure::wallet::hd_private const key(seed);
    return key.secret();
}

// ---------------------------------------------------------------------------
extern "C" {

long_hash_t wallet_mnemonics_to_seed(word_list_t mnemonics) {
    auto const& mnemonics_cpp = *static_cast<std::vector<std::string> const*>(mnemonics);
    auto hash_cpp = kth::infrastructure::wallet::decode_mnemonic(mnemonics_cpp);
    return kth::to_long_hash_t(hash_cpp);
}

//TODO(fernando): return error code and use output parameters
ec_secret_t wallet_ec_new(uint8_t* seed, uint64_t n) {

    if (n < BITCOIN_MINIMUM_SEED_SIZE) return kth::null_ec_secret;

    kth::data_chunk seed_cpp(seed, std::next(seed, n));

    // if (seed_cpp.size() < minimum_seed_size)
    // {
    //     error << BX_EC_NEW_SHORT_SEED << std::endl;
    //     return console_result::failure;
    // }

    kth::ec_secret secret(new_key(seed_cpp));
    // if (secret == null_hash)
    // {
    //     error << BX_EC_NEW_INVALID_KEY << std::endl;
    //     return console_result::failure;
    // }

    // return secret;

    return kth::to_ec_secret_t(secret);

}

ec_public_t wallet_ec_to_public(ec_secret_t secret, bool_t uncompressed) {
    
    auto secret_cpp = kth::to_array(secret.data);
    bool uncompressed_cpp = kth::int_to_bool(uncompressed);
    
    kth::ec_compressed point;
    kth::secret_to_public(point, secret_cpp);
    return new kth::domain::wallet::ec_public(point, !uncompressed_cpp);
}

payment_address_t wallet_ec_to_address(ec_public_t point, uint32_t version) {
    kth::domain::wallet::ec_public const& point_cpp = *static_cast<kth::domain::wallet::ec_public const*>(point);
    return new kth::domain::wallet::payment_address(point_cpp, version);
}

//TODO(fernando): implement ec-to-wif

// console_result hd_new::invoke(std::ostream& output, std::ostream& error)
// {
//     // Bound parameters.
//     auto const version = get_version_option();
//     const data_chunk& seed = get_seed_argument();

//     if (seed.size() < minimum_seed_size)
//     {
//         error << BX_HD_NEW_SHORT_SEED << std::endl;
//         return console_result::failure;
//     }

//     // We require the private version, but public is unused here.
//     auto const prefixes = bc::wallet::hd_private::to_prefixes(version, 0);
//     const bc::wallet::hd_private private_key(seed, prefixes);

//     if ( ! private_key)
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
//     auto const prefixes = bc::wallet::hd_private::to_prefixes(version, 0);
//     const bc::wallet::hd_private private_key(seed, prefixes);

//     if ( ! private_key)
//     {
//         error << BX_HD_NEW_INVALID_KEY << std::endl;
//         return console_result::failure;
//     }

//     output << private_key << std::endl;
//     return console_result::okay;

    // printf("C++ wallet_hd_new - 1\n");
    if (n < BITCOIN_MINIMUM_SEED_SIZE) return nullptr;

    // printf("C++ wallet_hd_new - 2\n");

    kth::data_chunk seed_cpp(seed, std::next(seed, n));

    // printf("C++ wallet_hd_new - 3\n");


    // We require the private version, but public is unused here.
    auto const prefixes = kth::infrastructure::wallet::to_prefixes(version, 0);
    // printf("C++ wallet_hd_new - 4\n");

    // kth::infrastructure::wallet::hd_private const private_key(seed_cpp, prefixes);
    auto* res = new kth::infrastructure::wallet::hd_private(seed_cpp, prefixes);

    // printf("C++ wallet_hd_new - 5\n");

    return res;
}


// console_result hd_to_ec::invoke(std::ostream& output, std::ostream& error)
// {
//     // Bound parameters.
//     auto const& key = get_hd_key_argument();
//     auto const private_version = get_secret_version_option();
//     auto const public_version = get_public_version_option();

//     auto const key_version = key.version();
//     if (key_version != private_version && key_version != public_version)
//     {
//         output << "ERROR_VERSION" << std::endl;
//         return console_result::failure;
//     }

//     if (key.version() == private_version)
//     {
//         auto const prefixes = bc::wallet::hd_private::to_prefixes(
//             key.version(), public_version);

//         // Create the private key from hd_key and the public version.
//         auto const private_key = bc::wallet::hd_private(key, prefixes);
//         if (private_key)
//         {
//             output << encode_base16(private_key.secret()) << std::endl;
//             return console_result::okay;
//         }
//     }
//     else
//     {
//         // Create the public key from hd_key and the public version.
//         auto const public_key = bc::wallet::hd_public(key, public_version);
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
    auto const& key_cpp = *static_cast<kth::infrastructure::wallet::hd_private const*>(key);
    kth::ec_secret secret = key_cpp.secret();
    return kth::to_ec_secret_t(secret);
}


//void long_hash_destroy(long_hash_t ptr) {
//    free(ptr);
//}

} // extern "C"
