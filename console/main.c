// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <stdio.h>

#include <kth/capi/executor_c.h>


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

