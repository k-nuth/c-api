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

#include <kth/domain/multi_crypto_support.hpp>
#include <kth/node.hpp>
#include <kth/node/parser.hpp>

#include <kth/capi/version.h>

namespace kth::capi {

using boost::null_deleter;
using std::error_code;
// using bc::chain::block;
using kth::database::data_base;
using std::placeholders::_1;

static constexpr int initialize_stop = 0;
static constexpr int directory_exists = 0;
static constexpr int directory_not_found = 2;

std::promise<kth::code> executor::stopping_; //NOLINT

executor::executor(kth::node::configuration const& config, std::ostream& output, std::ostream& error)
    : config_(config), output_(output), error_(error)
{
    auto const& network = config_.network;
    auto const verbose = network.verbose;

//TODO(fernando): implement this for spdlog and binlog
#if defined(KTH_LOG_LIBRARY_BOOST)
    kth::log::rotable_file const debug_file {
                    network.debug_file.string(),
                    network.archive_directory.string(),
                    network.rotation_size,
                    network.maximum_archive_size,
                    network.minimum_free_space,
                    network.maximum_archive_files
    };

    kth::log::rotable_file const error_file {
                    network.error_file.string(),
                    network.archive_directory.string(),
                    network.rotation_size,
                    network.maximum_archive_size,
                    network.minimum_free_space,
                    network.maximum_archive_files
    };

    kth::log::stream console_out(&output_, null_deleter());
    kth::log::stream console_err(&error_, null_deleter());
    kth::log::initialize(debug_file, error_file, console_out, console_err, verbose);
#endif
}

#if ! defined(KTH_DB_READONLY)
bool executor::init_directory(error_code& ec) {
    
    auto const& directory = config_.database.directory;
  
    if (create_directories(directory, ec)) {
        LOG_INFO(LOG_NODE, fmt::format(KTH_INITIALIZING_CHAIN, directory.string()));
        // auto const genesis = kth::node::full_node::get_genesis_block(config_.chain);
        auto const genesis = kth::node::full_node::get_genesis_block(get_network(config_.network.identifier));
        auto const& settings = config_.database;
        auto const result = data_base(settings).create(genesis);

        if ( ! result ) {
            LOG_INFO(LOG_NODE, KTH_INITCHAIN_FAILED);
            return false;
        }

        LOG_INFO(LOG_NODE, KTH_INITCHAIN_COMPLETE);
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
        LOG_ERROR(LOG_NODE, fmt::format(KTH_INITCHAIN_EXISTS, directory.string()));
        return false;
    }

    LOG_ERROR(LOG_NODE, fmt::format(KTH_INITCHAIN_NEW, directory.string(), ec.message()));
    return false;
}
#endif // ! defined(KTH_DB_READONLY)

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

bool executor::run(kth::handle0 handler) {

    run_handler_ = std::move(handler);

    initialize_output();

    LOG_INFO(LOG_NODE, KTH_NODE_INTERRUPT);
    LOG_INFO(LOG_NODE, KTH_NODE_STARTING);

    if ( ! verify_directory()) {
        return false;
    }

    // Now that the directory is verified we can create the node for it.
    node_ = std::make_shared<kth::node::full_node>(config_);


#ifdef KTH_WITH_KEOKEN
    keoken_manager_.reset(new keoken_manager_cpp_t(node_->chain_kth(), config_.node.keoken_genesis_height));    //NOLINT
#endif

//TODO(fernando): implement this for spdlog and binlog
#if defined(KTH_LOG_LIBRARY_BOOST)
    // Initialize broadcast to statistics server if configured.
    kth::log::initialize_statsd(node_->thread_pool(), config_.network.statistics_server);
#endif

    // The callback may be returned on the same thread.
    node_->start(std::bind(&executor::handle_started, this, _1));

    return true;
}

#if ! defined(KTH_DB_READONLY)
bool executor::init_and_run(kth::handle0 handler) {
    
    run_handler_ = std::move(handler);

    initialize_output();

    LOG_INFO(LOG_NODE, KTH_NODE_INTERRUPT);
    LOG_INFO(LOG_NODE, KTH_NODE_STARTING);

    if ( ! verify_directory() ) {
        error_code ec;
        
        if ( ! init_directory(ec) ) {
            auto const& directory = config_.database.directory;
            LOG_ERROR(LOG_NODE, fmt::format(KTH_INITCHAIN_NEW, directory.string(), ec.message()));
            return false;
        }
    }

    // Now that the directory is verified we can create the node for it.
    node_ = std::make_shared<kth::node::full_node>(config_);

#ifdef KTH_WITH_KEOKEN
    keoken_manager_.reset(new keoken_manager_cpp_t(node_->chain_kth(), config_.node.keoken_genesis_height));    //NOLINT
#endif

//TODO(fernando): implement this for spdlog and binlog
#if defined(KTH_LOG_LIBRARY_BOOST)
    // Initialize broadcast to statistics server if configured.
    kth::log::initialize_statsd(node_->thread_pool(), config_.network.statistics_server);
#endif

    // The callback may be returned on the same thread.
    node_->start(std::bind(&executor::handle_started, this, _1));

    return true;
}

bool executor::init_run_and_wait_for_signal(kth::handle0 handler) {
    run_handler_ = std::move(handler);

    initialize_output();

    LOG_INFO(LOG_NODE, KTH_NODE_INTERRUPT);
    LOG_INFO(LOG_NODE, KTH_NODE_STARTING);

    if ( ! verify_directory() ) {
        error_code ec;
        
        if ( ! init_directory(ec) ) {
            auto const& directory = config_.database.directory;
            LOG_ERROR(LOG_NODE, fmt::format(KTH_INITCHAIN_NEW, directory.string(), ec.message()));
            return false;
        }
    }

    // Now that the directory is verified we can create the node for it.
    node_ = std::make_shared<kth::node::full_node>(config_);

#ifdef KTH_WITH_KEOKEN
    keoken_manager_.reset(new keoken_manager_cpp_t(node_->chain_kth(), config_.node.keoken_genesis_height));    //NOLINT
#endif

//TODO(fernando): implement this for spdlog and binlog
#if defined(KTH_LOG_LIBRARY_BOOST)
    // Initialize broadcast to statistics server if configured.
    kth::log::initialize_statsd(node_->thread_pool(), config_.network.statistics_server);
#endif

    // The callback may be returned on the same thread.
    node_->start(std::bind(&executor::handle_started, this, _1));

    // Wait for stop.
    stopping_.get_future().wait();

    LOG_INFO(LOG_NODE, KTH_NODE_STOPPING);

    // Close must be called from main thread.
    if (node_->close()) {
        LOG_INFO(LOG_NODE, KTH_NODE_STOPPED);
    } else {
        LOG_INFO(LOG_NODE, KTH_NODE_STOP_FAIL);
    }

    return true;
}
#endif // ! defined(KTH_DB_READONLY)

// bool executor::run_wait(kth::handle0 handler) {

//     run(std::move(handler));

//     // Wait for stop.
//     stopping_.get_future().wait();

//     LOG_INFO(LOG_NODE, KTH_NODE_STOPPING);

//     // Close must be called from main thread.
//     if (node_->close()) {
//         LOG_INFO(LOG_NODE, KTH_NODE_STOPPED);
//     } else {
//         LOG_INFO(LOG_NODE, KTH_NODE_STOP_FAIL);
//     }

//     return true;
// }

// Handle the completion of the start sequence and begin the run sequence.
void executor::handle_started(kth::code const& ec) {
    if (ec) {
        LOG_ERROR(LOG_NODE, fmt::format(KTH_NODE_START_FAIL, ec.message()));
//        stop(ec);

        if (run_handler_) {
            run_handler_(ec);
        }
        return;
    }

    LOG_INFO(LOG_NODE, KTH_NODE_SEEDED);

    // This is the beginning of the stop sequence.
    node_->subscribe_stop(std::bind(&executor::handle_stopped, this, _1));

    // This is the beginning of the run sequence.
    node_->run(std::bind(&executor::handle_running, this, _1));
}

// This is the end of the run sequence.
void executor::handle_running(kth::code const& ec) {
    if (ec) {
        LOG_INFO(LOG_NODE, fmt::format(KTH_NODE_START_FAIL, ec.message()));
//        stop(ec);

        if (run_handler_) {
            run_handler_(ec);
        }

        return;
    }

    LOG_INFO(LOG_NODE, KTH_NODE_STARTED);

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

bool executor::stop() {
    bool res = node_->stop();
    return res;
}

// Manage the race between console stop and server stop.
void executor::signal_stop() {
    static std::once_flag stop_mutex;
    std::call_once(stop_mutex, [&](){ stopping_.set_value(kth::code()); });
}

bool executor::stopped() const {
    return node_->stopped();
}

// Utilities.
// ----------------------------------------------------------------------------

// Set up logging.
void executor::initialize_output() {
    // auto const header = fmt::format(KTH_LOG_HEADER, kth::local_time());

    // LOG_DEBUG(LOG_NODE, header);
    // LOG_INFO(LOG_NODE, header);
    // LOG_WARNING(LOG_NODE, header);
    // LOG_ERROR(LOG_NODE, header);
    // LOG_FATAL(LOG_NODE, header);

    auto const& file = config_.file;

    if (file.empty()) {
        LOG_INFO(LOG_NODE, KTH_USING_DEFAULT_CONFIG);
    } else {
        LOG_INFO(LOG_NODE, fmt::format(KTH_USING_CONFIG_FILE, file.string()));
    }

    LOG_INFO(LOG_NODE, fmt::format(KTH_VERSION_MESSAGE_INIT, KTH_CAPI_VERSION));
    LOG_INFO(LOG_NODE, fmt::format(KTH_CRYPTOCURRENCY_INIT, KTH_CURRENCY_SYMBOL_STR, KTH_CURRENCY_STR));
#ifdef KTH_WITH_KEOKEN
    LOG_INFO(LOG_NODE, fmt::format(KTH_KEOKEN_MESSAGE_INIT)));
#endif

    LOG_INFO(LOG_NODE, fmt::format(KTH_MICROARCHITECTURE_INIT, KTH_MICROARCHITECTURE_STR));
    LOG_INFO(LOG_NODE, fmt::format(KTH_DB_TYPE_INIT, KTH_DB_TYPE));
    LOG_INFO(LOG_NODE, fmt::format(KTH_NETWORK_INIT, name(kth::get_network(config_.network.identifier)), config_.network.identifier));
    LOG_INFO(LOG_NODE, fmt::format(KTH_CORES_INIT, kth::thread_ceiling(config_.chain.cores)));
}

// Use missing directory as a sentinel indicating lack of initialization.
bool executor::verify_directory() {
    error_code ec;
    auto const& directory = config_.database.directory;

    if (exists(directory, ec)) {
        return true;
    }

    if (ec.value() == directory_not_found) {
        LOG_ERROR(LOG_NODE, fmt::format(KTH_UNINITIALIZED_CHAIN, directory.string()));
        return false;
    }

    auto const message = ec.message();
    LOG_ERROR(LOG_NODE, fmt::format(KTH_INITkth_chain_tRY, directory.string(), message));
    return false;
}

} // namespace kth::capi
