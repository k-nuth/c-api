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
// Header Golang idiomatic Interface
// --------------------------------

package bitprim

import (
	"fmt" // or "runtime"
	"unsafe"
)

type Header struct {
	native_ptr unsafe.Pointer
	height     int
}

func NewHeader(native_ptr unsafe.Pointer, height int) *Header {
	x := new(Header)
	x.native_ptr = native_ptr
	x.height = height
	return x
}

func (x *Header) Close() {
	fmt.Printf("Go.Header.Close() - native_ptr: %p\n", x.native_ptr)
	headerDestruct(x.native_ptr)
	x.native_ptr = nil
}

func (x Header) IsValid() bool {
	return headerIsValid(x.native_ptr)
}

func (x Header) Version() int {
	return headerVersion(x.native_ptr)
}

func (x *Header) SetVersion(version int) {
	headerSetVersion(x.native_ptr, version)
}

func (x Header) Timestamp() int {
	return headerTimestamp(x.native_ptr)
}

func (x *Header) SetTimestamp(timestamp int) {
	headerSetTimestamp(x.native_ptr, timestamp)
}

func (x Header) Bits() int {
	return headerBits(x.native_ptr)
}

func (x *Header) SetBits(bits int) {
	headerSetBits(x.native_ptr, bits)
}

func (x Header) Nonce() int {
	return headerNonce(x.native_ptr)
}

func (x *Header) SetNonce(nonce int) {
	headerSetNonce(x.native_ptr, nonce)
}

func (x Header) PreviousBlockHash() HashT {
	return headerPreviousBlockHash(x.native_ptr)
}

func (x Header) Merkle() HashT {
	return headerMerkle(x.native_ptr)
}

func (x Header) Hash() HashT {
	return headerHash(x.native_ptr)
}
