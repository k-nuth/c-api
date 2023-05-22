// Copyright (c) 2016-2023 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <chrono>
#include <csignal>
#include <cstdio>
#include <iostream>
#include <thread>

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
#include <kth/capi/helpers.hpp>
#include <kth/capi/string_list.h>
#include <kth/capi/wallet/payment_address.h>
#include <kth/capi/wallet/wallet.h>
#include <kth/capi/wallet/payment_address_list.h>

#include <kth/domain/message/transaction.hpp>

#include <kth/infrastructure/utility/binary.hpp>
#include <kth/infrastructure/wallet/hd_private.hpp>

void print_hex(uint8_t const* data, size_t n) {
    while (n != 0) {
        printf("%02x", *data);
        ++data;
        --n;
    }
    printf("\n");
}

inline
kth::long_hash longhash_to_cpp(uint8_t const* x) {
    kth::long_hash ret;
    std::copy_n(x, ret.size(), std::begin(ret));
    return ret;
}

int main(int argc, char* argv[]) {
    using kth::infrastructure::wallet::hd_private;
    using kth::infrastructure::wallet::hd_first_hardened_key;

   // car slab tail dirt wife custom front shield diet pear skull vapor gorilla token yard
   // https://iancoleman.io/bip39/
   // e0b6ebf43ebcaa428f59a1f9241019ba4c083a1c05d988677c8bf28ec6505ae07286515a9bb0bf98d836f582a94f29fc92bbe9a0a5805ce6dc4756a439ebd1d9

    auto wl = kth_core_string_list_construct();
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
    auto seed_hash = longhash_to_cpp(seed_c.hash);
    kth::data_chunk seed(std::begin(seed_hash), std::end(seed_hash));

    std::cout << "seed: ";
    print_hex(seed.data(), seed.size());

    hd_private const m(seed, hd_private::mainnet);
    auto const m44h = m.derive_private(44 + hd_first_hardened_key);
    // auto const m44h0h = m44h.derive_private(0 + hd_first_hardened_key);
    // auto const m44h0h0h = m44h0h.derive_private(0 + hd_first_hardened_key);
    // auto const m44h0h0h0 = m44h0h0h.derive_private(0);
    auto const m44h145h = m44h.derive_private(145 + hd_first_hardened_key);
    auto const m44h145h0h = m44h145h.derive_private(0 + hd_first_hardened_key);
    auto const m44h145h0h0 = m44h145h0h.derive_private(0);

    std::cout << "BIP32 Root Key:                      " << m.encoded() << std::endl;
    std::cout << "BIP44 Account Extended Private Key: " << m44h145h0h.encoded() << std::endl;
    std::cout << "BIP44 Account Extended Public Key:  " << m44h145h0h.to_public().encoded() << std::endl;

    std::cout << "BIP32 Account Extended Private Key: " << m44h145h0h0.encoded() << std::endl;
    std::cout << "BIP32 Account Extended Public Key:  " << m44h145h0h0.to_public().encoded() << std::endl;

    // print addresses
    // auto key = m44h145h0h0;
    for (size_t i = 0; i < 20; ++i) {
        auto key = m44h145h0h0.derive_private(i);

        std::cout << "i: " << i << " - Private key: " << key.encoded() << std::endl;
        std::cout << "i: " << i << " - Public key: " << key.to_public().encoded() << std::endl;

        auto secret = key.secret();


        kth::ec_compressed point;
        kth::secret_to_public(point, secret);

        std::cout << "i: " << i << " - secret: ";
        print_hex(secret.data(), secret.size());
        std::cout << "i: " << i << " - point: ";
        print_hex(point.data(), point.size());

        kth::domain::wallet::ec_public ecp(point);

        std::cout << "i: " << i << " - ecp: " << ecp.encoded() << std::endl;

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


    std::cout << std::endl;


    // auto const m0h = m.derive_private(hd_first_hardened_key);
    // auto const m0h1 = m0h.derive_private(1);
    // auto const m0h12h = m0h1.derive_private(2 + hd_first_hardened_key);
    // auto const m0h12h2 = m0h12h.derive_private(2);
    // auto const m0h12h2x = m0h12h2.derive_private(1000000000);

    // REQUIRE(m.encoded() == "xprv9s21ZrQH143K3QTDL4LXw2F7HEK3wJUD2nW2nRk4stbPy6cq3jPPqjiChkVvvNKmPGJxWUtg6LnF5kejMRNNU3TGtRBeJgk33yuGBxrMPHi");
    // REQUIRE(m0h.encoded() == "xprv9uHRZZhk6KAJC1avXpDAp4MDc3sQKNxDiPvvkX8Br5ngLNv1TxvUxt4cV1rGL5hj6KCesnDYUhd7oWgT11eZG7XnxHrnYeSvkzY7d2bhkJ7");
    // REQUIRE(m0h1.encoded() == "xprv9wTYmMFdV23N2TdNG573QoEsfRrWKQgWeibmLntzniatZvR9BmLnvSxqu53Kw1UmYPxLgboyZQaXwTCg8MSY3H2EU4pWcQDnRnrVA1xe8fs");
    // REQUIRE(m0h12h.encoded() == "xprv9z4pot5VBttmtdRTWfWQmoH1taj2axGVzFqSb8C9xaxKymcFzXBDptWmT7FwuEzG3ryjH4ktypQSAewRiNMjANTtpgP4mLTj34bhnZX7UiM");
    // REQUIRE(m0h12h2.encoded() == "xprvA2JDeKCSNNZky6uBCviVfJSKyQ1mDYahRjijr5idH2WwLsEd4Hsb2Tyh8RfQMuPh7f7RtyzTtdrbdqqsunu5Mm3wDvUAKRHSC34sJ7in334");
    // REQUIRE(m0h12h2x.encoded() == "xprvA41z7zogVVwxVSgdKUHDy1SKmdb533PjDz7J6N6mV6uS3ze1ai8FHa8kmHScGpWmj4WggLyQjgPie1rFSruoUihUZREPSL39UNdE3BBDu76");


//     auto wl = kth_core_string_list_construct();

//    // -----------------------------------------------------------------------------------------
//    // Copay Fernando
//    // genre salon chuckle oval finish loan crystal delay mixed erupt clown horn
//    // c8e30a6df5fb13257d5044e0c2a9546681f20c7318c676e5cb616c98df20f4d83f119fd03ef2061511008e022c8c28450ff1fa2d3a83df04818313a7b9996023
//    // 15LdCdQoXio4tYAtPd8v2cvdrzrtoHYyaW

//     kth_core_string_list_push_back(wl, "genre");
//     kth_core_string_list_push_back(wl, "salon");
//     kth_core_string_list_push_back(wl, "chuckle");
//     kth_core_string_list_push_back(wl, "oval");
//     kth_core_string_list_push_back(wl, "finish");
//     kth_core_string_list_push_back(wl, "loan");
//     kth_core_string_list_push_back(wl, "crystal");
//     kth_core_string_list_push_back(wl, "delay");
//     kth_core_string_list_push_back(wl, "mixed");
//     kth_core_string_list_push_back(wl, "erupt");
//     kth_core_string_list_push_back(wl, "clown");
//     kth_core_string_list_push_back(wl, "horn");

//     kth_longhash_t seed;
//     kth_wallet_mnemonics_to_seed_out(wl, &seed);
//     // print_hex((char const*)seed.hash, 64);
//     print_hex(seed.hash, 64);

//     auto hd_priv = kth_wallet_hd_new(seed, 76066276);

//     kth_ec_secret_t ec_priv;
//     kth_wallet_hd_private_to_ec_out(hd_priv, &ec_priv);


//    auto pubk = kth_wallet_ec_to_public(ec_priv, 1);
//    auto addr = kth_wallet_ec_to_address(pubk, 0);
//    auto* addr_str = kth_wallet_payment_address_encoded(addr);

//    // // seed_hex = seed[::-1].encode('hex')
//    // seed_hex = seed.encode('hex')

//    // print(seed_hex)

//    // // print(len(seed))

//    // // for x in seed:
//    // //     print(int(x))

//    // // print(pubk)
//    // // print(addr)
//    // print(addr_str)

//    printf("addr_str: %s\n", addr_str);

//    kth_core_string_list_destruct(wl);

// //    remind differ angry glove almost swear era student sorry beauty odor habit
}


   // -----------------------------------------------------------------------------------------
   // car slab tail dirt wife custom front shield diet pear skull vapor gorilla token yard
   // https://iancoleman.io/bip39/
   // e0b6ebf43ebcaa428f59a1f9241019ba4c083a1c05d988677c8bf28ec6505ae07286515a9bb0bf98d836f582a94f29fc92bbe9a0a5805ce6dc4756a439ebd1d9

   // kth_core_string_list_push_back(wl, "car");
   // kth_core_string_list_push_back(wl, "slab");
   // kth_core_string_list_push_back(wl, "tail");
   // kth_core_string_list_push_back(wl, "dirt");
   // kth_core_string_list_push_back(wl, "wife");
   // kth_core_string_list_push_back(wl, "custom");
   // kth_core_string_list_push_back(wl, "front");
   // kth_core_string_list_push_back(wl, "shield");
   // kth_core_string_list_push_back(wl, "diet");
   // kth_core_string_list_push_back(wl, "pear");
   // kth_core_string_list_push_back(wl, "skull");
   // kth_core_string_list_push_back(wl, "vapor");
   // kth_core_string_list_push_back(wl, "gorilla");
   // kth_core_string_list_push_back(wl, "token");
   // kth_core_string_list_push_back(wl, "yard");
   // -----------------------------------------------------------------------------------------
