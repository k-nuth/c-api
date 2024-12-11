// Copyright (c) 2016-2024 Knuth Project developers.
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
#include <kth/capi/hash.h>
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


 void wait_until_block(kth_chain_t chain, size_t desired_height) {
     printf("wait_until_block - 1\n");

     uint64_t height;
     int error = kth_chain_sync_last_height(chain, &height);
     //printf("wait_until_block; desired_height: %zd, error: %d, height: %zd\n", desired_height, error, height);

     while (error == 0 && height < desired_height) {
         error = kth_chain_sync_last_height(chain, &height);
         //printf("wait_until_block; desired_height: %zd, error: %d, height: %zd\n", desired_height, error, height);

         if (height < desired_height) {
             //printf("wait_until_block - 2\n");
             // time.sleep(1)

             // std::this_thread::sleep_for(10s);
             std::this_thread::sleep_for(std::chrono::seconds(10));

             //printf("wait_until_block - 3\n");
         }
     }

     //printf("wait_until_block - 4\n");
 }

void print_hex(char const* data, size_t n) {
    while (n != 0) {
        printf("%2x", *data);
        ++data;
        --n;
    }
    printf("\n");
}


// int main(int /*argc*/, char* /*argv*/[]) {
//     kth_bool_t ok;
//     char* error_message;
//     // kth_settings settings = kth_config_settings_get_from_file("/home/fernando/dev/kth/cs-api/console/node.cfg", &ok, &error_message);
//     // kth_settings settings = kth_config_settings_get_from_file("/Users/fernando/dev/kth/cs-api/console/node.cfg", &ok, &error_message);
//     kth_settings settings = kth_config_settings_get_from_file("C:\\development\\kth\\cs-api\\console\\node_win.cfg", &ok, &error_message);
// }

int main(int /*argc*/, char* /*argv*/[]) {
//    using namespace std::chrono_literals;

    // std::signal(SIGINT, handle_stop);
    // std::signal(SIGTERM, handle_stop);

    kth_settings* settings;
    char* error_message;
    kth_bool_t ok = kth_config_settings_get_from_file("/home/fernando/kth-exec/kth-bch-mainnet-pruned.cfg", &settings, &error_message);

    if ( ! ok) {
        printf("error: %s", error_message);
        return -1;
    }

    // auto node = kth_node_construct_fd(settings, 0, 0);
    // auto node = kth_node_construct_fd(settings, -1, -1);
    auto node = kth_node_construct(settings, 1);


    kth_chain_t chain = kth_node_get_chain(node);

    kth_size_t height;
    auto res = kth_chain_sync_last_height(chain, &height);


	// // std::string hash = "0000000071966c2b1d065fd446b1e485b2c9d9594acd2007ccbd5441cfc89444";
	// // // kth::hash_digest hash_bytes;
	// // // hex2bin(hash.c_str(), hash_bytes.data());
	// // // std::reverse(hash_bytes.begin(), hash_bytes.end());
    // // // auto prevout_hash = kth::to_hash_t(hash_bytes);

    // // auto prevout_hash = kth_str_to_hash(hash.c_str());


    // // uint64_t out_h;
    // // auto res = kth_chain_get_block_height(chain, prevout_hash, &out_h);
    // // printf("res: %d\n", res);
    // // printf("out_h: %lu\n", out_h);

    // // printf("**-- 7\n");

    // // kth_payment_address_list_t addresses = kth_wallet_payment_address_list_construct_default();
    // // kth_payment_address_t addr1 = kth_wallet_payment_address_construct_from_string("bchtest:qq6g5362emyqppwx6kwpsl08xkgep7xwkyh9p68qsj");
    // // kth_payment_address_t addr2 = kth_wallet_payment_address_construct_from_string("bchtest:qqg2fwfzd4xeywf8h2zajqy77357gk0v7yvsvhd4xu");
    // // kth_wallet_payment_address_list_push_back(addresses, addr1);
    // // kth_wallet_payment_address_list_push_back(addresses, addr2);
    // // //Copies were pushed, so clean up
    // // kth_wallet_payment_address_destruct(addr1);
    // // kth_wallet_payment_address_destruct(addr2);
    // // kth_transaction_list_t txs = kth_chain_get_mempool_transactions_from_wallets(chain, addresses, 1);
    // // kth_wallet_payment_address_list_destruct(addresses);
    // // auto tx_count = kth_chain_transaction_list_count(txs);
    // // printf("tx_count: %lu\n", tx_count);
    // // printf("**-- 1\n");

    // // int res1 = kth_node_initchain(exec);
    // // if (res1 == 0) {
    // //     printf("Error initializing files\n");
    // //     kth_node_destruct(exec);
    // //     return -1;
    // // }

    // // printf("**-- 2aaaaaa\n");

    // // int res2 = kth_node_run_wait(exec);
    // int res2 = kth_node_init_and_run_wait(exec);

    // printf("**-- 3\n");
    // if (res2 != 0) {
    //     printf("Error initializing files\n");
    //     kth_node_destruct(exec);
    //     return -1;
    // }
    // std::this_thread::sleep_for(std::chrono::seconds(10));
    // printf("**-- 4\n");

    // kth_chain_t chain = kth_node_get_chain(exec);

    // wait_until_block(chain, 170);


	// // std::string hash = "0000000071966c2b1d065fd446b1e485b2c9d9594acd2007ccbd5441cfc89444";
	// // kth::hash_digest hash_bytes;
	// // hex2bin(hash.c_str(), hash_bytes.data());
	// // std::reverse(hash_bytes.begin(), hash_bytes.end());
    // // auto prevout_hash = kth::to_hash_t(hash_bytes);

    // // uint64_t out_h;
    // // auto res = kth_chain_sync_block_height(chain, prevout_hash, &out_h);
    // // printf("res: %d\n", res);
    // // printf("out_h: %lu\n", out_h);

    // // printf("**-- 7\n");

    // // kth_payment_address_list_t addresses = kth_wallet_payment_address_list_construct_default();
    // // kth_payment_address_t addr1 = kth_wallet_payment_address_construct_from_string("bchtest:qq6g5362emyqppwx6kwpsl08xkgep7xwkyh9p68qsj");
    // // kth_payment_address_t addr2 = kth_wallet_payment_address_construct_from_string("bchtest:qqg2fwfzd4xeywf8h2zajqy77357gk0v7yvsvhd4xu");
    // // kth_wallet_payment_address_list_push_back(addresses, addr1);
    // // kth_wallet_payment_address_list_push_back(addresses, addr2);
    // // //Copies were pushed, so clean up
    // // kth_wallet_payment_address_destruct(addr1);
    // // kth_wallet_payment_address_destruct(addr2);
    // // kth_transaction_list_t txs = kth_chain_sync_mempool_transactions_from_wallets(chain, addresses, 1);
    // // kth_wallet_payment_address_list_destruct(addresses);
    // // auto tx_count = kth_chain_transaction_list_count(txs);
    // // printf("tx_count: %lu\n", tx_count);

    // kth_config_settings_destruct(settings);
    // kth_node_destruct(exec);

    // printf("**-- 8\n");

    return 0;
}



// // kth_chain_sync_last_height()
// // int kth_chain_sync_last_height(kth_chain_t chain, kth_size_t* height) {





// kth_node_t exec;
// bool stopped = false;

// void handle_stop(int signal) {
//     std::cout << "handle_stop()\n";
//     // stop(kth::error::success);
//     //kth_node_stop(exec);
//     //kth_chain_t chain = kth_node_get_chain(exec);
//     //chain_unsubscribe(chain);
//     //stopped = true;
//     kth_node_stop(exec);
// }

// int xxx = 0;

// int kth_chain_subscribe_blockchain_handler(kth_node_t exec, kth_chain_t chain, void* ctx, int error, uint64_t fork_height, kth_block_list_t blocks_incoming, kth_block_list_t blocks_replaced) {
//     //printf("chain_subscribe_blockchain_handler error: %d\n", error);

//     if (kth_node_stopped(exec) == 1 || error == 1) {
//         printf("chain_subscribe_blockchain_handler -- stopping -- error: %d\n", error);
//         return 0;
//     }

//     //++xxx;

//     //if (xxx >= 3000) {
//     //    int s = kth_node_stopped(exec);
//     //    std::cout << s << std::endl;

//     //    //kth_node_stop(exec);
//     //    //kth_node_close(exec);

//     //    s = kth_node_stopped(exec);
//     //    std::cout << s << std::endl;
//     //    kth_chain_unsubscribe(chain);
//     //}


// 	return 1;
// }

// int main(int /*argc*/, char* /*argv*/[]) {
// //    using namespace std::chrono_literals;

//     std::signal(SIGINT, handle_stop);
//     std::signal(SIGTERM, handle_stop);


//     exec = kth_node_construct("/home/FERFER/exec/btc-mainnet.cfg", stdout, stderr);
//     // kth_node_t exec = kth_node_construct("/home/FERFER/exec/btc-mainnet.cfg", stdout, stderr);
//     //kth_node_t exec = kth_node_construct("/home/fernando/exec/btc-mainnet.cfg", nullptr, nullptr);


//     printf("**-- 1\n");
//     int res1 = kth_node_initchain(exec);

//     if (res1 == 0) {
//         printf("Error initializing files\n");
//         kth_node_destruct(exec);
//         return -1;
//     }

//     printf("**-- 2\n");

//     int res2 = kth_node_run_wait(exec);

//     if (res2 != 0) {
//         printf("Error initializing files\n");
//         kth_node_destruct(exec);
//         return -1;
//     }
//     std::this_thread::sleep_for(std::chrono::seconds(10));

//     printf("**-- 3\n");

//     kth_chain_t chain = kth_node_get_chain(exec);

//     // fetch_last_height(exec, last_height_fetch_handler);
//     // wait_until_block(chain, 170);


//     printf("**-- 4\n");

//     kth_chain_subscribe_blockchain(exec, chain, nullptr, kth_chain_subscribe_blockchain_handler);

//     printf("**-- 5\n");

//     // while ( ! kth_node_stopped(exec) ) {
//     //while ( ! stopped ) {
//     while (kth_node_stopped(exec) == 0) {
//         printf("**-- 6\n");

//         uint64_t height;
//         int error = kth_chain_sync_last_height(chain, &height);
//         printf("error: %d, height: %zd\n", error, height);

//         if (height >= 3000) {
//             int s = kth_node_stopped(exec);
//             std::cout << s << std::endl;

//             kth_node_stop(exec);
//             //kth_node_close(exec);

//             s = kth_node_stopped(exec);
//             std::cout << s << std::endl;
//         }

//         std::this_thread::sleep_for(std::chrono::seconds(10));
//     }

//     printf("**-- 7\n");

//     kth_node_destruct(exec);

//     printf("**-- 8\n");

//     return 0;
// }




// ---------------------------------------------------------------------------------------------------------------------------












// kth::domain::message::transaction const& tx_const_cpp2(kth_transaction_t transaction) {
// 	return *static_cast<kth::domain::message::transaction const*>(transaction);
// }

// int main(int /*argc*/, char* /*argv*/[]) {
// //    using namespace std::chrono_literals;

//     kth_node_t exec = kth_node_construct("/home/FERFER/exec/btc-mainnet.cfg", stdout, stderr);
//     //kth_node_t exec = kth_node_construct("/home/fernando/exec/btc-mainnet.cfg", nullptr, nullptr);

//     int res1 = kth_node_initchain(exec);

//     if (res1 == 0) {
//         printf("Error initializing files\n");
//         kth_node_destruct(exec);
//         return -1;
//     }

//     int res2 = kth_node_run_wait(exec);

//     if (res2 != 0) {
//         printf("Error initializing files\n");
//         kth_node_destruct(exec);
//         return -1;
//     }


//     auto inputs = kth_chain_input_list_construct_default();

//     auto input0 = kth_chain_input_construct_default();
//     auto input1 = kth_chain_input_construct_default();
//     auto input2 = kth_chain_input_construct_default();
//     kth_chain_input_list_push_back(inputs, input0);
//     kth_chain_input_list_push_back(inputs, input1);
//     kth_chain_input_list_push_back(inputs, input2);


//     auto outputs = kth_chain_output_list_construct_default();
//     auto output0 = kth_chain_output_construct_default();
//     auto output1 = kth_chain_output_construct_default();
//     auto output2 = kth_chain_output_construct_default();
//     kth_chain_output_list_push_back(outputs, output0);
//     kth_chain_output_list_push_back(outputs, output1);
//     kth_chain_output_list_push_back(outputs, output2);


//     auto tr = kth_chain_transaction_construct(1, 1, inputs, outputs);
//     kth_chain_transaction_destruct(tr);

//     kth_node_destruct(exec);

//     return 0;
// }

// ------------------------------------------

//int main(int argc, char* argv[]) {
//	using namespace std::chrono_literals;
//
//    kth_node_t exec = kth_node_construct("/home/FERFER/exec/btc-mainnet.cfg", stdout, stderr);
//	//kth_node_t exec = kth_node_construct("/home/fernando/exec/btc-mainnet.cfg", nullptr, nullptr);
//
//    int res1 = kth_node_initchain(exec);
//
//	int res2 = kth_node_run_wait(exec);
//
//	size_t height;
//	get_last_height(exec, &height);
//
//	//while (height < 1000) {
//	//	get_last_height(exec, &height);
//	//}
//
//	//std::string hash = "4a5e1e4baab89f3a32518a88c31bc87f618f76673e2cc77ab2127b7afdeda33b";
//	//kth::hash_digest hash_bytes;
//	//hex2bin(hash.c_str(), hash_bytes.data());
//	//std::reverse(hash_bytes.begin(), hash_bytes.end());
//	// kth_transaction_t tx;
//
//	//size_t index;
//
//	////get_transaction(exec, (kth_hash_t)hash.c_str(), false, &tx, &height, &index);
//	//get_transaction(exec, (kth_hash_t)hash_bytes.data(), false, &tx, &height, &index);
//
//	//auto& txlib = tx_const_cpp2(tx);
//	//auto data = txlib.to_data();
//
//	//for (int i = 0; i < data.size(); ++i) {
//	//	std::cout << std::hex << (int)data[i];
//	//}
//
//
//	std::string tx_hex_cpp = "0100000001b3807042c92f449bbf79b33ca59d7dfec7f4cc71096704a9c526dddf496ee0970100000069463044022039a36013301597daef41fbe593a02cc513d0b55527ec2df1050e2e8ff49c85c202204fcc407ce9b6f719ee7d009aeb8d8d21423f400a5b871394ca32e00c26b348dd2103c40cbd64c9c608df2c9730f49b0888c4db1c436e8b2b74aead6c6afbd10428c0ffffffff01905f0100000000001976a91418c0bd8d1818f1bf99cb1df2269c645318ef7b7388ac00000000";
//	//std::string tx_hex_cpp = "1000100000000000000000000000000000000ffffffff4d4ffff01d14455468652054696d65732030332f4a616e2f32303039204368616e63656c6c6f72206f6e206272696e6b206f66207365636f6e64206261696c6f757420666f722062616e6b73ffffffff10f252a100043414678afdb0fe5548271967f1a67130b7105cd6a828e0399a67962e0ea1f61deb649f6bc3f4cef38c4f3554e51ec112de5c384df7bab8d578a4c702b6bf11d5fac0000";
//	auto tx = hex_to_tx(tx_hex_cpp.c_str());
//
//	validate_tx(exec, tx, nullptr);
//
//	//kth_node_run(exec, [](int e) {
//	//	waiting = false;
//	//});
//
//	//while (waiting) {
//	//	std::this_thread::sleep_for(500ms);
//	//	//std::cout << "..." << std::endl;
//	//}
//
////    fetch_merkle_block_by_height(exec, 0, NULL);
//
//
//	//fetch_last_height(exec, last_height_fetch_handler);
//
//
//    //kth_history_compact_t history;
//    //kth_point_kind_t xxx = history_compact_get_point_kind(history);
//
//	//std::this_thread::sleep_for(5s);
//
//	while (true) {
//		fetch_last_height(exec, last_height_fetch_handler);
//		std::this_thread::sleep_for(500ms);
//		//std::cout << "..." << std::endl;
//	}
//
//    kth_node_destruct(exec);
//
//    return 0;
//}



// ------------------------------------------



/*int main(int argc, char* argv[]) {

    printf("hola -*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-\n");

    kth_node_t exec = kth_node_construct("c:\\blockchain\\bcc-testnet_insight\\kth-node-bcc-testnet.cfg", stdout, stderr);

    int config_valid = kth_node_load_config_valid(exec);

    printf("config valid result %i",config_valid);

    kth_node_destruct(exec);

    return 0;
}*/

/*int main(int argc, char* argv[]) {

    printf("hola -*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-\n");

    kth_node_t exec = kth_node_construct("c:\\blockchain\\bcc-testnet_insight\\kth-node-bcc-testnet.cfg", stdout, stderr);


    int res1 = kth_node_initchain(exec);
    int res2 = kth_node_run_wait(exec);

    kth_chain_t chain = kth_node_get_chain(exec);

    wait_until_block(chain, 170);



    std::string raw = "0200000001ffecbd2b832ea847a7da905a40d5abaff8323cc18ff3121532f6fe781ce79f6e000000008b483045022100a26515b4bb5f3eb0259c0cc0806b4d8096f91a801ee9b15ced76f2537f7de94b02205becd631fe0ae232e4453f1b4a8a5375e4caec62e3971dbfe5a6d86b2538dcf64141044636673164f4b636d560cb4192cb07aa62054154f1a7a99a694b235f8fba56950b34e6ab55d58991470a13ca59330bc6339a2f72eb6f9204a64a1a538ddff4fbffffffff0290d00300000000001976a9144913233162944e9239637f998235d76e1601b1cf88ac80d1f008000000001976a914cc1d800e7f83edd96a0340a4e269b2956f636e3f88ac00000000";

    kth::data_chunk chunk;
    kth::decode_base16(chunk,raw);

    kth_transaction_t tx = kth_chain_transaction_factory_from_data(1,chunk.data(),chunk.size());


    auto ret = kth_chain_organize_transaction_sync(chain,tx);

    printf("organize result %i",ret);

    kth_node_destruct(exec);

    return 0;
}*/

// void fetch_txns_handler(kth_chain_t chain, void* ctx, error_code ec, kth_hash_list_t txs) {
//     int txs_count =  kth_chain_hash_list_count(txs);
//     printf("Txs count: %d\n", txs_count);
//     for(int i=0; i<txs_count; i++) {
//         kth_hash_t tx_hash = kth_chain_hash_list_nth(txs, i);
//         //print_hex(tx_hash.hash, 32);
//     }
//     kth_chain_hash_list_destruct(txs);
//     printf("Txs list destroyed\n");
// }

// int main(int argc, char* argv[]) {
//     printf("fetch_txns test -*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-\n");

//     kth_node_t exec = kth_node_construct("", stdout, stderr);
//     int res1 = kth_node_initchain(exec);
//     int res2 = kth_node_run_wait(exec);

//     kth_chain_t chain = kth_node_get_chain(exec);

//     wait_until_block(chain, 170);

//     std::string address_str = "bitcoincash:qqgekzvw96vq5g57zwdfa5q6g609rrn0ycp33uc325";
//     auto address = kth_wallet_payment_address_construct_from_string(address_str.c_str());
//     kth_chain_fetch_confirmed_transactions(chain, nullptr, address, INT_MAX, 0, fetch_txns_handler);

//     std::this_thread::sleep_for(std::chrono::milliseconds(10000));

//     printf("Shutting down node... -*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-\n");
//     kth_node_destruct(exec);
//     printf("fetch_txns test EXITED OK -*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-\n");
//     return 0;
// }