// Copyright (c) 2016-2023 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_CAPI_P2P_P2P_H_
#define KTH_CAPI_P2P_P2P_H_

#include <kth/capi/primitives.h>
#include <kth/capi/visibility.h>

#ifdef __cplusplus
extern "C" {
#endif

KTH_EXPORT
kth_size_t kth_p2p_address_count(kth_p2p_t p2p);

KTH_EXPORT
void kth_p2p_stop(kth_p2p_t p2p);

KTH_EXPORT
void kth_p2p_close(kth_p2p_t p2p);

KTH_EXPORT
kth_bool_t kth_p2p_stopped(kth_p2p_t p2p);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* KTH_CAPI_P2P_P2P_H_ */
