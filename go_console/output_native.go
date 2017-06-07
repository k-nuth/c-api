// --------------------------------
// Output
// --------------------------------

package bitprim

// #include <bitprim/nodecint/output.h>
import "C"

import (
	"unsafe"
)

func outputDestruct(output unsafe.Pointer) {
	ptr := (C.output_t)(output)
	C.output_destruct(ptr)
}
