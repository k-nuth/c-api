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

#include <stdio.h>

#include <bitprim/nodecint/executor_c.h>
#include <bitprim/nodecint/payment_address.h>
#include <bitprim/nodecint/history_compact_list.h>
#include <bitprim/nodecint/history_compact.h>
#include <bitcoin/bitcoin/message/transaction.hpp>


#include <iostream>
#include <chrono>
#include <thread>

void history_fetch_handler(int error, history_compact_list_t history_list) {
     printf("C callback (history_fetch_handler) called\n");

	 auto count = history_compact_list_count(history_list);
	 printf("history_fetch_handler count: %zu\n", count);

	 history_compact_list_destruct(history_list);
}

void last_height_fetch_handler(int error, size_t h) {
	printf("last_height_fetch_handler h: %zu\n", h);

	//if (h >= 1000) {

	//}
}

bool waiting = true;


libbitcoin::message::transaction const& tx_const_cpp2(transaction_t transaction) {
	return *static_cast<libbitcoin::message::transaction const*>(transaction);
}

int char2int(char input) {
	if (input >= '0' && input <= '9')
		return input - '0';
	if (input >= 'A' && input <= 'F')
		return input - 'A' + 10;
	if (input >= 'a' && input <= 'f')
		return input - 'a' + 10;
	throw std::invalid_argument("Invalid input string");
}

void hex2bin(const char* src, uint8_t* target) {
	while (*src && src[1]) {
		*(target++) = char2int(*src) * 16 + char2int(src[1]);
		src += 2;
	}
}

int main(int argc, char* argv[]) {
	using namespace std::chrono_literals;

    executor_t exec = executor_construct("/home/FERFER/exec/btc-mainnet.cfg", stdout, stderr);
	//executor_t exec = executor_construct("/home/fernando/exec/btc-mainnet.cfg", nullptr, nullptr);

    int res1 = executor_initchain(exec);

	int res2 = executor_run_wait(exec);

	size_t height;
	get_last_height(exec, &height);
	
	//while (height < 1000) {
	//	get_last_height(exec, &height);
	//}

	//std::string hash = "4a5e1e4baab89f3a32518a88c31bc87f618f76673e2cc77ab2127b7afdeda33b";
	//libbitcoin::hash_digest hash_bytes;
	//hex2bin(hash.c_str(), hash_bytes.data());
	//std::reverse(hash_bytes.begin(), hash_bytes.end());
	//transaction_t tx;

	//size_t index;

	////get_transaction(exec, (hash_t)hash.c_str(), false, &tx, &height, &index);
	//get_transaction(exec, (hash_t)hash_bytes.data(), false, &tx, &height, &index);

	//auto& txlib = tx_const_cpp2(tx);
	//auto data = txlib.to_data();

	//for (int i = 0; i < data.size(); ++i) {
	//	std::cout << std::hex << (int)data[i];
	//}


	std::string tx_hex_cpp = "0100000001b3807042c92f449bbf79b33ca59d7dfec7f4cc71096704a9c526dddf496ee0970100000069463044022039a36013301597daef41fbe593a02cc513d0b55527ec2df1050e2e8ff49c85c202204fcc407ce9b6f719ee7d009aeb8d8d21423f400a5b871394ca32e00c26b348dd2103c40cbd64c9c608df2c9730f49b0888c4db1c436e8b2b74aead6c6afbd10428c0ffffffff01905f0100000000001976a91418c0bd8d1818f1bf99cb1df2269c645318ef7b7388ac00000000";
	//std::string tx_hex_cpp = "1000100000000000000000000000000000000ffffffff4d4ffff01d14455468652054696d65732030332f4a616e2f32303039204368616e63656c6c6f72206f6e206272696e6b206f66207365636f6e64206261696c6f757420666f722062616e6b73ffffffff10f252a100043414678afdb0fe5548271967f1a67130b7105cd6a828e0399a67962e0ea1f61deb649f6bc3f4cef38c4f3554e51ec112de5c384df7bab8d578a4c702b6bf11d5fac0000";
	auto tx = hex_to_tx(tx_hex_cpp.c_str());

	validate_tx(exec, tx, nullptr);

	//executor_run(exec, [](int e) {
	//	waiting = false;
	//});

	//while (waiting) {
	//	std::this_thread::sleep_for(500ms);
	//	//std::cout << "..." << std::endl;
	//}

//    fetch_merkle_block_by_height(exec, 0, NULL);


	//fetch_last_height(exec, last_height_fetch_handler);


    //history_compact_t history;
    //point_kind_t xxx = history_compact_get_point_kind(history);

	//std::this_thread::sleep_for(5s);

	while (true) {
		fetch_last_height(exec, last_height_fetch_handler);
		std::this_thread::sleep_for(500ms);
		//std::cout << "..." << std::endl;
	}

    executor_destruct(exec);

    return 0;
}
