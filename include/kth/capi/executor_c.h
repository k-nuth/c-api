// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#ifndef KTH_CAPI_EXECUTOR_C_H
#define KTH_CAPI_EXECUTOR_C_H

#include <stdint.h>
#include <stdio.h>

#include <kth/capi/primitives.h>
#include <kth/capi/visibility.h>

#ifdef __cplusplus
extern "C" {
#endif

KTH_EXPORT
executor_t executor_construct(char const* path, FILE* sout, FILE* serr);

KTH_EXPORT
executor_t executor_construct_fd(char const* path, int sout_fd, int serr_fd);


#if defined(_WIN32)

KTH_EXPORT
executor_t executor_construct_handles(char const* path, void* sout, void* serr);

#endif /* defined(_WIN32) */


KTH_EXPORT
void executor_destruct(executor_t exec);

KTH_EXPORT
int executor_initchain(executor_t exec);

KTH_EXPORT
void executor_run(executor_t exec, void* ctx, run_handler_t handler);

KTH_EXPORT
void executor_init_and_run(executor_t exec, void* ctx, run_handler_t handler);

KTH_EXPORT
int executor_run_wait(executor_t exec);

KTH_EXPORT
int executor_init_and_run_wait(executor_t exec);

KTH_EXPORT
int executor_stop(executor_t exec);

//KTH_EXPORT
//int executor_close(executor_t exec);

KTH_EXPORT
int executor_stopped(executor_t exec);

KTH_EXPORT
chain_t executor_get_chain(executor_t exec);

KTH_EXPORT
p2p_t executor_get_p2p(executor_t exec);

#ifdef KTH_WITH_KEOKEN
KTH_EXPORT
keoken_manager_t executor_get_keoken_manager(executor_t exec);
#endif

KTH_EXPORT
char const* executor_version(void);

KTH_EXPORT
int executor_load_config_valid(executor_t exec);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // KTH_CAPI_EXECUTOR_C_H
