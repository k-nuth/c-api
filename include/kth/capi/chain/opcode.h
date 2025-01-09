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

// TODO: re-write the enum

typedef enum {
    // push value
    kth_opcode_push_size_0 = 0x00,     // 0        // is_version (pushes [] to the stack, not 0)
    kth_opcode_push_size_1 = 0x01,     // 1
    kth_opcode_push_size_2 = 0x02,     // 2
    kth_opcode_push_size_3 = 0x03,     // 3
    kth_opcode_push_size_4 = 0x04,     // 4
    kth_opcode_push_size_5 = 0x05,     // 5
    kth_opcode_push_size_6 = 0x06,     // 6
    kth_opcode_push_size_7 = 0x07,     // 7
    kth_opcode_push_size_8 = 0x08,     // 8
    kth_opcode_push_size_9 = 0x09,     // 9
    kth_opcode_push_size_10 = 0x0a,    // 10
    kth_opcode_push_size_11 = 0x0b,    // 11
    kth_opcode_push_size_12 = 0x0c,    // 12
    kth_opcode_push_size_13 = 0x0d,    // 13
    kth_opcode_push_size_14 = 0x0e,    // 14
    kth_opcode_push_size_15 = 0x0f,    // 15
    kth_opcode_push_size_16 = 0x10,    // 16
    kth_opcode_push_size_17 = 0x11,    // 17
    kth_opcode_push_size_18 = 0x12,    // 18
    kth_opcode_push_size_19 = 0x13,    // 19
    kth_opcode_push_size_20 = 0x14,    // 20
    kth_opcode_push_size_21 = 0x15,    // 21
    kth_opcode_push_size_22 = 0x16,    // 22
    kth_opcode_push_size_23 = 0x17,    // 23
    kth_opcode_push_size_24 = 0x18,    // 24
    kth_opcode_push_size_25 = 0x19,    // 25
    kth_opcode_push_size_26 = 0x1a,    // 26
    kth_opcode_push_size_27 = 0x1b,    // 27
    kth_opcode_push_size_28 = 0x1c,    // 28
    kth_opcode_push_size_29 = 0x1d,    // 29
    kth_opcode_push_size_30 = 0x1e,    // 30
    kth_opcode_push_size_31 = 0x1f,    // 31
    kth_opcode_push_size_32 = 0x20,    // 32
    kth_opcode_push_size_33 = 0x21,    // 33
    kth_opcode_push_size_34 = 0x22,    // 34
    kth_opcode_push_size_35 = 0x23,    // 35
    kth_opcode_push_size_36 = 0x24,    // 36
    kth_opcode_push_size_37 = 0x25,    // 37
    kth_opcode_push_size_38 = 0x26,    // 38
    kth_opcode_push_size_39 = 0x27,    // 39
    kth_opcode_push_size_40 = 0x28,    // 40
    kth_opcode_push_size_41 = 0x29,    // 41
    kth_opcode_push_size_42 = 0x2a,    // 42
    kth_opcode_push_size_43 = 0x2b,    // 43
    kth_opcode_push_size_44 = 0x2c,    // 44
    kth_opcode_push_size_45 = 0x2d,    // 45
    kth_opcode_push_size_46 = 0x2e,    // 46
    kth_opcode_push_size_47 = 0x2f,    // 47
    kth_opcode_push_size_48 = 0x30,    // 48
    kth_opcode_push_size_49 = 0x31,    // 49
    kth_opcode_push_size_50 = 0x32,    // 50
    kth_opcode_push_size_51 = 0x33,    // 51
    kth_opcode_push_size_52 = 0x34,    // 52
    kth_opcode_push_size_53 = 0x35,    // 53
    kth_opcode_push_size_54 = 0x36,    // 54
    kth_opcode_push_size_55 = 0x37,    // 55
    kth_opcode_push_size_56 = 0x38,    // 56
    kth_opcode_push_size_57 = 0x39,    // 57
    kth_opcode_push_size_58 = 0x3a,    // 58
    kth_opcode_push_size_59 = 0x3b,    // 59
    kth_opcode_push_size_60 = 0x3c,    // 60
    kth_opcode_push_size_61 = 0x3d,    // 61
    kth_opcode_push_size_62 = 0x3e,    // 62
    kth_opcode_push_size_63 = 0x3f,    // 63
    kth_opcode_push_size_64 = 0x40,    // 64
    kth_opcode_push_size_65 = 0x41,    // 65
    kth_opcode_push_size_66 = 0x42,    // 66
    kth_opcode_push_size_67 = 0x43,    // 67
    kth_opcode_push_size_68 = 0x44,    // 68
    kth_opcode_push_size_69 = 0x45,    // 69
    kth_opcode_push_size_70 = 0x46,    // 70
    kth_opcode_push_size_71 = 0x47,    // 71
    kth_opcode_push_size_72 = 0x48,    // 72
    kth_opcode_push_size_73 = 0x49,    // 73
    kth_opcode_push_size_74 = 0x4a,    // 74
    kth_opcode_push_size_75 = 0x4b,    // 75
    kth_opcode_push_one_size = 0x4c,   // 76
    kth_opcode_push_two_size = 0x4d,   // 77
    kth_opcode_push_four_size = 0x4e,  // 78

    kth_opcode_push_negative_1 = 0x4f, // 79 is_numeric
    kth_opcode_reserved_80 = 0x50,     // 80 [reserved]

    kth_opcode_push_positive_1 = 0x51, // 81, is_numeric, is_positive, is_version
    kth_opcode_push_positive_2 = 0x52, // 82, is_numeric, is_positive, is_version
    kth_opcode_push_positive_3 = 0x53, // 83, is_numeric, is_positive, is_version
    kth_opcode_push_positive_4 = 0x54, // 84, is_numeric, is_positive, is_version
    kth_opcode_push_positive_5 = 0x55, // 85, is_numeric, is_positive, is_version
    kth_opcode_push_positive_6 = 0x56, // 86, is_numeric, is_positive, is_version
    kth_opcode_push_positive_7 = 0x57, // 87, is_numeric, is_positive, is_version
    kth_opcode_push_positive_8 = 0x58, // 88, is_numeric, is_positive, is_version
    kth_opcode_push_positive_9 = 0x59, // 89, is_numeric, is_positive, is_version
    kth_opcode_push_positive_10 = 0x5a, // 90, is_numeric, is_positive, is_version
    kth_opcode_push_positive_11 = 0x5b, // 91, is_numeric, is_positive, is_version
    kth_opcode_push_positive_12 = 0x5c, // 92, is_numeric, is_positive, is_version
    kth_opcode_push_positive_13 = 0x5d, // 93, is_numeric, is_positive, is_version
    kth_opcode_push_positive_14 = 0x5e, // 94, is_numeric, is_positive, is_version
    kth_opcode_push_positive_15 = 0x5f, // 95, is_numeric, is_positive, is_version
    kth_opcode_push_positive_16 = 0x60, // 96, is_numeric, is_positive, is_version

    //-------------------------------------------------------------------------
    // is_counted

// control
    kth_opcode_nop = 0x61,               // 97
    kth_opcode_reserved_98 = 0x62,       // 98 [ver]
    kth_opcode_if_ = 0x63,               // 99 is_conditional
    kth_opcode_notif = 0x64,             // 100 is_conditional
    kth_opcode_disabled_verif = 0x65,    // 101 is_disabled
    kth_opcode_disabled_vernotif = 0x66, // 102 is_disabled
    kth_opcode_else_ = 0x67,             // 103 is_conditional
    kth_opcode_endif = 0x68,             // 104 is_conditional
    kth_opcode_verify = 0x69,            // 105
    kth_opcode_return_ = 0x6a,           // 106

// stack ops
    kth_opcode_toaltstack = 0x6b,        // 107
    kth_opcode_fromaltstack = 0x6c,      // 108
    kth_opcode_drop2 = 0x6d,             // 109
    kth_opcode_dup2 = 0x6e,              // 110
    kth_opcode_dup3 = 0x6f,              // 111
    kth_opcode_over2 = 0x70,             // 112
    kth_opcode_rot2 = 0x71,              // 113
    kth_opcode_swap2 = 0x72,             // 114
    kth_opcode_ifdup = 0x73,             // 115
    kth_opcode_depth = 0x74,             // 116
    kth_opcode_drop = 0x75,              // 117
    kth_opcode_dup = 0x76,               // 118
    kth_opcode_nip = 0x77,               // 119
    kth_opcode_over = 0x78,              // 120
    kth_opcode_pick = 0x79,              // 121
    kth_opcode_roll = 0x7a,              // 122
    kth_opcode_rot = 0x7b,               // 123
    kth_opcode_swap = 0x7c,              // 124
    kth_opcode_tuck = 0x7d,              // 125

// splice ops
    kth_opcode_cat = 0x7e,             // 126
    kth_opcode_split = 0x7f,           // 127 was called substr before (disabled and re-enabled after pythagoras/monolith upgrade, May 2018)
    kth_opcode_num2bin = 0x80,         // 128 was called left before (disabled and re-enabled after pythagoras/monolith upgrade, May 2018)
    kth_opcode_bin2num = 0x81,         // 129 was called right before (disabled and re-enabled after pythagoras/monolith upgrade, May 2018)
    kth_opcode_size = 0x82,            // 130

// bit logic
    kth_opcode_disabled_invert = 0x83, // 131, is_disabled
    kth_opcode_and_ = 0x84,            // 132, disabled and re-enabled after pythagoras/monolith upgrade, May 2018
    kth_opcode_or_ = 0x85,             // 133, disabled and re-enabled after pythagoras/monolith upgrade, May 2018
    kth_opcode_xor_ = 0x86,            // 134, disabled and re-enabled after pythagoras/monolith upgrade, May 2018
    kth_opcode_equal = 0x87,           // 135
    kth_opcode_equalverify = 0x88,     // 136
    kth_opcode_reserved_137 = 0x89,    // 137 [reserved1]
    kth_opcode_reserved_138 = 0x8a,    // 138 [reserved2]

// numeric
    kth_opcode_add1 = 0x8b,            //  139
    kth_opcode_sub1 = 0x8c,            // 140
    kth_opcode_disabled_mul2 = 0x8d,   // 141 is_disabled
    kth_opcode_disabled_div2 = 0x8e,   // 142 is_disabled
    kth_opcode_negate = 0x8f,          // 143
    kth_opcode_abs = 0x90,             // 144
    kth_opcode_not_ = 0x91,            // 145
    kth_opcode_nonzero = 0x92,         // 146

    kth_opcode_add = 0x93,             // 147
    kth_opcode_sub = 0x94,             // 148
    kth_opcode_mul = 0x95,             // 149, disabled and re-enabled after gauss/upgrade8 upgrade, May 2022
    kth_opcode_div = 0x96,             // 150, disabled and re-enabled after pythagoras/monolith upgrade, May 2018
    kth_opcode_mod = 0x97,             // 151, disabled and re-enabled after pythagoras/monolith upgrade, May 2018
    kth_opcode_disabled_lshift = 0x98, // 152 is_disabled
    kth_opcode_disabled_rshift = 0x99, // 153 is_disabled

    kth_opcode_booland = 0x9a,            // 154
    kth_opcode_boolor = 0x9b,             // 155
    kth_opcode_numequal = 0x9c,           // 156
    kth_opcode_numequalverify = 0x9d,     // 157
    kth_opcode_numnotequal = 0x9e,        // 158
    kth_opcode_lessthan = 0x9f,           // 159
    kth_opcode_greaterthan = 0xa0,        // 160
    kth_opcode_lessthanorequal = 0xa1,    // 161
    kth_opcode_greaterthanorequal = 0xa2, // 162
    kth_opcode_min = 0xa3,                // 163
    kth_opcode_max = 0xa4,                // 164

    kth_opcode_within = 0xa5,             // 165

// crypto
    kth_opcode_ripemd160 = 0xa6,           // 166
    kth_opcode_sha1 = 0xa7,                // 167
    kth_opcode_sha256 = 0xa8,              // 168
    kth_opcode_hash160 = 0xa9,             // 169
    kth_opcode_hash256 = 0xaa,             // 170
    kth_opcode_codeseparator = 0xab,       // 171
    kth_opcode_checksig = 0xac,            // 172
    kth_opcode_checksigverify = 0xad,      // 173
    kth_opcode_checkmultisig = 0xae,       // 174
    kth_opcode_checkmultisigverify = 0xaf, // 175

// expansion
    kth_opcode_nop1 = 0xb0,                 // 176
    kth_opcode_nop2 = 0xb1,                 // 177
    kth_opcode_checklocktimeverify = kth_opcode_nop2,  // 177
    kth_opcode_nop3 = 0xb2,                 // 178
    kth_opcode_checksequenceverify = kth_opcode_nop3,  // 178
    kth_opcode_nop4 = 0xb3,                 // 179
    kth_opcode_nop5 = 0xb4,                 // 180
    kth_opcode_nop6 = 0xb5,                 // 181
    kth_opcode_nop7 = 0xb6,                 // 182
    kth_opcode_nop8 = 0xb7,                 // 183
    kth_opcode_nop9 = 0xb8,                 // 184
    kth_opcode_nop10 = 0xb9,                // 185

// more crypto
    kth_opcode_checkdatasig = 0xba,         // 186
    kth_opcode_checkdatasigverify = 0xbb,   // 187

// additional byte string operations
    kth_opcode_reverse_bytes = 0xbc,         // 188

// Available codepoints
    // 0xbd,                     // 189
    // 0xbe,                     // 190
    // 0xbf,                     // 191

// Native Introspection opcodes
    kth_opcode_input_index = 0xc0,           // 192
    kth_opcode_active_bytecode = 0xc1,       // 193
    kth_opcode_tx_version = 0xc2,            // 194
    kth_opcode_tx_input_count = 0xc3,        // 195
    kth_opcode_tx_output_count = 0xc4,       // 196
    kth_opcode_tx_locktime = 0xc5,           // 197
    kth_opcode_utxo_value = 0xc6,            // 198
    kth_opcode_utxo_bytecode = 0xc7,         // 199
    kth_opcode_outpoint_tx_hash = 0xc8,      // 200
    kth_opcode_outpoint_index = 0xc9,        // 201
    kth_opcode_input_bytecode = 0xca,        // 202
    kth_opcode_input_sequence_number = 0xcb, // 203
    kth_opcode_output_value = 0xcc,          // 204
    kth_opcode_output_bytecode = 0xcd,       // 205

// Native Introspection of tokens (SCRIPT_ENABLE_TOKENS must be set)
    kth_opcode_utxo_token_category = 0xce,     // 206
    kth_opcode_utxo_token_commitment = 0xcf,   // 207
    kth_opcode_utxo_token_amount = 0xd0,       // 208
    kth_opcode_output_token_category = 0xd1,   // 209
    kth_opcode_output_token_commitment = 0xd2, // 210
    kth_opcode_output_token_amount = 0xd3,     // 211

    kth_opcode_reserved_212 = 0xd4,          // 212
    kth_opcode_reserved_213 = 0xd5,          // 213
    kth_opcode_reserved_214 = 0xd6,          // 214

// The first op_code value after all defined opcodes
    kth_opcode_first_undefined_op_value = kth_opcode_reserved_214, // 0xd6 214

    kth_opcode_reserved_215 = 0xd7,          // 215
    kth_opcode_reserved_216 = 0xd8,          // 216
    kth_opcode_reserved_217 = 0xd9,          // 217
    kth_opcode_reserved_218 = 0xda,          // 218
    kth_opcode_reserved_219 = 0xdb,          // 219
    kth_opcode_reserved_220 = 0xdc,          // 220
    kth_opcode_reserved_221 = 0xdd,          // 221
    kth_opcode_reserved_222 = 0xde,          // 222
    kth_opcode_reserved_223 = 0xdf,          // 223
    kth_opcode_reserved_224 = 0xe0,          // 224
    kth_opcode_reserved_225 = 0xe1,          // 225
    kth_opcode_reserved_226 = 0xe2,          // 226
    kth_opcode_reserved_227 = 0xe3,          // 227
    kth_opcode_reserved_228 = 0xe4,          // 228
    kth_opcode_reserved_229 = 0xe5,          // 229
    kth_opcode_reserved_230 = 0xe6,          // 230
    kth_opcode_reserved_231 = 0xe7,          // 231
    kth_opcode_reserved_232 = 0xe8,          // 232
    kth_opcode_reserved_233 = 0xe9,          // 233
    kth_opcode_reserved_234 = 0xea,          // 234
    kth_opcode_reserved_235 = 0xeb,          // 235
    kth_opcode_reserved_236 = 0xec,          // 236
    kth_opcode_reserved_237 = 0xed,          // 237
    kth_opcode_reserved_238 = 0xee,          // 238
    kth_opcode_reserved_239 = 0xef,          // 239

// Invalid opcode if executed, but used for special token prefix if at
// position 0 in scriptPubKey. See: primitives/token.h
    kth_opcode_special_token_prefix = kth_opcode_reserved_239, // 0xef 239

    kth_opcode_reserved_240 = 0xf0,        // 240
    kth_opcode_reserved_241 = 0xf1,        // 241
    kth_opcode_reserved_242 = 0xf2,        // 242
    kth_opcode_reserved_243 = 0xf3,        // 243
    kth_opcode_reserved_244 = 0xf4,        // 244
    kth_opcode_reserved_245 = 0xf5,        // 245
    kth_opcode_reserved_246 = 0xf6,        // 246
    kth_opcode_reserved_247 = 0xf7,        // 247
    kth_opcode_reserved_248 = 0xf8,        // 248
    kth_opcode_reserved_249 = 0xf9,        // 249
    kth_opcode_reserved_250 = 0xfa,        // 250
    kth_opcode_reserved_251 = 0xfb,        // 251
    kth_opcode_reserved_252 = 0xfc,        // 252
    kth_opcode_reserved_253 = 0xfd,        // 253
    kth_opcode_reserved_254 = 0xfe,        // 254
    kth_opcode_reserved_255 = 0xff,        // 255

    kth_opcode_kth_opcode_invalidopcode = kth_opcode_reserved_255,  //  0xff 255  < Not a real OPCODE!

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
