// Copyright (c) 2016-2023 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/capi/wallet/ec_public.h>

#include <kth/capi/conversions.hpp>
#include <kth/capi/helpers.hpp>
#include <kth/capi/type_conversions.h>

#include <kth/capi/wallet/conversions.hpp>

KTH_CONV_DEFINE(wallet, kth_ec_public_t, kth::domain::wallet::ec_public, ec_public)

extern "C" {

kth_ec_public_t kth_wallet_ec_public_construct_default() {
    return new kth::domain::wallet::ec_public();
}

kth_ec_public_t kth_wallet_ec_public_construct(kth_ec_private_t secret) {
    auto const& secret_cpp = kth_wallet_ec_private_const_cpp(secret);
    return new kth::domain::wallet::ec_public(secret_cpp);
}

kth_ec_public_t kth_wallet_ec_public_construct_from_decoded(uint8_t const* decoded, kth_size_t size) {
    return new kth::domain::wallet::ec_public(std::vector<uint8_t>(decoded, decoded + size));
}

kth_ec_public_t kth_wallet_ec_public_construct_from_base16(char const* base16) {
    return new kth::domain::wallet::ec_public(std::string(base16));
}

kth_ec_public_t kth_wallet_ec_public_construct_from_point(kth_ec_compressed_t const* point, kth_bool_t compress) {
    auto const& point_cpp = detail::from_ec_compressed_t(*point);
    return new kth::domain::wallet::ec_public(point_cpp, kth::int_to_bool(compress));
}

void kth_wallet_ec_public_destruct(kth_ec_public_t obj) {
    delete &kth_wallet_ec_public_cpp(obj);
}

kth_bool_t kth_wallet_ec_public_is_valid(kth_ec_public_t obj) {
    return kth::bool_to_int(kth_wallet_ec_public_const_cpp(obj).operator bool());
}

char* kth_wallet_ec_public_encoded(kth_ec_public_t obj) {
    std::string encoded = kth_wallet_ec_public_const_cpp(obj).encoded();
    return kth::create_c_str(encoded);
}

kth_ec_compressed_t kth_wallet_ec_public_point(kth_ec_public_t obj) {
    auto const& point_cpp = kth_wallet_ec_public_const_cpp(obj).point();
    return detail::to_ec_compressed_t(point_cpp);
}

// uint16_t kth_wallet_ec_public_version(kth_ec_public_t obj) {
//     return kth_wallet_ec_public_const_cpp(obj).version();
// }

// uint8_t kth_wallet_ec_public_payment_version(kth_ec_public_t obj) {
//     return kth_wallet_ec_public_const_cpp(obj).payment_version();
// }

// uint8_t kth_wallet_ec_public_wif_version(kth_ec_public_t obj) {
//     return kth_wallet_ec_public_const_cpp(obj).wif_version();
// }

kth_bool_t kth_wallet_ec_public_compressed(kth_ec_public_t obj) {
    return kth::bool_to_int(kth_wallet_ec_public_const_cpp(obj).compressed());
}

//Note: It is the responsability of the user to release/destruct the array
uint8_t const* kth_wallet_ec_public_to_data(kth_ec_public_t obj, kth_size_t* out_size) {
    kth::data_chunk data;
    bool const success = kth_wallet_ec_public_const_cpp(obj).to_data(data);
    if ( ! success) {
        *out_size = 0;
        return nullptr;
    }
    return kth::create_c_array(data, *out_size);
}

kth_bool_t kth_wallet_ec_public_to_uncompressed(kth_ec_public_t obj, kth_ec_uncompressed_t* out_data) {
    kth::ec_uncompressed uncompressed;
    bool const success = kth_wallet_ec_public_const_cpp(obj).to_uncompressed(uncompressed);
    if ( ! success) {
        out_data = nullptr;
        return false;
    }
    std::memcpy(out_data, uncompressed.data(), uncompressed.size());
    return kth::bool_to_int(success);
}

kth_payment_address_t kth_wallet_ec_public_to_payment_address(kth_ec_public_t obj, uint8_t version) {
    auto const& payment_address_cpp = kth_wallet_ec_public_const_cpp(obj).to_payment_address(version);
    return kth::move_or_copy_and_leak(std::move(payment_address_cpp));
}

} // extern "C"


// // kth_payment_address_t kth_wallet_ec_public_destiny(kth_ec_public_t obj) {
// //     return &kth_wallet_ec_public_cpp(obj).first;
// // }

// uint16_t kth_wallet_ec_public_version(kth_ec_public_t obj) {
//     return kth_wallet_ec_public_const_cpp(obj).version();
// }

// uint8_t kth_wallet_ec_public_payment_version(kth_ec_public_t obj) {
//     return kth_wallet_ec_public_const_cpp(obj).payment_version();
// }

// uint8_t kth_wallet_ec_public_wif_version(kth_ec_public_t obj) {
//     return kth_wallet_ec_public_const_cpp(obj).wif_version();
// }

