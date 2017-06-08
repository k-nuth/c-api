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

#ifndef BITPRIM_NODE_CINT_SCRIPT_H_
#define BITPRIM_NODE_CINT_SCRIPT_H_

#include <stdio.h>
#include <stdint.h>

#include <bitprim/nodecint/visibility.h>
#include <bitprim/nodecint/primitives.h>

#ifdef __cplusplus
extern "C" {
#endif

BITPRIM_EXPORT
void script_destruct(script_t script);

BITPRIM_EXPORT
int script_is_valid(script_t script);

BITPRIM_EXPORT
int script_is_valid_operations(script_t script);

BITPRIM_EXPORT
size_t script_satoshi_content_size(script_t script);

BITPRIM_EXPORT
size_t script_serialized_size(script_t script, bool prefix);

//Note: user of the function has to release the resource (memory) manually
BITPRIM_EXPORT
char const* script_to_string(script_t script, uint32_t active_forks);

BITPRIM_EXPORT
size_t script_sigops(script_t script, bool embedded);

BITPRIM_EXPORT
size_t script_embedded_sigops(script_t script, script_t prevout_script);


#ifdef __cplusplus
} // extern "C"
#endif

#endif /* BITPRIM_NODE_CINT_SCRIPT_H_ */
