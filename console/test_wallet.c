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

   // car slab tail dirt wife custom front shield diet pear skull vapor gorilla token yard
   // https://iancoleman.io/bip39/
   // e0b6ebf43ebcaa428f59a1f9241019ba4c083a1c05d988677c8bf28ec6505ae07286515a9bb0bf98d836f582a94f29fc92bbe9a0a5805ce6dc4756a439ebd1d9

    kth_string_list_t wl = kth_core_string_list_construct();
    kth_core_string_list_push_back(wl, "car");
    kth_core_string_list_push_back(wl, "slab");
    kth_core_string_list_push_back(wl, "tail");
    kth_core_string_list_push_back(wl, "dirt");
    kth_core_string_list_push_back(wl, "wife");
    kth_core_string_list_push_back(wl, "custom");
    kth_core_string_list_push_back(wl, "front");
    kth_core_string_list_push_back(wl, "shield");
    kth_core_string_list_push_back(wl, "diet");
    kth_core_string_list_push_back(wl, "pear");
    kth_core_string_list_push_back(wl, "skull");
    kth_core_string_list_push_back(wl, "vapor");
    kth_core_string_list_push_back(wl, "gorilla");
    kth_core_string_list_push_back(wl, "token");
    kth_core_string_list_push_back(wl, "yard");


    kth_longhash_t seed_c;
    kth_wallet_mnemonics_to_seed_out(wl, &seed_c);

    printf("seed: ");
    print_hex(seed_c.hash, sizeof(seed_c));

    kth_hd_private_t m = kth_wallet_hd_private_construct_seed(seed_c.hash, sizeof(seed_c), KTH_WALLET_HD_PRIVATE_MAINNET);
    kth_hd_private_t m44h = kth_wallet_hd_private_derive_private(m, 44 + KTH_HD_FIRST_HARDENED_KEY);
    kth_hd_private_t m44h145h = kth_wallet_hd_private_derive_private(m44h, 145 + KTH_HD_FIRST_HARDENED_KEY);
    kth_hd_private_t m44h145h0h = kth_wallet_hd_private_derive_private(m44h145h, 0 + KTH_HD_FIRST_HARDENED_KEY);
    kth_hd_private_t m44h145h0h0 = kth_wallet_hd_private_derive_private(m44h145h0h, 0);

    printf("BIP32 Root Key:                     %s\n", kth_wallet_hd_private_encoded(m));
    printf("BIP44 Account Extended Private Key: %s\n", kth_wallet_hd_private_encoded(m44h145h0h));
    printf("BIP44 Account Extended Public Key:  %s\n", kth_wallet_hd_public_encoded(kth_wallet_hd_private_to_public(m44h145h0h)));
    printf("BIP32 Account Extended Private Key: %s\n", kth_wallet_hd_private_encoded(m44h145h0h0));
    printf("BIP32 Account Extended Public Key:  %s\n", kth_wallet_hd_public_encoded(kth_wallet_hd_private_to_public(m44h145h0h0)));

    // print addresses
    for (size_t i = 0; i < 20; ++i) {
        kth_hd_private_t key = kth_wallet_hd_private_derive_private(m44h145h0h0, i);
        kth_ec_secret_t secret = kth_wallet_hd_private_secret(key);
        kth_ec_compressed_t point;
        kth_wallet_secret_to_public(&point, secret);
        kth_ec_public_t ecp = kth_wallet_ec_public_construct_from_point(&point, 1);
        kth_payment_address_t pa = kth_wallet_ec_public_to_payment_address(ecp, MAINNET_P2KH);
        printf("%s\n", kth_wallet_payment_address_encoded_cashaddr(pa, 0));
    }

    printf("\n");
}
