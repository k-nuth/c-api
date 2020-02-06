// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#ifndef KTH_NODECINT_CHAIN_OUTPUT_LIST_H_
#define KTH_NODECINT_CHAIN_OUTPUT_LIST_H_

#include <stdint.h>

#include <kth/capi/list_creator.h>
#include <kth/capi/primitives.h>
#include <kth/capi/visibility.h>

#ifdef __cplusplus
extern "C" {
#endif

KTH_LIST_DECLARE(chain, output_list_t, output_t, output_list)

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* KTH_NODECINT_CHAIN_OUTPUT_LIST_H_ */
