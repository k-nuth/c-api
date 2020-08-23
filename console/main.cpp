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
#include <kth/capi/wallet/payment_address.h>
#include <kth/capi/wallet/wallet.h>
#include <kth/capi/wallet/word_list.h>
#include <kth/capi/wallet/payment_address_list.h>

#include <kth/domain/message/transaction.hpp>

#include <kth/infrastructure/utility/binary.hpp>
#include <kth/infrastructure/wallet/hd_private.hpp>


 void wait_until_block(kth_chain_t chain, size_t desired_height) {
     printf("wait_until_block - 1\n");

     uint64_t height;
     int error = kth_chain_get_last_height(chain, &height);
     //printf("wait_until_block; desired_height: %zd, error: %d, height: %zd\n", desired_height, error, height);
    
     while (error == 0 && height < desired_height) {
         error = kth_chain_get_last_height(chain, &height);
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


void print_hex(uint8_t const* data, size_t n) {
    while (n != 0) {
        printf("%2x", *data);
        ++data;
        --n;
    }
    printf("\n");
}

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


int main(int /*argc*/, char* /*argv*/[]) {
//    using namespace std::chrono_literals;

    // std::signal(SIGINT, handle_stop);
    // std::signal(SIGTERM, handle_stop);


    auto exec = kth_node_construct("/home/kth/dev/kth/github/k-nuth/insight/kth.insight/bcc-testnet.cfg", stdout, stderr);
    //auto exec = kth_node_construct("/home/FERFER/exec/btc-mainnet.cfg", stdout, stderr);
    // kth_node_t exec = kth_node_construct("/home/FERFER/exec/btc-mainnet.cfg", stdout, stderr);
    //kth_node_t exec = kth_node_construct("/home/fernando/exec/btc-mainnet.cfg", nullptr, nullptr);


    // printf("**-- 1\n");
    // int res1 = kth_node_initchain(exec);

    // if (res1 == 0) {
    //     printf("Error initializing files\n");
    //     kth_node_destruct(exec);
    //     return -1;
    // }

    printf("**-- 2aaaaaa\n");
    
    int res2 = kth_node_run_wait(exec);

    printf("**-- 3\n");
    if (res2 != 0) {
        printf("Error initializing files\n");
        kth_node_destruct(exec);
        return -1;
    }
    std::this_thread::sleep_for(std::chrono::seconds(10));
    printf("**-- 4\n");

    kth_chain_t chain = kth_node_get_chain(exec);
        
    wait_until_block(chain, 170);

    
	std::string hash = "0000000071966c2b1d065fd446b1e485b2c9d9594acd2007ccbd5441cfc89444";
	kth::hash_digest hash_bytes;
	hex2bin(hash.c_str(), hash_bytes.data());
	std::reverse(hash_bytes.begin(), hash_bytes.end());
    auto prevout_hash = kth::to_hash_t(hash_bytes);

    uint64_t out_h;
    auto res = kth_chain_get_block_height(chain, prevout_hash, &out_h);
    printf("res: %d\n", res);
    printf("out_h: %lu\n", out_h);

    printf("**-- 7\n");

    kth_payment_address_list_t addresses = kth_wallet_payment_address_list_construct_default();
    kth_payment_address_t addr1 = kth_wallet_payment_address_construct_from_string("bchtest:qq6g5362emyqppwx6kwpsl08xkgep7xwkyh9p68qsj");
    kth_payment_address_t addr2 = kth_wallet_payment_address_construct_from_string("bchtest:qqg2fwfzd4xeywf8h2zajqy77357gk0v7yvsvhd4xu");
    kth_wallet_payment_address_list_push_back(addresses, addr1);
    kth_wallet_payment_address_list_push_back(addresses, addr2);
    //Copies were pushed, so clean up
    kth_wallet_payment_address_destruct(addr1);
    kth_wallet_payment_address_destruct(addr2);
    kth_transaction_list_t txs = kth_chain_get_mempool_transactions_from_wallets(chain, addresses, 1);
    kth_wallet_payment_address_list_destruct(addresses);
    auto tx_count = kth_chain_transaction_list_count(txs);
    printf("tx_count: %lu\n", tx_count);

    kth_node_destruct(exec);

    printf("**-- 8\n");
    
    return 0;
}





// kth_transaction_t make_P2PKH_transaction(uint32_t version, uint32_t locktime, std::string const& addr, uint64_t satoshis, uint8_t* sig, size_t sig_n, uint8_t* pubk, size_t pubk_n, kth_hash_t prevout_hash, uint32_t prevout_index, uint32_t sequence) {
//     uint8_t locking_script_data[25];
//     locking_script_data[0]  = 0x76;   // DUP opcode
//     locking_script_data[1]  = 0xa9;   // HASH160 opcode
//     locking_script_data[2]  = 0x14;   // PubKHash size, 14 (base16) = 20 (base10)
//     locking_script_data[23] = 0x88;   // EQUALVERIFY opcode
//     locking_script_data[24] = 0xac;   // CHECKSIG opcode

//     auto address = kth_wallet_payment_address_construct_from_string(addr.c_str());
        
//     if (kth_wallet_payment_address_is_valid(address) == 0) {
//         std::cout << "Invalid payment address: " << addr << std::endl;
//     }

//     kth_shorthash_t addr_hash = kth_wallet_payment_address_hash(address);
//     std::copy_n(static_cast<uint8_t*>(addr_hash.hash), 20, static_cast<uint8_t*>(locking_script_data) + 3);
//     kth_wallet_payment_address_destruct(address);

//     //--------------------------------------------------------------------------------------------------------------
//     kth_script_t locking_script = kth_chain_script_construct(static_cast<uint8_t*>(locking_script_data), 25, 0 /*int bool prefix*/);

//     if (kth_chain_script_is_valid(locking_script) == 0) {
//         std::cout << "Invalid locking script\n";
//     }

//     //--------------------------------------------------------------------------------------------------------------
//     std::vector<uint8_t> unlocking_script_data(sig_n + pubk_n + 2);
//     unlocking_script_data[0] = sig_n;
//     std::copy_n(sig, sig_n, begin(unlocking_script_data) + 1);

//     unlocking_script_data[sig_n + 1] = pubk_n;
//     std::copy_n(pubk, pubk_n, begin(unlocking_script_data) + (sig_n + 2));
    
//     kth_script_t unlocking_script = kth_chain_script_construct(unlocking_script_data.data(), unlocking_script_data.size(), 0 /*int bool prefix*/);

//     if (kth_chain_script_is_valid(unlocking_script) == 0) {
//         std::cout << "Invalid unlocking script\n";
//     }

//     //--------------------------------------------------------------------------------------------------------------
//     kth_outputpoint_t previous_output = kth_chain_output_point_construct_from_hash_index(prevout_hash, prevout_index);
//     kth_input_t input = kth_chain_input_construct(previous_output, unlocking_script, sequence);
//     auto inputs = kth_chain_input_list_construct_default();
//     kth_chain_input_list_push_back(inputs, input);

//     //--------------------------------------------------------------------------------------------------------------
//     auto outputs = kth_chain_output_list_construct_default();
//     kth_output_t output = kth_chain_output_construct(satoshis, locking_script);
//     kth_chain_output_list_push_back(outputs, output);
//     //--------------------------------------------------------------------------------------------------------------

//     auto tx = kth_chain_transaction_construct(version, locktime, inputs, outputs);
//     return tx;
// }

// int main(int  /*argc*/, char*  /*argv*/[]) {

//     //Construye la TX de id: b7749347c9e5b2a38b19fb2ab5a390d04d3368f1113aeb565d5fcf72d0e6391e

//     kth_wallet_payment_address_set_cashaddr_prefix("bitcoincash");   //BCH mainnet
//     // kth_wallet_payment_address_set_cashaddr_prefix("bchtest");       //BCH testnet

//     std::string sig_str = "30440220420e56991b7729105fe427ac474224f2a4152aec97d6b5b1f4d275d4ca7a7a3b022032307c9596ca43a234f89a9f60a01364ad33e3cb62c1d76d212c8969e8593e6341";
//     std::vector<uint8_t> sig(sig_str.size() / 2);
// 	hex2bin(sig_str.c_str(), sig.data());

//     std::string pubk_str = "02c6511ed2576d789ddc8ae2c02515585773311b9f49b523a1a2f227e16d5a798a";
//     std::vector<uint8_t> pubk(pubk_str.size() / 2);
// 	hex2bin(pubk_str.c_str(), pubk.data());

//     std::string prevout_hash_str = "98a2c7b069d6aa414dc4138a45dcc9c804928338599a4df67d73d8e21e00622b";
// 	kth::hash_digest hash_bytes;
// 	hex2bin(prevout_hash_str.c_str(), hash_bytes.data());
// 	std::reverse(hash_bytes.begin(), hash_bytes.end());
//     auto prevout_hash = kth::to_hash_t(hash_bytes);


//     // bitcoincash:qprzrw2lsj85qdnw9qwrc6cjg7ypgcs7fq40e4v5wn
//     auto tx = make_P2PKH_transaction(
//                     1,
//                     533204,
//                     "bitcoincash:qp8etlc40l747y74my8teujlfr6frx644yxze0g8wh", 
//                     229973000,
//                     sig.data(), sig.size(), 
//                     pubk.data(), pubk.size(),
//                     prevout_hash, 0,
//                     0xfffffffe
//                     );

//     uint64_t tx_data_n;
//     uint8_t* tx_data = kth_chain_transaction_to_data(tx, 1 /*int bool wire*/, &tx_data_n);
//     std::cout << "-----------------------------------------------------------------------------\n";
//     print_hex(tx_data, tx_data_n);
//     std::cout << "-----------------------------------------------------------------------------\n";
//     free(tx_data);

//     kth_chain_transaction_destruct(tx);
//     return 0;
// }

//int main(int argc, char* argv[]) {
//    auto wl = word_list_construct();
//
//    // -----------------------------------------------------------------------------------------
//    // Copay Fernando
//    // genre salon chuckle oval finish loan crystal delay mixed erupt clown horn
//    // c8e30a6df5fb13257d5044e0c2a9546681f20c7318c676e5cb616c98df20f4d83f119fd03ef2061511008e022c8c28450ff1fa2d3a83df04818313a7b9996023
//    // 15LdCdQoXio4tYAtPd8v2cvdrzrtoHYyaW
//
//    word_list_add_word(wl, "genre");
//    word_list_add_word(wl, "salon");
//    word_list_add_word(wl, "chuckle");
//    word_list_add_word(wl, "oval");
//    word_list_add_word(wl, "finish");
//    word_list_add_word(wl, "loan");
//    word_list_add_word(wl, "crystal");
//    word_list_add_word(wl, "delay");
//    word_list_add_word(wl, "mixed");
//    word_list_add_word(wl, "erupt");
//    word_list_add_word(wl, "clown");
//    word_list_add_word(wl, "horn");
//
//
//    // -----------------------------------------------------------------------------------------
//    // car slab tail dirt wife custom front shield diet pear skull vapor gorilla token yard
//    // https://iancoleman.io/bip39/
//    // e0b6ebf43ebcaa428f59a1f9241019ba4c083a1c05d988677c8bf28ec6505ae07286515a9bb0bf98d836f582a94f29fc92bbe9a0a5805ce6dc4756a439ebd1d9
//
//    // word_list_add_word(wl, "car");
//    // word_list_add_word(wl, "slab");
//    // word_list_add_word(wl, "tail");
//    // word_list_add_word(wl, "dirt");
//    // word_list_add_word(wl, "wife");
//    // word_list_add_word(wl, "custom");
//    // word_list_add_word(wl, "front");
//    // word_list_add_word(wl, "shield");
//    // word_list_add_word(wl, "diet");
//    // word_list_add_word(wl, "pear");
//    // word_list_add_word(wl, "skull");
//    // word_list_add_word(wl, "vapor");
//    // word_list_add_word(wl, "gorilla");
//    // word_list_add_word(wl, "token");
//    // word_list_add_word(wl, "yard");
//    // -----------------------------------------------------------------------------------------
//
//
//    auto seed = kth_wallet_mnemonics_to_seed(wl);
//
//    // ec_priv = kth_wallet_ec_new(seed)
//
//    auto hd_priv = kth_wallet_hd_new(seed.hash, 64, 76066276);
//    // auto ec_priv = kth_wallet_hd_private_to_ec(hd_priv);
//
//
//    // pubk = kth.wallet_ec_to_public(ec_priv, 1)
//    // addr = kth.wallet_ec_to_address(pubk, 0)
//    // addr_str = kth.payment_address_encoded(addr)
//
//    // // seed_hex = seed[::-1].encode('hex')
//    // seed_hex = seed.encode('hex')
//
//    // print(seed_hex)
//
//    // // print(len(seed))
//
//    // // for x in seed:
//    // //     print(int(x))
//
//    // // print(pubk)
//    // // print(addr)
//    // print(addr_str)
//
//
//    word_list_destruct(wl);
//
//
//}

// ---------------------------------------------------------------------------------------------------------------------------

// // using namespace std::chrono_literals;

// bool waiting = true;


// // kth_chain_get_last_height()
// // int kth_chain_get_last_height(kth_chain_t chain, kth_size_t* height) {





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
//         int error = kth_chain_get_last_height(chain, &height);
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