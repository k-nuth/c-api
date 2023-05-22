// Copyright (c) 2016-2023 Knuth Project developers.
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

// #include <kth/domain/message/transaction.hpp>

// #include <kth/infrastructure/utility/binary.hpp>
// #include <kth/infrastructure/wallet/hd_private.hpp>

void print_hex(uint8_t const* data, size_t n) {
    while (n != 0) {
        printf("%02x", *data);
        ++data;
        --n;
    }
    printf("\n");
}

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

    // hd_private const m(seed, hd_private::mainnet);
    // auto const m44h = m.derive_private(44 + KTH_HD_FIRST_HARDENED_KEY);
    // auto const m44h145h = m44h.derive_private(145 + KTH_HD_FIRST_HARDENED_KEY);
    // auto const m44h145h0h = m44h145h.derive_private(0 + KTH_HD_FIRST_HARDENED_KEY);
    // auto const m44h145h0h0 = m44h145h0h.derive_private(0);

    kth_hd_private_t m = kth_wallet_hd_private_construct_with_seed(seed_c.hash, sizeof(seed_c), KTH_WALLET_HD_PRIVATE_MAINNET);
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
        // auto key = m44h145h0h0.derive_private(i);
        // auto secret = key.secret();

        kth_hd_private_t key = kth_wallet_hd_private_derive_private(m44h145h0h0, i);
        kth_ec_secret_t secret = kth_wallet_hd_private_secret(key);
        kth::ec_compressed point;
        kth::secret_to_public(point, secret);

        kth_wallet_secret_to_public


        kth::domain::wallet::ec_public ecp(point);
        kth::domain::wallet::payment_address pa(ecp);

        // std::cout << pa.encoded() << std::endl;
        std::cout << pa.encoded_cashaddr(false) << std::endl;

        // // auto hd_priv = kth_wallet_hd_new(seed, 76066276);
        // kth_ec_secret_t ec_priv;
        // kth_wallet_hd_private_to_ec_out(key, &ec_priv);
        // auto pubk = kth_wallet_ec_to_public(ec_priv, 1);
        // auto addr = kth_wallet_ec_to_address(pubk, 0);
        // auto* addr_str = kth_wallet_payment_address_encoded(addr);

    }

    printf("\n");
}


    // auto const m44h0h = m44h.derive_private(0 + hd_first_hardened_key);
    // auto const m44h0h0h = m44h0h.derive_private(0 + hd_first_hardened_key);
    // auto const m44h0h0h0 = m44h0h0h.derive_private(0);
