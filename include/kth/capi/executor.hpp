// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#ifndef KTH_CAPI_EXECUTOR_HPP_
#define KTH_CAPI_EXECUTOR_HPP_

#ifdef KTH_USE_DOMAIN
#include <kth/infrastructure/handlers.hpp>
#else
#include <kth/domain/handlers.hpp>
#endif // KTH_USE_DOMAIN

#include <kth/node.hpp>
#include <future>
#include <iostream>

#ifdef KTH_WITH_KEOKEN
#include <kth/keoken/manager.hpp>
#include <kth/keoken/state_delegated.hpp>
#endif

namespace kth { 

#ifdef KTH_WITH_KEOKEN
    using keoken_manager_cpp_t = kth::keoken::manager<kth::keoken::state_delegated>;
#endif


namespace capi {

class executor {
public:

    executor(kth::node::configuration const& config, std::ostream& output, std::ostream& error);

    executor(executor const&) = delete;
    void operator=(executor const&) = delete;

//    bool menu();

    bool do_initchain();

    bool run(kth::handle0 handler);
    //bool run_wait(kth::handle0 handler);

    bool init_and_run(kth::handle0 handler);
   
    //static void stop(kth::code const& ec);
    //static void stop();
    bool stop();

    kth::node::full_node& node();
    kth::node::full_node const& node() const;

#ifdef KTH_WITH_KEOKEN
    keoken_manager_cpp_t const& keoken_manager() const;
    keoken_manager_cpp_t& keoken_manager();
#endif // KTH_WITH_KEOKEN

    bool load_config_valid() const;

    bool stopped() const;

private:
//    static void stop(kth::code const& ec);
    //static void handle_stop(int code);

    void handle_started(kth::code const& ec);
    void handle_running(kth::code const& ec);
    void handle_stopped(kth::code const& ec);

    void do_help();
    void do_settings();
    void do_version();
    void initialize_output();

    bool init_directory(boost::system::error_code& ec);

//    bool do_initchain();
    bool verify_directory();

    // Termination state.
    static std::promise<kth::code> stopping_;

//    parser& metadata_;
    kth::node::configuration config_;
    std::ostream& output_;
    std::ostream& error_;
    
    kth::node::full_node::ptr node_;
#ifdef KTH_WITH_KEOKEN
    std::unique_ptr<keoken_manager_cpp_t> keoken_manager_;
#endif

    kth::handle0 run_handler_;
    bool parse_config_from_file_result_;
};

// Localizable messages.
#define BN_SETTINGS_MESSAGE \
    "These are the configuration settings that can be set."
#define BN_INFORMATION_MESSAGE \
    "Runs a full bitcoin node with additional client-server query protocol."
#define BN_UNINITIALIZED_CHAIN \
    "The %1% directory is not initialized, run: kth --initchain"
#define BN_INITIALIZING_CHAIN \
    "Please wait while initializing %1% directory..."
#define BN_INITCHAIN_NEW \
    "Failed to create directory %1% with error, '%2%'."
#define BN_INITCHAIN_EXISTS \
    "Failed because the directory %1% already exists."
#define BN_INITCHAIN_TRY \
    "Failed to test directory %1% with error, '%2%'."
#define BN_INITCHAIN_COMPLETE \
    "Completed initialization."
#define BN_INITCHAIN_FAILED \
    "Error creating database files."

#define BN_NODE_INTERRUPT \
    "Press CTRL-C to stop the node."
#define BN_NODE_STARTING \
    "Please wait while the node is starting..."
#define BN_NODE_START_FAIL \
    "Node failed to start with error, %1%."
#define BN_NODE_SEEDED \
    "Seeding is complete."
#define BN_NODE_STARTED \
    "Node is started."

#define BN_NODE_SIGNALED \
    "Stop signal detected (code: %1%)."
#define BN_NODE_STOPPING \
    "Please wait while the node is stopping..."
#define BN_NODE_STOP_FAIL \
    "Node failed to stop properly, see log."
#define BN_NODE_STOPPED \
    "Node stopped successfully."

#define BN_USING_CONFIG_FILE \
    "Using config file: %1%"
#define BN_USING_DEFAULT_CONFIG \
    "Using default configuration settings."

#define BN_VERSION_MESSAGE_INIT "Node version: %1%"

#define BN_KEOKEN_MESSAGE_INIT "Keoken protocol enabled"

#define BN_CRYPTOCURRENCY_INIT "Currency: %1% - %2%"

#define BN_MICROARCHITECTURE_INIT "Compiled for microarchitecture: %1%"

#define BN_DB_TYPE_INIT "Database type: %1%"

#define BN_NETWORK_INIT "Network: %1% (%2%)"

#define BN_CORES_INIT "Configured to use %1% cores"


#define BN_LOG_HEADER \
    "================= startup %1% =================="

#if defined(KTH_DB_NEW_FULL)
#define BN_DB_TYPE "full, new version"
#elif defined(KTH_DB_NEW_BLOCKS)
#define BN_DB_TYPE "UTXO and Blocks, new version"
#elif defined(KTH_DB_NEW)
#define BN_DB_TYPE "just UTXO, new version"
#elif defined(KTH_DB_HISTORY)
#define BN_DB_TYPE "full, legacy version"
#else
#define BN_DB_TYPE "TXs and Blocks, legacy version"
#endif

} // namespace capi
} // namespace kth

#endif /* KTH_CAPI_EXECUTOR_HPP_ */
