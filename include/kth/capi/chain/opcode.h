// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_CAPI_CHAIN_OPCODE_H_
#define KTH_CAPI_CHAIN_OPCODE_H_

#include <stdint.h>

#include <kth/capi/primitives.h>
#include <kth/capi/visibility.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    kth_opcode_push_size_0 = 0,        // is_version (pushes [] to the stack, not 0)
    kth_opcode_push_size_1 = 1,
    kth_opcode_push_size_2 = 2,
    kth_opcode_push_size_3 = 3,
    kth_opcode_push_size_4 = 4,
    kth_opcode_push_size_5 = 5,
    kth_opcode_push_size_6 = 6,
    kth_opcode_push_size_7 = 7,
    kth_opcode_push_size_8 = 8,
    kth_opcode_push_size_9 = 9,
    kth_opcode_push_size_10 = 10,
    kth_opcode_push_size_11 = 11,
    kth_opcode_push_size_12 = 12,
    kth_opcode_push_size_13 = 13,
    kth_opcode_push_size_14 = 14,
    kth_opcode_push_size_15 = 15,
    kth_opcode_push_size_16 = 16,
    kth_opcode_push_size_17 = 17,
    kth_opcode_push_size_18 = 18,
    kth_opcode_push_size_19 = 19,
    kth_opcode_push_size_20 = 20,
    kth_opcode_push_size_21 = 21,
    kth_opcode_push_size_22 = 22,
    kth_opcode_push_size_23 = 23,
    kth_opcode_push_size_24 = 24,
    kth_opcode_push_size_25 = 25,
    kth_opcode_push_size_26 = 26,
    kth_opcode_push_size_27 = 27,
    kth_opcode_push_size_28 = 28,
    kth_opcode_push_size_29 = 29,
    kth_opcode_push_size_30 = 30,
    kth_opcode_push_size_31 = 31,
    kth_opcode_push_size_32 = 32,
    kth_opcode_push_size_33 = 33,
    kth_opcode_push_size_34 = 34,
    kth_opcode_push_size_35 = 35,
    kth_opcode_push_size_36 = 36,
    kth_opcode_push_size_37 = 37,
    kth_opcode_push_size_38 = 38,
    kth_opcode_push_size_39 = 39,
    kth_opcode_push_size_40 = 40,
    kth_opcode_push_size_41 = 41,
    kth_opcode_push_size_42 = 42,
    kth_opcode_push_size_43 = 43,
    kth_opcode_push_size_44 = 44,
    kth_opcode_push_size_45 = 45,
    kth_opcode_push_size_46 = 46,
    kth_opcode_push_size_47 = 47,
    kth_opcode_push_size_48 = 48,
    kth_opcode_push_size_49 = 49,
    kth_opcode_push_size_50 = 50,
    kth_opcode_push_size_51 = 51,
    kth_opcode_push_size_52 = 52,
    kth_opcode_push_size_53 = 53,
    kth_opcode_push_size_54 = 54,
    kth_opcode_push_size_55 = 55,
    kth_opcode_push_size_56 = 56,
    kth_opcode_push_size_57 = 57,
    kth_opcode_push_size_58 = 58,
    kth_opcode_push_size_59 = 59,
    kth_opcode_push_size_60 = 60,
    kth_opcode_push_size_61 = 61,
    kth_opcode_push_size_62 = 62,
    kth_opcode_push_size_63 = 63,
    kth_opcode_push_size_64 = 64,
    kth_opcode_push_size_65 = 65,
    kth_opcode_push_size_66 = 66,
    kth_opcode_push_size_67 = 67,
    kth_opcode_push_size_68 = 68,
    kth_opcode_push_size_69 = 69,
    kth_opcode_push_size_70 = 70,
    kth_opcode_push_size_71 = 71,
    kth_opcode_push_size_72 = 72,
    kth_opcode_push_size_73 = 73,
    kth_opcode_push_size_74 = 74,
    kth_opcode_push_size_75 = 75,
    kth_opcode_push_one_size = 76,
    kth_opcode_push_two_size = 77,
    kth_opcode_push_four_size = 78,
    kth_opcode_push_negative_1 = 79,   // is_numeric
    kth_opcode_reserved_80 = 80,       // [reserved]
    kth_opcode_push_positive_1 = 81,   // is_numeric, is_positive, is_version
    kth_opcode_push_positive_2 = 82,   // is_numeric, is_positive, is_version
    kth_opcode_push_positive_3 = 83,   // is_numeric, is_positive, is_version
    kth_opcode_push_positive_4 = 84,   // is_numeric, is_positive, is_version
    kth_opcode_push_positive_5 = 85,   // is_numeric, is_positive, is_version
    kth_opcode_push_positive_6 = 86,   // is_numeric, is_positive, is_version
    kth_opcode_push_positive_7 = 87,   // is_numeric, is_positive, is_version
    kth_opcode_push_positive_8 = 88,   // is_numeric, is_positive, is_version
    kth_opcode_push_positive_9 = 89,   // is_numeric, is_positive, is_version
    kth_opcode_push_positive_10 = 90,  // is_numeric, is_positive, is_version
    kth_opcode_push_positive_11 = 91,  // is_numeric, is_positive, is_version
    kth_opcode_push_positive_12 = 92,  // is_numeric, is_positive, is_version
    kth_opcode_push_positive_13 = 93,  // is_numeric, is_positive, is_version
    kth_opcode_push_positive_14 = 94,  // is_numeric, is_positive, is_version
    kth_opcode_push_positive_15 = 95,  // is_numeric, is_positive, is_version
    kth_opcode_push_positive_16 = 96,  // is_numeric, is_positive, is_version

    //-------------------------------------------------------------------------
    // is_counted

    kth_opcode_nop = 97,
    kth_opcode_reserved_98 = 98,       // [ver]
    kth_opcode_if_ = 99,               // is_conditional
    kth_opcode_notif = 100,            // is_conditional
    kth_opcode_disabled_verif = 101,   // is_disabled
    kth_opcode_disabled_vernotif = 102,// is_disabled
    kth_opcode_else_ = 103,            // is_conditional
    kth_opcode_endif = 104,            // is_conditional
    kth_opcode_verify = 105,
    kth_opcode_return_ = 106,
    kth_opcode_toaltstack = 107,
    kth_opcode_fromaltstack = 108,
    kth_opcode_drop2 = 109,
    kth_opcode_dup2 = 110,
    kth_opcode_dup3 = 111,
    kth_opcode_over2 = 112,
    kth_opcode_rot2 = 113,
    kth_opcode_swap2 = 114,
    kth_opcode_ifdup = 115,
    kth_opcode_depth = 116,
    kth_opcode_drop = 117,
    kth_opcode_dup = 118,
    kth_opcode_nip = 119,
    kth_opcode_over = 120,
    kth_opcode_pick = 121,
    kth_opcode_roll = 122,
    kth_opcode_rot = 123,
    kth_opcode_swap = 124,
    kth_opcode_tuck = 125,
    kth_opcode_disabled_cat = 126,     // is_disabled
    kth_opcode_disabled_substr = 127,  // is_disabled
    kth_opcode_disabled_left = 128,    // is_disabled
    kth_opcode_disabled_right = 129,   // is_disabled
    kth_opcode_size = 130,
    kth_opcode_disabled_invert = 131,  // is_disabled
    kth_opcode_disabled_and = 132,     // is_disabled
    kth_opcode_disabled_or = 133,      // is_disabled
    kth_opcode_disabled_xor = 134,     // is_disabled
    kth_opcode_equal = 135,
    kth_opcode_equalverify = 136,
    kth_opcode_reserved_137 = 137,     // [reserved1]
    kth_opcode_reserved_138 = 138,     // [reserved2]
    kth_opcode_add1 = 139,
    kth_opcode_sub1 = 140,
    kth_opcode_disabled_mul2 = 141,    // is_disabled
    kth_opcode_disabled_div2 = 142,    // is_disabled
    kth_opcode_negate = 143,
    kth_opcode_abs = 144,
    kth_opcode_not_ = 145,
    kth_opcode_nonzero = 146,
    kth_opcode_add = 147,
    kth_opcode_sub = 148,
    kth_opcode_disabled_mul = 149,     // is_disabled
    kth_opcode_disabled_div = 150,     // is_disabled
    kth_opcode_disabled_mod = 151,     // is_disabled
    kth_opcode_disabled_lshift = 152,  // is_disabled
    kth_opcode_disabled_rshift = 153,  // is_disabled
    kth_opcode_booland = 154,
    kth_opcode_boolor = 155,
    kth_opcode_numequal = 156,
    kth_opcode_numequalverify = 157,
    kth_opcode_numnotequal = 158,
    kth_opcode_lessthan = 159,
    kth_opcode_greaterthan = 160,
    kth_opcode_lessthanorequal = 161,
    kth_opcode_greaterthanorequal = 162,
    kth_opcode_min = 163,
    kth_opcode_max = 164,
    kth_opcode_within = 165,
    kth_opcode_ripemd160 = 166,
    kth_opcode_sha1 = 167,
    kth_opcode_sha256 = 168,
    kth_opcode_hash160 = 169,
    kth_opcode_hash256 = 170,
    kth_opcode_codeseparator = 171,
    kth_opcode_checksig = 172,
    kth_opcode_checksigverify = 173,
    kth_opcode_checkmultisig = 174,
    kth_opcode_checkmultisigverify = 175,


    kth_opcode_nop1 = 176,
    kth_opcode_nop2 = 177,
    kth_opcode_checklocktimeverify = kth_opcode_nop2,
    kth_opcode_nop3 = 178,
    kth_opcode_checksequenceverify = kth_opcode_nop3,
    kth_opcode_nop4 = 179,
    kth_opcode_nop5 = 180,
    kth_opcode_nop6 = 181,
    kth_opcode_nop7 = 182,
    kth_opcode_nop8 = 183,
    kth_opcode_nop9 = 184,
    kth_opcode_nop10 = 185,

    // More crypto
    kth_opcode_checkdatasig = 0xba,
    kth_opcode_checkdatasigverify = 0xbb,

    // additional byte string operations
    kth_opcode_reversebytes = 0xbc,

    // Available codepoints
    // 0xbd,
    // 0xbe,
    // 0xbf,

    // Native Introspection opcodes
    kth_opcode_inputindex = 0xc0,
    kth_opcode_activebytecode = 0xc1,
    kth_opcode_txversion = 0xc2,
    kth_opcode_txinputcount = 0xc3,
    kth_opcode_txoutputcount = 0xc4,
    kth_opcode_txlocktime = 0xc5,
    kth_opcode_utxovalue = 0xc6,
    kth_opcode_utxobytecode = 0xc7,
    kth_opcode_outpointtxhash = 0xc8,
    kth_opcode_outpointindex = 0xc9,
    kth_opcode_inputbytecode = 0xca,
    kth_opcode_inputsequencenumber = 0xcb,
    kth_opcode_outputvalue = 0xcc,
    kth_opcode_outputbytecode = 0xcd,

    // Native Introspection of tokens (SCRIPT_ENABLE_TOKENS must be set)
    kth_opcode_utxotokencategory = 0xce,
    kth_opcode_utxotokencommitment = 0xcf,
    kth_opcode_utxotokenamount = 0xd0,
    kth_opcode_outputtokencategory = 0xd1,
    kth_opcode_outputtokencommitment = 0xd2,
    kth_opcode_outputtokenamount = 0xd3,

    kth_opcode_reserved3 = 0xd4,
    kth_opcode_reserved4 = 0xd5,

    // The first op_code value after all defined opcodes
    kth_opcode_first_undefined_op_value,

    // Invalid opcode if executed, but used for special token prefix if at
    // position 0 in scriptPubKey. See: primitives/token.h
    kth_opcode_special_token_prefix = 0xef,

    kth_opcode_invalidopcode = 0xff,   ///< Not a real OPCODE!

    kth_opcode_reserved_186 = 186,
    kth_opcode_reserved_187 = 187,

    kth_opcode_reserved_188 = 188,
    kth_opcode_reserved_189 = 189,
    kth_opcode_reserved_190 = 190,
    kth_opcode_reserved_191 = 191,
    kth_opcode_reserved_192 = 192,
    kth_opcode_reserved_193 = 193,
    kth_opcode_reserved_194 = 194,
    kth_opcode_reserved_195 = 195,
    kth_opcode_reserved_196 = 196,
    kth_opcode_reserved_197 = 197,
    kth_opcode_reserved_198 = 198,
    kth_opcode_reserved_199 = 199,
    kth_opcode_reserved_200 = 200,
    kth_opcode_reserved_201 = 201,
    kth_opcode_reserved_202 = 202,
    kth_opcode_reserved_203 = 203,
    kth_opcode_reserved_204 = 204,
    kth_opcode_reserved_205 = 205,
    kth_opcode_reserved_206 = 206,
    kth_opcode_reserved_207 = 207,
    kth_opcode_reserved_208 = 208,
    kth_opcode_reserved_209 = 209,
    kth_opcode_reserved_210 = 210,
    kth_opcode_reserved_211 = 211,
    kth_opcode_reserved_212 = 212,
    kth_opcode_reserved_213 = 213,
    kth_opcode_reserved_214 = 214,
    kth_opcode_reserved_215 = 215,
    kth_opcode_reserved_216 = 216,
    kth_opcode_reserved_217 = 217,
    kth_opcode_reserved_218 = 218,
    kth_opcode_reserved_219 = 219,
    kth_opcode_reserved_220 = 220,
    kth_opcode_reserved_221 = 221,
    kth_opcode_reserved_222 = 222,
    kth_opcode_reserved_223 = 223,
    kth_opcode_reserved_224 = 224,
    kth_opcode_reserved_225 = 225,
    kth_opcode_reserved_226 = 226,
    kth_opcode_reserved_227 = 227,
    kth_opcode_reserved_228 = 228,
    kth_opcode_reserved_229 = 229,
    kth_opcode_reserved_230 = 230,
    kth_opcode_reserved_231 = 231,
    kth_opcode_reserved_232 = 232,
    kth_opcode_reserved_233 = 233,
    kth_opcode_reserved_234 = 234,
    kth_opcode_reserved_235 = 235,
    kth_opcode_reserved_236 = 236,
    kth_opcode_reserved_237 = 237,
    kth_opcode_reserved_238 = 238,
    kth_opcode_reserved_239 = 239,
    kth_opcode_reserved_240 = 240,
    kth_opcode_reserved_241 = 241,
    kth_opcode_reserved_242 = 242,
    kth_opcode_reserved_243 = 243,
    kth_opcode_reserved_244 = 244,
    kth_opcode_reserved_245 = 245,
    kth_opcode_reserved_246 = 246,
    kth_opcode_reserved_247 = 247,
    kth_opcode_reserved_248 = 248,
    kth_opcode_reserved_249 = 249,
    kth_opcode_reserved_250 = 250,
    kth_opcode_reserved_251 = 251,
    kth_opcode_reserved_252 = 252,
    kth_opcode_reserved_253 = 253,
    kth_opcode_reserved_254 = 254,
    kth_opcode_reserved_255 = 255

} kth_opcode_t;


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

#endif /* KTH_CAPI_CHAIN_OPCODE_H_ */
