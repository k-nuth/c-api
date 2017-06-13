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

package bitprim

// #include <bitprim/nodecint/input.h>
import "C"

import (
	"unsafe"
)

func inputDestruct(input unsafe.Pointer) {
	C.input_destruct(C.input_t(input))
}

func inputIsValid(input unsafe.Pointer) bool {
	return CToBool(C.input_is_valid(C.input_t(input)))
}

func inputIsFinal(input unsafe.Pointer) bool {
	return CToBool(C.input_is_final(C.input_t(input)))
}

func inputSerializedSize(input unsafe.Pointer, wire bool /* = true*/) uint64 /*size_t*/ {
	return uint64(C.input_serialized_size(C.input_t(input), boolToC(wire)))
}

func inputSequence(input unsafe.Pointer) uint32 {
	return uint32(C.input_sequence(C.input_t(input)))
}

func inputSignatureOperations(input unsafe.Pointer, bip16Active bool) uint64 /*size_t*/ {
	return uint64(C.input_signature_operations(C.input_t(input), boolToC(bip16Active)))
}

func inputScript(input unsafe.Pointer) unsafe.Pointer {
	return unsafe.Pointer(C.input_script(C.input_t(input)))
}

func inputPreviousOutput(input unsafe.Pointer) unsafe.Pointer {
	return unsafe.Pointer(C.input_previous_output(C.input_t(input)))
}
