// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_CAPI_NODE_H_
#define KTH_CAPI_NODE_H_

#include <stdint.h>
#include <stdio.h>

#include <kth/capi/primitives.h>
#include <kth/capi/visibility.h>

#ifdef __cplusplus
extern "C" {
#endif

KTH_EXPORT
kth_node_t kth_node_construct(char const* path, FILE* sout, FILE* serr);

KTH_EXPORT
kth_node_t kth_node_construct_fd(char const* path, int sout_fd, int serr_fd);


#if defined(_WIN32)

KTH_EXPORT
kth_node_t kth_node_construct_handles(char const* path, void* sout, void* serr);

#endif /* defined(_WIN32) */


KTH_EXPORT
void kth_node_destruct(kth_node_t node);

#if ! defined(KTH_DB_READONLY)
KTH_EXPORT
int kth_node_initchain(kth_node_t node);
#endif // ! defined(KTH_DB_READONLY)

KTH_EXPORT
void kth_node_run(kth_node_t node, void* ctx, kth_run_handler_t handler);

#if ! defined(KTH_DB_READONLY)
KTH_EXPORT
void kth_node_init_and_run(kth_node_t node, void* ctx, kth_run_handler_t handler);

KTH_EXPORT
void kth_node_init_run_and_wait_for_signal(kth_node_t node, void* ctx, kth_run_handler_t handler);
#endif // ! defined(KTH_DB_READONLY)

KTH_EXPORT
int kth_node_run_wait(kth_node_t node);

#if ! defined(KTH_DB_READONLY)
KTH_EXPORT
int kth_node_init_and_run_wait(kth_node_t node);
#endif // ! defined(KTH_DB_READONLY)

KTH_EXPORT
int kth_node_stop(kth_node_t node);

KTH_EXPORT
void kth_node_signal_stop(kth_node_t node);

KTH_EXPORT
int kth_node_close(kth_node_t node);

KTH_EXPORT
int kth_node_stopped(kth_node_t node);

KTH_EXPORT
kth_chain_t kth_node_get_chain(kth_node_t node);

KTH_EXPORT
kth_p2p_t kth_node_get_p2p(kth_node_t node);

KTH_EXPORT
void kth_node_print_thread_id();

#ifdef KTH_WITH_KEOKEN
KTH_EXPORT
keoken_manager_t kth_node_get_keoken_manager(kth_node_t node);
#endif

KTH_EXPORT
char const* kth_node_version(void);

KTH_EXPORT
int kth_node_load_config_valid(kth_node_t node);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // KTH_CAPI_NODE_H_
