/**
 * Copyright (c) 2018 Bitprim developers (see AUTHORS)
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

#ifndef BITPRIM_NODE_CINT_PLATFORM_H
#define BITPRIM_NODE_CINT_PLATFORM_H

#include <bitprim/nodecint/visibility.h>

#ifdef __cplusplus
extern "C" {
#endif

BITPRIM_EXPORT
void platform_free(void* ptr);

#ifdef __cplusplus
} // extern "C"
#endif

#endif //BITPRIM_NODE_CINT_PLATFORM_H
