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

#include <bitprim/nodecint/parser.hpp>

#include <cstdint>
#include <iostream>
#include <string>
#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>
#include <bitcoin/bitcoin/multi_crypto_support.hpp>
#include <bitcoin/blockchain.hpp>
#include <bitcoin/network.hpp>
#include <bitcoin/node/full_node.hpp>
#include <bitcoin/node/settings.hpp>

//BC_DECLARE_CONFIG_DEFAULT_PATH("libbitcoin" / "bn.cfg")

// TODO(libbitcoin): localize descriptions.

namespace bitprim { namespace nodecint {

using boost::filesystem::path;
using boost::program_options::value;
using boost::program_options::reading_file;

// Initialize configuration by copying the given instance.
parser::parser(libbitcoin::node::configuration const& defaults)
  : configured(defaults)
{}

// Initialize configuration using defaults of the given context.
parser::parser(libbitcoin::config::settings const& context)
  : configured(context)
{
    // A node doesn't require history, and history is expensive.
//    configured.database.index_start_height = libbitcoin::max_uint32;

#if WITH_NODE_REQUESTER
    // Default endpoint for blockchain replier.
    configured.chain.replier = { "tcp://localhost:5502" };
#endif

    // A node allows 8 inbound connections by default.
    configured.network.inbound_connections = 8;
    // Logs will slow things if not rotated.
    configured.network.rotation_size = 10000000;

    // With block-first sync the count should be low until complete.
    configured.network.outbound_connections = 2;

    // A node allows 1000 host names by default.
    configured.network.host_pool_capacity = 1000;

    // A node requests transaction relay by default.
    // configured.network.relay_transactions = true;

    // A node exposes full node (1) network services by default.
    configured.network.services = libbitcoin::message::version::service::node_network;
}

libbitcoin::options_metadata parser::load_options() {
    return libbitcoin::options_metadata("options");
}

libbitcoin::arguments_metadata parser::load_arguments() {
    libbitcoin::arguments_metadata description;
    return description;
}

libbitcoin::options_metadata parser::load_environment() {
    libbitcoin::options_metadata description("environment");
    return description;
}

libbitcoin::options_metadata parser::load_settings() {
    libbitcoin::options_metadata description("settings");
    description.add_options()
    /* [log] */
    (
        "log.debug_file",
        value<path>(&configured.network.debug_file),
        "The debug log file path, defaults to 'debug.log'."
    )
    (
        "log.error_file",
        value<path>(&configured.network.error_file),
        "The error log file path, defaults to 'error.log'."
    )
    (
        "log.archive_directory",
        value<path>(&configured.network.archive_directory),
        "The log archive directory, defaults to 'archive'."
    )
    (
        "log.rotation_size",
        value<size_t>(&configured.network.rotation_size),
        "The size at which a log is archived, defaults to 10000000 (0 disables)."
    )
    (
        "log.minimum_free_space",
        value<size_t>(&configured.network.minimum_free_space),
        "The minimum free space required in the archive directory, defaults to 0."
    )
    (
        "log.maximum_archive_size",
        value<size_t>(&configured.network.maximum_archive_size),
        "The maximum combined size of archived logs, defaults to 0 (maximum)."
    )
    (
        "log.maximum_archive_files",
        value<size_t>(&configured.network.maximum_archive_files),
        "The maximum number of logs to archive, defaults to 0 (maximum)."
    )
    (
        "log.statistics_server",
        value<libbitcoin::config::authority>(&configured.network.statistics_server),
        "The address of the statistics collection server, defaults to none."
    )
    (
        "log.verbose",
        value<bool>(&configured.network.verbose),
        "Enable verbose logging, defaults to false."
    )
    /* [network] */
    (
        "network.threads",
        value<uint32_t>(&configured.network.threads),
        "The minimum number of threads in the network threadpool, defaults to 0 (physical cores)."
    )
    (
        "network.protocol_maximum",
        value<uint32_t>(&configured.network.protocol_maximum),
        "The maximum network protocol version, defaults to 70013."
    )
    (
        "network.protocol_minimum",
        value<uint32_t>(&configured.network.protocol_minimum),
        "The minimum network protocol version, defaults to 31402."
    )
    (
        "network.services",
        value<uint64_t>(&configured.network.services),
        "The services exposed by network connections, defaults to 1 (full node)."
    )
    (
        "network.invalid_services",
        value<uint64_t>(&configured.network.invalid_services),
        "The advertised services that cause a peer to be dropped, defaults to 0 (none)."
    )
    (
        "network.validate_checksum",
        value<bool>(&configured.network.validate_checksum),
        "Validate the checksum of network messages, defaults to false."
    )
    (
        "network.identifier",
        value<uint32_t>(&configured.network.identifier),
        "The magic number for message headers, defaults to 3652501241."
    )
    (
        "network.inbound_port",
        value<uint16_t>(&configured.network.inbound_port),
        "The port for incoming connections, defaults to 8333."
    )
    (
        "network.inbound_connections",
        value<uint32_t>(&configured.network.inbound_connections),
        "The target number of incoming network connections, defaults to 0."
    )
    (
        "network.outbound_connections",
        value<uint32_t>(&configured.network.outbound_connections),
        "The target number of outgoing network connections, defaults to 2."
    )
    (
        "network.manual_attempt_limit",
        value<uint32_t>(&configured.network.manual_attempt_limit),
        "The attempt limit for manual connection establishment, defaults to 0 (forever)."
    )
    (
        "network.connect_batch_size",
        value<uint32_t>(&configured.network.connect_batch_size),
        "The number of concurrent attempts to establish one connection, defaults to 5."
    )
    (
        "network.connect_timeout_seconds",
        value<uint32_t>(&configured.network.connect_timeout_seconds),
        "The time limit for connection establishment, defaults to 5."
    )
    (
        "network.channel_handshake_seconds",
        value<uint32_t>(&configured.network.channel_handshake_seconds),
        "The time limit to complete the connection handshake, defaults to 30."
    )
    (
        "network.channel_heartbeat_minutes",
        value<uint32_t>(&configured.network.channel_heartbeat_minutes),
        "The time between ping messages, defaults to 5."
    )
    (
        "network.channel_inactivity_minutes",
        value<uint32_t>(&configured.network.channel_inactivity_minutes),
        "The inactivity time limit for any connection, defaults to 30."
    )
    (
        "network.channel_expiration_minutes",
        value<uint32_t>(&configured.network.channel_expiration_minutes),
        "The age limit for any connection, defaults to 60."
    )
    (
        "network.channel_germination_seconds",
        value<uint32_t>(&configured.network.channel_germination_seconds),
        "The time limit for obtaining seed addresses, defaults to 30."
    )
    (
        "network.host_pool_capacity",
        value<uint32_t>(&configured.network.host_pool_capacity),
        "The maximum number of peer hosts in the pool, defaults to 1000."
    )
    (
        "network.hosts_file",
        value<path>(&configured.network.hosts_file),
        "The peer hosts cache file path, defaults to 'hosts.cache'."
    )
    (
        "network.self",
        value<libbitcoin::config::authority>(&configured.network.self),
        "The advertised public address of this node, defaults to none."
    )
    (
        "network.blacklist",
        value<libbitcoin::config::authority::list>(&configured.network.blacklists),
        "IP address to disallow as a peer, multiple entries allowed."
    )
    (
        "network.peer",
        value<libbitcoin::config::endpoint::list>(&configured.network.peers),
        "A persistent peer node, multiple entries allowed."
    )
    (
        "network.seed",
        value<libbitcoin::config::endpoint::list>(&configured.network.seeds),
        "A seed node for initializing the host pool, multiple entries allowed."
    )
    (
        "network.bitcoin_cash",
        value<bool>(&configured.network.bitcoin_cash),
        "Use Bitcoin Cash (true) or Bitcoin Legacy (false), defaults to false."
    )


    /* [database] */
    (
        "database.directory",
        value<path>(&configured.database.directory),
        "The blockchain database directory, defaults to 'blockchain'."
    )
    (
        "database.flush_writes",
        value<bool>(&configured.database.flush_writes),
        "Flush each write to disk, defaults to false."
    )
    (
        "database.file_growth_rate",
        value<uint16_t>(&configured.database.file_growth_rate),
        "Full database files increase by this percentage, defaults to 50."
    )
    (
        "database.block_table_buckets",
        value<uint32_t>(&configured.database.block_table_buckets),
        "Block hash table size, defaults to 650000."
    )
    (
        "database.transaction_table_buckets",
        value<uint32_t>(&configured.database.transaction_table_buckets),
        "Transaction hash table size, defaults to 110000000."
    )
    (
        "database.transaction_unconfirmed_table_buckets",
        value<uint32_t>(&configured.database.transaction_unconfirmed_table_buckets),
        "Unconfirmed Transaction hash table size, defaults to 10000."
    )
    (
        "database.cache_capacity",
        value<uint32_t>(&configured.database.cache_capacity),
        "The maximum number of entries in the unspent outputs cache, defaults to 10000."
    )
#if defined(WITH_REMOTE_DATABASE)    
    (
        "database.replier",
        value<config::endpoint>(&configured.database.replier),
        "Database-blockchain connection, defaults to 127.0.0.1:5568."
    )    
#endif //defined(WITH_REMOTE_DATABASE)    

    /* [blockchain] */
    (
        "blockchain.cores",
        value<uint32_t>(&configured.chain.cores),
        "The number of cores dedicated to block validation, defaults to 0 (physical cores)."
    )
    (
        "blockchain.priority",
        value<bool>(&configured.chain.priority),
        "Use high thread priority for block validation, defaults to true."
    )
    (
        "blockchain.use_libconsensus",
        value<bool>(&configured.chain.use_libconsensus),
        "Use libconsensus for script validation if integrated, defaults to false."
    )
    (
        "blockchain.reorganization_limit",
        value<uint32_t>(&configured.chain.reorganization_limit),
        "The maximum reorganization depth, defaults to 256 (0 for unlimited)."
    )
    (
        "blockchain.checkpoint",
        value<libbitcoin::config::checkpoint::list>(&configured.chain.checkpoints),
        "A hash:height checkpoint, multiple entries allowed."
    )

    /* [fork] */
    (
        "fork.easy_blocks",
        value<bool>(&configured.chain.easy_blocks),
        "Allow minimum difficulty blocks, defaults to false."
    )
    (
        "fork.bip16",
        value<bool>(&configured.chain.bip16),
        "Add pay-to-script-hash processing, defaults to true (soft fork)."
    )
    (
        "fork.bip30",
        value<bool>(&configured.chain.bip30),
        "Disallow collision of unspent transaction hashes, defaults to true (hard fork)."
    )
    (
        "fork.bip34",
        value<bool>(&configured.chain.bip34),
        "Require coinbase input includes block height, defaults to true (soft fork)."
    )
    (
        "fork.bip66",
        value<bool>(&configured.chain.bip66),
        "Require strict signature encoding, defaults to true (soft fork)."
    )
    (
        "fork.bip65",
        value<bool>(&configured.chain.bip65),
        "Add check-locktime-verify op code, defaults to true (soft fork)."
    )
    (
        "fork.bip90",
        value<bool>(&configured.chain.bip90),
        "Assume bip34, bip65, and bip66 activation if enabled, defaults to true (hard fork)."
    )
#if defined(WITH_REMOTE_BLOCKCHAIN)
    (
        "blockchain.replier",
        value<config::endpoint>(&configured.chain.replier),
        "Blockchain Replier connect() endpoint."
    )
#endif // defined(WITH_REMOTE_BLOCKCHAIN)

    (
        "fork.bip68",
        value<bool>(&configured.chain.bip68),
        "Add relative locktime enforcement, defaults to true (soft fork)."
    )
    (
        "fork.bip112",
        value<bool>(&configured.chain.bip112),
        "Add check-sequence-verify op code, defaults to true (soft fork)."
    )
    (
        "fork.bip113",
        value<bool>(&configured.chain.bip113),
        "Use median time past for locktime, defaults to true (soft fork)."
    )

    /* [node] */
    ////(
    ////    "node.sync_peers",
    ////    value<uint32_t>(&configured.node.sync_peers),
    ////    "The maximum number of initial block download peers, defaults to 0 (physical cores)."
    ////)
    ////(
    ////    "node.sync_timeout_seconds",
    ////    value<uint32_t>(&configured.node.sync_timeout_seconds),
    ////    "The time limit for block response during initial block download, defaults to 5."
    ////)
    (
        "node.block_latency_seconds",
        value<uint32_t>(&configured.node.block_latency_seconds),
        "The time to wait for a requested block, defaults to 60."
    )
    (
        /* Internally this is blockchain, but it is conceptually a node setting. */
        "node.notify_limit_hours",
        value<uint32_t>(&configured.chain.notify_limit_hours),
        "Disable relay when top block age exceeds, defaults to 24 (0 disables)."
    )
    (
        /* Internally this is blockchain, but it is conceptually a node setting. */
        "node.byte_fee_satoshis",
        value<float>(&configured.chain.byte_fee_satoshis),
        "The minimum fee per byte, cumulative for conflicts, defaults to 1."
    )
    (
        /* Internally this is blockchain, but it is conceptually a node setting. */
        "node.sigop_fee_satoshis",
        value<float>(&configured.chain.sigop_fee_satoshis),
        "The minimum fee per sigop, additional to byte fee, defaults to 100."
    )
    (
        /* Internally this is blockchain, but it is conceptually a node setting. */
        "node.minimum_output_satoshis",
        value<uint64_t>(&configured.chain.minimum_output_satoshis),
        "The minimum output value, defaults to 500."
    )
    (
        /* Internally this is network, but it is conceptually a node setting. */
        "node.relay_transactions",
        value<bool>(&configured.network.relay_transactions),
        "Request that peers relay transactions, defaults to false."
    )
    (
        "node.refresh_transactions",
        value<bool>(&configured.node.refresh_transactions),
        "Request transactions on each channel start, defaults to true."
    )
    // TODO(bitprim): ver como implementamos esto para diferenciar server y node
    (
        /* Internally this database, but it applies to server.*/
        "node.index_start_height",
        value<uint32_t>(&configured.database.index_start_height),
        "The lower limit of address and spend indexing, defaults to 0."
    )
    ;

    return description;
}

libbitcoin::config::checkpoint::list parser::default_checkpoints() {
    //case config::settings::mainnet:

// #ifdef BITPRIM_LITECOIN
//     auto const testnet = (configured.network.identifier == 4056470269u); //Litecoin
// #else
//     auto const testnet = (configured.network.identifier == 118034699u);  //Bitcoin
// #endif //BITPRIM_LITECOIN
    bool const testnet = libbitcoin::is_testnet(configured.network.identifier, configured.network.bitcoin_cash);

    libbitcoin::config::checkpoint::list checkpoints;

    if (configured.network.bitcoin_cash) {
        if (testnet) {
            checkpoints.reserve(15);
            checkpoints.emplace_back("000000000933ea01ad0ee984209779baaec3ced90fa3f408719526f8d77f4943", 0);
            checkpoints.emplace_back("00000000009e2958c15ff9290d571bf9459e93b19765c6801ddeccadbb160a1e", 100000);
            checkpoints.emplace_back("0000000000287bffd321963ef05feab753ebe274e1d78b2fd4e2bfe9ad3aa6f2", 200000);
            checkpoints.emplace_back("000000000000226f7618566e70a2b5e020e29579b46743f05348427239bf41a1", 300000);
            checkpoints.emplace_back("000000000598cbbb1e79057b79eef828c495d4fc31050e6b179c57d07d00367c", 400000);
            checkpoints.emplace_back("000000000001a7c0aaa2630fbb2c0e476aafffc60f82177375b2aaa22209f606", 500000);
            checkpoints.emplace_back("000000000000624f06c69d3a9fe8d25e0a9030569128d63ad1b704bbb3059a16", 600000);
            checkpoints.emplace_back("000000000000406178b12a4dea3b27e13b3c4fe4510994fd667d7c1e6a3f4dc1", 700000);
            checkpoints.emplace_back("0000000000209b091d6519187be7c2ee205293f25f9f503f90027e25abf8b503", 800000);
            checkpoints.emplace_back("0000000000356f8d8924556e765b7a94aaebc6b5c8685dcfa2b1ee8b41acd89b", 900000);
            checkpoints.emplace_back("0000000000478e259a3eda2fafbeeb0106626f946347955e99278fe6cc848414", 1000000);
            checkpoints.emplace_back("00000000f17c850672894b9a75b63a1e72830bbd5f4c8889b5c1a80e7faef138", 1155875);
            checkpoints.emplace_back("00000000000e38fef93ed9582a7df43815d5c2ba9fd37ef70c9a0ea4a285b8f5", 1155876);
        } else {
            // Cash Mainnet
            checkpoints.reserve(30);
            checkpoints.emplace_back("000000000019d6689c085ae165831e934ff763ae46a2a6c172b3f1b60a8ce26f", 0);
            checkpoints.emplace_back("0000000069e244f73d78e8fd29ba2fd2ed618bd6fa2ee92559f542fdb26e7c1d", 11111);
            checkpoints.emplace_back("000000002dd5588a74784eaa7ab0507a18ad16a236e7b1ce69f00d7ddfb5d0a6", 33333);
            checkpoints.emplace_back("00000000001e1b4903550a0b96e9a9405c8a95f387162e4944e8d9fbe501cd6a", 68555);
            checkpoints.emplace_back("00000000006a49b14bcf27462068f1264c961f11fa2e0eddd2be0791e1d4124a", 70567);
            checkpoints.emplace_back("0000000000573993a3c9e41ce34471c079dcf5f52a0e824a81e7f953b8661a20", 74000);
            checkpoints.emplace_back("00000000000291ce28027faea320c8d2b054b2e0fe44a773f3eefb151d6bdc97", 105000);
            checkpoints.emplace_back("000000000000774a7f8a7a12dc906ddb9e17e75d684f15e00f8767f9e8f36553", 118000);
            checkpoints.emplace_back("00000000000005b12ffd4cd315cd34ffd4a594f430ac814c91184a0d42d2b0fe", 134444);
            checkpoints.emplace_back("000000000000033b512028abb90e1626d8b346fd0ed598ac0a3c371138dce2bd", 140700);
            checkpoints.emplace_back("000000000000099e61ea72015e79632f216fe6cb33d7899acb35b75c8303b763", 168000);
            checkpoints.emplace_back("000000000000059f452a5f7340de6682a977387c17010ff6e6c3bd83ca8b1317", 193000);
            checkpoints.emplace_back("000000000000048b95347e83192f69cf0366076336c639f9b7228e9ba171342e", 210000);
            checkpoints.emplace_back("00000000000001b4f4b433e81ee46494af945cf96014816a4e2370f11b23df4e", 216116);
            checkpoints.emplace_back("00000000000001c108384350f74090433e7fcf79a606b8e797f065b130575932", 225430);
            checkpoints.emplace_back("000000000000003887df1f29024b06fc2200b55f8af8f35453d7be294df2d214", 250000);
            checkpoints.emplace_back("0000000000000001ae8c72a0b0c301f67e3afca10e819efa9041e458e9bd7e40", 279000);
            checkpoints.emplace_back("00000000000000004d9b4ef50f0f9d686fd69db2e03af35a100370c64632a983", 295000);
            checkpoints.emplace_back("000000000000000082ccf8f1557c5d40b21edabb18d2d691cfbf87118bac7254", 300000);
            checkpoints.emplace_back("00000000000000000409695bce21828b31a7143fa35fcab64670dd337a71425d", 325000);
            checkpoints.emplace_back("0000000000000000053cf64f0400bb38e0c4b3872c38795ddde27acb40a112bb", 350000);
            checkpoints.emplace_back("000000000000000009733ff8f11fbb9575af7412df3fae97f382376709c965dc", 375000);
            checkpoints.emplace_back("000000000000000004ec466ce4732fe6f1ed1cddc2ed4b328fff5224276e3f6f", 400000);
            checkpoints.emplace_back("00000000000000000142adfebcb9a0aa75f0c4980dd5c7dd17062bf7de77c16d", 425000);
            checkpoints.emplace_back("0000000000000000014083723ed311a461c648068af8cef8a19dcd620c07a20b", 450000);
            checkpoints.emplace_back("0000000000000000017c42fd88e78ab02c5f5c684f8344e1f5c9e4cebecde71c", 475000);
            checkpoints.emplace_back("0000000000000000011865af4122fe3b144e2cbeea86142e8ff2fb4107352d43", 478558);
            checkpoints.emplace_back("000000000000000000651ef99cb9fcbe0dadde1d424bd9f15ff20136191a5eec", 478559);
        }
    }
    else {
        if (testnet) {
            checkpoints.reserve(15);
            checkpoints.emplace_back("000000000933ea01ad0ee984209779baaec3ced90fa3f408719526f8d77f4943", 0);
            checkpoints.emplace_back("00000000009e2958c15ff9290d571bf9459e93b19765c6801ddeccadbb160a1e", 100000);
            checkpoints.emplace_back("0000000000287bffd321963ef05feab753ebe274e1d78b2fd4e2bfe9ad3aa6f2", 200000);
            checkpoints.emplace_back("000000000000226f7618566e70a2b5e020e29579b46743f05348427239bf41a1", 300000);
            checkpoints.emplace_back("000000000598cbbb1e79057b79eef828c495d4fc31050e6b179c57d07d00367c", 400000);
            checkpoints.emplace_back("000000000001a7c0aaa2630fbb2c0e476aafffc60f82177375b2aaa22209f606", 500000);
            checkpoints.emplace_back("000000000000624f06c69d3a9fe8d25e0a9030569128d63ad1b704bbb3059a16", 600000);
            checkpoints.emplace_back("000000000000406178b12a4dea3b27e13b3c4fe4510994fd667d7c1e6a3f4dc1", 700000);
            checkpoints.emplace_back("0000000000209b091d6519187be7c2ee205293f25f9f503f90027e25abf8b503", 800000);
            checkpoints.emplace_back("0000000000356f8d8924556e765b7a94aaebc6b5c8685dcfa2b1ee8b41acd89b", 900000);
            checkpoints.emplace_back("0000000000478e259a3eda2fafbeeb0106626f946347955e99278fe6cc848414", 1000000);
            checkpoints.emplace_back("00000000f17c850672894b9a75b63a1e72830bbd5f4c8889b5c1a80e7faef138", 1155875);
            checkpoints.emplace_back("0000000093b3cdf2b50a05fa1527810f52d6826781916ef129098e06ee03fb18", 1155876);
        } else {
            // BTC Mainnet
            checkpoints.reserve(30);
            checkpoints.emplace_back("000000000019d6689c085ae165831e934ff763ae46a2a6c172b3f1b60a8ce26f", 0);
            checkpoints.emplace_back("0000000069e244f73d78e8fd29ba2fd2ed618bd6fa2ee92559f542fdb26e7c1d", 11111);
            checkpoints.emplace_back("000000002dd5588a74784eaa7ab0507a18ad16a236e7b1ce69f00d7ddfb5d0a6", 33333);
            checkpoints.emplace_back("00000000001e1b4903550a0b96e9a9405c8a95f387162e4944e8d9fbe501cd6a", 68555);
            checkpoints.emplace_back("00000000006a49b14bcf27462068f1264c961f11fa2e0eddd2be0791e1d4124a", 70567);
            checkpoints.emplace_back("0000000000573993a3c9e41ce34471c079dcf5f52a0e824a81e7f953b8661a20", 74000);
            checkpoints.emplace_back("00000000000291ce28027faea320c8d2b054b2e0fe44a773f3eefb151d6bdc97", 105000);
            checkpoints.emplace_back("000000000000774a7f8a7a12dc906ddb9e17e75d684f15e00f8767f9e8f36553", 118000);
            checkpoints.emplace_back("00000000000005b12ffd4cd315cd34ffd4a594f430ac814c91184a0d42d2b0fe", 134444);
            checkpoints.emplace_back("000000000000033b512028abb90e1626d8b346fd0ed598ac0a3c371138dce2bd", 140700);
            checkpoints.emplace_back("000000000000099e61ea72015e79632f216fe6cb33d7899acb35b75c8303b763", 168000);
            checkpoints.emplace_back("000000000000059f452a5f7340de6682a977387c17010ff6e6c3bd83ca8b1317", 193000);
            checkpoints.emplace_back("000000000000048b95347e83192f69cf0366076336c639f9b7228e9ba171342e", 210000);
            checkpoints.emplace_back("00000000000001b4f4b433e81ee46494af945cf96014816a4e2370f11b23df4e", 216116);
            checkpoints.emplace_back("00000000000001c108384350f74090433e7fcf79a606b8e797f065b130575932", 225430);
            checkpoints.emplace_back("000000000000003887df1f29024b06fc2200b55f8af8f35453d7be294df2d214", 250000);
            checkpoints.emplace_back("0000000000000001ae8c72a0b0c301f67e3afca10e819efa9041e458e9bd7e40", 279000);
            checkpoints.emplace_back("00000000000000004d9b4ef50f0f9d686fd69db2e03af35a100370c64632a983", 295000);
            checkpoints.emplace_back("000000000000000082ccf8f1557c5d40b21edabb18d2d691cfbf87118bac7254", 300000);
            checkpoints.emplace_back("00000000000000000409695bce21828b31a7143fa35fcab64670dd337a71425d", 325000);
            checkpoints.emplace_back("0000000000000000053cf64f0400bb38e0c4b3872c38795ddde27acb40a112bb", 350000);
            checkpoints.emplace_back("000000000000000009733ff8f11fbb9575af7412df3fae97f382376709c965dc", 375000);
            checkpoints.emplace_back("000000000000000004ec466ce4732fe6f1ed1cddc2ed4b328fff5224276e3f6f", 400000);
            checkpoints.emplace_back("00000000000000000142adfebcb9a0aa75f0c4980dd5c7dd17062bf7de77c16d", 425000);
            checkpoints.emplace_back("0000000000000000014083723ed311a461c648068af8cef8a19dcd620c07a20b", 450000);
            checkpoints.emplace_back("0000000000000000017c42fd88e78ab02c5f5c684f8344e1f5c9e4cebecde71c", 475000);
            checkpoints.emplace_back("0000000000000000011865af4122fe3b144e2cbeea86142e8ff2fb4107352d43", 478558);
            checkpoints.emplace_back("00000000000000000019f112ec0a9982926f1258cdcc558dd7c3b7e5dc7fa148", 478559);
        }
    }


    return checkpoints;
}

void parser::fix_checkpoints() {

    auto const checkpoints = default_checkpoints();

    auto const it = std::max_element(checkpoints.begin(), checkpoints.end(), [](libbitcoin::config::checkpoint const& x, libbitcoin::config::checkpoint const& y) {
        return x.height() < y.height();
    });

    if (it != checkpoints.end()) {
        auto const max_checkpoint_height = it->height();

        configured.chain.checkpoints.erase(std::remove_if(configured.chain.checkpoints.begin(), configured.chain.checkpoints.end(), [max_checkpoint_height](libbitcoin::config::checkpoint const& x) {
            return x.height() <= max_checkpoint_height;
        }), configured.chain.checkpoints.end());

        configured.chain.checkpoints.insert(configured.chain.checkpoints.begin(), checkpoints.begin(), checkpoints.end());
    }
}


// // bool parser::load_configuration_variables(variables_map& variables, std::string const& option_name) {
// bool parser::load_configuration_variables(variables_map& variables, boost::filesystem::path const& config_path) {

//     auto const config_settings = load_settings();
//     //auto const config_path = get_config_option(variables, option_name);

//     // If the existence test errors out we pretend there's no file :/.
//     boost::system::error_code code;
//     if ( ! config_path.empty() && exists(config_path, code))
//     {
//         auto const& path = config_path.string();
//         bc::ifstream file(path);

//         if ( ! file.good())
//         {
//             BOOST_THROW_EXCEPTION(reading_file(path.c_str()));
//         }

//         auto const config = parse_config_file(file, config_settings);
//         store(config, variables);
//         return true;
//     }

//     // Loading from an empty stream causes the defaults to populate.
//     std::stringstream stream;
//     auto const config = parse_config_file(stream, config_settings);
//     store(config, variables);
//     return false;
// }

//TODO(fernando): replace int return type with an appropriate enum or "try_bool" or something
//1 success, 0 default, -1 non-existing file
int parser::load_configuration_variables(variables_map& variables, boost::filesystem::path const& config_path) {

    auto const config_settings = load_settings();
    //auto const config_path = get_config_option(variables, option_name);

    // If the existence test errors out we pretend there's no file :/.
    boost::system::error_code code;
    if ( ! config_path.empty()) {
        if (exists(config_path, code)) {
            auto const& path = config_path.string();
            bc::ifstream file(path);

            if ( ! file.good()) {
                BOOST_THROW_EXCEPTION(reading_file(path.c_str()));
            }

            auto const config = parse_config_file(file, config_settings);
            store(config, variables);
            return 1;
        } else {
            return -1;
        }
    }

    // Loading from an empty stream causes the defaults to populate.
    std::stringstream stream;
    auto const config = parse_config_file(stream, config_settings);
    store(config, variables);
    return 0;
}

// bool parser::parse(int argc, char const* argv[], std::ostream& error) {
bool parser::parse(boost::filesystem::path const& config_path, std::ostream& error) 
{
    try {
        variables_map variables;

        configured.file = config_path;
        auto file = load_configuration_variables(variables, config_path);

        if (file == -1) {
            LOG_ERROR(LOG_NODE) << "Config file provided does not exists.";
            return false;
        }

        // Update bound variables in metadata.settings.
        notify(variables);

        fix_checkpoints();

        // Clear the config file path if it wasn't used.
        if ( ! file) {
            configured.file.clear();
        }

    } catch (boost::program_options::error const& e) {
        // This is obtained from boost, which circumvents our localization.
        error << format_invalid_parameter(e.what()) << std::endl;
        return false;
    }

    return true;
}

} // namespace nodecint
} // namespace bitprim
