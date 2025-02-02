// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_CAPI_WALLET_PRIMITIVES_H_
#define KTH_CAPI_WALLET_PRIMITIVES_H_

#include <stdint.h>

#include <kth/capi/primitives.h>
#include <kth/capi/visibility.h>

#ifdef __cplusplus
extern "C" {
#endif

#define KTH_HD_CHAIN_CODE_SIZE 32
#define KTH_HD_KEY_SIZE 82
#define KTH_EC_COMPRESSED_SIZE 33
#define KTH_BITCOIN_EC_UNCOMPRESSED_SIZE 65
#define KTH_BITCOIN_EC_SECRET_SIZE 32
#define KTH_HD_FIRST_HARDENED_KEY (1 << 31)
#define KTH_WIF_UNCOMPRESSED_SIZE 37U
#define KTH_WIF_COMPRESSED_SIZE 38U
#define KTH_EC_SIGNATURE_SIZE 64
typedef struct {
    uint8_t data[KTH_HD_CHAIN_CODE_SIZE];
} kth_hd_chain_code_t;

typedef struct {
    uint8_t data[KTH_HD_KEY_SIZE];
} kth_hd_key_t;

typedef struct {
    uint8_t data[KTH_EC_COMPRESSED_SIZE];
} kth_ec_compressed_t;

typedef struct {
    uint8_t data[KTH_BITCOIN_EC_UNCOMPRESSED_SIZE];
} kth_ec_uncompressed_t;

typedef struct kth_ec_secret_t {
    uint8_t hash[KTH_BITCOIN_EC_SECRET_SIZE];
} kth_ec_secret_t;

typedef struct {
    uint8_t data[KTH_WIF_UNCOMPRESSED_SIZE];
} kth_wif_uncompressed_t;

typedef struct {
    uint8_t data[KTH_WIF_COMPRESSED_SIZE];
} kth_wif_compressed_t;


// Parsed ECDSA signature:
typedef struct {
    uint8_t data[KTH_EC_SIGNATURE_SIZE];
} kth_ec_signature_t;


typedef void* kth_ec_private_t;
typedef void* kth_ec_public_t;
typedef void* kth_hd_private_t;
typedef void* kth_hd_public_t;

#ifdef __cplusplus
} // extern "C"
#endif


#endif /* KTH_CAPI_WALLET_PRIMITIVES_H_ */
