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

#ifndef BITPRIM_NODECINT_CHAIN_STEALTH_COMPACT_LIST_H
#define BITPRIM_NODECINT_CHAIN_STEALTH_COMPACT_LIST_H

//#include <stdio.h>
#include <stdint.h>

#include <bitprim/nodecint/visibility.h>
#include <bitprim/nodecint/primitives.h>

#ifdef __cplusplus
extern "C" {
#endif

BITPRIM_EXPORT
void stealth_compact_list_destruct(stealth_compact_list_t list);

BITPRIM_EXPORT
uint64_t /*size_t*/ stealth_compact_list_count(stealth_compact_list_t list);

BITPRIM_EXPORT
stealth_compact_t stealth_compact_list_nth(stealth_compact_list_t list, uint64_t /*size_t*/ n);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // BITPRIM_NODECINT_CHAIN_STEALTH_COMPACT_LIST_H
