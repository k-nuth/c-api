// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#ifndef KTH_NODECINT_CHAIN_BLOCK_INDEXES_H_
#define KTH_NODECINT_CHAIN_BLOCK_INDEXES_H_

#include <stdint.h>

#include <knuth/nodecint/list_creator.h>
#include <knuth/nodecint/primitives.h>
#include <knuth/nodecint/visibility.h>

#ifdef __cplusplus
extern "C" {
#endif

KTH_LIST_DECLARE(chain, block_indexes_t, uint64_t, block_indexes)

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* KTH_NODECINT_CHAIN_BLOCK_INDEXES_H_ */
