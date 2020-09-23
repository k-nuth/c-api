// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_CAPI_EXECUTOR_HPP_
#define KTH_CAPI_EXECUTOR_HPP_

#include <kth/infrastructure/handlers.hpp>

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

#if ! defined(KTH_DB_READONLY)
    bool do_initchain();
#endif // ! defined(KTH_DB_READONLY)    

    bool run(kth::handle0 handler);
    //bool run_wait(kth::handle0 handler);

#if ! defined(KTH_DB_READONLY)
    bool init_and_run(kth::handle0 handler);
    bool init_run_and_wait_for_signal(kth::handle0 handler);
#endif // ! defined(KTH_DB_READONLY)   

    //static void stop(kth::code const& ec);
    //static void stop();
    bool stop();
    void signal_stop();

    kth::node::full_node& node();
    kth::node::full_node const& node() const;

#ifdef KTH_WITH_KEOKEN
    keoken_manager_cpp_t const& keoken_manager() const;
    keoken_manager_cpp_t& keoken_manager();
#endif // KTH_WITH_KEOKEN

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

#if ! defined(KTH_DB_READONLY)
    bool init_directory(std::error_code& ec);
#endif // ! defined(KTH_DB_READONLY)

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
};

// Localizable messages.
#define KTH_SETTINGS_MESSAGE "These are the configuration settings that can be set."
#define KTH_INFORMATION_MESSAGE "Runs a full bitcoin node with additional client-server query protocol."
#define KTH_UNINITIALIZED_CHAIN "The {} directory is not initialized, run: kth --initchain"
#define KTH_INITIALIZING_CHAIN "Please wait while initializing {} directory..."
#define KTH_INITCHAIN_NEW "Failed to create directory {} with error, '{}'."
#define KTH_INITCHAIN_EXISTS "Failed because the directory {} already exists."
#define KTH_INITkth_chain_tRY "Failed to test directory {} with error, '{}'."
#define KTH_INITCHAIN_COMPLETE "Completed initialization."
#define KTH_INITCHAIN_FAILED "Error creating database files."

#define KTH_NODE_INTERRUPT "Press CTRL-C to stop the node."
#define KTH_NODE_STARTING "Please wait while the node is starting..."
#define KTH_NODE_START_FAIL "Node failed to start with error, {}."
#define KTH_NODE_SEEDED "Seeding is complete."
#define KTH_NODE_STARTED "Node is started."

#define KTH_NODE_SIGNALED "Stop signal detected (code: {})."
#define KTH_NODE_STOPPING "Please wait while the node is stopping..."
#define KTH_NODE_STOP_FAIL "Node failed to stop properly, see log."
#define KTH_NODE_STOPPED "Node stopped successfully."

#define KTH_USING_CONFIG_FILE "Using config file: {}"
#define KTH_USING_DEFAULT_CONFIG "Using default configuration settings."

#define KTH_VERSION_MESSAGE_INIT "Node version: {}"

#define KTH_KEOKEN_MESSAGE_INIT "Keoken protocol enabled"

#define KTH_CRYPTOCURRENCY_INIT "Currency: {} - {}"
#define KTH_MICROARCHITECTURE_INIT "Compiled for microarchitecture: {}"
#define KTH_DB_TYPE_INIT "Database type: {}"
#define KTH_NETWORK_INIT "Network: {0} ({1} - {1:#x})"
#define KTH_CORES_INIT "Configured to use {} cores"


// #define KTH_LOG_HEADER "================= startup {} =================="

#if defined(KTH_DB_NEW_FULL)
#define KTH_DB_TYPE "full, new version"
#elif defined(KTH_DB_NEW_BLOCKS)
#define KTH_DB_TYPE "UTXO and Blocks, new version"
#elif defined(KTH_DB_NEW)
#define KTH_DB_TYPE "just UTXO, new version"
#elif defined(KTH_DB_HISTORY)
#define KTH_DB_TYPE "full, legacy version"
#else
#define KTH_DB_TYPE "TXs and Blocks, legacy version"
#endif

} // namespace capi
} // namespace kth

#endif /* KTH_CAPI_EXECUTOR_HPP_ */
