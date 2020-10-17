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


#include <boost/thread/latch.hpp>


//  void wait_until_block(kth_chain_t chain, size_t desired_height) {
//      printf("wait_until_block - 1\n");

//      uint64_t height;
//      int error = kth_chain_sync_last_height(chain, &height);
//      //printf("wait_until_block; desired_height: %zd, error: %d, height: %zd\n", desired_height, error, height);
    
//      while (error == 0 && height < desired_height) {
//          error = kth_chain_sync_last_height(chain, &height);
//          //printf("wait_until_block; desired_height: %zd, error: %d, height: %zd\n", desired_height, error, height);
        
//          if (height < desired_height) {
//              //printf("wait_until_block - 2\n");
//              // time.sleep(1)
            
//              // std::this_thread::sleep_for(10s);
//              std::this_thread::sleep_for(std::chrono::seconds(10));

//              //printf("wait_until_block - 3\n");
//          }
//      }

//      //printf("wait_until_block - 4\n");
//  }

// void print_hex(char const* data, size_t n) {
//     while (n != 0) {
//         printf("%2x", *data);
//         ++data;
//         --n;
//     }
//     printf("\n");
// }

struct Node {
    std::atomic<bool> stopped_ = true;
    std::atomic<bool> running_ = true;
    kth_node_t node_;

    Node(kth_settings* settings, bool dummy) {
        // auto exec = kth_node_construct_fd(settings, 0, 0);
        // auto exec = kth_node_construct_fd(settings, -1, -1);
        node_ = kth_node_construct(settings, stdout, stderr);
    }

    ~Node() {
        kth_node_signal_stop(node_); 

        while (running_ &&  ! stopped_) {
            // System.Threading.Thread.Sleep(100);
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        std::cout << "~Node() BEFORE kth_node_destruct" << std::endl;
        kth_node_destruct(node_);
        std::cout << "~Node() AFTER kth_node_destruct" << std::endl;
    }

    template <typename F>
    void LaunchAsync(void* ctx, F handler) {
        std::thread t1([&, this](){
            stopped_ = false;
            kth_node_init_run_and_wait_for_signal(node_, ctx, handler);
            stopped_ = true;
            running_ = true;
        });
        t1.detach();
    }
};


int main(int /*argc*/, char* /*argv*/[]) {
//    using namespace std::chrono_literals;

    kth_settings* settings;
    char* error_message;
    kth_bool_t ok = kth_config_settings_get_from_file("C:\\development\\kth\\cs-api\\console\\node_win.cfg", &settings, &error_message);

    if ( ! ok) {
        printf("error: %s", error_message);
        return -1;
    }

    {
        auto node = Node(settings, true);

        boost::latch latch(2); //Note: workaround to fix an error on some versions of Boost.Threads

        node.LaunchAsync(&latch, [](auto node, auto ctx, auto ec) {
            auto local_latch = static_cast<boost::latch*>(ctx);
            std::cout << ec << std::endl;

            auto chain = kth_node_get_chain(node);
            kth_size_t height;
            auto ec2 = kth_chain_sync_last_height(chain, &height);

            std::cout << "Current height in local copy: " << height << std::endl;
            local_latch->count_down();
        });
        latch.count_down_and_wait();

        std::cout << "Disposing things..." << std::endl;
    }

    return 0;
}
