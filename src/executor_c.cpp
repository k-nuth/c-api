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
#include <memory>
#include <boost/iostreams/device/file_descriptor.hpp>
#include <bitprim/nodecint/executor.hpp>
#include <inttypes.h>   //TODO: Remove, it is for the printf (printing pointer addresses)


libbitcoin::node::configuration make_config(char const* path) {
    libbitcoin::node::configuration config(libbitcoin::config::settings::mainnet);
    config.file = boost::filesystem::path(path);
    return config;
}

extern "C" {

struct header {

};

struct executor {

    // template <typename... Args>
    // node(Args&&... args)
    //     : actual(std::forward<Args>(args)...)
    // {}

    executor(char const* path, FILE* sin, FILE* sout, FILE* serr)
        //: actual(path)
        : sin_buffer_(boost::iostreams::file_descriptor_source(fileno(sin), boost::iostreams::never_close_handle))
        , sout_buffer_(boost::iostreams::file_descriptor_sink(fileno(sout), boost::iostreams::never_close_handle))
        , serr_buffer_(boost::iostreams::file_descriptor_sink(fileno(serr), boost::iostreams::never_close_handle))
        , sin_(&sin_buffer_)
        , sout_(&sout_buffer_)
        , serr_(&serr_buffer_)
//        , actual(libbitcoin::node::configuration(libbitcoin::config::settings::mainnet), sin_, sout_, serr_)
        , actual(make_config(path), sin_, sout_, serr_)
    {
        std::ostream os(&sout_buffer_);
        os << "Hello World!" << std::endl;
    }

    executor(char const* path, int sin_fd, int sout_fd, int serr_fd)
        : sin_buffer_(boost::iostreams::file_descriptor_source(sin_fd, boost::iostreams::never_close_handle))
          , sout_buffer_(boost::iostreams::file_descriptor_sink(sout_fd, boost::iostreams::never_close_handle))
          , serr_buffer_(boost::iostreams::file_descriptor_sink(serr_fd, boost::iostreams::never_close_handle))
          , sin_(&sin_buffer_)
          , sout_(&sout_buffer_)
          , serr_(&serr_buffer_)
          , actual(make_config(path), sin_, sout_, serr_)
    {
        std::ostream os(&sout_buffer_);
        os << "Hello World -- 2!" << std::endl;
    }



    boost::iostreams::stream_buffer<boost::iostreams::file_descriptor_source> sin_buffer_;
    boost::iostreams::stream_buffer<boost::iostreams::file_descriptor_sink> sout_buffer_;
    boost::iostreams::stream_buffer<boost::iostreams::file_descriptor_sink> serr_buffer_;

    std::istream sin_;
    std::ostream sout_;
    std::ostream serr_;

    bitprim::nodecint::executor actual;
};

executor_t executor_construct(char const* path, FILE* sin, FILE* sout, FILE* serr) {
    return std::make_unique<executor>(path, sin, sout, serr).release();
}

executor_t executor_construct_fd(char const* path, int sin_fd, int sout_fd, int serr_fd) {
    return std::make_unique<executor>(path, sin_fd, sout_fd, serr_fd).release();
}

void executor_destruct(executor_t exec) {
    std::cout << "From C++: executor_destruct\n";
    printf("executor_destruct - exec: 0x%" PRIXPTR "\n", (uintptr_t)exec);

    delete exec;
}

int executor_initchain(executor_t exec) {
    return exec->actual.do_initchain();
}

int executor_run(executor_t exec) {
    return exec->actual.run();
}

int executor_run_wait(executor_t exec) {
    return exec->actual.run_wait();
}

void executor_stop(executor_t exec) {
    exec->actual.stop();
}







void fetch_last_height(executor_t exec, last_height_fetch_handler_t handler) {
    exec->actual.node().chain().fetch_last_height([handler](std::error_code const& ec, size_t h) {
        handler(ec.value(), h);
    });
}

void fetch_block_height(executor_t exec, hash_t hash, block_height_fetch_handler_t handler) {

    libbitcoin::hash_digest hash_cpp;
    std::copy_n(hash, hash_cpp.size(), std::begin(hash_cpp));

    exec->actual.node().chain().fetch_block_height(hash_cpp, [handler](std::error_code const& ec, size_t h) {
        handler(ec.value(), h);
    });
}

void fetch_block_header(executor_t exec, size_t height, block_header_fetch_handler_t handler) {
    exec->actual.node().chain().fetch_block_header(height, [handler](std::error_code const& ec, libbitcoin::message::header::ptr header, size_t h) {
        auto new_header = new libbitcoin::message::header(*header.get());
//        auto new_header = std::make_unique(*header.get()).release();
        //Note: It is the responsability of the user to release/destruct the object
        handler(ec.value(), new_header, h);
    });
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

void fetch_block(executor_t exec, size_t height, block_fetch_handler_t handler) {
    exec->actual.node().chain().fetch_block(height, [handler](std::error_code const& ec, libbitcoin::message::block::ptr block, size_t h) {
        auto new_block = new libbitcoin::message::block(*block.get());
//        auto new_block = std::make_unique(*block.get()).release();
        //Note: It is the responsability of the user to release/destruct the object
        handler(ec.value(), new_block, h);
    });
}

void fetch_block_by_hash(executor_t exec, hash_t hash, block_fetch_handler_t handler) {

    libbitcoin::hash_digest hash_cpp;
    std::copy_n(hash, hash_cpp.size(), std::begin(hash_cpp));

    exec->actual.node().chain().fetch_block(hash_cpp, [handler](std::error_code const& ec, libbitcoin::message::block::ptr block, size_t h) {
        auto new_block = new libbitcoin::message::block(*block.get());
//        auto new_block = std::make_unique(*block.get()).release();
        //Note: It is the responsability of the user to release/destruct the object
        handler(ec.value(), new_block, h);
    });
}

//virtual void fetch_transaction(const hash_digest& hash,
//                               bool require_confirmed, transaction_fetch_handler handler) const = 0;


void fetch_transaction(executor_t exec, hash_t hash, int require_confirmed, transaction_fetch_handler_t handler) {

    libbitcoin::hash_digest hash_cpp;
    std::copy_n(hash, hash_cpp.size(), std::begin(hash_cpp));

    exec->actual.node().chain().fetch_transaction(hash_cpp, require_confirmed, [handler](std::error_code const& ec, libbitcoin::message::transaction::ptr transaction, size_t h, size_t i) {
        auto new_transaction = new libbitcoin::message::transaction(*transaction.get());
        handler(ec.value(), new_transaction, h, i);
    });
}

// ------------------------------------------------
// Header
// ------------------------------------------------

void header_destruct(header_t header) {
    auto header_cpp = static_cast<libbitcoin::message::header*>(header);
    delete header_cpp;
}

int header_is_valid(header_t header) {
    return static_cast<libbitcoin::message::header const*>(header)->is_valid();
}

uint32_t header_version(header_t header) {
    return static_cast<libbitcoin::message::header const*>(header)->version();
}

void header_set_version(header_t header, uint32_t version) {
    return static_cast<libbitcoin::message::header*>(header)->set_version(version);
}

uint32_t header_timestamp(header_t header) {
    return static_cast<libbitcoin::message::header const*>(header)->timestamp();
}

void header_set_timestamp(header_t header, uint32_t timestamp) {
    return static_cast<libbitcoin::message::header*>(header)->set_timestamp(timestamp);
}

uint32_t header_bits(header_t header) {
    return static_cast<libbitcoin::message::header const*>(header)->bits();
}

void header_set_bits(header_t header, uint32_t bits) {
    return static_cast<libbitcoin::message::header*>(header)->set_bits(bits);
}

uint32_t header_nonce(header_t header) {
    return static_cast<libbitcoin::message::header const*>(header)->nonce();
}

void header_set_nonce(header_t header, uint32_t nonce) {
    return static_cast<libbitcoin::message::header*>(header)->set_nonce(nonce);
}

hash_t header_previous_block_hash(header_t header) {
    auto hash_cpp = static_cast<libbitcoin::message::header const*>(header)->previous_block_hash();
    return hash_cpp.data();
}

hash_t header_merkle(header_t header) {
    auto hash_cpp = static_cast<libbitcoin::message::header const*>(header)->merkle();
    return hash_cpp.data();
}

hash_t header_hash(header_t header) {
    auto hash_cpp = static_cast<libbitcoin::message::header const*>(header)->hash();
    return hash_cpp.data();
}


//const hash_digest& () const;
//void set_previous_block_hash(const hash_digest& value);





//// Serialization.
////-----------------------------------------------------------------------------
//
//data_chunk to_data() const;
//void to_data(std::ostream& stream) const;
//void to_data(writer& sink) const;
//
//// Properties (size, accessors, cache).
////-----------------------------------------------------------------------------
//
//static size_t satoshi_fixed_size();
//size_t serialized_size() const;
//
//
//void set_previous_block_hash(const hash_digest& value);
//void set_previous_block_hash(hash_digest&& value);
//
//
//void set_merkle(const hash_digest& value);
//void set_merkle(hash_digest&& value);
//

//
//#ifdef LITECOIN
//hash_digest litecoin_proof_of_work_hash() const;
//#endif
//
//// Validation.
////-----------------------------------------------------------------------------
//
//bool is_valid_time_stamp() const;
//bool is_valid_proof_of_work() const;
//
//code check() const;
//code accept(const chain_state& state) const;



// ------------------------------------------------
// Block
// ------------------------------------------------

void block_destruct(block_t block) {
    auto block_cpp = static_cast<libbitcoin::message::block*>(block);
    delete block_cpp;
}

int block_is_valid(block_t block) {
    return static_cast<libbitcoin::message::block const*>(block)->is_valid();
}

header_t block_header(block_t block) {
    auto& header = static_cast<libbitcoin::message::block*>(block)->header();
    return &header;
}

hash_t block_hash(block_t block) {
    auto hash_cpp = static_cast<libbitcoin::message::block const*>(block)->hash();
    return hash_cpp.data();
}

size_t block_transaction_count(block_t block) {
    return static_cast<libbitcoin::message::block const*>(block)->transactions().size();
}

transaction_t block_transactions(block_t block, size_t* n) {
    auto* block_cpp = static_cast<libbitcoin::message::block*>(block);
    *n = block_cpp->transactions().size();
    return block_cpp->transactions().data();
}

transaction_t block_transaction_next(transaction_t transaction) {
    auto* transaction_cpp = static_cast<libbitcoin::message::transaction*>(transaction);
    ++transaction_cpp;
    return transaction_cpp;
}


//
//bool from_data(const data_chunk& data);
//bool from_data(std::istream& stream);
//bool from_data(reader& source);
//
//
//// Serialization.
////-------------------------------------------------------------------------
//
//data_chunk to_data() const;
//void to_data(std::ostream& stream) const;
//void to_data(writer& sink) const;
//hash_list to_hashes() const;
//
//// Properties (size, accessors, cache).
////-------------------------------------------------------------------------
//
//size_t serialized_size() const;
//
//void set_header(const chain::header& value);
//void set_header(chain::header&& value);
//
//// deprecated (unsafe)
//transaction::list& transactions();
//
//const transaction::list& transactions() const;
//void set_transactions(const transaction::list& value);
//void set_transactions(transaction::list&& value);
//
//

//// Validation.
////-------------------------------------------------------------------------
//
//static uint64_t subsidy(size_t height);
//static uint256_t proof(uint32_t bits);
//
//uint64_t fees() const;
//uint64_t claim() const;
//uint64_t reward(size_t height) const;
//uint256_t proof() const;
//hash_digest generate_merkle_root() const;
//size_t signature_operations() const;
//size_t signature_operations(bool bip16_active) const;
//size_t total_inputs(bool with_coinbase=true) const;
//
//bool is_extra_coinbases() const;
//bool is_final(size_t height) const;
//bool is_distinct_transaction_set() const;
//bool is_valid_coinbase_claim(size_t height) const;
//bool is_valid_coinbase_script(size_t height) const;
//bool is_internal_double_spend() const;
//bool is_valid_merkle_root() const;
//
//code check() const;
//code check_transactions() const;
//code accept(bool transactions=true) const;
//code accept(const chain_state& state, bool transactions=true) const;
//code accept_transactions(const chain_state& state) const;
//code connect() const;
//code connect(const chain_state& state) const;
//code connect_transactions(const chain_state& state) const;


// ------------------------------------------------
// Transaction
// ------------------------------------------------

void transaction_destruct(transaction_t transaction) {
    auto transaction_cpp = static_cast<libbitcoin::message::transaction*>(transaction);
    delete transaction_cpp;
}

int transaction_is_valid(transaction_t transaction) {
    return static_cast<libbitcoin::message::transaction const*>(transaction)->is_valid();
}

uint32_t transaction_version(transaction_t transaction) {
    return static_cast<libbitcoin::message::transaction const*>(transaction)->version();
}

void transaction_set_version(transaction_t transaction, uint32_t version) {
    return static_cast<libbitcoin::message::transaction*>(transaction)->set_version(version);
}

hash_t transaction_hash(transaction_t transaction) {
    auto hash_cpp = static_cast<libbitcoin::message::transaction const*>(transaction)->hash();
    return hash_cpp.data();
}


//
//// Serialization.
////-----------------------------------------------------------------------------
//
//data_chunk to_data(bool wire=true) const;
//void to_data(std::ostream& stream, bool wire=true) const;
//void to_data(writer& sink, bool wire=true) const;
//
//// Properties (size, accessors, cache).
////-----------------------------------------------------------------------------
//
//size_t serialized_size(bool wire=true) const;
//
//uint32_t version() const;
//void set_version(uint32_t value);
//
//uint32_t locktime() const;
//void set_locktime(uint32_t value);
//
//// Deprecated (unsafe).
//ins& inputs();
//
//const input::list& inputs() const;
//void set_inputs(const ins& value);
//void set_inputs(ins&& value);
//
//// Deprecated (unsafe).
//outs& outputs();
//
//const outs& outputs() const;
//void set_outputs(const outs& value);
//void set_outputs(outs&& value);
//
//hash_digest hash() const;
//hash_digest hash(uint32_t sighash_type) const;
//
//void recompute_hash();
//
//// Validation.
////-----------------------------------------------------------------------------
//
//uint64_t fees() const;
//output_point::list missing_previous_outputs() const;
//hash_list missing_previous_transactions() const;
//uint64_t total_input_value() const;
//uint64_t total_output_value() const;
//size_t signature_operations() const;
//size_t signature_operations(bool bip16_active) const;
//
//bool is_coinbase() const;
//bool is_null_non_coinbase() const;
//bool is_oversized_coinbase() const;
//bool is_immature(size_t target_height) const;
//bool is_overspent() const;
//bool is_double_spend(bool include_unconfirmed) const;
//bool is_missing_previous_outputs() const;
//bool is_final(size_t block_height, uint32_t block_time) const;
//bool is_locktime_conflict() const;
//
//code check(bool transaction_pool=true) const;
//code accept(bool transaction_pool=true) const;
//code accept(const chain_state& state, bool transaction_pool=true) const;
//code connect() const;
//code connect(const chain_state& state) const;
//code connect_input(const chain_state& state, size_t input_index) const;


} /* extern "C" */
