// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <bitcoin/network/user_agent.hpp>
#include <knuth/nodecint/version.h>

namespace libbitcoin {
namespace network {

std::string get_user_agent() {
    return "/bitprim:" KTH_NODECINT_VERSION "/";
}

} // namespace network
} // namespace kth