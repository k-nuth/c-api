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


#include <iostream>
#include <chrono>
#include <thread>

void history_fetch_handler(int error, history_compact_list_t history_list) {
     printf("C callback (history_fetch_handler) called\n");

	 auto count = history_compact_list_count(history_list);
	 printf("history_fetch_handler count: %d\n", count);

	 history_compact_list_destruct(history_list);
}

void last_height_fetch_handler(int error, size_t h) {
	printf("last_height_fetch_handler h: %d\n", h);

	//if (h >= 1000) {

	//}
}

bool waiting = true;


int main(int argc, char* argv[]) {
	using namespace std::chrono_literals;

    executor_t exec = executor_construct("/home/FERFER/exec/btc-mainnet.cfg", stdout, stderr);
	//executor_t exec = executor_construct("/home/fernando/exec/btc-mainnet.cfg", nullptr, nullptr);

    int res1 = executor_initchain(exec);

	int res2 = executor_run_wait(exec);

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
