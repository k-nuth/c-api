// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_CAPI_CHAIN_SCRIPT_PATTERN_H_
#define KTH_CAPI_CHAIN_SCRIPT_PATTERN_H_

#include <stdint.h>

#include <kth/capi/primitives.h>
#include <kth/capi/visibility.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    /// Null Data
    /// Pubkey Script: OP_RETURN <0 to 80 bytes of data> (formerly 40 bytes)
    /// Null data scripts cannot be spent, so there's no signature script.
    kth_script_pattern_null_data,

    /// Pay to Multisig [BIP11]
    /// Pubkey script: <m> <A pubkey>[B pubkey][C pubkey...] <n> OP_CHECKMULTISIG
    /// Signature script: OP_0 <A sig>[B sig][C sig...]
    kth_script_pattern_pay_multisig,

    /// Pay to Public Key (obsolete)
    kth_script_pattern_pay_public_key,

    /// Pay to Public Key Hash [P2PKH]
    /// Pubkey script: OP_DUP OP_HASH160 <PubKeyHash> OP_EQUALVERIFY OP_CHECKSIG
    /// Signature script: <sig> <pubkey>
    kth_script_pattern_pay_public_key_hash,

    /// Pay to Script Hash [P2SH/BIP16]
    /// The redeem script may be any pay type, but only multisig makes sense.
    /// Pubkey script: OP_HASH160 <Hash160(redeemScript)> OP_EQUAL
    /// Signature script: <sig>[sig][sig...] <redeemScript>
    kth_script_pattern_pay_script_hash,

    /// Pay to Script Hash 32
    /// The redeem script may be any pay type, but only multisig makes sense.
    /// Pubkey script: OP_HASH256 <Hash256(redeemScript)> OP_EQUAL
    /// Signature script: <sig>[sig][sig...] <redeemScript>
    kth_script_pattern_pay_script_hash_32,

    /// Sign Multisig script [BIP11]
    kth_script_pattern_sign_multisig,

    /// Sign Public Key (obsolete)
    kth_script_pattern_sign_public_key,

    /// Sign Public Key Hash [P2PKH]
    kth_script_pattern_sign_public_key_hash,

    /// Sign Script Hash [P2SH/BIP16]
    kth_script_pattern_sign_script_hash,

    /// Witness coinbase reserved value [BIP141].
    kth_script_pattern_witness_reservation,

    /// The script may be valid but does not conform to the common templates.
    /// Such scripts are always accepted if they are mined into blocks, but
    /// transactions with uncommon scripts may not be forwarded by peers.
    kth_script_pattern_non_standard

} kth_script_pattern_t;


#ifdef __cplusplus
} // extern "C"
#endif

#endif /* KTH_CAPI_CHAIN_SCRIPT_PATTERN_H_ */
