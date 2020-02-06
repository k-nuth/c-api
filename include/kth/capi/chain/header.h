// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#ifndef KTH_NODECINT_CHAIN_HEADER_H_
#define KTH_NODECINT_CHAIN_HEADER_H_

#include <stdint.h>

#include <kth/capi/primitives.h>
#include <kth/capi/visibility.h>


#ifdef __cplusplus
extern "C" {
#endif

KTH_EXPORT
header_t chain_header_factory_from_data(uint32_t version, uint8_t* data, uint64_t n);

KTH_EXPORT
uint64_t /*size_t*/ chain_header_satoshi_fixed_size(uint32_t version);

KTH_EXPORT
void chain_header_reset(header_t header);

KTH_EXPORT
uint64_t /*size_t*/ chain_header_serialized_size(header_t header, uint32_t version);

KTH_EXPORT
uint8_t const* chain_header_to_data(header_t header, uint32_t version, uint64_t* /*size_t*/ out_size);

KTH_EXPORT
header_t chain_header_construct_default(void);

KTH_EXPORT
header_t chain_header_construct(uint32_t version, uint8_t* previous_block_hash, uint8_t* merkle, uint32_t timestamp, uint32_t bits, uint32_t nonce);

KTH_EXPORT
void chain_header_destruct(header_t header);

KTH_EXPORT
int chain_header_is_valid(header_t header);

KTH_EXPORT
uint32_t chain_header_version(header_t header);

KTH_EXPORT
void chain_header_set_version(header_t header, uint32_t version);

KTH_EXPORT
uint32_t chain_header_timestamp(header_t header);

KTH_EXPORT
void chain_header_set_timestamp(header_t header, uint32_t timestamp);

KTH_EXPORT
uint32_t chain_header_bits(header_t header);

KTH_EXPORT
char const* chain_header_proof_str(header_t header);

KTH_EXPORT
void chain_header_set_bits(header_t header, uint32_t bits);

KTH_EXPORT
uint32_t chain_header_nonce(header_t header);

KTH_EXPORT
void chain_header_set_nonce(header_t header, uint32_t nonce);

KTH_EXPORT
hash_t chain_header_previous_block_hash(header_t header);

KTH_EXPORT
void chain_header_previous_block_hash_out(header_t header, hash_t* out_previous_block_hash);

KTH_EXPORT
hash_t chain_header_merkle(header_t header);

KTH_EXPORT
void chain_header_merkle_out(header_t header, hash_t* out_merkle);

KTH_EXPORT
hash_t chain_header_hash(header_t header);

KTH_EXPORT
void chain_header_hash_out(header_t header, hash_t* out_hash);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* KTH_NODECINT_CHAIN_HEADER_H_ */
