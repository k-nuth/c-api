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
// Output Golang idiomatic Interface
// --------------------------------

package bitprim

import (
	"unsafe"
)

type Output struct {
	ptr unsafe.Pointer
}

func NewOutput(ptr unsafe.Pointer) *Output {
	x := new(Output)
	x.ptr = ptr
	return x
}

func (x *Output) Close() {
	// fmt.Printf("Go.Output.Close() - ptr: %p\n", x.ptr)
	outputDestruct(x.ptr)
	x.ptr = nil
}

func (x *Output) IsValid() bool {
	return outputIsValid(x.ptr)
}

func (x *Output) SerializedSize(wire bool /* = true*/) uint64 /*size_t*/ {
	return outputSerializedSize(x.ptr, wire)
}

func (x *Output) Value() uint64 {
	return outputValue(x.ptr)
}

func (x *Output) SignatureOperations() uint64 /*size_t*/ {
	return outputSignatureOperations(x.ptr)
}

// func (x *Output) Script() unsafe.Pointer {
// 	return outputScript(x.ptr)
// }
