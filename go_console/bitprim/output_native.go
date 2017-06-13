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

// #include <bitprim/nodecint/output.h>
import "C"

import (
	"unsafe"
)

func outputDestruct(output unsafe.Pointer) {
	C.output_destruct(C.output_t(output))
}

func outputIsValid(output unsafe.Pointer) bool {
	return CToBool(C.output_is_valid(C.output_t(output)))
}

func outputSerializedSize(output unsafe.Pointer, wire bool /* = true*/) uint64 /*size_t*/ {
	return uint64(C.output_serialized_size(C.output_t(output), boolToC(wire)))
}

func outputValue(output unsafe.Pointer) uint64 {
	return uint64(C.output_value(C.output_t(output)))
}

func outputSignatureOperations(output unsafe.Pointer) uint64 /*size_t*/ {
	return uint64(C.output_signature_operations(C.output_t(output)))
}

func outputScript(output unsafe.Pointer) unsafe.Pointer {
	return unsafe.Pointer(C.output_script(C.output_t(output)))
}
