/*
export PATH=$PATH:$(/usr/lib/go-1.8/bin/go env GOROOT)/bin
export GOPATH=$(go env GOPATH)
export GODEBUG=cgocheck=0
*/

// 1. 	go install github.com/fpelliccioni/bitprim
// 2.	cd $GOPATH/src/github.com/fpelliccioni/bitprim
// 		go install

// export LD_LIBRARY_PATH=/home/fernando/dev/bitprim/bitprim-node-cint/cmake-build-debug:$LD_LIBRARY_PATH
// $GOPATH/bin/bitprim

// package bitprim
package main

/*
#cgo CFLAGS: -I/home/fernando/dev/bitprim/bitprim-node-cint/include -I/home/fernando/dev/bitprim/bitprim-core/include
#cgo LDFLAGS: -L/home/fernando/dev/bitprim/bitprim-node-cint/cmake-build-debug -lbitprim-node-cint

#include <stdio.h>
#include <stdlib.h>
#include <bitprim/nodecint/executor_c.h>

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
	"fmt"
	"os"
	"os/signal"
	"syscall"
	"time" // or "runtime"
	"unsafe"
)

// --------------------------------------------------------------------------------

func CHashToGo(hashCPtr C.hash_t) hashT {
	hashC := unsafe.Pointer(hashCPtr)

	hashGoSlice := C.GoBytes(hashC, 32)
	var hash hashT
	copy(hash[:], hashGoSlice)
	return hash
}

// --------------------------------
// Interface one-to-one with C Interface
// --------------------------------

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

// --------------------------------
// Header
// --------------------------------

func headerDestruct(header unsafe.Pointer) {
	ptr := (C.header_t)(header)
	C.header_destruct(ptr)
}

func headerIsValid(header unsafe.Pointer) bool {
	ptr := (C.header_t)(header)
	res := C.header_is_valid(ptr)
	return res == 0
}

func headerVersion(header unsafe.Pointer) int {
	ptr := (C.header_t)(header)
	return (int)(C.header_version(ptr))
}

func headerSetVersion(header unsafe.Pointer, version int) {
	ptr := (C.header_t)(header)
	C.header_set_version(ptr, (C.uint32_t)(version))
}

func headerTimestamp(header unsafe.Pointer) int {
	ptr := (C.header_t)(header)
	return (int)(C.header_timestamp(ptr))
}

func headerSetTimestamp(header unsafe.Pointer, timestamp int) {
	ptr := (C.header_t)(header)
	C.header_set_timestamp(ptr, (C.uint32_t)(timestamp))
}

func headerBits(header unsafe.Pointer) int {
	ptr := (C.header_t)(header)
	return (int)(C.header_bits(ptr))
}

func headerSetBits(header unsafe.Pointer, bits int) {
	ptr := (C.header_t)(header)
	C.header_set_bits(ptr, (C.uint32_t)(bits))
}

func headerNonce(header unsafe.Pointer) int {
	ptr := (C.header_t)(header)
	return (int)(C.header_nonce(ptr))
}

func headerSetNonce(header unsafe.Pointer, nonce int) {
	ptr := (C.header_t)(header)
	C.header_set_nonce(ptr, (C.uint32_t)(nonce))
}

func headerPreviousBlockHash(header unsafe.Pointer) hashT {
	ptr := (C.header_t)(header)
	return CHashToGo(C.header_previous_block_hash(ptr))
}

func headerMerkle(header unsafe.Pointer) hashT {
	ptr := (C.header_t)(header)
	return CHashToGo(C.header_merkle(ptr))
}

func headerHash(header unsafe.Pointer) hashT {
	ptr := (C.header_t)(header)
	return CHashToGo(C.header_hash(ptr))
}

// --------------------------------
// Block
// --------------------------------

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

// transaction_t block_transaction_next(transaction_t transaction);

// --------------------------------
// Transaction
// --------------------------------

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

// --------------------------------

// --------------------------------------------------------------------------------

// --------------------------------
// Executor Golang idiomatic Interface
// --------------------------------

type Executor struct {
	native_ptr unsafe.Pointer
}

/*
func (x Executor) Construct() *Executor {
	m := new(matrix)
	m.rows = rows
	m.cols = cols
	m.elems = make([]float, rows*cols)
	return m
}
*/

func NewExecutorWithStd(path string, sin_fd int, sout_fd int, serr_fd int) *Executor {
	x := new(Executor)
	x.native_ptr = ExecutorConstruct(path, sin_fd, sout_fd, serr_fd)
	return x
}

func NewExecutor(path string) *Executor {
	return NewExecutorWithStd(path, syscall.Stdin, syscall.Stdout, syscall.Stderr)
}

func (x *Executor) Close() {
	ExecutorDestruct(x.native_ptr)
	x.native_ptr = nil
}

func (x Executor) Run() int {
	return ExecutorRun(x.native_ptr)
}

func (x Executor) Initchain() int {
	return ExecutorInitchain(x.native_ptr)
}

func (x Executor) FetchLastHeight() int {
	return fetchLastHeight(x.native_ptr)
}

func (x Executor) FetchBlockHeight(hash hashT) int {
	return fetchBlockHeight(x.native_ptr, hash)
}

func (x Executor) FetchBlockHeader(height int) *Header {
	res := NewHeader(fetchBlockHeader(x.native_ptr, height))
	return res
}

func (x Executor) FetchBlockHeaderByHash(hash hashT) *Header {
	res := NewHeader(fetchBlockHeaderByHash(x.native_ptr, hash))
	return res
}

func (x Executor) FetchBlock(height int) *Block {
	res := NewBlock(fetchBlock(x.native_ptr, height))
	return res
}

func (x Executor) FetchBlockByHash(hash hashT) *Block {
	res := NewBlock(fetchBlockByHash(x.native_ptr, hash))
	return res
}

func (x Executor) FetchTransaction(hash hashT, requiredConfirmed bool) *Transaction {
	res := NewTransaction(fetchTransaction(x.native_ptr, hash, requiredConfirmed))
	return res
}

// --------------------------------
// Header Golang idiomatic Interface
// --------------------------------

type Header struct {
	native_ptr unsafe.Pointer
	height     int
}

func NewHeader(native_ptr unsafe.Pointer, height int) *Header {
	x := new(Header)
	x.native_ptr = native_ptr
	x.height = height
	return x
}

func (x *Header) Close() {
	fmt.Printf("Go.Header.Close() - native_ptr: %p\n", x.native_ptr)
	headerDestruct(x.native_ptr)
	x.native_ptr = nil
}

func (x Header) IsValid() bool {
	return headerIsValid(x.native_ptr)
}

func (x Header) Version() int {
	return headerVersion(x.native_ptr)
}

func (x *Header) SetVersion(version int) {
	headerSetVersion(x.native_ptr, version)
}

func (x Header) Timestamp() int {
	return headerTimestamp(x.native_ptr)
}

func (x *Header) SetTimestamp(timestamp int) {
	headerSetTimestamp(x.native_ptr, timestamp)
}

func (x Header) Bits() int {
	return headerBits(x.native_ptr)
}

func (x *Header) SetBits(bits int) {
	headerSetBits(x.native_ptr, bits)
}

func (x Header) Nonce() int {
	return headerNonce(x.native_ptr)
}

func (x *Header) SetNonce(nonce int) {
	headerSetNonce(x.native_ptr, nonce)
}

func (x Header) PreviousBlockHash() hashT {
	return headerPreviousBlockHash(x.native_ptr)
}

func (x Header) Merkle() hashT {
	return headerMerkle(x.native_ptr)
}

func (x Header) Hash() hashT {
	return headerHash(x.native_ptr)
}

// --------------------------------
// Block Golang idiomatic Interface
// --------------------------------

type Block struct {
	native_ptr unsafe.Pointer
	height     int
}

func NewBlock(native_ptr unsafe.Pointer, height int) *Block {
	x := new(Block)
	x.native_ptr = native_ptr
	x.height = height
	return x
}

func (x *Block) Close() {
	fmt.Printf("Go.Block.Close() - native_ptr: %p\n", x.native_ptr)
	blockDestruct(x.native_ptr)
	x.native_ptr = nil
}

func (x Block) IsValid() bool {
	return blockIsValid(x.native_ptr)
}

func (x Block) Hash() hashT {
	return blockHash(x.native_ptr)
}

func (x Block) Header() *Header {
	return NewHeader(blockHeader(x.native_ptr), x.height)
}

func (x Block) Transactions() []Transaction {
	var res []Transaction
	return res
}

// --------------------------------
// Transaction Golang idiomatic Interface
// --------------------------------

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

// ----------------------------------------------------------------
// Test code
// ----------------------------------------------------------------

func cleanup() {
	fmt.Println("cleanup")
}

func reverseHash(h hashT) hashT {
	for i, j := 0, len(h)-1; i < j; i, j = i+1, j-1 {
		h[i], h[j] = h[j], h[i]
	}
	return h
}

func doSomeQueries(e *Executor) {
	// block_hash := reverseHash([32]byte{0x00, 0x00, 0x00, 0x00, 0x7d, 0x07, 0x68, 0x1a, 0x95, 0x5b, 0x7b, 0xb9, 0xd9, 0x6c, 0x47, 0x3e, 0x84, 0x73, 0x95, 0xb5, 0x92, 0xb6, 0xe9, 0xe5, 0xa7, 0x3b, 0x15, 0xb5, 0x94, 0xbd, 0x40, 0x13})
	// //fmt.Println(block_hash)
	// block_height := e.FetchBlockHeight(block_hash)
	// fmt.Printf("block_height: %d\n", block_height)

	// -------------------------------------

	// // 1c773f36f009504e53ef709a3c7f5abb9e7e6f5c26594baf5539e004591c5ae3
	// // 0x1c, 0x77, 0x3f, 0x36, 0xf0, 0x09, 0x50, 0x4e, 0x53, 0xef, 0x70, 0x9a, 0x3c, 0x7f, 0x5a, 0xbb, 0x9e, 0x7e, 0x6f, 0x5c, 0x26, 0x59, 0x4b, 0xaf, 0x55, 0x39, 0xe0, 0x04, 0x59, 0x1c, 0x5a, 0xe3
	// tx_hash := reverseHash([32]byte{0x1c, 0x77, 0x3f, 0x36, 0xf0, 0x09, 0x50, 0x4e, 0x53, 0xef, 0x70, 0x9a, 0x3c, 0x7f, 0x5a, 0xbb, 0x9e, 0x7e, 0x6f, 0x5c, 0x26, 0x59, 0x4b, 0xaf, 0x55, 0x39, 0xe0, 0x04, 0x59, 0x1c, 0x5a, 0xe3})
	// fmt.Println(tx_hash)

	// tx := e.FetchTransaction(tx_hash, false)
	// fmt.Printf("tx.native_ptr: %p\n", tx.native_ptr)
	// fmt.Printf("tx.height:     %d\n", tx.height)
	// fmt.Printf("tx.index:      %d\n", tx.index)
	// fmt.Printf("tx.IsValid():  %t\n", tx.IsValid())
	// fmt.Printf("tx.Version():  %d\n", tx.Version())
	// defer tx.Close()

	// -------------------------------------

	// head := e.FetchBlockHeader(1500)
	// defer head.Close()

	// fmt.Printf("head.native_ptr: %p\n", head.native_ptr)
	// fmt.Printf("head.height:        %d\n", head.height)
	// fmt.Printf("head.IsValid():     %t\n", head.IsValid())
	// fmt.Printf("head.Version():     %d\n", head.Version())
	// fmt.Printf("head.Timestamp():   %d\n", head.Timestamp())
	// fmt.Printf("head.Bits():        %d\n", head.Bits())
	// fmt.Printf("head.Nonce():       %d\n", head.Nonce())
	// fmt.Println("head.PreviousBlockHash():", head.PreviousBlockHash())
	// fmt.Println("head.Merkle():           ", head.Merkle())
	// fmt.Println("head.Hash():             ", head.Hash())

	// prev := e.FetchBlockHeaderByHash(head.PreviousBlockHash())
	// defer prev.Close()
	// fmt.Printf("prev.native_ptr: %p\n", prev.native_ptr)
	// fmt.Printf("prev.height:        %d\n", prev.height)
	// fmt.Printf("prev.IsValid():     %t\n", prev.IsValid())
	// fmt.Printf("prev.Version():     %d\n", prev.Version())
	// fmt.Printf("prev.Timestamp():   %d\n", prev.Timestamp())
	// fmt.Printf("prev.Bits():        %d\n", prev.Bits())
	// fmt.Printf("prev.Nonce():       %d\n", prev.Nonce())
	// fmt.Println("prev.PreviousBlockHash():", prev.PreviousBlockHash())
	// fmt.Println("prev.Merkle():           ", prev.Merkle())
	// fmt.Println("prev.Hash():             ", prev.Hash())

	// -------------------------------------

	block := e.FetchBlock(100000)
	defer block.Close()

	for index, tx := range block.Transactions() {
		fmt.Println("index:     ", index)
		fmt.Println("tx.Hash(): ", tx.Hash())
	}

	// fmt.Printf("block.native_ptr: %p\n", block.native_ptr)
	// fmt.Printf("block.height:        %d\n", block.height)
	// fmt.Printf("block.IsValid():     %t\n", block.IsValid())
	// fmt.Println("block.Hash():             ", block.Hash())

	// fmt.Println("blockTransactionCount(block):   ", blockTransactionCount(block.native_ptr))

	// ptr, n := blockTransactions(block.native_ptr)
	// fmt.Println("blockTransactions(block) ptr: ", ptr)
	// fmt.Println("blockTransactions(block) n:   ", n)

	// fmt.Printf("block.Header().IsValid():     %t\n", block.Header().IsValid())
	// fmt.Printf("block.Header().Version():     %d\n", block.Header().Version())
	// fmt.Printf("block.Header().Timestamp():   %d\n", block.Header().Timestamp())
	// fmt.Printf("block.Header().Bits():        %d\n", block.Header().Bits())
	// fmt.Printf("block.Header().Nonce():       %d\n", block.Header().Nonce())
	// fmt.Println("block.Header().PreviousBlockHash():", block.Header().PreviousBlockHash())
	// fmt.Println("block.Header().Merkle():           ", block.Header().Merkle())
	// fmt.Println("block.Header().Hash():             ", block.Header().Hash())

}

func main() {
	running := true
	fetchLastHeightChannel = make(chan int)
	fetchBlockHeightChannel = make(chan int)

	fetchBlockHeaderChannel1 = make(chan unsafe.Pointer)
	fetchBlockHeaderChannel2 = make(chan int)
	fetchBlockHeaderByHashChannel1 = make(chan unsafe.Pointer)
	fetchBlockHeaderByHashChannel2 = make(chan int)

	fetchBlockChannel1 = make(chan unsafe.Pointer)
	fetchBlockChannel2 = make(chan int)
	fetchBlockByHashChannel1 = make(chan unsafe.Pointer)
	fetchBlockByHashChannel2 = make(chan int)

	fetchTransactionChannel1 = make(chan unsafe.Pointer)
	fetchTransactionChannel2 = make(chan int)

	e := NewExecutor("/pepe")
	//defer e.Close()

	fmt.Println("before RUN")

	//res := e.Initchain()
	res := e.Run()

	if res == 0 {
		e.Close()
		return
	}

	fmt.Println("after RUN")
	fmt.Printf("%d\n", res)

	defer fmt.Println("deferred message")

	// c := make(chan os.Signal, 2)
	c := make(chan os.Signal, 1)

	//signal.Notify(c, os.Interrupt, syscall.SIGINT)
	signal.Notify(c, os.Interrupt, syscall.SIGTERM)

	/*
	   go func() {
	       <-c
	       cleanup()
	       os.Exit(1)
	   }()
	*/

	go func() {

		for sig := range c {
			signal.Notify(c, os.Interrupt, syscall.SIGTERM)
			fmt.Printf("captured %v\n", sig)

			if running {
				running = false
				fmt.Println("cleanup")
				e.Close()
				fmt.Println("exiting..")
				os.Exit(1)
			}

		}
	}()

	for {
		// fmt.Println("running: ", running)
		if running {
			height := e.FetchLastHeight()

			if height >= 100000 {
				doSomeQueries(e)
			} else {
				fmt.Printf("FetchLastHeight: %d\n", height)
			}

		} else {
			//runtime.Gosched()
			fmt.Println("wait...")
		}
		time.Sleep(30 * time.Second) // or runtime.Gosched() or similar per @misterbee
	}
}

/*
func main() {
	fmt.Printf("Hello, world.\n")

	exec := ExecutorConstruct("/pepe", 0, 1, 2)
	// ExecutorInitchain(exec)
	ExecutorRun(exec)
	ExecutorDestruct(exec)

	// fmt.Printf("%d\n", res)
}
*/
