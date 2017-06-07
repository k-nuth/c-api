// --------------------------------
// Transaction Golang idiomatic Interface
// --------------------------------

package bitprim

import (
	"fmt" // or "runtime"
	"unsafe"
)

type Transaction struct {
	native_ptr unsafe.Pointer
	height     int
	index      int
}

func NewTransaction(native_ptr unsafe.Pointer, height int, index int) *Transaction {
	x := new(Transaction)
	x.native_ptr = native_ptr
	x.height = height
	x.index = index
	return x
}

func (x *Transaction) Close() {
	fmt.Printf("Go.Transaction.Close() - native_ptr: %p\n", x.native_ptr)
	transactionDestruct(x.native_ptr)
	x.native_ptr = nil
}

func (x Transaction) IsValid() bool {
	return transactionIsValid(x.native_ptr)
}

func (x Transaction) Version() int {
	return transactionVersion(x.native_ptr)
}

func (x *Transaction) SetVersion(version int) {
	transactionSetVersion(x.native_ptr, version)
}

func (x Transaction) Hash() hashT {
	return transactionHash(x.native_ptr)
}
