// --------------------------------
// Interface one-to-one with C Interface
// --------------------------------

package bitprim

/*
#cgo CFLAGS: -I/home/fernando/dev/bitprim/bitprim-node-cint/include -I/home/fernando/dev/bitprim/bitprim-core/include
#cgo LDFLAGS: -L/home/fernando/dev/bitprim/bitprim-node-cint/cmake-build-debug -lbitprim-node-cint

#include <stdio.h>
#include <stdlib.h>
// #include <bitprim/nodecint/block.h>
#include <bitprim/nodecint/executor_c.h>
#include <bitprim/nodecint/header.h>
#include <bitprim/nodecint/transaction.h>

typedef void (*fetch_last_height_handler)(int);
typedef void (*fetch_block_height_handler)(int);

void fetchLastHeightGoCallBack_cgo(int in); // Forward declaration.
void fetchBlockHeightGoCallBack_cgo(int in); // Forward declaration.

void fetchBlockHeaderGoCallBack_cgo(header_t header, size_t height); // Forward declaration.
void fetchBlockHeaderByHashGoCallBack_cgo(header_t header, size_t height); // Forward declaration.

void fetchBlockGoCallBack_cgo(block_t block, size_t height); // Forward declaration.
void fetchBlockByHashGoCallBack_cgo(block_t block, size_t height); // Forward declaration.

void fetchTransactionGoCallBack_cgo(transaction_t transaction, size_t height, size_t index); // Forward declaration.

*/
import "C"

// --------------------------------------------------------------------------------

import (
	"fmt" // or "runtime"
	"unsafe"
)

func CHashToGo(hashCPtr C.hash_t) hashT {
	hashC := unsafe.Pointer(hashCPtr)

	hashGoSlice := C.GoBytes(hashC, 32)
	var hash hashT
	copy(hash[:], hashGoSlice)
	return hash
}

func ExecutorConstruct(path string, sin_fd int, sout_fd int, serr_fd int) unsafe.Pointer {
	path_c := C.CString(path)
	defer C.free(unsafe.Pointer(path_c))

	exec := C.executor_construct_fd(path_c, C.int(sin_fd), C.int(sout_fd), C.int(serr_fd))
	fmt.Printf("exec address = %p.\n", unsafe.Pointer(exec))
	return unsafe.Pointer(exec)

}

func ExecutorDestruct(exec unsafe.Pointer) {
	ptr := (*C.struct_executor)(exec)
	C.executor_destruct(ptr)
}

func ExecutorRun(exec unsafe.Pointer) int {
	ptr := (*C.struct_executor)(exec)
	res := C.executor_run(ptr)
	return int(res)
}

func ExecutorInitchain(exec unsafe.Pointer) int {
	ptr := (*C.struct_executor)(exec)
	res := C.executor_initchain(ptr)
	return int(res)
}

// --------------------------------
// fetchLastHeight
// --------------------------------

var fetchLastHeightChannel chan int

//export fetchLastHeightGoCallBack
func fetchLastHeightGoCallBack(err int, height int) {
	// fmt.Printf("Go.fetchLastHeightGoCallBack(): height = %d\n", height)
	fetchLastHeightChannel <- height
}

func fetchLastHeight(exec unsafe.Pointer) int {
	ptr := (*C.struct_executor)(exec)

	fptr := unsafe.Pointer(C.fetchLastHeightGoCallBack_cgo)
	fptr2 := (C.last_height_fetch_handler_t)(fptr)

	go C.fetch_last_height(ptr, fptr2)
	return <-fetchLastHeightChannel
}

// --------------------------------
// fetchBlockHeight
// --------------------------------

type hashT [32]byte

var fetchBlockHeightChannel chan int

//export fetchBlockHeightGoCallBack
func fetchBlockHeightGoCallBack(err int, height int) {
	// fmt.Printf("Go.fetchBlockHeightGoCallBack(): height = %d\n", height)
	fetchBlockHeightChannel <- height
}

func fetchBlockHeight(exec unsafe.Pointer, hash hashT) int {
	ptr := (*C.struct_executor)(exec)

	fptr := unsafe.Pointer(C.fetchBlockHeightGoCallBack_cgo)
	fptr2 := (C.block_height_fetch_handler_t)(fptr)

	hashC := C.CBytes(hash[:])
	defer C.free(hashC)

	go C.fetch_block_height(ptr, (*C.uint8_t)(hashC), fptr2)
	return <-fetchBlockHeightChannel
}

// --------------------------------
// fetchBlockHeader
// --------------------------------

var fetchBlockHeaderChannel1 chan unsafe.Pointer
var fetchBlockHeaderChannel2 chan int

//export fetchBlockHeaderGoCallBack
func fetchBlockHeaderGoCallBack(err int, header unsafe.Pointer, height int) {
	// fmt.Printf("Go.fetchBlockHeaderGoCallBack(): height = %d\n", height)
	// fmt.Printf("Go.fetchBlockHeaderGoCallBack(): header = %p\n", header)
	// fmt.Printf("Go.fetchBlockHeaderGoCallBack(): err    = %d\n", err)

	fetchBlockHeaderChannel1 <- header
	fetchBlockHeaderChannel2 <- height
}

func fetchBlockHeader(exec unsafe.Pointer, height int) (unsafe.Pointer, int) {
	ptr := (*C.struct_executor)(exec)

	fptr := unsafe.Pointer(C.fetchBlockHeaderGoCallBack_cgo)
	fptr2 := (C.block_header_fetch_handler_t)(fptr)

	go C.fetch_block_header(ptr, (C.size_t)(height), fptr2)
	return <-fetchBlockHeaderChannel1, <-fetchBlockHeaderChannel2
}

// --------------------------------
// fetchBlockHeaderByHash
// --------------------------------

var fetchBlockHeaderByHashChannel1 chan unsafe.Pointer
var fetchBlockHeaderByHashChannel2 chan int

//export fetchBlockHeaderByHashGoCallBack
func fetchBlockHeaderByHashGoCallBack(err int, header unsafe.Pointer, height int) {
	// fmt.Printf("Go.fetchBlockHeaderByHashGoCallBack(): height = %d\n", height)
	// fmt.Printf("Go.fetchBlockHeaderByHashGoCallBack(): header = %p\n", header)
	// fmt.Printf("Go.fetchBlockHeaderByHashGoCallBack(): err    = %d\n", err)

	fetchBlockHeaderByHashChannel1 <- header
	fetchBlockHeaderByHashChannel2 <- height
}

func fetchBlockHeaderByHash(exec unsafe.Pointer, hash hashT) (unsafe.Pointer, int) {
	ptr := (*C.struct_executor)(exec)

	fptr := unsafe.Pointer(C.fetchBlockHeaderByHashGoCallBack_cgo)
	fptr2 := (C.block_header_fetch_handler_t)(fptr)

	hashC := C.CBytes(hash[:])
	defer C.free(hashC)

	go C.fetch_block_header_by_hash(ptr, (*C.uint8_t)(hashC), fptr2)
	return <-fetchBlockHeaderByHashChannel1, <-fetchBlockHeaderByHashChannel2
}

// --------------------------------
// fetchBlock
// --------------------------------

var fetchBlockChannel1 chan unsafe.Pointer
var fetchBlockChannel2 chan int

//export fetchBlockGoCallBack
func fetchBlockGoCallBack(err int, block unsafe.Pointer, height int) {
	// fmt.Printf("Go.fetchBlockGoCallBack(): height = %d\n", height)
	// fmt.Printf("Go.fetchBlockGoCallBack(): block = %p\n", block)
	// fmt.Printf("Go.fetchBlockGoCallBack(): err    = %d\n", err)

	fetchBlockChannel1 <- block
	fetchBlockChannel2 <- height
}

func fetchBlock(exec unsafe.Pointer, height int) (unsafe.Pointer, int) {
	ptr := (*C.struct_executor)(exec)

	fptr := unsafe.Pointer(C.fetchBlockGoCallBack_cgo)
	fptr2 := (C.block_fetch_handler_t)(fptr)

	go C.fetch_block(ptr, (C.size_t)(height), fptr2)
	return <-fetchBlockChannel1, <-fetchBlockChannel2
}

// --------------------------------
// fetchBlockByHash
// --------------------------------

var fetchBlockByHashChannel1 chan unsafe.Pointer
var fetchBlockByHashChannel2 chan int

//export fetchBlockByHashGoCallBack
func fetchBlockByHashGoCallBack(err int, block unsafe.Pointer, height int) {
	// fmt.Printf("Go.fetchBlockByHashGoCallBack(): height = %d\n", height)
	// fmt.Printf("Go.fetchBlockByHashGoCallBack(): block = %p\n", block)
	// fmt.Printf("Go.fetchBlockByHashGoCallBack(): err    = %d\n", err)

	fetchBlockByHashChannel1 <- block
	fetchBlockByHashChannel2 <- height
}

func fetchBlockByHash(exec unsafe.Pointer, hash hashT) (unsafe.Pointer, int) {
	ptr := (*C.struct_executor)(exec)

	fptr := unsafe.Pointer(C.fetchBlockByHashGoCallBack_cgo)
	fptr2 := (C.block_fetch_handler_t)(fptr)

	hashC := C.CBytes(hash[:])
	defer C.free(hashC)

	go C.fetch_block_by_hash(ptr, (*C.uint8_t)(hashC), fptr2)
	return <-fetchBlockByHashChannel1, <-fetchBlockByHashChannel2
}

// --------------------------------
// fetchTransaction
// --------------------------------

var fetchTransactionChannel1 chan unsafe.Pointer
var fetchTransactionChannel2 chan int

//export fetchTransactionGoCallBack
func fetchTransactionGoCallBack(err int, transaction unsafe.Pointer, height int, index int) {
	fmt.Printf("Go.fetchTransactionGoCallBack(): height = %d\n", height)
	fmt.Printf("Go.fetchTransactionGoCallBack(): index = %d\n", index)
	fmt.Printf("Go.fetchTransactionGoCallBack(): transaction = %p\n", transaction)
	fmt.Printf("Go.fetchTransactionGoCallBack(): err    = %d\n", err)

	fetchTransactionChannel1 <- transaction
	fetchTransactionChannel2 <- height
	fetchTransactionChannel2 <- index
}

func fetchTransaction(exec unsafe.Pointer, hash hashT, requireConfirmed bool) (unsafe.Pointer, int, int) {
	ptr := (*C.struct_executor)(exec)

	fptr := unsafe.Pointer(C.fetchTransactionGoCallBack_cgo)
	fptr2 := (C.transaction_fetch_handler_t)(fptr)

	hashC := C.CBytes(hash[:])
	defer C.free(hashC)

	var requireConfirmedC C.int
	if requireConfirmed {
		requireConfirmedC = 1
	} else {
		requireConfirmedC = 0
	}

	go C.fetch_transaction(ptr, (*C.uint8_t)(hashC), requireConfirmedC, fptr2)
	return <-fetchTransactionChannel1, <-fetchTransactionChannel2, <-fetchTransactionChannel2
}
