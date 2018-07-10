/**
 * Copyright (c) 2017-2018 Bitprim Inc.
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

#ifndef BITPRIM_NODECINT_P2P_P2P_H_
#define BITPRIM_NODECINT_P2P_P2P_H_

#include <bitprim/nodecint/primitives.h>
#include <bitprim/nodecint/visibility.h>

#ifdef __cplusplus
extern "C" {
#endif

BITPRIM_EXPORT
uint64_t /*size_t*/ p2p_address_count(p2p_t p2p);

BITPRIM_EXPORT
void p2p_stop(p2p_t p2p);

BITPRIM_EXPORT
void p2p_close(p2p_t p2p);

BITPRIM_EXPORT
int /*bool*/ p2p_stopped(p2p_t p2p);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* BITPRIM_NODECINT_P2P_P2P_H_ */
