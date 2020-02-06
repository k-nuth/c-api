// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#ifndef KTH_CAPI_CHAIN_STEALTH_COMPACT_H_
#define KTH_CAPI_CHAIN_STEALTH_COMPACT_H_

#include <stdint.h>

#include <kth/capi/primitives.h>
#include <kth/capi/visibility.h>

#ifdef __cplusplus
extern "C" {
#endif

KTH_EXPORT
hash_t chain_stealth_compact_get_ephemeral_public_key_hash(stealth_compact_t stealth);

KTH_EXPORT
void chain_stealth_compact_get_ephemeral_public_key_hash_out(stealth_compact_t stealth, hash_t* out_epk_hash);

KTH_EXPORT
hash_t chain_stealth_compact_get_transaction_hash(stealth_compact_t stealth);

KTH_EXPORT
void chain_stealth_compact_get_transaction_hash_out(stealth_compact_t stealth, hash_t* out_tx_hash);

KTH_EXPORT
short_hash_t chain_stealth_compact_get_public_key_hash(stealth_compact_t stealth);

KTH_EXPORT
void chain_stealth_compact_get_public_key_hash_out(stealth_compact_t stealth, short_hash_t* out_pk_hash);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // KTH_CAPI_CHAIN_STEALTH_COMPACT_H_
