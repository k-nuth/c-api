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
#include <kth/capi/wallet/wallet_manager.h>
#include <kth/capi/wallet/wallet_data.h>

void print_hex(uint8_t const* data, size_t n) {
    while (n != 0) {
        printf("%02x", *data);
        ++data;
        --n;
    }
    printf("\n");
}

int main(int argc, char* argv[]) {
    kth_wallet_data_t wallet_data;
    kth_error_code_t code = kth_wallet_create_wallet(
        "12345678",
        "",
        &wallet_data);

    printf("code: %d\n", code);
    // printf("wallet_data: %s\n", kth_wallet_wallet_data_encoded(wallet_data));

    kth_string_list_t mnemonics = kth_wallet_wallet_data_mnemonics(wallet_data);

    kth_size_t count = kth_core_string_list_count(mnemonics);
    printf("count: %d\n", count);

    for (kth_size_t i = 0; i < count; i++) {
        char const* mnemonic = kth_core_string_list_nth(mnemonics, i);
        printf("mnemonic: %s\n", mnemonic);
    }

    kth_encrypted_seed_t seed = kth_wallet_wallet_data_encrypted_seed(wallet_data);
    print_hex(seed.hash, KTH_BITCOIN_ENCRYPTED_SEED_SIZE);


    // -------------------------------------------------------------------------

    kth_longhash_t decrypted_seed;
    kth_error_code_t code2 = kth_wallet_decrypt_seed(
        "12345678",
        &seed,
        &decrypted_seed);

    printf("code2: %d\n", code2);
    print_hex(decrypted_seed.hash, KTH_BITCOIN_LONG_HASH_SIZE);
}
