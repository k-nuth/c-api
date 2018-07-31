/**
 * Copyright (c) 2016-2018 Bitprim Inc.
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

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <bitprim/nodecint/executor_c.h>
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
