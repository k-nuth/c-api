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

void fetchOutputGoCallBack_cgo(output_t output); // Forward declaration.

*/
import "C"

// --------------------------------------------------------------------------------

import (
	"fmt" // or "runtime"
	"unsafe"
)

func CHashToGo(hashCPtr C.hash_t) HashT {
	hashC := unsafe.Pointer(hashCPtr)

	hashGoSlice := C.GoBytes(hashC, 32)
	var hash HashT
	copy(hash[:], hashGoSlice)
	return hash
}

func boolToC(x bool) C.int {
	if x {
		return 1
	}
	return 0
}

func CToBool(x C.int) bool {
	if x == 0 {
		return false
	}
	return true
}

// func ExecutorConstruct(path string, sin_fd int, sout_fd int, serr_fd int) unsafe.Pointer {
// 	path_c := C.CString(path)
// 	defer C.free(unsafe.Pointer(path_c))

// 	exec := C.executor_construct_fd(path_c, C.int(sin_fd), C.int(sout_fd), C.int(serr_fd))
// 	fmt.Printf("exec address = %p.\n", unsafe.Pointer(exec))
// 	return unsafe.Pointer(exec)

// }

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
// FetchLastHeight
// --------------------------------

var FetchLastHeightChannel chan int

//export FetchLastHeightGoCallBack
func FetchLastHeightGoCallBack(err int, height int) {
	// fmt.Printf("Go.FetchLastHeightGoCallBack(): height = %d\n", height)
	FetchLastHeightChannel <- height
}

func FetchLastHeight(exec unsafe.Pointer) int {
	ptr := (*C.struct_executor)(exec)

	fptr := unsafe.Pointer(C.fetchLastHeightGoCallBack_cgo)
	fptr2 := (C.last_height_fetch_handler_t)(fptr)

	go C.fetch_last_height(ptr, fptr2)
	return <-FetchLastHeightChannel
}

// --------------------------------
// fetchBlockHeight
// --------------------------------
type HashT [32]byte

var FetchBlockHeightChannel chan int

//export FetchBlockHeightGoCallBack
func FetchBlockHeightGoCallBack(err int, height int) {
	// fmt.Printf("Go.FetchBlockHeightGoCallBack(): height = %d\n", height)
	FetchBlockHeightChannel <- height
}

func FetchBlockHeight(exec unsafe.Pointer, hash HashT) int {
	ptr := (*C.struct_executor)(exec)

	fptr := unsafe.Pointer(C.fetchBlockHeightGoCallBack_cgo)
	fptr2 := (C.block_height_fetch_handler_t)(fptr)

	hashC := C.CBytes(hash[:])
	defer C.free(hashC)

	go C.fetch_block_height(ptr, (*C.uint8_t)(hashC), fptr2)
	return <-FetchBlockHeightChannel
}

// --------------------------------
// FetchBlockHeader
// --------------------------------

var FetchBlockHeaderChannel1 chan unsafe.Pointer
var FetchBlockHeaderChannel2 chan int

//export FetchBlockHeaderGoCallBack
func FetchBlockHeaderGoCallBack(err int, header unsafe.Pointer, height int) {
	// fmt.Printf("Go.FetchBlockHeaderGoCallBack(): height = %d\n", height)
	// fmt.Printf("Go.FetchBlockHeaderGoCallBack(): header = %p\n", header)
	// fmt.Printf("Go.FetchBlockHeaderGoCallBack(): err    = %d\n", err)

	FetchBlockHeaderChannel1 <- header
	FetchBlockHeaderChannel2 <- height
}

func FetchBlockHeader(exec unsafe.Pointer, height int) (unsafe.Pointer, int) {
	ptr := (*C.struct_executor)(exec)

	fptr := unsafe.Pointer(C.fetchBlockHeaderGoCallBack_cgo)
	fptr2 := (C.block_header_fetch_handler_t)(fptr)

	go C.fetch_block_header(ptr, (C.size_t)(height), fptr2)
	return <-FetchBlockHeaderChannel1, <-FetchBlockHeaderChannel2
}

// --------------------------------
// FetchBlockHeaderByHash
// --------------------------------

var FetchBlockHeaderByHashChannel1 chan unsafe.Pointer
var FetchBlockHeaderByHashChannel2 chan int

//export FetchBlockHeaderByHashGoCallBack
func FetchBlockHeaderByHashGoCallBack(err int, header unsafe.Pointer, height int) {
	// fmt.Printf("Go.FetchBlockHeaderByHashGoCallBack(): height = %d\n", height)
	// fmt.Printf("Go.FetchBlockHeaderByHashGoCallBack(): header = %p\n", header)
	// fmt.Printf("Go.FetchBlockHeaderByHashGoCallBack(): err    = %d\n", err)

	FetchBlockHeaderByHashChannel1 <- header
	FetchBlockHeaderByHashChannel2 <- height
}

func FetchBlockHeaderByHash(exec unsafe.Pointer, hash HashT) (unsafe.Pointer, int) {
	ptr := (*C.struct_executor)(exec)

	fptr := unsafe.Pointer(C.fetchBlockHeaderByHashGoCallBack_cgo)
	fptr2 := (C.block_header_fetch_handler_t)(fptr)

	hashC := C.CBytes(hash[:])
	defer C.free(hashC)

	go C.fetch_block_header_by_hash(ptr, (*C.uint8_t)(hashC), fptr2)
	return <-FetchBlockHeaderByHashChannel1, <-FetchBlockHeaderByHashChannel2
}

// --------------------------------
// FetchBlock
// --------------------------------

var FetchBlockChannel1 chan unsafe.Pointer
var FetchBlockChannel2 chan int

//export FetchBlockGoCallBack
func FetchBlockGoCallBack(err int, block unsafe.Pointer, height int) {
	// fmt.Printf("Go.FetchBlockGoCallBack(): height = %d\n", height)
	// fmt.Printf("Go.FetchBlockGoCallBack(): block = %p\n", block)
	// fmt.Printf("Go.FetchBlockGoCallBack(): err    = %d\n", err)

	FetchBlockChannel1 <- block
	FetchBlockChannel2 <- height
}

func FetchBlock(exec unsafe.Pointer, height int) (unsafe.Pointer, int) {
	ptr := (*C.struct_executor)(exec)

	fptr := unsafe.Pointer(C.fetchBlockGoCallBack_cgo)
	fptr2 := (C.block_fetch_handler_t)(fptr)

	go C.fetch_block(ptr, (C.size_t)(height), fptr2)
	return <-FetchBlockChannel1, <-FetchBlockChannel2
}

// --------------------------------
// FetchBlockByHash
// --------------------------------

var FetchBlockByHashChannel1 chan unsafe.Pointer
var FetchBlockByHashChannel2 chan int

//export FetchBlockByHashGoCallBack
func FetchBlockByHashGoCallBack(err int, block unsafe.Pointer, height int) {
	// fmt.Printf("Go.FetchBlockByHashGoCallBack(): height = %d\n", height)
	// fmt.Printf("Go.FetchBlockByHashGoCallBack(): block = %p\n", block)
	// fmt.Printf("Go.FetchBlockByHashGoCallBack(): err    = %d\n", err)

	FetchBlockByHashChannel1 <- block
	FetchBlockByHashChannel2 <- height
}

func FetchBlockByHash(exec unsafe.Pointer, hash HashT) (unsafe.Pointer, int) {
	ptr := (*C.struct_executor)(exec)

	fptr := unsafe.Pointer(C.fetchBlockByHashGoCallBack_cgo)
	fptr2 := (C.block_fetch_handler_t)(fptr)

	hashC := C.CBytes(hash[:])
	defer C.free(hashC)

	go C.fetch_block_by_hash(ptr, (*C.uint8_t)(hashC), fptr2)
	return <-FetchBlockByHashChannel1, <-FetchBlockByHashChannel2
}

// --------------------------------
// FetchTransaction
// --------------------------------

var FetchTransactionChannel1 chan unsafe.Pointer
var FetchTransactionChannel2 chan int

//export FetchTransactionGoCallBack
func FetchTransactionGoCallBack(err int, transaction unsafe.Pointer, height int, index int) {
	fmt.Printf("Go.FetchTransactionGoCallBack(): height = %d\n", height)
	fmt.Printf("Go.FetchTransactionGoCallBack(): index = %d\n", index)
	fmt.Printf("Go.FetchTransactionGoCallBack(): transaction = %p\n", transaction)
	fmt.Printf("Go.FetchTransactionGoCallBack(): err    = %d\n", err)

	FetchTransactionChannel1 <- transaction
	FetchTransactionChannel2 <- height
	FetchTransactionChannel2 <- index
}

func FetchTransaction(exec unsafe.Pointer, hash HashT, requireConfirmed bool) (unsafe.Pointer, int, int) {
	ptr := (*C.struct_executor)(exec)

	fptr := unsafe.Pointer(C.fetchTransactionGoCallBack_cgo)
	fptr2 := (C.transaction_fetch_handler_t)(fptr)

	hashC := C.CBytes(hash[:])
	defer C.free(hashC)

	go C.fetch_transaction(ptr, (*C.uint8_t)(hashC), boolToC(requireConfirmed), fptr2)
	return <-FetchTransactionChannel1, <-FetchTransactionChannel2, <-FetchTransactionChannel2
}

// --------------------------------
// fetchOutput
// --------------------------------

var FetchOutputChannel chan unsafe.Pointer

//export FetchOutputGoCallBack
func FetchOutputGoCallBack(err int, output unsafe.Pointer) {
	fmt.Printf("Go.FetchOutputGoCallBack(): output = %p\n", output)
	fmt.Printf("Go.FetchOutputGoCallBack(): err    = %d\n", err)

	FetchOutputChannel <- output
}

func FetchOutput(exec unsafe.Pointer, hash HashT, index int, requireConfirmed bool) unsafe.Pointer {
	ptr := (*C.struct_executor)(exec)

	fptr := unsafe.Pointer(C.fetchOutputGoCallBack_cgo)
	fptr2 := (C.output_fetch_handler_t)(fptr)

	hashC := C.CBytes(hash[:])
	defer C.free(hashC)

	var requireConfirmedC C.int
	if requireConfirmed {
		requireConfirmedC = 1
	} else {
		requireConfirmedC = 0
	}

	go C.fetch_output(ptr, (*C.uint8_t)(hashC), C.uint32_t(index), requireConfirmedC, fptr2)
	return <-FetchOutputChannel
}
