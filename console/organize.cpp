// printf "[requires]\nc-api/0.X@kth/stable\n[options]\nc-api:shared=True\n[imports]\ninclude/kth, *.h -> ./include/kth\ninclude/kth, *.hpp -> ./include/kth\nlib, *.so -> ./lib\n" > conanfile.txt
// conan install .
// g++ -std=c++20 -O3 -Iinclude -c organize.cpp
// g++ -std=c++20 -O3 -Llib -o organize organize.o -lkth-c-api
// export LD_LIBRARY_PATH=/home/fernando/organize/lib

#include <atomic>
#include <chrono>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include <kth/capi.h>
#include <kth/capi/hash.h>

// std::string const blocks_filename = "blocks-0-100000.csv";
// std::string const blocks_filename = "blocks-100000-200000.csv";

uint8_t char2int(char input) {
    if(input >= '0' && input <= '9') return input - '0';
    if(input >= 'A' && input <= 'F') return input - 'A' + 10;
    if(input >= 'a' && input <= 'f') return input - 'a' + 10;
    throw std::invalid_argument("Invalid input string");
}

void hex2bin(char const* src, uint8_t* target) {
    while(*src && src[1]) {
        *(target++) = char2int(*src)*16 + char2int(src[1]);
        src += 2;
    }
}

using bytes_t = std::vector<uint8_t>;

bytes_t hex2vec(char const* src, size_t n) {
    bytes_t bytes(n / 2);
    hex2bin(src, bytes.data());
    return bytes;
}

std::vector<bytes_t> get_blocks_raw(std::string const& blocks_filename) {
    std::cout << "Allocating some memory ...\n";

    std::vector<bytes_t> blocks_raw;
    blocks_raw.reserve(100000);

    std::cout << "Reading " << blocks_filename << " into memory ...\n";

    std::ifstream file(blocks_filename);
    std::string str;
    while (std::getline(file, str)) {
        auto bytes = hex2vec(str.data(), str.size());
        blocks_raw.push_back(std::move(bytes));
    }

    return blocks_raw;
}

std::vector<kth_block_t> get_blocks(std::vector<bytes_t>& blocks_raw) {
    std::cout << "Deserializing blocks ...\n";
    std::vector<kth_block_t> blocks;
    blocks.reserve(100000);

    for (auto& block_raw : blocks_raw) {
        auto block_ptr = kth_chain_block_factory_from_data(1, block_raw.data(), std::size(block_raw));
        auto valid = kth_chain_block_is_valid(block_ptr);

        if ( ! valid) {
            std::cout << "****** INVALID BLOCK ******\n";
        }

        blocks.push_back(block_ptr);

        // auto fees = kth_chain_block_fees(block_ptr);
        // std::cout << "fees: " << fees << " ...\n";
        // auto hash = kth_chain_block_hash(block_ptr);
        // char* hash_str = kth_hash_to_str(hash);
        // std::cout << "hash: " << hash_str << " ...\n";

        // kth_chain_block_destruct(block_ptr);
    }

    std::cout << "Deserialization OK.\n";

    return blocks;
}

std::vector<kth_block_t> get_blocks_from_to(std::vector<bytes_t>& blocks_raw, size_t from, size_t n) {
    std::cout << "Deserializing blocks ...\n";
    std::vector<kth_block_t> blocks;
    blocks.reserve(n);

    for (size_t i = 0; i < n; ++i) {
        auto& block_raw = blocks_raw[from + i];
        auto block_ptr = kth_chain_block_factory_from_data(1, block_raw.data(), std::size(block_raw));
        auto valid = kth_chain_block_is_valid(block_ptr);

        if ( ! valid) {
            std::cout << "****** INVALID BLOCK ******\n";
        }

        blocks.push_back(block_ptr);

        // auto fees = kth_chain_block_fees(block_ptr);
        // std::cout << "fees: " << fees << " ...\n";
        // auto hash = kth_chain_block_hash(block_ptr);
        // char* hash_str = kth_hash_to_str(hash);
        // std::cout << "hash: " << hash_str << " ...\n";

        // kth_chain_block_destruct(block_ptr);
    }


    std::cout << "Deserialization OK.\n";

    return blocks;
}

std::vector<kth_block_t> get_blocks_from_file(std::string const& blocks_filename) {
    auto blocks_raw = get_blocks_raw(blocks_filename);
    auto blocks = get_blocks(blocks_raw);
    return blocks;
}

void process_0(kth_chain_t chain, std::string const& blocks_filename) {
    auto blocks = get_blocks_from_file(blocks_filename);

    std::cout << "-------------------------------------------------------\n";

    std::cout << "*********** Organizing blocks ...\n";

    auto start = std::chrono::high_resolution_clock::now();

    size_t block_h = 0;
    for (auto const& block_ptr : blocks) {
        auto res = kth_chain_sync_organize_block(chain,  block_ptr);
        // std::cout << "res: " << res << " ...\n";
        if (res != 0) {
            std::cout << "****** INVALID BLOCK ORGANIZATION: " << block_h << " -- res: " << res << " ******\n";
        }

        // size_t height;
        // kth_chain_sync_last_height(chain, &height);
        // std::cout << "height: " << height << " ...\n";

        // kth_chain_block_destruct(block_ptr);

        if (block_h % 1000 == 0) {
            std::cout << "height: " << block_h << " ...\n";
        }

        ++block_h;
    }

    auto finish = std::chrono::high_resolution_clock::now();

    std::cout << "Organization OK.\n";
    std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count() << "ns\n";

}

void process_1(kth_chain_t chain, std::string const& blocks_filename) {
    size_t const max = 1000;
    auto blocks_raw = get_blocks_raw(blocks_filename);

    std::cout << "-------------------------------------------------------\n";
    std::cout << "*********** Organizing blocks ...\n";

    double total_time = 0.0;
    for (size_t i = 0; i < blocks_raw.size(); i += max) {
        std::cout << "process_1 i: " << i << '\n';
        auto blocks = get_blocks_from_to(blocks_raw, i, max);

        auto start = std::chrono::high_resolution_clock::now();

        size_t block_h = 0;
        for (auto const& block_ptr : blocks) {
            auto res = kth_chain_sync_organize_block(chain, block_ptr);
            // void kth_chain_async_organize_block(kth_chain_t chain, void* ctx, kth_block_t block, kth_result_handler_t handler);

            // std::cout << "res: " << res << " ...\n";
            if (res != 0 && res != 51) {
                std::cout << "****** INVALID BLOCK ORGANIZATION: " << block_h << " -- res: " << res << " ******\n";
            }

            // size_t height;
            // kth_chain_sync_last_height(chain, &height);
            // std::cout << "height: " << height << " ...\n";

            // kth_chain_block_destruct(block_ptr);

            if (block_h % 1000 == 0) {
                std::cout << "height: " << block_h << " ...\n";
            }

            ++block_h;
        }

        auto finish = std::chrono::high_resolution_clock::now();
        auto partial_time = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count();
        total_time += partial_time;
        std::cout << "partial_time: " << partial_time << " - Total time: " << total_time << "ns\n";


        std::cout << "Destructing blokcs ...\n";
        for (auto const& block_ptr : blocks) {
            kth_chain_block_destruct(block_ptr);
        }

    }
    std::cout << "Organization OK.\n";
    std::cout << "Total time: " << total_time << "ns\n";
}


std::atomic<size_t> organized = 0;
std::atomic<size_t> sent = 0;

void on_block_organized(kth_chain_t chain, void* ctx, kth_error_code_t err) {
    if (err != 0 && err != 51) {
        std::cout << "****** INVALID BLOCK ORGANIZATION: -- err: " << err << " ******\n";
    }
    ++organized;
}

void process_2(kth_chain_t chain, std::string const& blocks_filename) {
    size_t const max = 1000;
    auto blocks_raw = get_blocks_raw(blocks_filename);

    std::cout << "-------------------------------------------------------\n";
    std::cout << "*********** Organizing blocks ...\n";

    double total_time = 0.0;
    for (size_t i = 0; i < blocks_raw.size(); i += max) {
        std::cout << "process_2 i: " << i << '\n';
        auto blocks = get_blocks_from_to(blocks_raw, i, max);

        auto start = std::chrono::high_resolution_clock::now();

        size_t block_h = 0;
        for (auto const& block_ptr : blocks) {

            // auto res = kth_chain_sync_organize_block(chain, block_ptr);
            kth_chain_async_organize_block(chain, nullptr, block_ptr, on_block_organized);
            ++sent;

            if (block_h % 1000 == 0) {
                std::cout << "height: " << block_h << " ...\n";
            }

            ++block_h;
        }

        auto finish = std::chrono::high_resolution_clock::now();
        auto partial_time = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count();
        total_time += partial_time;
        std::cout << "partial_time: " << partial_time << " - Total time: " << total_time << "ns\n";


        std::cout << "Destructing blokcs ...\n";
        for (auto const& block_ptr : blocks) {
            kth_chain_block_destruct(block_ptr);
        }

    }
    std::cout << "Organization OK.\n";
    std::cout << "Total time: " << total_time << "ns\n";
}

int main(int argc, char** argv) {
    if (argc <= 1) {
        std::cout << "USAGE: organize <filename>\n";
        return 1;
    }
    std::string blocks_filename = argv[1];

    kth_settings* settings;
    char* error_message;
    kth_bool_t ok = kth_config_settings_get_from_file("off.cfg", &settings, &error_message);

    if ( ! ok) {
        printf("error: %s", error_message);
        return -1;
    }

    kth_node_t node = kth_node_construct(settings, 1);
    auto res = kth_node_init_run_sync(node, kth_start_modules_just_chain);

    std::cout << "res: " << res << "\n";

    kth_chain_t chain = kth_node_get_chain(node);

    // process_0(chain, blocks_filename);
    // process_1(chain, blocks_filename);
    process_2(chain, blocks_filename);

    return 0;
}



// Database type: normal
    //       0 -  99'999:        131690853822ns        2.2 min
    // 100'000 - 200'000:        583663119926ns        9.7 min
    // 200'000 - 300'000:        2.52254e+12ns        42.04 min

    // 300'000 - 400'000:        ?


// Database type: pruned
    //       0 -  99'999:        1.3224e+11ns           2.204 min
    // 100'000 - 200'000:        5.06502e+11ns          8.441 min
    // 200'000 - 300'000:        2.48002e+12ns          41.33 min
    // 300'000 - 400'000:        8.60159e+12ns         143.35 min
    // 400'000 - 500'000:

// Database type: pruned (without reorg db prune)
    //       0 -  99'999:
    // 100'000 - 200'000:
    // 200'000 - 300'000:
    // 300'000 - 400'000:
    // 400'000 - 500'000:

// Database type: pruned (without 100% reorg db code removed)
    //       0 -  99'999:
    // 100'000 - 200'000:
    // 200'000 - 300'000:
    // 300'000 - 400'000:
    // 400'000 - 500'000:

// Database type: pruned ( UTXO unordered_map )
    //       0 -  99'999:       1.28372e+11ns           2.139 min
    // 100'000 - 200'000:
    // 200'000 - 300'000:
    // 300'000 - 400'000:
    // 400'000 - 500'000:
    // --------------------------------------------------------------------------------
    //       0 - 200'000:       5.07535e+11ns           8.45 min           (100 GB de memory mapped file)
    //       0 - 200'000:       5.01613e+11ns           8.36 min           (  1 GB de memory mapped file)
    //       0 - 200'000:       3.34369e+11ns           5.57 min           (  1 GB de memory mapped file, removed all the DB,  2 threads blockchain )
    //       0 - 200'000:       3.67022e+11ns           6.11 min           (  1 GB de memory mapped file, removed all the DB, 80 threads blockchain )




