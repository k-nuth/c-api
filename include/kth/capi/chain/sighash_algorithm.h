// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_CAPI_CHAIN_SIGHASH_ALGORITHM_H_
#define KTH_CAPI_CHAIN_SIGHASH_ALGORITHM_H_

#include <stdint.h>

#include <kth/capi/primitives.h>
#include <kth/capi/visibility.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    /// The default, signs all the inputs and outputs, protecting everything
    /// except the signature scripts against modification.
    kth_sighash_algorithm_all = 0x01,

    /// Signs all of the inputs but none of the outputs, allowing anyone to
    /// change where the satoshis are going unless other signatures using
    /// other signature hash flags protect the outputs.
    kth_sighash_algorithm_none = 0x02,

    /// The only output signed is the one corresponding to this input (the
    /// output with the same output index number as this input), ensuring
    /// nobody can change your part of the transaction but allowing other
    /// signers to change their part of the transaction. The corresponding
    /// output must exist or the value '1' will be signed, breaking the
    /// security scheme. This input, as well as other inputs, are included
    /// in the signature. The sequence numbers of other inputs are not
    /// included in the signature, and can be updated.
    kth_sighash_algorithm_single = 0x03,


#if defined(KTH_CURRENCY_BCH)
    ///< New in Descartes/Upgrade9 (2023-May), must only be accepted if flags & SCRIPT_ENABLE_TOKENS
    kth_sighash_algorithm_utxos = 0x20,
    kth_sighash_algorithm_utxos_all = kth_sighash_algorithm_all | kth_sighash_algorithm_utxos,
    kth_sighash_algorithm_utxos_none = kth_sighash_algorithm_none | kth_sighash_algorithm_utxos,
    kth_sighash_algorithm_utxos_single = kth_sighash_algorithm_single | kth_sighash_algorithm_utxos,

    kth_sighash_algorithm_forkid = 0x40,
    kth_sighash_algorithm_forkid_all = kth_sighash_algorithm_all | kth_sighash_algorithm_forkid,
    kth_sighash_algorithm_forkid_none = kth_sighash_algorithm_none | kth_sighash_algorithm_forkid,
    kth_sighash_algorithm_forkid_single = kth_sighash_algorithm_single | kth_sighash_algorithm_forkid,
#endif

    /// The above types can be modified with this flag, creating three new
    /// combined types.
    kth_sighash_algorithm_anyone_can_pay = 0x80,

    /// Signs all of the outputs but only this one input, and it also allows
    /// anyone to add or remove other inputs, so anyone can contribute
    /// additional satoshis but they cannot change how many satoshis are
    /// sent nor where they go.
    kth_sighash_algorithm_anyone_can_pay_all = kth_sighash_algorithm_all | kth_sighash_algorithm_anyone_can_pay,

    /// Signs only this one input and allows anyone to add or remove other
    /// inputs or outputs, so anyone who gets a copy of this input can spend
    /// it however they'd like.
    kth_sighash_algorithm_anyone_can_pay_none = kth_sighash_algorithm_none | kth_sighash_algorithm_anyone_can_pay,

    /// Signs this one input and its corresponding output. Allows anyone to
    /// add or remove other inputs.
    kth_sighash_algorithm_anyone_can_pay_single = kth_sighash_algorithm_single | kth_sighash_algorithm_anyone_can_pay,

    /// Used to mask unused bits in the signature hash byte.
    kth_sighash_algorithm_mask = 0x1f

} kth_sighash_algorithm_t;


/// Convert the opcode to a mnemonic string.
KTH_EXPORT
char const* kth_chain_opcode_to_string(kth_opcode_t value, uint32_t active_forks);

/// Convert a string to an opcode.
KTH_EXPORT
kth_bool_t kth_chain_opcode_from_string(kth_opcode_t* out_code, char const* value);

/// Convert any opcode to a string hexadecimal representation.
KTH_EXPORT
char const* kth_chain_opcode_to_hexadecimal(kth_opcode_t code);

// Convert any hexadecimal byte to an opcode.
KTH_EXPORT
kth_bool_t kth_chain_opcode_from_hexadecimal(kth_opcode_t* out_code, char const* value);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* KTH_CAPI_CHAIN_SIGHASH_ALGORITHM_H_ */