// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#ifndef KTH_NODE_CINT_PLATFORM_H
#define KTH_NODE_CINT_PLATFORM_H

#include <knuth/nodecint/visibility.h>

#ifdef __cplusplus
extern "C" {
#endif

KTH_EXPORT
void platform_free(void* ptr);

#ifdef __cplusplus
} // extern "C"
#endif

#endif //KTH_NODE_CINT_PLATFORM_H
