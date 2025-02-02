// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <stdio.h>

#include <kth/capi/chain/chain.h>
#include <kth/capi/chain/history_compact.h>
#include <kth/capi/chain/history_compact_list.h>
#include <kth/capi/chain/input.h>
#include <kth/capi/chain/input_list.h>
#include <kth/capi/chain/output.h>
#include <kth/capi/chain/output_list.h>
#include <kth/capi/chain/output_point.h>
#include <kth/capi/chain/script.h>
#include <kth/capi/chain/transaction.h>
#include <kth/capi/chain/transaction_list.h>
#include <kth/capi/node.h>
#include <kth/capi/hash_list.h>

// #include <kth/capi/helpers.hpp>
#include <kth/capi/string_list.h>
#include <kth/capi/wallet/payment_address.h>
#include <kth/capi/wallet/wallet.h>
#include <kth/capi/wallet/payment_address_list.h>
#include <kth/capi/wallet/hd_private.h>
#include <kth/capi/wallet/hd_public.h>
#include <kth/capi/wallet/elliptic_curve.h>
#include <kth/capi/wallet/ec_public.h>

void print_hex(uint8_t const* data, size_t n) {
    while (n != 0) {
        printf("%02x", *data);
        ++data;
        --n;
    }
    printf("\n");
}

#define MAINNET_P2KH 0x00
#define MAINNET_P2SH 0x05


int main(int argc, char* argv[]) {
    // m/44'/145'/0'
    char const* m44h145h0h_xpub_str = "xpub6CAemD8S648fre9X1e1YwQwWnumAjaXX7t7BxrN7mJRNFm6cwFusodAeyM6GaZXMVbALsYj7m6yf4SGHnoW6NojroW9MxspnUpNEeA6wWPV";

    kth_hd_public_t m44h145h0h = kth_wallet_hd_public_construct_string(m44h145h0h_xpub_str);
    kth_hd_public_t m44h145h0h0 = kth_wallet_hd_public_derive_public(m44h145h0h, 0);

    printf("BIP44 Account Extended Public Key:  %s\n", kth_wallet_hd_public_encoded(m44h145h0h));
    printf("BIP32 Account Extended Public Key:  %s\n", kth_wallet_hd_public_encoded(m44h145h0h0));

    // print addresses
    for (size_t i = 0; i < 20; ++i) {
        kth_hd_public_t key = kth_wallet_hd_public_derive_public(m44h145h0h0, i);
        kth_ec_compressed_t point = kth_wallet_hd_public_point(key);
        kth_ec_public_t ecp = kth_wallet_ec_public_construct_from_point(&point, 1);
        kth_payment_address_t pa = kth_wallet_ec_public_to_payment_address(ecp, MAINNET_P2KH);
        printf("%s\n", kth_wallet_payment_address_encoded_cashaddr(pa, 0));
    }

    // bitcoincash:qr9sawzzmstkluq9nqefsu7eqya4zk2w7udune2pmf
    // bitcoincash:qpvmwrhxcdyyq64ar6kz46rejp0r2tjcwg8d462hum
    // bitcoincash:qqftgwpz0wm45z3sumncfrzm0s3n7x5rcqq9350gd6
    // bitcoincash:qrwelh5dw56rjnr3nnttfc45j0p0yv2a3vtuwu9nlt
    // bitcoincash:qpawyf7fp6lhvhld5gtz74smm969fx2j2546uj60l0
    // bitcoincash:qqzhz2m6cg6au7r3hntjraqj4aj8akg3gvakarc69v
    // bitcoincash:qpzf4kuq03js0tnug5z6e5q7zcfse6guagmhktuzcd
    // bitcoincash:qr6jhutnh6jk7aphlyu9sq5f6zu2epj8uqpynlacwk
    // bitcoincash:qrlfnn7f03n020yyvgyfqtq9fcu35wussq4ev4glfv
    // bitcoincash:qrmn9ss3dsu79rws6j4jwa9qhdxrr4rqcqxxxvlnwx
    // bitcoincash:qqnwp4ja6435s3v22hzhr5d5x6l7v80leyk7uf9z42
    // bitcoincash:qqyy3hnlt5z6xrxg57a74xt6tsce9hgrxqz7cz8tue
    // bitcoincash:qpz2w7k0khnekpetayza9mq3uy47qkmgcvw46r0yga
    // bitcoincash:qq3evlrgcdsgef6ut7l33qe2nguefnhvzgymup7pqk
    // bitcoincash:qr3mpurdzyf0qkxq6qgue7ym98fsej4fwqsxq4u5j0
    // bitcoincash:qz5m8qceta5cckhs8k77lrzjzpwpe9y26ufvkl8gq7
    // bitcoincash:qzjnd7pykzsyt4z93j7mcphjxf8fk8unyym7et8x2z
    // bitcoincash:qr2klzr2vllfq70a0ccd7zxpeaj2x8ma85wfrnp0tv
    // bitcoincash:qq38t4jlhsz7gn9z9lrqptklpdm3n9z6eqn3hhqgme
    // bitcoincash:qp9h0sjhe0m2pedjn3qr7x78c6utlpje9ulu40nej8


    printf("\n");
}
