// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#ifndef KTH_NODECINT_P2P_P2P_H_
#define KTH_NODECINT_P2P_P2P_H_

#include <kth/capi/primitives.h>
#include <kth/capi/visibility.h>

#ifdef __cplusplus
extern "C" {
#endif

KTH_EXPORT
uint64_t /*size_t*/ p2p_address_count(p2p_t p2p);

KTH_EXPORT
void p2p_stop(p2p_t p2p);

KTH_EXPORT
void p2p_close(p2p_t p2p);

KTH_EXPORT
bool_t p2p_stopped(p2p_t p2p);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* KTH_NODECINT_P2P_P2P_H_ */
