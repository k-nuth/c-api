// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_CAPI_HASH_H_
#define KTH_CAPI_HASH_H_

#include <kth/capi/primitives.h>
#include <kth/capi/visibility.h>
#include <kth/capi/wallet/primitives.h>

#ifdef __cplusplus
extern "C" {
#endif

KTH_EXPORT
kth_hash_t kth_sha256_hash(uint8_t const* data, kth_size_t size);

KTH_EXPORT
kth_hash_t kth_sha256_hash_reversed(uint8_t const* data, kth_size_t size);

KTH_EXPORT
char* kth_sha256_hash_reversed_str(uint8_t const* data, kth_size_t size);

KTH_EXPORT
kth_hash_t kth_str_to_hash(char const* str);

KTH_EXPORT
char* kth_hash_to_str(kth_hash_t hash);

KTH_EXPORT
void kth_shorthash_set(kth_shorthash_t* shorthash, uint8_t const* data);

KTH_EXPORT
void kth_shorthash_destruct(kth_shorthash_t* shorthash);

KTH_EXPORT
void kth_hash_set(kth_hash_t* hash, uint8_t const* data);

KTH_EXPORT
void kth_hash_destruct(kth_hash_t* hash);

KTH_EXPORT
void kth_longhash_set(kth_longhash_t* longhash, uint8_t const* data);

KTH_EXPORT
void kth_longhash_destruct(kth_longhash_t* longhash);

KTH_EXPORT
void kth_encrypted_seed_set(kth_encrypted_seed_t* seed, uint8_t const* data);

KTH_EXPORT
void kth_encrypted_seed_destruct(kth_encrypted_seed_t* seed);

KTH_EXPORT
void kth_ec_secret_set(kth_ec_secret_t* secret, uint8_t const* data);

KTH_EXPORT
void kth_ec_secret_destruct(kth_ec_secret_t* secret);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* KTH_CAPI_HASH_H_ */
