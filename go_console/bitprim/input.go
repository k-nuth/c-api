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
// Input Golang idiomatic Interface
// --------------------------------

package bitprim

import (
	"unsafe"
)

type Input struct {
	ptr unsafe.Pointer
}

func NewInput(ptr unsafe.Pointer) *Input {
	x := new(Input)
	x.ptr = ptr
	return x
}

func (x *Input) Close() {
	// fmt.Printf("Go.Input.Close() - ptr: %p\n", x.ptr)
	inputDestruct(x.ptr)
	x.ptr = nil
}

func (x *Input) IsValid() bool {
	return inputIsValid(x.ptr)
}

func (x *Input) IsFinal() bool {
	return inputIsFinal(x.ptr)
}

func (x *Input) SerializedSize(wire bool /* = true*/) uint64 /*size_t*/ {
	return inputSerializedSize(x.ptr, wire)
}

func (x *Input) Sequence() uint32 {
	return inputSequence(x.ptr)
}

func (x *Input) SignatureOperations(bip16Active bool) uint64 /*size_t*/ {
	return inputSignatureOperations(x.ptr, bip16Active)
}

// func (x *Input) Script() unsafe.Pointer {
// 	return inputScript(x.ptr)
// }

// func (x *Input) PreviousOutput() unsafe.Pointer {
// 	return inputPreviousOutput(x.ptr)
// }
