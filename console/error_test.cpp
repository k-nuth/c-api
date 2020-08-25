// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <cstdio>

#include <algorithm>
#include <chrono>
#include <stdexcept>
#include <thread>

#include <kth/capi.h>
#include <kth/infrastructure.hpp>
#include <kth/capi/helpers.hpp>

inline
int char2int(char input) {
    if (input >= '0' && input <= '9') {
        return input - '0';
    }
    if (input >= 'A' && input <= 'F') {
        return input - 'A' + 10;
    }
    if (input >= 'a' && input <= 'f') {
        return input - 'a' + 10;
    }
    throw std::invalid_argument("Invalid input string");
}

inline
void hex2bin(const char* src, uint8_t* target) {
    while ((*src != 0) && (src[1] != 0)) {
        *(target++) = char2int(*src) * 16 + char2int(src[1]);
        src += 2;
    }
}

inline
kth_hash_t str_to_hash(const char* str) {
	// std::string hash = "0000000071966c2b1d065fd446b1e485b2c9d9594acd2007ccbd5441cfc89444";
	kth::hash_digest hash_bytes;
	hex2bin(str, hash_bytes.data());
	std::reverse(hash_bytes.begin(), hash_bytes.end());
    auto res = kth::to_hash_t(hash_bytes);
    return res;
}

void WaitUntilBlock(kth_chain_t chain, uint64_t desiredHeight) {
    kth_error_code_t error;
    kth_size_t height = 0;

    while (error == 0 && height < desiredHeight) {
        printf("---> height: %d desiredHeight: %d", height, desiredHeight);
        auto error = kth_chain_get_last_height(chain, &height);

        if (height < desiredHeight) {
            std::this_thread::sleep_for(std::chrono::milliseconds(10000));
        }
    }
    printf("---> height: %d desiredHeight: %d", height, desiredHeight);
}

void DoSomething(kth_node_t node) {
    int FIRST_NON_COINBASE_BLOCK_HEIGHT = 170;

    int res = kth_node_init_and_run_wait(node);
    if (res != kth_ec_success) {
        printf("kth_node_init_and_run_wait failed: error code: %d", res);
        return;
    }

    auto chain = kth_node_get_chain(node);
    WaitUntilBlock(chain, FIRST_NON_COINBASE_BLOCK_HEIGHT);

    auto hash = str_to_hash("f4184fc596403b9d638783cf57adfe4c75c605f6356fbc91338530e9831e9e16");
    kth_transaction_t out_transaction;
    kth_size_t out_height;
    kth_size_t out_index;
    res = kth_chain_get_transaction(chain, hash, true, &out_transaction, &out_height, &out_index);

    // kth_size_t sigops = kth_chain_transaction_signature_operations(out_transaction);
    kth_size_t sigops = kth_chain_transaction_signature_operations_bip16_active(out_transaction, true);
    printf("sigops: %d", sigops);

    // string txHashHexStr = "f4184fc596403b9d638783cf57adfe4c75c605f6356fbc91338530e9831e9e16";
    // byte[] hash = Binary.HexStringToByteArray(txHashHexStr);

    // var ret = await node.Chain.GetTransactionAsync(hash, true);
    // var x1 = ret.Result;
    // var x2 = ret.Result.Tx;
    // var x3 = ret.Result.Tx.SignatureOperations;

    // Console.WriteLine($"ret.Result.Tx.SignatureOperations: {ret.Result.Tx.SignatureOperations}");
} 



int main(int argc, char* argv[]) {
    // string configFile = "/home/fernando/dev/kth/cs-api/tests/bch/config/invalid.cfg";
    kth_node_t node = kth_node_construct("/home/fernando/dev/kth/cs-api/console/node.cfg", stdout, stderr);
    printf("Is config file valid: %d\n", kth_node_load_config_valid(node));


    DoSomething(node);
    printf("Shutting down node...");

    kth_node_destruct(node);

    return 0;
}


// -----------------------------------------------------------
// #include <stdio.h>

// #include <kth/capi/node.h>


// int main(int argc, char* argv[]) {

//     // kth_node_t node = kth_node_construct("/home/fernando/exec/btc-mainnet.cfg", stdout, stderr);
//     // kth_node_t node = kth_node_construct("/home/fernando/dev/kth/cs-api/tests/bch/config/invalid.cfg", stdout, stderr);
//     kth_node_t node = kth_node_construct("/home/fernando/dev/kth/cs-api/tests/bch/config/invalid.cfg", NULL, NULL);

//     printf("Is config file valid: %d\n", kth_node_load_config_valid(node));

//     int res1 = kth_node_initchain(node);
//     // int res2 = kth_node_run_wait(node);

//     kth_node_destruct(node);

//     return 0;
// }
