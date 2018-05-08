/**
 * Copyright (c) 2017 Bitprim developers (see AUTHORS)
 *
 * This file is part of Bitprim.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <bitprim/nodecint/chain/script.h>

#include <bitprim/nodecint/convertions.hpp>

libbitcoin::chain::script const& chain_script_const_cpp(script_t s) {
    return *static_cast<libbitcoin::chain::script const*>(s);
}

libbitcoin::chain::script& chain_script_cpp(script_t s) {
    return *static_cast<libbitcoin::chain::script*>(s);
}

extern "C" {

void chain_script_destruct(script_t script) {
    auto script_cpp = static_cast<libbitcoin::chain::script*>(script);
    delete script_cpp;
}

int /*bool*/ chain_script_is_valid(script_t script) {
    return static_cast<int>(chain_script_const_cpp(script).is_valid());
}

int /*bool*/ chain_script_is_valid_operations(script_t script) {
    return static_cast<int>(chain_script_const_cpp(script).is_valid_operations());
}

uint64_t /*size_t*/ chain_script_serialized_size(script_t script, int /*bool*/ prefix) {
    return chain_script_const_cpp(script).serialized_size(prefix != 0);
}

//Note: user of the function has to release the resource (memory) manually
char const* chain_script_to_string(script_t script, uint32_t active_forks) {
    auto str = chain_script_const_cpp(script).to_string(active_forks);
    auto* ret = (char*)malloc((str.size() + 1) * sizeof(char)); // NOLINT

//    std::strcpy(ret, str.c_str());
    std::copy_n(str.begin(), str.size() + 1, ret);
    return ret;
}

//TODO Move this logic elsewhere (this does not go in a wrapper like node-cint)
char const* chain_script_type(script_t script){
    auto script_pattern = chain_script_const_cpp(script).pattern();
    std::string type = "non_standard";
    switch(script_pattern)
    {
        case libbitcoin::machine::script_pattern::null_data: type = "nulldata"; break;
        case libbitcoin::machine::script_pattern::pay_multisig: type = "pay_multisig"; break;
        case libbitcoin::machine::script_pattern::pay_public_key: type = "pay_public_key"; break;
        case libbitcoin::machine::script_pattern::pay_key_hash: type = "pay_key_hash"; break;
        case libbitcoin::machine::script_pattern::pay_script_hash: type = "pay_script_hash"; break;
        case libbitcoin::machine::script_pattern::sign_multisig: type = "sign_multisig"; break;
        case libbitcoin::machine::script_pattern::sign_public_key: type = "sign_public_key"; break;
        case libbitcoin::machine::script_pattern::sign_key_hash: type = "sign_key_hash"; break;
        case libbitcoin::machine::script_pattern::sign_script_hash: type = "sign_script_hash"; break;
        default: type = "non_standard"; break;
    }
    auto* ret = (char*)malloc((type.size() + 1) * sizeof(char)); // NOLINT
    std::copy_n(type.begin(), type.size() + 1, ret);
    return ret;
}

uint8_t const* chain_script_to_data(script_t script, int /*bool*/ prefix, uint64_t* /*size_t*/ out_size) {
    auto script_data = chain_script_const_cpp(script).to_data(prefix);
    auto* ret = (uint8_t*)malloc((script_data.size()) * sizeof(uint8_t)); // NOLINT
    std::copy_n(script_data.begin(), script_data.size(), ret);
    *out_size = script_data.size();
    return ret;
}

uint64_t /*size_t*/ chain_script_sigops(script_t script, int /*bool*/ embedded) {
    return chain_script_const_cpp(script).sigops(embedded != 0);
}

//TODO DELETE
//uint64_t /*size_t*/ chain_script_embedded_sigops(script_t script, script_t prevout_script) {
//    auto const& prevout_script_cpp = chain_script_const_cpp(prevout_script);
//    return chain_script_const_cpp(script).embedded_sigops(prevout_script_cpp);
//}

//void chain_script_find_and_delete(script_t script, const data_stack& endorsements) {
//    return chain_script_const_cpp(script).embedded_sigops(find_and_delete);
//}







//
//// Serialization.
////-------------------------------------------------------------------------
//
//data_chunk to_data(bool prefix) const;
//void to_data(std::ostream& stream, bool prefix) const;
//void to_data(writer& sink, bool prefix) const;
//
//std::string to_string(uint32_t active_forks) const;
//
//// Iteration.
////-------------------------------------------------------------------------
//
//void clear();
//bool empty() const;
//size_t size() const;
//const operation& front() const;
//const operation& back() const;
//operation::iterator begin() const;
//operation::iterator end() const;
//const operation& operator[](size_t index) const;
//
//// Properties (size, accessors, cache).
////-------------------------------------------------------------------------
//
//const operation::list& operations() const;
//
//// Signing.
////-------------------------------------------------------------------------
//
//static hash_digest generate_signature_hash(const transaction& tx,
//                                           uint32_t input_index, const script& script_code, uint8_t sighash_type);
//
//static bool check_signature(const ec_signature& signature,
//                            uint8_t sighash_type, const data_chunk& public_key,
//                            const script& script_code, const transaction& tx,
//                            uint32_t input_index);
//
//static bool create_endorsement(endorsement& out, const ec_secret& secret,
//                               const script& prevout_script, const transaction& tx,
//                               uint32_t input_index, uint8_t sighash_type);
//
//// Utilities (static).
////-------------------------------------------------------------------------
//
///// Determine if the fork is enabled in the active forks set.
//static bool is_enabled(uint32_t active_forks, machine::rule_fork fork)
//{
//    return (fork & active_forks) != 0;
//}
//
///// No-code patterns (consensus).
//static bool is_push_only(const operation::list& ops);
//static bool is_relaxed_push(const operation::list& ops);
//static bool is_coinbase_pattern(const operation::list& ops, size_t height);
//
///// Unspendable pattern (standard).
//static bool is_null_data_pattern(const operation::list& ops);
//
///// Payment script patterns (standard, psh is also consensus).
//static bool is_pay_multisig_pattern(const operation::list& ops);
//static bool is_pay_public_key_pattern(const operation::list& ops);
//static bool is_pay_key_hash_pattern(const operation::list& ops);
//static bool is_pay_script_hash_pattern(const operation::list& ops);
//
///// Signature script patterns (standard).
//static bool is_sign_multisig_pattern(const operation::list& ops);
//static bool is_sign_public_key_pattern(const operation::list& ops);
//static bool is_sign_key_hash_pattern(const operation::list& ops);
//static bool is_sign_script_hash_pattern(const operation::list& ops);
//
///// Stack factories (standard).
//static operation::list to_null_data_pattern(data_slice data);
//static operation::list to_pay_public_key_pattern(data_slice point);
//static operation::list to_pay_key_hash_pattern(const short_hash& hash);
//static operation::list to_pay_script_hash_pattern(const short_hash& hash);
//static operation::list to_pay_multisig_pattern(uint8_t signatures,
//                                               const point_list& points);
//static operation::list to_pay_multisig_pattern(uint8_t signatures,
//                                               const data_stack& points);
//
//// Utilities (non-static).
////-------------------------------------------------------------------------
//
//machine::script_pattern pattern() const;
//void find_and_delete(const data_stack& endorsements);
//
//// Validation.
////-------------------------------------------------------------------------
//
//static code verify(const transaction& tx, uint32_t input, uint32_t forks);
//
//// TOD: move back to private.
//static code verify(const transaction& tx, uint32_t input_index,
//                   uint32_t forks, const script& input_script,
//                   const script& prevout_script);

} /* extern "C" */
