// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


/**
 * API Users: Include only this header. Direct use of other headers is fragile
 * and unsupported as header organization is subject to change.
 *
 * Maintainers: Do not include this header internal to this library.
 */

#ifndef KTH_CAPI_CAPI_H_
#define KTH_CAPI_CAPI_H_

#include <kth/capi/primitives.h>
#include <kth/capi/visibility.h>
#include <kth/capi/version.h>
#include <kth/capi/executor_c.h>

#include <kth/capi/binary.h>

#include <kth/capi/chain/block.h>
#include <kth/capi/chain/block_list.h>
#include <kth/capi/chain/chain.h>
#include <kth/capi/chain/compact_block.h>
#include <kth/capi/chain/header.h>
#include <kth/capi/chain/history_compact.h>
#include <kth/capi/chain/history_compact_list.h>
#include <kth/capi/chain/stealth_compact.h>
#include <kth/capi/chain/stealth_compact_list.h>
#include <kth/capi/chain/input.h>
#include <kth/capi/chain/input_list.h>
#include <kth/capi/chain/merkle_block.h>
#include <kth/capi/chain/output.h>
#include <kth/capi/chain/output_list.h>
#include <kth/capi/chain/output_point.h>
#include <kth/capi/wallet/payment_address.h>
#include <kth/capi/chain/point.h>
#include <kth/capi/chain/point_list.h>
#include <kth/capi/chain/script.h>
#include <kth/capi/chain/transaction.h>
#include <kth/capi/chain/transaction_list.h>

#include <kth/capi/p2p/p2p.h>

#include <kth/capi/wallet/wallet.h>
#include <kth/capi/wallet/word_list.h>

#endif /* KTH_CAPI_CAPI_H_ */
