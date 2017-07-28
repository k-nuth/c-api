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


#include <iostream>
#include <chrono>
#include <thread>

void history_fetch_handler(int error, history_compact_list_t list) {
    // printf("C callback (history_fetch_handler) called\n");
    // printf("Calling Python callback\n");

    PyObject* arglist = Py_BuildValue("(iO)", error, history_list);
    PyObject* result = PyObject_CallObject(global_callback, arglist);
    Py_DECREF(arglist);
}

int main(int argc, char* argv[]) {

    executor_t exec = executor_construct("/home/fernando/exec/btc-mainnet.cfg", stdout, stderr);

    int res1 = executor_initchain(exec);
    int res2 = executor_run(exec);

//    fetch_merkle_block_by_height(exec, 0, NULL);

    fetch_history(exec, "134HfD2fdeBTohfx8YANxEpsYXsv5UoWyz", 0, 0, history_fetch_handler);


    using namespace std::chrono_literals;
    std::cout << "Hello waiter" << std::endl;
    auto start = std::chrono::high_resolution_clock::now();
    std::this_thread::sleep_for(2s);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end-start;
    std::cout << "Waited " << elapsed.count() << " ms\n";


    executor_destruct(exec);

    return 0;
}

