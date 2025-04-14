// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#include <kth/capi/wallet/wallet.h>

#include <kth/capi/primitives.h>
#include <kth/capi/wallet/primitives.h>
#include <kth/capi/wallet/conversions.hpp>

#include <kth/infrastructure/math/elliptic_curve.hpp>
#include <kth/domain/wallet/ec_public.hpp>
#include <kth/infrastructure/wallet/hd_private.hpp>

#include <kth/domain/wallet/payment_address.hpp>
#include <kth/capi/helpers.hpp>

#include <kth/infrastructure/wallet/mnemonic.hpp>  //Warning, put it after boost headers


kth::ec_secret new_key(kth::data_chunk const& seed) {
    kth::infrastructure::wallet::hd_private const key(seed);
    return key.secret();
}

// ---------------------------------------------------------------------------
extern "C" {

kth_longhash_t kth_wallet_mnemonics_to_seed(kth_string_list_t mnemonics) {
    auto const& mnemonics_cpp = *static_cast<std::vector<std::string> const*>(mnemonics);
    auto hash_cpp = kth::infrastructure::wallet::decode_mnemonic(mnemonics_cpp);
    return kth::to_longhash_t(hash_cpp);
}

void kth_wallet_mnemonics_to_seed_out(kth_string_list_t mnemonics, kth_longhash_t* out_hash) {
    auto const& mnemonics_cpp = *static_cast<std::vector<std::string> const*>(mnemonics);
    auto hash_cpp = kth::infrastructure::wallet::decode_mnemonic(mnemonics_cpp);
    kth::copy_c_hash(hash_cpp, out_hash);
}

kth_longhash_t kth_wallet_mnemonics_to_seed_normalized_passphrase(kth_string_list_t mnemonics, char const* normalized_passphrase) {
    auto const& mnemonics_cpp = *static_cast<std::vector<std::string> const*>(mnemonics);
    auto hash_cpp = kth::infrastructure::wallet::decode_mnemonic_normalized_passphrase(mnemonics_cpp, std::string(normalized_passphrase));
    return kth::to_longhash_t(hash_cpp);
}

void kth_wallet_mnemonics_to_seed_normalized_passphrase_out(kth_string_list_t mnemonics, char const* normalized_passphrase, kth_longhash_t* out_hash) {
    auto const& mnemonics_cpp = *static_cast<std::vector<std::string> const*>(mnemonics);
    auto hash_cpp = kth::infrastructure::wallet::decode_mnemonic_normalized_passphrase(mnemonics_cpp, std::string(normalized_passphrase));
    kth::copy_c_hash(hash_cpp, out_hash);
}

//TODO(fernando): return error code and use output parameters
kth_hd_private_t kth_wallet_hd_new(kth_longhash_t seed, uint32_t version /* = 76066276*/) {
    kth::data_chunk seed_cpp(seed.hash, std::next(seed.hash, KTH_BITCOIN_LONG_HASH_SIZE));
    auto const prefixes = kth::infrastructure::wallet::to_prefixes(version, 0);
    auto* res = new kth::infrastructure::wallet::hd_private(seed_cpp, prefixes);
    return res;

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
}

//TODO(fernando): return error code and use output parameters
kth_ec_secret_t kth_wallet_hd_private_to_ec(kth_hd_private_t key) {
    auto const& key_cpp = *static_cast<kth::infrastructure::wallet::hd_private const*>(key);
    kth::ec_secret secret = key_cpp.secret();
    return detail::to_ec_secret_t(secret);
}

void kth_wallet_hd_private_to_ec_out(kth_hd_private_t key, kth_ec_secret_t* out_secret) {
    auto const& key_cpp = *static_cast<kth::infrastructure::wallet::hd_private const*>(key);
    kth::ec_secret secret = key_cpp.secret();
    kth::copy_c_hash(secret, out_secret);
}

kth_ec_public_t kth_wallet_ec_to_public(kth_ec_secret_t secret, kth_bool_t uncompressed) {
    auto secret_cpp = kth::to_array(secret.hash);
    bool uncompressed_cpp = kth::int_to_bool(uncompressed);

    kth::ec_compressed point;
    kth::secret_to_public(point, secret_cpp);
    return new kth::domain::wallet::ec_public(point, !uncompressed_cpp);
}

kth_payment_address_t kth_wallet_ec_to_address(kth_ec_public_t point, uint32_t version) {
    kth::domain::wallet::ec_public const& point_cpp = *static_cast<kth::domain::wallet::ec_public const*>(point);
    return new kth::domain::wallet::payment_address(point_cpp, version);
}

} // extern "C"
