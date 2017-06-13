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

// --------------------------------
// Header
// --------------------------------

package bitprim

// #include <bitprim/nodecint/header.h>
import "C"

import (
	"unsafe"
)

func headerDestruct(header unsafe.Pointer) {
	ptr := (C.header_t)(header)
	C.header_destruct(ptr)
}

func headerIsValid(header unsafe.Pointer) bool {
	ptr := (C.header_t)(header)
	res := C.header_is_valid(ptr)
	return res == 0
}

func headerVersion(header unsafe.Pointer) int {
	ptr := (C.header_t)(header)
	return (int)(C.header_version(ptr))
}

func headerSetVersion(header unsafe.Pointer, version int) {
	ptr := (C.header_t)(header)
	C.header_set_version(ptr, (C.uint32_t)(version))
}

func headerTimestamp(header unsafe.Pointer) int {
	ptr := (C.header_t)(header)
	return (int)(C.header_timestamp(ptr))
}

func headerSetTimestamp(header unsafe.Pointer, timestamp int) {
	ptr := (C.header_t)(header)
	C.header_set_timestamp(ptr, (C.uint32_t)(timestamp))
}

func headerBits(header unsafe.Pointer) int {
	ptr := (C.header_t)(header)
	return (int)(C.header_bits(ptr))
}

func headerSetBits(header unsafe.Pointer, bits int) {
	ptr := (C.header_t)(header)
	C.header_set_bits(ptr, (C.uint32_t)(bits))
}

func headerNonce(header unsafe.Pointer) int {
	ptr := (C.header_t)(header)
	return (int)(C.header_nonce(ptr))
}

func headerSetNonce(header unsafe.Pointer, nonce int) {
	ptr := (C.header_t)(header)
	C.header_set_nonce(ptr, (C.uint32_t)(nonce))
}

func headerPreviousBlockHash(header unsafe.Pointer) HashT {
	ptr := (C.header_t)(header)
	return CHashToGo(C.header_previous_block_hash(ptr))
}

func headerMerkle(header unsafe.Pointer) HashT {
	ptr := (C.header_t)(header)
	return CHashToGo(C.header_merkle(ptr))
}

func headerHash(header unsafe.Pointer) HashT {
	ptr := (C.header_t)(header)
	return CHashToGo(C.header_hash(ptr))
}
