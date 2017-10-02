/**
 * Copyright (c) 2017 Bitprim developers (see AUTHORS)
 *
 * This file is part of Bitprim.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <chrono>
#include <cstdio>
#include <iostream>
#include <thread>

#include <bitprim/nodecint/executor_c.h>
#include <bitprim/nodecint/helpers.hpp>

#include <bitprim/nodecint/chain/chain.h>
#include <bitprim/nodecint/chain/payment_address.h>
#include <bitprim/nodecint/chain/history_compact_list.h>
#include <bitprim/nodecint/chain/history_compact.h>
#include <bitprim/nodecint/chain/transaction.h>
#include <bitprim/nodecint/chain/input_list.h>
#include <bitprim/nodecint/chain/input.h>
#include <bitprim/nodecint/chain/output_list.h>
#include <bitprim/nodecint/chain/output.h>

#include <bitcoin/bitcoin/message/transaction.hpp>
#include <bitcoin/bitcoin/utility/binary.hpp>


using namespace std::chrono_literals;

bool waiting = true;


// chain_get_last_height()
// int chain_get_last_height(chain_t chain, uint64_t /*size_t*/* height) {

void wait_until_block(chain_t chain, size_t desired_height) {
    printf("wait_until_block - 1\n");

    uint64_t height;
    int error = chain_get_last_height(chain, &height);
    printf("wait_until_block; desired_height: %zd, error: %d, height: %zd\n", desired_height, error, height);
    
    while (error == 0 && height < desired_height) {
        error = chain_get_last_height(chain, &height);
        printf("wait_until_block; desired_height: %zd, error: %d, height: %zd\n", desired_height, error, height);
        
        if (height < desired_height) {
            printf("wait_until_block - 2\n");
            // time.sleep(1)
            std::this_thread::sleep_for(10s);
            printf("wait_until_block - 3\n");
        }
    }

    printf("wait_until_block - 4\n");
}

int main(int /*argc*/, char* /*argv*/[]) {
//    using namespace std::chrono_literals;

    executor_t exec = executor_construct("/home/FERFER/exec/btc-mainnet.cfg", stdout, stderr);
    //executor_t exec = executor_construct("/home/fernando/exec/btc-mainnet.cfg", nullptr, nullptr);

    int res1 = executor_initchain(exec);

    if (res1 == 0) {
        printf("Error initializing files\n");
        executor_destruct(exec);
        return -1;
    }

    int res2 = executor_run_wait(exec);

    if (res2 != 0) {
        printf("Error initializing files\n");
        executor_destruct(exec);
        return -1;
    }

    chain_t chain = executor_get_chain(exec);
        
    // fetch_last_height(exec, last_height_fetch_handler);
    wait_until_block(chain, 2000);

//    executor_get_raw_transaction(exec);
//    executor_getspentinfo(exec);
//    executor_getaddresstxids(exec);
//
//    executor_getaddressdeltas(exec);
//
//    executor_getblockhashes(exec, 1232768195, 1232758195);
//
//    executor_getaddressbalance(exec);
//    executor_getaddressutxos(exec);

    executor_destruct(exec);

    return 0;
}




// ------------------------------------------











// libbitcoin::message::transaction const& tx_const_cpp2(transaction_t transaction) {
// 	return *static_cast<libbitcoin::message::transaction const*>(transaction);
// }

// int main(int /*argc*/, char* /*argv*/[]) {
// //    using namespace std::chrono_literals;

//     executor_t exec = executor_construct("/home/FERFER/exec/btc-mainnet.cfg", stdout, stderr);
//     //executor_t exec = executor_construct("/home/fernando/exec/btc-mainnet.cfg", nullptr, nullptr);

//     int res1 = executor_initchain(exec);

//     if (res1 == 0) {
//         printf("Error initializing files\n");
//         executor_destruct(exec);
//         return -1;
//     }

//     int res2 = executor_run_wait(exec);

//     if (res2 != 0) {
//         printf("Error initializing files\n");
//         executor_destruct(exec);
//         return -1;
//     }


//     auto inputs = chain_input_list_construct_default();

//     auto input0 = chain_input_construct_default();
//     auto input1 = chain_input_construct_default();
//     auto input2 = chain_input_construct_default();
//     chain_input_list_push_back(inputs, input0);
//     chain_input_list_push_back(inputs, input1);
//     chain_input_list_push_back(inputs, input2);


//     auto outputs = chain_output_list_construct_default();
//     auto output0 = chain_output_construct_default();
//     auto output1 = chain_output_construct_default();
//     auto output2 = chain_output_construct_default();
//     chain_output_list_push_back(outputs, output0);
//     chain_output_list_push_back(outputs, output1);
//     chain_output_list_push_back(outputs, output2);


//     auto tr = chain_transaction_construct(1, 1, inputs, outputs);
//     chain_transaction_destruct(tr);

//     executor_destruct(exec);

//     return 0;
// }

// ------------------------------------------

//int main(int argc, char* argv[]) {
//	using namespace std::chrono_literals;
//
//    executor_t exec = executor_construct("/home/FERFER/exec/btc-mainnet.cfg", stdout, stderr);
//	//executor_t exec = executor_construct("/home/fernando/exec/btc-mainnet.cfg", nullptr, nullptr);
//
//    int res1 = executor_initchain(exec);
//
//	int res2 = executor_run_wait(exec);
//
//	size_t height;
//	get_last_height(exec, &height);
//
//	//while (height < 1000) {
//	//	get_last_height(exec, &height);
//	//}
//
//	//std::string hash = "4a5e1e4baab89f3a32518a88c31bc87f618f76673e2cc77ab2127b7afdeda33b";
//	//libbitcoin::hash_digest hash_bytes;
//	//hex2bin(hash.c_str(), hash_bytes.data());
//	//std::reverse(hash_bytes.begin(), hash_bytes.end());
//	//transaction_t tx;
//
//	//size_t index;
//
//	////get_transaction(exec, (hash_t)hash.c_str(), false, &tx, &height, &index);
//	//get_transaction(exec, (hash_t)hash_bytes.data(), false, &tx, &height, &index);
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
//	//executor_run(exec, [](int e) {
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
//    //history_compact_t history;
//    //point_kind_t xxx = history_compact_get_point_kind(history);
//
//	//std::this_thread::sleep_for(5s);
//
//	while (true) {
//		fetch_last_height(exec, last_height_fetch_handler);
//		std::this_thread::sleep_for(500ms);
//		//std::cout << "..." << std::endl;
//	}
//
//    executor_destruct(exec);
//
//    return 0;
//}
