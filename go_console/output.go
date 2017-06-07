// --------------------------------
// Transaction Golang idiomatic Interface
// --------------------------------

package bitprim

import (
	"fmt" // or "runtime"
	"unsafe"
)

type Output struct {
	native_ptr unsafe.Pointer
}

func NewOutput(native_ptr unsafe.Pointer) *Output {
	x := new(Output)
	x.native_ptr = native_ptr
	return x
}

func (x *Output) Close() {
	fmt.Printf("Go.Output.Close() - native_ptr: %p\n", x.native_ptr)
	outputDestruct(x.native_ptr)
	x.native_ptr = nil
}
