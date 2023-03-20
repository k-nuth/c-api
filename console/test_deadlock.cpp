// Copyright (c) 2016-2023 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/capi/node.h>

#include <iostream>
#include <chrono>
#include <thread>

int main() {
    std::cout << "Initializing...\n";

    // using (var node = new Knuth.Node("node.cfg")) {
    // auto node = kth_node_construct_fd("/Users/fernando/dev/kth/cs-api/console/node.cfg", 0, 0);
    auto node = kth_node_construct_fd("/Users/fernando/dev/kth/cs-api/console/node_throttling.cfg", 0, 0);
    {
        // var result = await node.InitAndRunAsync();
        // kth_node_init_and_run(node, handlerPtr, internalRunNodeHandler_);
        auto result = kth_node_init_and_run_wait(node);
        if (result != 0) {
            std::cout << "kth_node_init_and_run_wait failed; error code: " << result << std::endl;
            std::cout << "sleeping 5 seconds" << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(5));
        }
        // kth_node_close(node);

        std::cout << "main thread: " << std::this_thread::get_id() << std::endl;

        std::thread t1([&] {
            std::cout << "t1 thread: " << std::this_thread::get_id() << std::endl;
            kth_node_close(node);
        });
        t1.join();
    }
}





// void history_fetch_handler(int error, history_compact_list_t list) {
//     // printf("C callback (history_fetch_handler) called\n");
//     // printf("Calling Python callback\n");

//     PyObject* arglist = Py_BuildValue("(iO)", error, history_list);
//     PyObject* result = PyObject_CallObject(global_callback, arglist);
//     Py_DECREF(arglist);
// }

// int main(int argc, char* argv[]) {

//     kth_node_t exec = kth_node_construct("/home/fernando/exec/btc-mainnet.cfg", stdout, stderr);

//     int res1 = kth_node_initchain(exec);
//     int res2 = kth_node_run(exec);

// //    fetch_merkle_block_by_height(exec, 0, NULL);

//     fetch_history(exec, "134HfD2fdeBTohfx8YANxEpsYXsv5UoWyz", 0, 0, history_fetch_handler);


//     using namespace std::chrono_literals;
//     std::cout << "Hello waiter" << std::endl;
//     auto start = std::chrono::high_resolution_clock::now();
//     std::this_thread::sleep_for(2s);
//     auto end = std::chrono::high_resolution_clock::now();
//     std::chrono::duration<double, std::milli> elapsed = end-start;
//     std::cout << "Waited " << elapsed.count() << " ms\n";


//     kth_node_destruct(exec);

//     return 0;
// }

