// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/capi/wallet/elliptic_curve.h>

#include <kth/capi/conversions.hpp>
#include <kth/capi/helpers.hpp>
#include <kth/capi/primitives.h>
#include <kth/capi/wallet/conversions.hpp>

extern "C" {

kth_bool_t kth_wallet_secret_to_public(kth_ec_compressed_t* out, kth_ec_secret_t secret) {
    kth::ec_compressed out_cpp;
    auto secret_cpp = detail::from_ec_secret_t(secret);
    bool success = kth::secret_to_public(out_cpp, secret_cpp);

    if (success) {
        *out = detail::to_ec_compressed_t(out_cpp);
    }

    return kth::bool_to_int(success);
}

} // extern "C"
