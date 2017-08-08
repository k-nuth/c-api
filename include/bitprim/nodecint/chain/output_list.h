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

#ifndef BITPRIM_NODECINT_CHAIN_OUTPUT_LIST_H_
#define BITPRIM_NODECINT_CHAIN_OUTPUT_LIST_H_

#include <stdint.h>

#include <bitprim/nodecint/visibility.h>
#include <bitprim/nodecint/primitives.h>



#ifdef __cplusplus
extern "C" {
#endif

BITPRIM_EXPORT
output_list_t chain_output_list_construct_default(void);

BITPRIM_EXPORT
void chain_output_list_push_back(output_list_t list, output_t output);

BITPRIM_EXPORT
void chain_output_list_destruct(output_list_t list);

BITPRIM_EXPORT
uint64_t /*size_t*/ chain_output_list_count(output_list_t list);

BITPRIM_EXPORT
output_t chain_output_list_nth(output_list_t list, uint64_t /*size_t*/ n);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* BITPRIM_NODECINT_CHAIN_OUTPUT_LIST_H_ */
