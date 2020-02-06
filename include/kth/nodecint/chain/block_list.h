// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#ifndef KTH_NODECINT_CHAIN_BLOCK_LIST_H_
#define KTH_NODECINT_CHAIN_BLOCK_LIST_H_

#include <stdint.h>

#include <knuth/nodecint/list_creator.h>
#include <knuth/nodecint/primitives.h>
#include <knuth/nodecint/visibility.h>

#ifdef __cplusplus
extern "C" {
#endif

KTH_LIST_DECLARE(chain, block_list_t, block_t, block_list)

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* KTH_NODECINT_CHAIN_BLOCK_LIST_H_ */
