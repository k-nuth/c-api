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

#ifndef BITPRIM_NODE_CINT_EXECUTOR_H_
#define BITPRIM_NODE_CINT_EXECUTOR_H_

#include <stdio.h>

#include <bitprim/nodecint/visibility.h>


#ifdef __cplusplus
extern "C" {
#endif

typedef struct executor* executor_t;

BITPRIM_EXPORT
executor_t executor_construct(char const* path, FILE* sin, FILE* sout, FILE* serr);

BITPRIM_EXPORT
executor_t executor_construct_fd(char const* path, int sin_fd, int sout_fd, int serr_fd);

BITPRIM_EXPORT
void executor_destruct(executor_t exec);

BITPRIM_EXPORT
int executor_run(executor_t exec);

BITPRIM_EXPORT
int executor_run_wait(executor_t exec);


BITPRIM_EXPORT
int executor_initchain(executor_t exec);

BITPRIM_EXPORT
void executor_stop(executor_t exec);


// virtual void fetch_last_height(last_height_fetch_handler handler) const = 0;


// typedef void (*last_height_fetch_handler_t)(void* client_data, const char* name, int32_t votes, const char* html);
typedef void (*last_height_fetch_handler_t)(size_t h);


BITPRIM_EXPORT
void executor_fetch_last_height(executor_t exec, last_height_fetch_handler_t handler);


#ifdef __cplusplus
} // extern "C"
#endif

#endif /* BITPRIM_NODE_CINT_EXECUTOR_H_ */
