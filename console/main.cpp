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
#include <bitcoin/bitcoin/utility/binary.hpp>

#include <iostream>
#include <chrono>
#include <thread>

void stealth_fetch_handler(int error, stealth_compact_list_t history_list) {
     printf("C callback (stealth_fetch_handler) called\n");

	 //auto count = history_compact_list_count(history_list);
	 //printf("history_fetch_handler count: %d\n", count);

	 //history_compact_list_destruct(history_list);
}

/*binary_t = void**/

binary_t binary_construct(char* str) {
	std::string str_cpp(str);

	auto* ret = new libbitcoin::binary(str_cpp);
	return ret;
}

//binary(const std::string& bit_string);


int main(int argc, char* argv[]) {
	using namespace std::chrono_literals;

    //executor_t exec = executor_construct("/home/FERFER/exec/btc-mainnet.cfg", stdout, stderr);
	//executor_t exec = executor_construct("/home/fernando/exec/btc-mainnet.cfg", nullptr, nullptr);
    executor_t exec = executor_construct("", stdout, stderr);


    int res1 = executor_initchain(exec);

	int res2 = executor_run_wait(exec);

	size_t from_height = 0;
	

	auto filter = binary_construct ("pepe");
	fetch_stealth(exec, filter, from_height, stealth_fetch_handler);
    while (true) {
		std::this_thread::sleep_for(500ms);
		std::cout << "..." << std::endl;
	}


    executor_destruct(exec);

    return 0;
}
