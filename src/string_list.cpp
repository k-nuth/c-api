// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#include <knuth/nodecint/string_list.h>

#include <string>
#include <vector>

#include <knuth/nodecint/list_creator.h>

KTH_LIST_DEFINE_CONVERTERS(core, string_list_t, std::string, string_list)

// ---------------------------------------------------------------------------
extern "C" {

string_list_t core_string_list_construct() {
    return new std::vector<std::string>();
}

void core_string_list_destruct(string_list_t string_list) {
    delete &core_string_list_cpp(string_list);
}

void core_string_list_push_back(string_list_t string_list, char const* string) {
    core_string_list_cpp(string_list).emplace_back(std::string(string));
}

} // extern "C"