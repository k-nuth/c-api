// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_CAPI_CHAIN_HEADER_H_
#define KTH_CAPI_CHAIN_HEADER_H_

#include <stdint.h>

#include <kth/capi/primitives.h>
#include <kth/capi/visibility.h>


#ifdef __cplusplus
extern "C" {
#endif

KTH_EXPORT
kth_header_t kth_chain_header_factory_from_data(uint8_t* data, kth_size_t n);

KTH_EXPORT
kth_size_t kth_chain_header_satoshi_fixed_size();

KTH_EXPORT
void kth_chain_header_reset(kth_header_t header);

KTH_EXPORT
kth_size_t kth_chain_header_serialized_size(kth_header_t header);

KTH_EXPORT
uint8_t const* kth_chain_header_to_data(kth_header_t header, kth_size_t* out_size);

KTH_EXPORT
kth_header_t kth_chain_header_construct_default(void);

KTH_EXPORT
kth_header_t kth_chain_header_construct(uint32_t version, uint8_t* previous_block_hash, uint8_t* merkle, uint32_t timestamp, uint32_t bits, uint32_t nonce);

KTH_EXPORT
void kth_chain_header_destruct(kth_header_t header);

KTH_EXPORT
kth_bool_t kth_chain_header_is_valid(kth_header_t header);

KTH_EXPORT
uint32_t kth_chain_header_version(kth_header_t header);

KTH_EXPORT
void kth_chain_header_set_version(kth_header_t header, uint32_t version);

KTH_EXPORT
uint32_t kth_chain_header_timestamp(kth_header_t header);

KTH_EXPORT
void kth_chain_header_set_timestamp(kth_header_t header, uint32_t timestamp);

KTH_EXPORT
uint32_t kth_chain_header_bits(kth_header_t header);

KTH_EXPORT
char const* kth_chain_header_proof_str(kth_header_t header);

KTH_EXPORT
void kth_chain_header_set_bits(kth_header_t header, uint32_t bits);

KTH_EXPORT
uint32_t kth_chain_header_nonce(kth_header_t header);

KTH_EXPORT
void kth_chain_header_set_nonce(kth_header_t header, uint32_t nonce);

KTH_EXPORT
kth_hash_t kth_chain_header_previous_block_hash(kth_header_t header);

KTH_EXPORT
void kth_chain_header_previous_block_hash_out(kth_header_t header, kth_hash_t* out_previous_block_hash);

KTH_EXPORT
kth_hash_t kth_chain_header_merkle(kth_header_t header);

KTH_EXPORT
void kth_chain_header_merkle_out(kth_header_t header, kth_hash_t* out_merkle);

KTH_EXPORT
kth_hash_t kth_chain_header_hash(kth_header_t header);

KTH_EXPORT
void kth_chain_header_hash_out(kth_header_t header, kth_hash_t* out_hash);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* KTH_CAPI_CHAIN_HEADER_H_ */
