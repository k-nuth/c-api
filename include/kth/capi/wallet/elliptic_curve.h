// Copyright (c) 2016-2023 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_CAPI_WALLET_ELLIPTIC_CURVE_H_
#define KTH_CAPI_WALLET_ELLIPTIC_CURVE_H_

#include <kth/capi/primitives.h>
#include <kth/capi/visibility.h>
#include <kth/capi/wallet/primitives.h>

#ifdef __cplusplus
extern "C" {
#endif

kth_bool_t kth_wallet_secret_to_public(kth_ec_compressed_t* out, kth_ec_secret_t secret);

#ifdef __cplusplus
} // extern "C"
#endif


#endif /* KTH_CAPI_WALLET_ELLIPTIC_CURVE_H_ */
