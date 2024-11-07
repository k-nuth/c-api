// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <kth/capi/node.h>
#include <iostream>

class QueriesTestsFixture {
private:
    kth_node_t exec;
public:
    QueriesTestsFixture() {
        exec = kth_node_construct("/home/fernando/exec/btc-mainnet.cfg", stdout, stderr);
        int res1 = kth_node_initchain(exec);
        std::cout << "Init chain returned: " << res1 << std::endl;
        //int res2 = kth_node_run(exec);
    }

    kth_node_t getExecutor() {
        return exec;
    }
};

TEST_CASE_FIXTURE(QueriesTestsFixture, "Query interface tests") {
    REQUIRE(getExecutor() != nullptr);
    //REQUIRE_THROWS(conn.executeSQL("INSERT INTO employee (id, name) VALUES (?, ?)", getID(), ""));
    //fetch_block(exec, 0, NULL);

    //kth_node_destruct(exec);
}
