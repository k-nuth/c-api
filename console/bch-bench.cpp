// printf "[requires]\nc-api/0.X@kth/stable\n[options]\nc-api:shared=True\n[imports]\ninclude/kth, *.h -> ./include/kth\ninclude/kth, *.hpp -> ./include/kth\nlib, *.so -> ./lib\n" > conanfile.txt
// conan install .
// gcc -Iinclude -c hello_knuth.c
// gcc -Llib -o hello_knuth hello_knuth.o -lkth-c-api

#include <cinttypes>
#include <cstdint>
#include <cstdio>

#include <fstream>
#include <iostream>
#include <string>

#include <kth/capi.h>

#include <kth/infrastructure/utility/data.hpp>
#include <kth/infrastructure/formats/base_16.hpp>

void do_the_work(kth_node_t node) {
    kth_chain_t chain = kth_node_get_chain(node);

    uint64_t height;
    kth_chain_sync_last_height(chain, &height);

    printf("%" PRIu64 "\n", height);


    double serialize_total_ns = 0;
    double organize_total_ns = 0;
    size_t block_counter = 0;
    size_t size_total = 0;
    size_t txs_total = 0;

    std::ifstream file("/Users/fernando/scalenet/test.txt");
    std::string str; 
    while (std::getline(file, str)) {

        if (block_counter >= 11) {
            std::cout << block_counter << std::endl;
        }

        auto start = std::chrono::high_resolution_clock::now();
        kth::data_chunk data;
        kth::decode_base16(data, str.data());
        // reinterpret_cast<uint8_t*>(str.data())
        auto end = std::chrono::high_resolution_clock::now();
        auto decode_base16_time_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

        // std::cout << "Decode base16: " 
        //           << str.size() << " chars - " 
        //           << (double(str.size()) / (1024 * 1024)) << " MiB - " 
        //           << (double(str.size()) / (1000 * 1000)) << " MB - " 
        //           << decode_base16_time_ns << " ns - " 
        //           << (decode_base16_time_ns / 1'000'000'000.0) << " secs." << std::endl;


        start = std::chrono::high_resolution_clock::now();
        auto block = kth_chain_block_factory_from_data(0, data.data(), data.size());
        // auto block = kth_chain_block_factory_from_data(0, reinterpret_cast<uint8_t*>(str.data()), str.size());
        end = std::chrono::high_resolution_clock::now();
        auto time_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        serialize_total_ns += double(time_ns);
        size_total += data.size();

        auto is_valid = kth_chain_block_is_valid(block);
        if ( ! is_valid) {
            std::cout << "Block not valid" << std::endl;
        }

        kth_transaction_list_t tx_list = kth_chain_block_transactions(block);
        auto tx_count = kth_chain_transaction_list_count(tx_list);
        txs_total += tx_count;

        std::cout << "Block serialization: " 
                  << data.size() << " bytes - " 
                  << (double(data.size()) / (1024 * 1024)) << " MiB - " 
                  << (double(data.size()) / (1000 * 1000)) << " MB - " 
                  << tx_count << " txs - " 
                  << time_ns << " ns - " 
                  << (time_ns / 1'000'000'000.0) << " secs." << std::endl;

        kth_chain_t chain = kth_node_get_chain(node);

        start = std::chrono::high_resolution_clock::now();
        // kth_chain_async_organize_block(chain, nullptr, block, [](kth_chain_t chain, void* ctx, kth_error_code_t err) {
        // });
        // int blk_err = kth_chain_sync_organize_block(chain, block);

        kth_size_t block_to_cpp_ns;
        kth_size_t pre_latch_ns;
        kth_size_t organize_ns;
        int blk_err = kth_chain_sync_organize_block(chain, block, block_to_cpp_ns, pre_latch_ns, organize_ns);

        end = std::chrono::high_resolution_clock::now();
        auto blk_time_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        organize_total_ns += double(blk_time_ns);

        if (blk_err != 0) {
            std::cout << "Block organize failed!" << std::endl;
        }

        std::cout << "kth_chain_sync_organize_block - Block to C++: " 
                << block_to_cpp_ns << " ns - " 
                << (block_to_cpp_ns / 1'000'000'000.0) << " secs." << std::endl;

        std::cout << "kth_chain_sync_organize_block - pre_latch_ns: " 
                << pre_latch_ns << " ns - " 
                << (pre_latch_ns / 1'000'000'000.0) << " secs." << std::endl;

        std::cout << "kth_chain_sync_organize_block - organize_ns: " 
                << organize_ns << " ns - " 
                << (organize_ns / 1'000'000'000.0) << " secs." << std::endl;

        std::cout << "Block organize: " 
                  << blk_time_ns << " ns - " 
                  << (blk_time_ns / 1'000'000'000.0) << " secs." << std::endl;

        std::cout << "------------------------------------------------------------" << std::endl;

        kth_chain_block_destruct(block);

        ++block_counter;
    }

    std::cout << "TOTAL Block serialization: " 
                << size_total << " bytes - " 
                << (double(size_total) / (1024 * 1024)) << " MiB - " 
                << (double(size_total) / (1000 * 1000)) << " MB - " 
                << txs_total << " txs - " 
                << serialize_total_ns << " ns - " 
                << (serialize_total_ns / 1'000'000'000.0) << " secs." << std::endl;

    std::cout << "TOTAL Block organize: " 
                << organize_total_ns << " ns - " 
                << (organize_total_ns / 1'000'000'000.0) << " secs." << std::endl;


}

int main() {


    kth_settings* settings;
    char* error_message;
    kth_bool_t ok = kth_config_settings_get_from_file("/Users/fernando/scalenet/scalenet-nopeers.cfg", &settings, &error_message);

    if ( ! ok) {
        printf("error: %s", error_message);
        return -1;
    }

    kth_node_t node = kth_node_construct(settings, true);


    std::cout << "Before kth_node_init_run_and_wait_for_signal" << std::endl;

    // kth_node_initchain(node);
    // kth_node_run_wait(node);
    kth_node_init_run_and_wait_for_signal(node, nullptr, [](kth_node_t node, void* ctx, kth_error_code_t err) {
        std::cout << "Node launched!!!" << std::endl;
        std::cout << "err: " << err << std::endl;
        do_the_work(node);
    });

    std::cout << "After kth_node_init_run_and_wait_for_signal" << std::endl;


    kth_node_destruct(node);
}