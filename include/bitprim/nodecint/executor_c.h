/**
 * Copyright (c) 2017 Bitprim developers (see AUTHORS)
 *
 * This file is part of Bitprim.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef BITPRIM_NODECINT_EXECUTOR_C_H
#define BITPRIM_NODECINT_EXECUTOR_C_H

#include <stdio.h>
#include <stdint.h>

#include <bitprim/nodecint/visibility.h>
#include <bitprim/nodecint/primitives.h>

#ifdef __cplusplus
extern "C" {
#endif


BITPRIM_EXPORT
executor_t executor_construct(char const* path, FILE* sout, FILE* serr);

BITPRIM_EXPORT
executor_t executor_construct_fd(char const* path, int sout_fd, int serr_fd);


#if defined(_WIN32)

BITPRIM_EXPORT
executor_t executor_construct_handles(char const* path, void* sout, void* serr);

#endif /* defined(_WIN32) */



BITPRIM_EXPORT
void executor_destruct(executor_t exec);

BITPRIM_EXPORT
void executor_run(executor_t exec, void* ctx, run_handler_t handler);

BITPRIM_EXPORT
int executor_run_wait(executor_t exec);

//BITPRIM_EXPORT
//int executor_run_wait(executor_t exec, run_handler_t handler);

BITPRIM_EXPORT
int executor_initchain(executor_t exec);

BITPRIM_EXPORT
void executor_stop(executor_t exec);

BITPRIM_EXPORT
chain_t executor_get_chain(executor_t exec);

BITPRIM_EXPORT
p2p_t executor_get_p2p(executor_t exec);


#ifdef __cplusplus
} // extern "C"
#endif

#endif // BITPRIM_NODECINT_EXECUTOR_C_H
