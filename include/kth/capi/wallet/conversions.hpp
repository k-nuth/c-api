// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_CAPI_WALLET_CONVERSIONS_HPP_
#define KTH_CAPI_WALLET_CONVERSIONS_HPP_

#include <algorithm>
#include <array>
#include <cstdint>

#include <kth/capi/wallet/primitives.h>
#include <kth/capi/wallet/hd_lineage.h>

#include <kth/infrastructure/wallet/hd_public.hpp>
#include <kth/domain/wallet/ec_private.hpp>

namespace detail {

// C++ -> C ---------------------------------------------------------
inline
kth_hd_chain_code_t to_hd_chain_code_t(std::array<uint8_t, KTH_HD_CHAIN_CODE_SIZE> const& x) {
    kth_hd_chain_code_t result;
    std::copy(x.begin(), x.end(), result.data);
    return result;
}

inline
kth_hd_key_t to_hd_key_t(std::array<uint8_t, KTH_HD_KEY_SIZE> const& x) {
    kth_hd_key_t result;
    std::copy(x.begin(), x.end(), result.data);
    return result;
}

inline
kth_ec_compressed_t to_ec_compressed_t(std::array<uint8_t, KTH_EC_COMPRESSED_SIZE> const& x) {
    kth_ec_compressed_t result;
    std::copy(x.begin(), x.end(), result.data);
    return result;
}

inline
kth_ec_uncompressed_t to_ec_uncompressed_t(kth::ec_uncompressed const& obj) {
    kth_ec_uncompressed_t res;
    std::copy_n(obj.begin(), obj.size(), res.data);
    return res;
}

inline
kth_ec_secret_t to_ec_secret_t(kth::ec_secret const& secret) {
    kth_ec_secret_t result;
    std::copy(secret.begin(), secret.end(), result.hash);
    return result;
}

inline
kth_wif_uncompressed_t to_wif_uncompressed_t(kth::domain::wallet::wif_uncompressed const& wif) {
    kth_wif_uncompressed_t result;
    std::copy(wif.begin(), wif.end(), result.data);
    return result;
}

inline
kth_wif_compressed_t to_wif_compressed_t(kth::domain::wallet::wif_compressed const& wif) {
    kth_wif_compressed_t result;
    std::copy(wif.begin(), wif.end(), result.data);
    return result;
}

inline
kth_hd_lineage_t to_hd_lineage_t(kth::infrastructure::wallet::hd_lineage const& lineage_cpp) {
    kth_hd_lineage_t lineage_c;
    lineage_c.prefixes = lineage_cpp.prefixes;
    lineage_c.depth = lineage_cpp.depth;
    lineage_c.parent_fingerprint = lineage_cpp.parent_fingerprint;
    lineage_c.child_number = lineage_cpp.child_number;
    return lineage_c;
}

inline
kth_ec_signature_t to_ec_signature_t(kth::ec_signature const& obj) {
    kth_ec_signature_t res;
    std::copy_n(obj.begin(), obj.size(), res.data);
    return res;
}



// C -> C++ ---------------------------------------------------------
inline
std::array<uint8_t, KTH_HD_CHAIN_CODE_SIZE> from_hd_chain_code_t(kth_hd_chain_code_t const& x) {
    std::array<uint8_t, KTH_HD_CHAIN_CODE_SIZE> result;
    std::copy(std::begin(x.data), std::end(x.data), result.begin());
    return result;
}

inline
std::array<uint8_t, KTH_HD_KEY_SIZE> from_hd_key_t(kth_hd_key_t const& x) {
    std::array<uint8_t, KTH_HD_KEY_SIZE> result;
    std::copy(std::begin(x.data), std::end(x.data), result.begin());
    return result;
}

inline
std::array<uint8_t, KTH_EC_COMPRESSED_SIZE> from_ec_compressed_t(kth_ec_compressed_t const& x) {
    std::array<uint8_t, KTH_EC_COMPRESSED_SIZE> result;
    std::copy(std::begin(x.data), std::end(x.data), result.begin());
    return result;
}

inline
kth::ec_uncompressed from_ec_uncompressed_t(kth_ec_uncompressed_t const& x) {
    kth::ec_uncompressed result;
    std::copy(std::begin(x.data), std::end(x.data), result.begin());
    return result;
}

inline
kth::ec_secret from_ec_secret_t(kth_ec_secret_t const& secret_c) {
    kth::ec_secret result;
    std::copy(std::begin(secret_c.hash), std::end(secret_c.hash), result.begin());
    return result;
}

inline
kth::domain::wallet::wif_uncompressed from_wif_uncompressed_t(kth_wif_uncompressed_t const& wif) {
    // return kth::domain::wallet::wif_uncompressed(wif.data, wif.data + KTH_WIF_UNCOMPRESSED_SIZE);
    kth::domain::wallet::wif_uncompressed result;
    std::copy(std::begin(wif.data), std::end(wif.data), result.begin());
    return result;

}

inline
kth::domain::wallet::wif_compressed from_wif_compressed_t(kth_wif_compressed_t const& wif) {
    // return kth::domain::wallet::wif_compressed(wif.data, wif.data + KTH_WIF_COMPRESSED_SIZE);
    kth::domain::wallet::wif_compressed result;
    std::copy(std::begin(wif.data), std::end(wif.data), result.begin());
    return result;
}

inline
kth::infrastructure::wallet::hd_lineage from_hd_lineage_t(kth_hd_lineage_t const& lineage_c) {
    kth::infrastructure::wallet::hd_lineage lineage_cpp;
    lineage_cpp.prefixes = lineage_c.prefixes;
    lineage_cpp.depth = lineage_c.depth;
    lineage_cpp.parent_fingerprint = lineage_c.parent_fingerprint;
    lineage_cpp.child_number = lineage_c.child_number;
    return lineage_cpp;
}

inline
kth::ec_signature from_ec_signature_t(kth_ec_signature_t const& x) {
    kth::ec_signature result;
    std::copy(std::begin(x.data), std::end(x.data), result.begin());
    return result;
}


} // namespace detail

#endif /* KTH_CAPI_WALLET_CONVERSIONS_HPP_ */
