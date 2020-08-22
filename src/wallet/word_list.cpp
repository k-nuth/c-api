// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/capi/wallet/word_list.h>

// #include <iostream>
#include <string>
#include <vector>

#include <kth/capi/list_creator.h>

KTH_LIST_DEFINE_CONVERTERS(wallet, kth_word_list_t, std::string, word_list)

// ---------------------------------------------------------------------------
extern "C" {

kth_word_list_t kth_wallet_word_list_construct() {
    return new std::vector<std::string>();
}

void kth_wallet_word_list_destruct(kth_word_list_t word_list) {
    delete &kth_wallet_word_list_cpp(word_list);
}

void kth_wallet_word_list_add_word(kth_word_list_t word_list, char const* word) {
    kth_wallet_word_list_cpp(word_list).emplace_back(std::string(word));
}

} // extern "C"