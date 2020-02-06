// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#include <knuth/nodecint/chain/output_point.h>

#include <knuth/nodecint/conversions.hpp>
#include <knuth/nodecint/helpers.hpp>

KTH_CONV_DEFINE(chain, output_point_t, libbitcoin::chain::output_point, output_point)

// ---------------------------------------------------------------------------
extern "C" {

output_point_t chain_output_point_construct() {
    // return std::make_unique<libbitcoin::chain::output_point>().release();
    return new libbitcoin::chain::output_point;
}


output_point_t chain_output_point_construct_from_hash_index(hash_t hash, uint32_t index) {
    auto hash_cpp = knuth::to_array(hash.hash);
    auto ret = new libbitcoin::chain::output_point(hash_cpp, index);
    return ret;
}

void chain_output_point_destruct(output_point_t op) {
    delete &chain_output_point_cpp(op);
}

//hash_t chain_output_point_get_hash(output_point_t op) {
//    auto const& hash_cpp = chain_output_point_const_cpp(op).hash();
//    return hash_cpp.data();
//}

hash_t chain_output_point_get_hash(output_point_t op) {
    auto const& hash_cpp = chain_output_point_const_cpp(op).hash();
    return knuth::to_hash_t(hash_cpp);
}

void chain_output_point_get_hash_out(output_point_t op, hash_t* out_hash) {
    auto const& hash_cpp = chain_output_point_const_cpp(op).hash();
    knuth::copy_c_hash(hash_cpp, out_hash);
}

uint32_t chain_output_point_get_index(output_point_t op) {
    return chain_output_point_const_cpp(op).index();
}

} // extern "C"
