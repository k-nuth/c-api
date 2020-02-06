// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#ifndef KTH_NODECINT_WALLET_RAW_OUTPUT_H_
#define KTH_NODECINT_WALLET_RAW_OUTPUT_H_

#include <stdint.h>

#include <kth/capi/primitives.h>
#include <kth/capi/visibility.h>

#ifdef __cplusplus
extern "C" {
#endif

KTH_EXPORT
payment_address_t wallet_raw_output_destiny(raw_output_t obj);

KTH_EXPORT
uint64_t wallet_raw_output_amount(raw_output_t obj);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* KTH_NODECINT_WALLET_RAW_OUTPUT_H_ */
