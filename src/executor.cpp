// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/capi/executor.hpp>

#include <csignal>
#include <functional>
#include <future>
#include <iostream>
#include <memory>
#include <mutex>

#include <boost/core/null_deleter.hpp>

#include <kth/bitcoin/multi_crypto_support.hpp>
#include <kth/node.hpp>
#include <kth/node/parser.hpp>

#include <kth/capi/version.h>

namespace kth { namespace capi {

using boost::format;
using boost::null_deleter;
using boost::system::error_code;
// using bc::chain::block;
using bc::database::data_base;
using std::placeholders::_1;

static constexpr int initialize_stop = 0;
static constexpr int directory_exists = 0;
static constexpr int directory_not_found = 2;

std::promise<kth::code> executor::stopping_; //NOLINT

executor::executor(kth::node::configuration const& config, std::ostream& output, std::ostream& error)
    : config_(config), output_(output), error_(error)
{
	
    kth::node::parser metadata(kth::config::settings::mainnet);
    parse_config_from_file_result_ = metadata.parse_from_file(config_.file, std::cerr);
  
    config_ = metadata.configured;

    auto const& network = config_.network;
    auto const verbose = network.verbose;

    kth::log::rotable_file const debug_file {
                    network.debug_file,
                    network.archive_directory,
                    network.rotation_size,
                    network.maximum_archive_size,
                    network.minimum_free_space,
                    network.maximum_archive_files
    };

    kth::log::rotable_file const error_file {
                    network.error_file,
                    network.archive_directory,
                    network.rotation_size,
                    network.maximum_archive_size,
                    network.minimum_free_space,
                    network.maximum_archive_files
    };

    kth::log::stream console_out(&output_, null_deleter());
    kth::log::stream console_err(&error_, null_deleter());

    kth::log::initialize(debug_file, error_file, console_out, console_err, verbose);
}

bool executor::init_directory(error_code& ec) {
    
    auto const& directory = config_.database.directory;
  
    if (create_directories(directory, ec)) {
        LOG_INFO(LOG_NODE) << format(BN_INITIALIZING_CHAIN) % directory;

        auto const genesis = kth::node::full_node::get_genesis_block(config_.chain);
        auto const& settings = config_.database;
        auto const result = data_base(settings).create(genesis);

        if ( ! result ) {
            LOG_INFO(LOG_NODE) << BN_INITCHAIN_FAILED;
            return false;
        }

        LOG_INFO(LOG_NODE) << BN_INITCHAIN_COMPLETE;
        return true;
    }

    return false;
}

// Emit to the log.
bool executor::do_initchain() {
    initialize_output();

    error_code ec;
    
    if (init_directory(ec)) {
        return true;
    }
    
    auto const& directory = config_.database.directory;

    if (ec.value() == directory_exists) {
        LOG_ERROR(LOG_NODE) << format(BN_INITCHAIN_EXISTS) % directory;
        return false;
    }

    LOG_ERROR(LOG_NODE) << format(BN_INITCHAIN_NEW) % directory % ec.message();
    return false;
}

// Run.
// ----------------------------------------------------------------------------

kth::node::full_node& executor::node() {
    return *node_;
}

kth::node::full_node const& executor::node() const {
    return *node_;
}

#ifdef KTH_WITH_KEOKEN
keoken_manager_cpp_t& executor::keoken_manager() {
    return *keoken_manager_;
}

keoken_manager_cpp_t const& executor::keoken_manager() const {
    return *keoken_manager_;
}
#endif // KTH_WITH_KEOKEN


bool executor::load_config_valid() const {
    return parse_config_from_file_result_;
}

bool executor::run(kth::handle0 handler) {

    run_handler_ = std::move(handler);

    initialize_output();

    LOG_INFO(LOG_NODE) << BN_NODE_INTERRUPT;
    LOG_INFO(LOG_NODE) << BN_NODE_STARTING;

    if (!verify_directory()) {
        return false;
    }

    // Now that the directory is verified we can create the node for it.
    node_ = std::make_shared<kth::node::full_node>(config_);


#ifdef KTH_WITH_KEOKEN
    keoken_manager_.reset(new keoken_manager_cpp_t(node_->chain_kth(), config_.node.keoken_genesis_height));    //NOLINT
#endif

    // Initialize broadcast to statistics server if configured.
    kth::log::initialize_statsd(node_->thread_pool(), config_.network.statistics_server);

    // The callback may be returned on the same thread.
    node_->start(std::bind(&executor::handle_started, this, _1));

    return true;
}

bool executor::init_and_run(kth::handle0 handler) {
    
    run_handler_ = std::move(handler);

    initialize_output();

    LOG_INFO(LOG_NODE) << BN_NODE_INTERRUPT;
    LOG_INFO(LOG_NODE) << BN_NODE_STARTING;

    if ( ! verify_directory() ) {
        error_code ec;
        
        if ( ! init_directory(ec) ) {
            auto const& directory = config_.database.directory;
            LOG_ERROR(LOG_NODE) << format(BN_INITCHAIN_NEW) % directory % ec.message();
            return false;
        }
    }

    // Now that the directory is verified we can create the node for it.
    node_ = std::make_shared<kth::node::full_node>(config_);

    #ifdef KTH_WITH_KEOKEN
        keoken_manager_.reset(new keoken_manager_cpp_t(node_->chain_kth(), config_.node.keoken_genesis_height));    //NOLINT
    #endif

    // Initialize broadcast to statistics server if configured.
    kth::log::initialize_statsd(node_->thread_pool(), config_.network.statistics_server);

    // The callback may be returned on the same thread.
    node_->start(std::bind(&executor::handle_started, this, _1));

    return true;
}

// bool executor::run_wait(kth::handle0 handler) {

//     run(std::move(handler));

//     // Wait for stop.
//     stopping_.get_future().wait();

//     LOG_INFO(LOG_NODE) << BN_NODE_STOPPING;

//     // Close must be called from main thread.
//     if (node_->close()) {
//         LOG_INFO(LOG_NODE) << BN_NODE_STOPPED;
//     } else {
//         LOG_INFO(LOG_NODE) << BN_NODE_STOP_FAIL;
//     }

//     return true;
// }

// Handle the completion of the start sequence and begin the run sequence.
void executor::handle_started(kth::code const& ec) {
    if (ec) {
        LOG_ERROR(LOG_NODE) << format(BN_NODE_START_FAIL) % ec.message();
//        stop(ec);

        if (run_handler_) {
            run_handler_(ec);
        }
        return;
    }

    LOG_INFO(LOG_NODE) << BN_NODE_SEEDED;

    // This is the beginning of the stop sequence.
    node_->subscribe_stop(std::bind(&executor::handle_stopped, this, _1));

    // This is the beginning of the run sequence.
    node_->run(std::bind(&executor::handle_running, this, _1));
}

// This is the end of the run sequence.
void executor::handle_running(kth::code const& ec) {
    if (ec) {
        LOG_INFO(LOG_NODE) << format(BN_NODE_START_FAIL) % ec.message();
//        stop(ec);

        if (run_handler_) {
            run_handler_(ec);
        }

        return;
    }

    LOG_INFO(LOG_NODE) << BN_NODE_STARTED;

    if (run_handler_) {
        run_handler_(ec);
    }
}

// This is the end of the stop sequence.
void executor::handle_stopped(kth::code const&  /*ec*/) {
    //stop(ec);
    
    //stop();

}

// Stop signal.
// ----------------------------------------------------------------------------

//void executor::handle_stop(int code) {
//    // Reinitialize after each capture to prevent hard shutdown.
//    // Do not capture failure signals as calling stop can cause flush lock file
//    // to clear due to the aborted thread dropping the flush lock mutex.
//    //std::signal(SIGINT, handle_stop);
//    //std::signal(SIGTERM, handle_stop);
//
//    if (code == initialize_stop) {
//        return;
//    }
//
//    LOG_INFO(LOG_NODE) << format(BN_NODE_SIGNALED) % code;
//    //stop(kth::error::success);
//    stop();
//    node_
//}

//// Manage the race between console stop and server stop.
//void executor::stop(kth::code const& ec) {
//    static std::once_flag stop_mutex;
//    std::call_once(stop_mutex, [&]() { stopping_.set_value(ec); });
//}

//void executor::stop() {
//    stop(kth::error::success);
//}

bool executor::stop() {
    // std::cout << "executor::stop() - 1\n";
    bool res = node_->stop();
    // std::cout << "executor::stop() - 2\n";
    return res;
}

bool executor::stopped() const {
    return node_->stopped();
}

// Utilities.
// ----------------------------------------------------------------------------

// Set up logging.
void executor::initialize_output() {
    auto const header = format(BN_LOG_HEADER) % kth::local_time();

    LOG_DEBUG(LOG_NODE) << header;
    LOG_INFO(LOG_NODE) << header;
    LOG_WARNING(LOG_NODE) << header;
    LOG_ERROR(LOG_NODE) << header;
    LOG_FATAL(LOG_NODE) << header;

    auto const& file = config_.file;

    if (file.empty()) {
        LOG_INFO(LOG_NODE) << BN_USING_DEFAULT_CONFIG;
    } else {
        LOG_INFO(LOG_NODE) << format(BN_USING_CONFIG_FILE) % file;
    }

    LOG_INFO(LOG_NODE) << format(BN_VERSION_MESSAGE_INIT) % KTH_CAPI_VERSION;
    LOG_INFO(LOG_NODE) << format(BN_CRYPTOCURRENCY_INIT) % KTH_CURRENCY_SYMBOL_STR % KTH_CURRENCY_STR;
#ifdef KTH_WITH_KEOKEN
    LOG_INFO(LOG_NODE) << format(BN_KEOKEN_MESSAGE_INIT);
#endif

    LOG_INFO(LOG_NODE) << format(BN_MICROARCHITECTURE_INIT) % KTH_MICROARCHITECTURE_STR;

    LOG_INFO(LOG_NODE) << format(BN_DB_TYPE_INIT) % BN_DB_TYPE;

    LOG_INFO(LOG_NODE) << format(BN_NETWORK_INIT) % 
            (kth::get_network(config_.network.identifier) == kth::config::settings::testnet ? "Testnet" : "Mainnet") %
            config_.network.identifier;
  
    LOG_INFO(LOG_NODE) << format(BN_CORES_INIT) % kth::thread_ceiling(config_.chain.cores);
}

// Use missing directory as a sentinel indicating lack of initialization.
bool executor::verify_directory() {
    error_code ec;
    auto const& directory = config_.database.directory;

    if (exists(directory, ec)) {
        return true;
    }

    if (ec.value() == directory_not_found) {
        LOG_ERROR(LOG_NODE) << format(BN_UNINITIALIZED_CHAIN) % directory;
        return false;
    }

    auto const message = ec.message();
    LOG_ERROR(LOG_NODE) << format(BN_INITCHAIN_TRY) % directory % message;
    return false;
}

} // namespace capi
} // namespace kth
