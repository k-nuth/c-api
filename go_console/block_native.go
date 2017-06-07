package bitprim

// #include <bitprim/nodecint/block.h>
import "C"

import (
	"unsafe"
)

func blockDestruct(block unsafe.Pointer) {
	ptr := (C.block_t)(block)
	C.block_destruct(ptr)
}

func blockIsValid(block unsafe.Pointer) bool {
	ptr := (C.block_t)(block)
	res := C.block_is_valid(ptr)
	return res == 0
}

func blockHash(block unsafe.Pointer) hashT {
	ptr := (C.block_t)(block)
	return CHashToGo(C.block_hash(ptr))
}

func blockHeader(block unsafe.Pointer) unsafe.Pointer {
	ptr := (C.block_t)(block)
	return unsafe.Pointer(C.block_header(ptr))
}

func blockTransactionCount(block unsafe.Pointer) int {
	ptr := (C.block_t)(block)
	return (int)(C.block_transaction_count(ptr))
}

func blockTransactions(block unsafe.Pointer) (unsafe.Pointer, int) {
	ptr := (C.block_t)(block)
	var n C.size_t
	res := C.block_transactions(ptr, &n)
	return unsafe.Pointer(res), int(n)
}

func blockTransactionNext(transaction unsafe.Pointer) unsafe.Pointer {
	ptr := (C.transaction_t)(transaction)
	return unsafe.Pointer(C.block_transaction_next(ptr))
}

func blockTransactionNth(block unsafe.Pointer, n int) unsafe.Pointer {
	ptr := (C.block_t)(block)
	res := C.block_transaction_nth(ptr, C.size_t(n))
	return unsafe.Pointer(res)
}
