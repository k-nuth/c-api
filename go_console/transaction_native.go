// --------------------------------
// Transaction
// --------------------------------

package bitprim

// #include <bitprim/nodecint/transaction.h>
import "C"

import (
	"unsafe"
)

func transactionDestruct(transaction unsafe.Pointer) {
	ptr := (C.transaction_t)(transaction)
	C.transaction_destruct(ptr)
}

func transactionIsValid(transaction unsafe.Pointer) bool {
	ptr := (C.transaction_t)(transaction)
	res := C.transaction_is_valid(ptr)
	return res == 0
}

func transactionVersion(transaction unsafe.Pointer) int {
	ptr := (C.transaction_t)(transaction)
	return (int)(C.transaction_version(ptr))
}

func transactionSetVersion(transaction unsafe.Pointer, version int) {
	ptr := (C.transaction_t)(transaction)
	C.transaction_set_version(ptr, (C.uint32_t)(version))
}

func transactionHash(transaction unsafe.Pointer) hashT {
	ptr := (C.transaction_t)(transaction)
	return CHashToGo(C.transaction_hash(ptr))
}
