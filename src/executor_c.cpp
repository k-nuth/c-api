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

#include <bitprim/nodecint/executor_c.h>
#include <cstdio>
#include <memory>
#include <boost/iostreams/device/file_descriptor.hpp>
#include <boost/thread/latch.hpp>
#include <bitprim/nodecint/executor.hpp>
//#include <bitprim/nodecint/output_point.h>
#include <bitcoin/bitcoin/wallet/mnemonic.hpp>
//#include <inttypes.h>   //TODO: Remove, it is for the printf (printing pointer addresses)
//#include <cinttypes>   //TODO: Remove, it is for the printf (printing pointer addresses)

libbitcoin::node::configuration make_config(char const* path) {
    libbitcoin::node::configuration config(libbitcoin::config::settings::mainnet);
    config.file = boost::filesystem::path(path);
    return config;
}

inline
FILE* devnull_file() {
#ifdef BOOST_IOSTREAMS_WINDOWS
    return fopen ("nul", "w");
#else
    return fopen ("/dev/null", "w");
#endif
}

inline
int devnull_fileno() {
    return fileno(devnull_file());
}

inline
int fileno_or_devnull(FILE* f) {
    if (f == nullptr) {
        return devnull_fileno();
    } else {
        return fileno(f);
    }
}

inline
int fileno_or_devnull(int fd) {
    if (fd < 0) {
        return devnull_fileno();
    } else {
        return fd;
    }
}

#ifdef BOOST_IOSTREAMS_WINDOWS
//using handle_source = typename boost::iostreams::file_descriptor_source::handle_type;
using handle_sink = typename boost::iostreams::file_descriptor_sink::handle_type;

//inline
//int fileno_or_devnull(handle_sink s) {
//    if (s == nullptr) {
//        return devnull_fileno();
//    } else {
//        return fileno(f);
//    }
//}

#endif /* BOOST_IOSTREAMS_WINDOWS */



extern "C" {

struct executor {

    executor(char const* path, FILE* sout, FILE* serr)
        : sout_buffer_(boost::iostreams::file_descriptor_sink(fileno_or_devnull(sout), boost::iostreams::never_close_handle))
        , serr_buffer_(boost::iostreams::file_descriptor_sink(fileno_or_devnull(serr), boost::iostreams::never_close_handle))
        , sout_(&sout_buffer_)
        , serr_(&serr_buffer_)
        , actual(make_config(path), sout_, serr_)
    {
//        std::ostream os(&sout_buffer_);
//        os << "Hello World!" << std::endl;
    }

    executor(char const* path, int sout_fd, int serr_fd)
        : sout_buffer_(boost::iostreams::file_descriptor_sink(fileno_or_devnull(sout_fd), boost::iostreams::never_close_handle))
        , serr_buffer_(boost::iostreams::file_descriptor_sink(fileno_or_devnull(serr_fd), boost::iostreams::never_close_handle))
        , sout_(&sout_buffer_)
        , serr_(&serr_buffer_)
        , actual(make_config(path), sout_, serr_)
    {
//        std::ostream os(&sout_buffer_);
//        os << "Hello World -- 2!" << std::endl;
    }

#ifdef BOOST_IOSTREAMS_WINDOWS
    executor(char const* path, handle_sink sout, handle_sink serr)
        : sout_buffer_(boost::iostreams::file_descriptor_sink(sout, boost::iostreams::never_close_handle))
        , serr_buffer_(boost::iostreams::file_descriptor_sink(serr, boost::iostreams::never_close_handle))
        , sout_(&sout_buffer_)
        , serr_(&serr_buffer_)
        , actual(make_config(path), sout_, serr_)
    {
//        std::ostream os(&sout_buffer_);
//        os << "Hello World -- 3!" << std::endl;
    }
#endif /* BOOST_IOSTREAMS_WINDOWS */

    boost::iostreams::stream_buffer<boost::iostreams::file_descriptor_sink> sout_buffer_;
    boost::iostreams::stream_buffer<boost::iostreams::file_descriptor_sink> serr_buffer_;
    std::ostream sout_;
    std::ostream serr_;
    bitprim::nodecint::executor actual;
};

executor_t executor_construct(char const* path, FILE* sout, FILE* serr) {
    return std::make_unique<executor>(path, sout, serr).release();
}

executor_t executor_construct_fd(char const* path, int sout_fd, int serr_fd) {
    return std::make_unique<executor>(path, sout_fd, serr_fd).release();
}

#ifdef BOOST_IOSTREAMS_WINDOWS

executor_t executor_construct_handles(char const* path, void* sout, void* serr) {
    return std::make_unique<executor>(path, sout, serr).release();
}

#endif /* BOOST_IOSTREAMS_WINDOWS */


void executor_destruct(executor_t exec) {
//    std::cout << "From C++: executor_destruct\n";
//    printf("executor_destruct - exec: 0x%" PRIXPTR "\n", (uintptr_t)exec);
    delete exec;
}

int executor_initchain(executor_t exec) {
    return exec->actual.do_initchain();
}

void executor_run(executor_t exec, run_handler_t handler) {
    exec->actual.run([handler](std::error_code const& ec) {
		if (handler != nullptr) {
			handler(ec.value());
		}
    });
}

int executor_run_wait(executor_t exec) {
    boost::latch latch(2); //Note: workaround to fix an error on some versions of Boost.Threads
    int res;
	bool run_res = exec->actual.run([&](std::error_code const& ec) {
//        std::cout << "lambda ec.value(): " << ec.value() << std::endl;
        res = ec.value();
        latch.count_down();
    });

//    std::cout << "run_res: " << std::boolalpha << run_res << std::endl;

    if (run_res) {
        latch.count_down_and_wait();
        return res;
    } else {
        return 1;
    }
}

void executor_stop(executor_t exec) {
    exec->actual.stop();
}

void fetch_last_height(executor_t exec, last_height_fetch_handler_t handler) {
    exec->actual.node().chain().fetch_last_height([handler](std::error_code const& ec, size_t h) {
        handler(ec.value(), h);
    });
}

int get_last_height(executor_t exec, size_t* height) {
    boost::latch latch(2); //Note: workaround to fix an error on some versions of Boost.Threads

    int res;
    exec->actual.node().chain().fetch_last_height([&](std::error_code const& ec, size_t h) {
        *height = h;
        res = ec.value();
        latch.count_down();
    });

    latch.count_down_and_wait();
    return res;
}

void fetch_block_height(executor_t exec, hash_t hash, block_height_fetch_handler_t handler) {

    libbitcoin::hash_digest hash_cpp;
    std::copy_n(hash, hash_cpp.size(), std::begin(hash_cpp));

    exec->actual.node().chain().fetch_block_height(hash_cpp, [handler](std::error_code const& ec, size_t h) {
        handler(ec.value(), h);
    });
}

int get_block_height(executor_t exec, hash_t hash, size_t* height) {
    boost::latch latch(2); //Note: workaround to fix an error on some versions of Boost.Threads
    int res;

    libbitcoin::hash_digest hash_cpp;
    std::copy_n(hash, hash_cpp.size(), std::begin(hash_cpp));

    exec->actual.node().chain().fetch_block_height(hash_cpp, [&](std::error_code const& ec, size_t h) {
        *height = h;
        res = ec.value();
        latch.count_down();
    });

    latch.count_down_and_wait();
    return res;
}

void fetch_block_header_by_height(executor_t exec, size_t height, block_header_fetch_handler_t handler) {
    exec->actual.node().chain().fetch_block_header(height, [handler](std::error_code const& ec, libbitcoin::message::header::ptr header, size_t h) {
        auto new_header = new libbitcoin::message::header(*header.get());
//        auto new_header = std::make_unique(*header.get()).release();
        //Note: It is the responsability of the user to release/destruct the object
        handler(ec.value(), new_header, h);
    });
}

int get_block_header_by_height(executor_t exec, size_t height, header_t* out_header, size_t* out_height) {
    boost::latch latch(2); //Note: workaround to fix an error on some versions of Boost.Threads
    int res;

    exec->actual.node().chain().fetch_block_header(height, [&](std::error_code const& ec, libbitcoin::message::header::ptr header, size_t h) {
        *out_header = new libbitcoin::message::header(*header.get());
        //Note: It is the responsability of the user to release/destruct the object

        *out_height = h;
        res = ec.value();
        latch.count_down();
    });

    latch.count_down_and_wait();
    return res;
}

void fetch_block_header_by_hash(executor_t exec, hash_t hash, block_header_fetch_handler_t handler) {

    libbitcoin::hash_digest hash_cpp;
    std::copy_n(hash, hash_cpp.size(), std::begin(hash_cpp));

    exec->actual.node().chain().fetch_block_header(hash_cpp, [handler](std::error_code const& ec, libbitcoin::message::header::ptr header, size_t h) {
        auto new_header = new libbitcoin::message::header(*header.get());
//        auto new_header = std::make_unique(*header.get()).release();
        //Note: It is the responsability of the user to release/destruct the object
        handler(ec.value(), new_header, h);
    });
}

int get_block_header_by_hash(executor_t exec, hash_t hash, header_t* out_header, size_t* out_height) {
    boost::latch latch(2); //Note: workaround to fix an error on some versions of Boost.Threads
    int res;

    libbitcoin::hash_digest hash_cpp;
    std::copy_n(hash, hash_cpp.size(), std::begin(hash_cpp));

    exec->actual.node().chain().fetch_block_header(hash_cpp, [&](std::error_code const& ec, libbitcoin::message::header::ptr header, size_t h) {
        *out_header = new libbitcoin::message::header(*header.get());
        //Note: It is the responsability of the user to release/destruct the object

        *out_height = h;
        res = ec.value();
        latch.count_down();
    });

    latch.count_down_and_wait();
    return res;
}

void fetch_block_by_height(executor_t exec, size_t height, block_fetch_handler_t handler) {
    exec->actual.node().chain().fetch_block(height, [handler](std::error_code const& ec, libbitcoin::message::block::ptr block, size_t h) {

        auto new_block = new libbitcoin::message::block(*block.get());
        //Note: It is the responsability of the user to release/destruct the object
        handler(ec.value(), new_block, h);
    });
}

int get_block_by_height(executor_t exec, size_t height, block_t* out_block, size_t* out_height) {
    boost::latch latch(2); //Note: workaround to fix an error on some versions of Boost.Threads
    int res;

    exec->actual.node().chain().fetch_block(height, [&](std::error_code const& ec, libbitcoin::message::block::ptr block, size_t h) {
        *out_block = new libbitcoin::message::block(*block.get());
        //Note: It is the responsability of the user to release/destruct the object

        *out_height = h;
        res = ec.value();
        latch.count_down();
    });

    latch.count_down_and_wait();
    return res;
}

void fetch_block_by_hash(executor_t exec, hash_t hash, block_fetch_handler_t handler) {

    libbitcoin::hash_digest hash_cpp;
    std::copy_n(hash, hash_cpp.size(), std::begin(hash_cpp));

    exec->actual.node().chain().fetch_block(hash_cpp, [handler](std::error_code const& ec, libbitcoin::message::block::ptr block, size_t h) {
        //Note: It is the responsability of the user to release/destruct the object
        auto new_block = new libbitcoin::message::block(*block.get());
        handler(ec.value(), new_block, h);
    });
}

int get_block_by_hash(executor_t exec, hash_t hash, block_t* out_block, size_t* out_height) {
    boost::latch latch(2); //Note: workaround to fix an error on some versions of Boost.Threads
    int res;

    libbitcoin::hash_digest hash_cpp;
    std::copy_n(hash, hash_cpp.size(), std::begin(hash_cpp));

    exec->actual.node().chain().fetch_block(hash_cpp, [&](std::error_code const& ec, libbitcoin::message::block::ptr block, size_t h) {
        //Note: It is the responsability of the user to release/destruct the object
        *out_block = new libbitcoin::message::block(*block.get());
        *out_height = h;
        res = ec.value();
        latch.count_down();
    });

    latch.count_down_and_wait();
    return res;
}

void fetch_merkle_block_by_height(executor_t exec, size_t height, merkle_block_fetch_handler_t handler){
    exec->actual.node().chain().fetch_merkle_block(height, [handler](std::error_code const& ec, libbitcoin::message::merkle_block::ptr block, size_t h) {

        auto new_block = new libbitcoin::message::merkle_block(*block.get());
        //Note: It is the responsibility of the user to release/destruct the object
        handler(ec.value(), new_block, h);
    });
}

void fetch_merkle_block_by_hash(executor_t exec, hash_t hash, merkle_block_fetch_handler_t handler) {

    libbitcoin::hash_digest hash_cpp;
    std::copy_n(hash, hash_cpp.size(), std::begin(hash_cpp));

    exec->actual.node().chain().fetch_merkle_block(hash_cpp, [handler](std::error_code const& ec, libbitcoin::message::merkle_block::ptr block, size_t h) {
        auto new_block = new libbitcoin::message::merkle_block(*block.get());
        handler(ec.value(), new_block, h);
    });
}

void fetch_transaction(executor_t exec, hash_t hash, int require_confirmed, transaction_fetch_handler_t handler) {
    //precondition:  [hash, 32] is a valid range

    libbitcoin::hash_digest hash_cpp;
    std::copy_n(hash, hash_cpp.size(), std::begin(hash_cpp));

    exec->actual.node().chain().fetch_transaction(hash_cpp, require_confirmed, [handler](std::error_code const& ec, libbitcoin::message::transaction::ptr transaction, size_t h, size_t i) {
        auto new_transaction = new libbitcoin::message::transaction(*transaction.get());
        handler(ec.value(), new_transaction, h, i);
    });
}

int get_transaction(executor_t exec, hash_t hash, int require_confirmed, transaction_t* out_transaction, size_t* out_height, size_t* out_index) {
    boost::latch latch(2); //Note: workaround to fix an error on some versions of Boost.Threads
    int res;

    libbitcoin::hash_digest hash_cpp;
    std::copy_n(hash, hash_cpp.size(), std::begin(hash_cpp));

    exec->actual.node().chain().fetch_transaction(hash_cpp, require_confirmed, [&](std::error_code const& ec, libbitcoin::message::transaction::ptr transaction, size_t h, size_t i) {
        *out_transaction = new libbitcoin::message::transaction(*transaction.get());
        *out_height = h;
        *out_index = i;
        res = ec.value();
        latch.count_down();
    });

    latch.count_down_and_wait();
    return res;

}

void fetch_output(executor_t exec, hash_t hash, uint32_t index, int require_confirmed, output_fetch_handler_t handler) {

    libbitcoin::hash_digest hash_cpp;
    std::copy_n(hash, hash_cpp.size(), std::begin(hash_cpp));

    libbitcoin::chain::output_point point(hash_cpp, index);

    exec->actual.node().chain().fetch_output(point, require_confirmed, [handler](std::error_code const& ec, libbitcoin::chain::output const& output) {
        //It is the user's responsibility to release this memory
        auto new_output = new libbitcoin::chain::output(output);
        handler(ec.value(), new_output);
    });
}

int get_output(executor_t exec, hash_t hash, uint32_t index, int require_confirmed, output_t* out_output) {
    boost::latch latch(2); //Note: workaround to fix an error on some versions of Boost.Threads
    int res;

    libbitcoin::hash_digest hash_cpp;
    std::copy_n(hash, hash_cpp.size(), std::begin(hash_cpp));

    libbitcoin::chain::output_point point(hash_cpp, index);

    exec->actual.node().chain().fetch_output(point, require_confirmed, [&](std::error_code const& ec, libbitcoin::chain::output const& output) {
        *out_output = new libbitcoin::chain::output(output);

        res = ec.value();
        latch.count_down();
    });

    latch.count_down_and_wait();
    return res;
}

void fetch_compact_block_by_height(executor_t exec, size_t height, compact_block_fetch_handler_t handler){
    exec->actual.node().chain().fetch_compact_block(height, [handler](std::error_code const& ec, libbitcoin::message::compact_block::ptr block, size_t h) {

        auto new_block = new libbitcoin::message::compact_block(*block.get());
        //Note: It is the responsibility of the user to release/destruct the object
        handler(ec.value(), new_block, h);
    });
}

void fetch_compact_block_by_hash(executor_t exec, hash_t hash, compact_block_fetch_handler_t handler){
    libbitcoin::hash_digest hash_cpp;
    std::copy_n(hash, hash_cpp.size(), std::begin(hash_cpp));

    exec->actual.node().chain().fetch_compact_block(hash_cpp, [handler](std::error_code const& ec, libbitcoin::message::compact_block::ptr block, size_t h) {
        auto new_block = new libbitcoin::message::compact_block(*block.get());
        //Note: It is the responsibility of the user to release/destruct the object
        handler(ec.value(), new_block, h);
    });
}

void fetch_transaction_position(executor_t exec, hash_t hash, int require_confirmed, transaction_index_fetch_handler_t handler){
    libbitcoin::hash_digest hash_cpp;
    std::copy_n(hash, hash_cpp.size(), std::begin(hash_cpp));

    exec->actual.node().chain().fetch_transaction_position(hash_cpp, require_confirmed, [handler](std::error_code const& ec, size_t position, size_t height){
        handler(ec.value(), position, height);
    });
}

//It is the user's responsibility to release the input point returned in the callback
void fetch_spend(executor_t exec, output_point_t outpoint, spend_fetch_handler_t handler){
    libbitcoin::chain::output_point* outpoint_cpp = static_cast<libbitcoin::chain::output_point*>(outpoint);

    exec->actual.node().chain().fetch_spend(*outpoint_cpp, [handler](std::error_code const& ec, libbitcoin::chain::input_point input){
        auto new_input = new libbitcoin::chain::input_point(input);
        handler(ec.value(), new_input);
    });
}

//It is the user's responsibility to release the history returned in the callback
void fetch_history(executor_t exec, payment_address_t address, size_t limit, size_t from_height, history_fetch_handler_t handler){
    libbitcoin::wallet::payment_address const& address_cpp = *static_cast<const libbitcoin::wallet::payment_address*>(address);

    exec->actual.node().chain().fetch_history(address_cpp, limit, from_height, [handler](std::error_code const& ec, libbitcoin::chain::history_compact::list history){
        auto new_history = new libbitcoin::chain::history_compact::list(history);
        handler(ec.value(), new_history);
    });
}

//It is the user's responsibility to release the history returned in the callback
int get_history(executor_t exec, payment_address_t address, size_t limit, size_t from_height, history_compact_list_t* out_history) {
    boost::latch latch(2); //Note: workaround to fix an error on some versions of Boost.Threads
    int res;

    libbitcoin::wallet::payment_address const& address_cpp = *static_cast<const libbitcoin::wallet::payment_address*>(address);

    exec->actual.node().chain().fetch_history(address_cpp, limit, from_height, [&](std::error_code const& ec, libbitcoin::chain::history_compact::list history){
        *out_history = new libbitcoin::chain::history_compact::list(history);

        res = ec.value();
        latch.count_down();
    });

    latch.count_down_and_wait();
    return res;
}


long_hash_t wallet_mnemonics_to_seed(word_list_t mnemonics) {

    auto const& mnemonics_cpp = *static_cast<const std::vector<std::string>*>(mnemonics);

//    for (auto const& x : mnemonics_cpp) {
//        std::cout << x << std::endl;
//    }

    auto hash_cpp = libbitcoin::wallet::decode_mnemonic(mnemonics_cpp);
//    return hash_cpp.data();

//    std::cout << (int)hash_cpp[0] << std::endl;
//    std::cout << (int)hash_cpp[1] << std::endl;
//    std::cout << (int)hash_cpp[2] << std::endl;


    uint8_t* ret = (uint8_t*)malloc(hash_cpp.size() * sizeof(uint8_t));
    printf("wallet_mnemonics_to_seed - ret: %p\n", ret);
    std::copy_n(std::begin(hash_cpp), hash_cpp.size(), ret);
    return ret;
}

void long_hash_destroy(long_hash_t ptr) {
    free(ptr);
}

libbitcoin::message::transaction::const_ptr const& tx_shared(transaction_t tx) {
    auto const& tx_ref = *static_cast<libbitcoin::message::transaction const*>(tx);
    auto* tx_new = new libbitcoin::message::transaction(tx_ref);
    return libbitcoin::message::transaction::const_ptr(tx_new);
}


namespace {
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
}

//It is the user's responsibility to release the transaction returned
transaction_t hex_to_tx(char const* tx_hex) {

    printf("hex_to_tx - 1\n");

    static const auto version = libbitcoin::message::version::level::canonical;

    printf("hex_to_tx - 2\n");

//    const auto tx = std::make_shared<libbitcoin::message::transaction>();
    auto* tx = new libbitcoin::message::transaction;
    printf("tx: %p\n", tx);
    printf("hex_to_tx - 3\n");

    printf("tx_hex: %s\n", tx_hex);
    std::string tx_hex_cpp(tx_hex);
    printf("tx_hex_cpp: %s\n", tx_hex_cpp.c_str());
	std::vector<uint8_t> data(tx_hex_cpp.size() / 2); // (tx_hex_cpp.begin(), tx_hex_cpp.end());
	//data.reserve(tx_hex_cpp.size() / 2);

	hex2bin(tx_hex_cpp.c_str(), data.data());

    printf("hex_to_tx - 4\n");

    if (!tx->from_data(version, data)) {
        printf("hex_to_tx - 6\n");
        return nullptr;
    }

    printf("hex_to_tx - 7\n");


    // Simulate organization into our chain.
    tx->validation.simulate = true;

    printf("hex_to_tx - 8\n");

    return tx;
}


void validate_tx(executor_t exec, transaction_t tx, run_handler_t handler) {
//    exec->actual.node().chain().organize(static_cast<libbitcoin::message::transaction::const_ptr>(tx), [handler](std::error_code const& ec){
//        handler(ec.value());
//    });

    printf("validate_tx - 1\n");
    printf("tx: %p\n", tx);
    exec->actual.node().chain().organize(tx_shared(tx), [handler](std::error_code const& ec) {
        printf("validate_tx CALLBACK - 2\n");
        handler(ec.value());
    });

    printf("validate_tx - 2\n");
}

} /* extern "C" */
