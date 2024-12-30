// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/capi/chain/operation.h>

#include <kth/capi/conversions.hpp>
#include <kth/capi/helpers.hpp>

// KTH_CONV_DEFINE(chain, kth_operation_t, kth::domain::machine::operation, operation)

// ---------------------------------------------------------------------------
extern "C" {

char const* kth_chain_opcode_to_string(kth_opcode_t value, uint32_t active_forks) {
    auto code_c = kth::opcode_to_cpp(value);
    auto str = kth::domain::machine::opcode_to_string(code_c, active_forks);
    return kth::create_c_str(str);
}

kth_bool_t kth_chain_opcode_from_string(kth_opcode_t* out_code, char const* value) {
    kth::domain::machine::opcode opc;
    auto const res = kth::domain::machine::opcode_from_string(opc, std::string(value));
    if ( ! res) {
        return kth::bool_to_int(false);
    }
    *out_code = kth::opcode_to_c(opc);
    return kth::bool_to_int(true);
}

char const* kth_chain_opcode_to_hexadecimal(kth_opcode_t code) {
    auto code_c = kth::opcode_to_cpp(code);
    auto str = kth::domain::machine::opcode_to_hexadecimal(code_c);
    return kth::create_c_str(str);
}

kth_bool_t kth_chain_opcode_from_hexadecimal(kth_opcode_t* out_code, char const* value) {
    kth::domain::machine::opcode opc;
    auto const res = kth::domain::machine::opcode_from_hexadecimal(opc, std::string(value));
    if ( ! res) {
        return kth::bool_to_int(false);
    }
    *out_code = kth::opcode_to_c(opc);
    return kth::bool_to_int(true);
}

} // extern "C"
