// Copyright (c) 2016-2020 Knuth Project developers.
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
        // auto xxx = *data;
        // int ixxx = xxx;

        // printf("%02x\n", xxx);
        // fflush(stdout);
        // printf("%02x\n", ixxx);
        // fflush(stdout);

        // printf("%02x", (int)*data);
        printf("%02x", *data);
        ++data;
        --n;
    }
    printf("\n");
}

int main(int argc, char* argv[]) {

    auto wl = kth_core_string_list_construct();

   // -----------------------------------------------------------------------------------------
   // Copay Fernando
   // genre salon chuckle oval finish loan crystal delay mixed erupt clown horn
   // c8e30a6df5fb13257d5044e0c2a9546681f20c7318c676e5cb616c98df20f4d83f119fd03ef2061511008e022c8c28450ff1fa2d3a83df04818313a7b9996023
   // 15LdCdQoXio4tYAtPd8v2cvdrzrtoHYyaW

    kth_core_string_list_push_back(wl, "genre");
    kth_core_string_list_push_back(wl, "salon");
    kth_core_string_list_push_back(wl, "chuckle");
    kth_core_string_list_push_back(wl, "oval");
    kth_core_string_list_push_back(wl, "finish");
    kth_core_string_list_push_back(wl, "loan");
    kth_core_string_list_push_back(wl, "crystal");
    kth_core_string_list_push_back(wl, "delay");
    kth_core_string_list_push_back(wl, "mixed");
    kth_core_string_list_push_back(wl, "erupt");
    kth_core_string_list_push_back(wl, "clown");
    kth_core_string_list_push_back(wl, "horn");

    kth_longhash_t seed;
    kth_wallet_mnemonics_to_seed_out(wl, &seed);
    // print_hex((char const*)seed.hash, 64);
    print_hex(seed.hash, 64);

    auto hd_priv = kth_wallet_hd_new(seed, 76066276);
    
    kth_ec_secret_t ec_priv;
    kth_wallet_hd_private_to_ec_out(hd_priv, &ec_priv);


   auto pubk = kth_wallet_ec_to_public(ec_priv, 1);
   auto addr = kth_wallet_ec_to_address(pubk, 0);
   auto* addr_str = kth_wallet_payment_address_encoded(addr);

   // // seed_hex = seed[::-1].encode('hex')
   // seed_hex = seed.encode('hex')

   // print(seed_hex)

   // // print(len(seed))

   // // for x in seed:
   // //     print(int(x))

   // // print(pubk)
   // // print(addr)
   // print(addr_str)

   printf("addr_str: %s\n", addr_str);

   kth_core_string_list_destruct(wl);

//    remind differ angry glove almost swear era student sorry beauty odor habit
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
