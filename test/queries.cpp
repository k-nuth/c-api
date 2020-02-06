// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <kth/capi/executor_c.h>
#include <iostream>

class QueriesTestsFixture {
private:
    executor_t exec;
public:
    QueriesTestsFixture() {
        exec = executor_construct("/home/fernando/exec/btc-mainnet.cfg", stdout, stderr);
        int res1 = executor_initchain(exec);
        std::cout << "Init chain returned: " << res1 << std::endl;
        //int res2 = executor_run(exec);
    }

    executor_t getExecutor() {
        return exec;
    }
};

TEST_CASE_FIXTURE(QueriesTestsFixture, "Query interface tests") {
    REQUIRE(getExecutor() != nullptr);
    //REQUIRE_THROWS(conn.executeSQL("INSERT INTO employee (id, name) VALUES (?, ?)", getID(), ""));
    //fetch_block(exec, 0, NULL);

    //executor_destruct(exec);
}
