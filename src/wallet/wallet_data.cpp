// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#include <kth/capi/wallet/wallet_data.h>

#include <kth/capi/conversions.hpp>
#include <kth/capi/helpers.hpp>
#include <kth/capi/type_conversions.h>

#include <kth/capi/wallet/conversions.hpp>


KTH_CONV_DEFINE(wallet, kth_wallet_data_t, kth::domain::wallet::wallet_data, wallet_data)

// ---------------------------------------------------------------------------
extern "C" {


void kth_wallet_wallet_data_destruct(kth_wallet_data_t wallet_data) {
    delete &kth_wallet_wallet_data_cpp(wallet_data);
}

kth_string_list_t kth_wallet_wallet_data_mnemonics(kth_wallet_data_t wallet_data) {
    auto& mnemonics_cpp = kth_wallet_wallet_data_cpp(wallet_data).mnemonics;
    return kth_core_string_list_construct_from_cpp(mnemonics_cpp);
}

kth_hd_public_t kth_wallet_wallet_data_xpub(kth_wallet_data_t wallet_data) {
    auto const& xpub_cpp = kth_wallet_wallet_data_cpp(wallet_data).xpub;
    return kth::move_or_copy_and_leak(std::move(xpub_cpp));
}

kth_encrypted_seed_t kth_wallet_wallet_data_encrypted_seed(kth_wallet_data_t wallet_data) {
    auto const& encrypted_seed_cpp = kth_wallet_wallet_data_cpp(wallet_data).encrypted_seed;
    return kth::to_encrypted_seed_t(encrypted_seed_cpp);
}

void kth_wallet_wallet_data_encrypted_seed_out(kth_wallet_data_t wallet_data, kth_encrypted_seed_t* out_encrypted_seed) {
    auto const& encrypted_seed_cpp = kth_wallet_wallet_data_cpp(wallet_data).encrypted_seed;
    kth::copy_c_hash(encrypted_seed_cpp, out_encrypted_seed);
}

} // extern "C"
