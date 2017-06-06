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
// ExecutorFetchLastHeight
// --------------------------------

var fetchLastHeightChannel chan int

//export fetchLastHeightGoCallBack
func fetchLastHeightGoCallBack(height int) {
	fmt.Printf("Go.fetchLastHeightGoCallBack(): height = %d\n", height)
	fetchLastHeightChannel <- height
}

func ExecutorFetchLastHeight(exec unsafe.Pointer) int {
	ptr := (*C.struct_executor)(exec)

	fptr := unsafe.Pointer(C.fetchLastHeightGoCallBack_cgo)
	fptr2 := (C.last_height_fetch_handler_t)(fptr)

	go C.executor_fetch_last_height(ptr, fptr2)
	return <-fetchLastHeightChannel
}

// --------------------------------
// ExecutorFetchBlockHeight
// --------------------------------

type hashT [32]byte

var fetchBlockHeightChannel chan int

//export fetchBlockHeightGoCallBack
func fetchBlockHeightGoCallBack(height int) {
	fmt.Printf("Go.fetchBlockHeightGoCallBack(): height = %d\n", height)
	fetchBlockHeightChannel <- height
}

func ExecutorFetchBlockHeight(exec unsafe.Pointer, hash hashT) int {
	ptr := (*C.struct_executor)(exec)

	fptr := unsafe.Pointer(C.fetchBlockHeightGoCallBack_cgo)
	fptr2 := (C.block_height_fetch_handler_t)(fptr)

	hashC := C.CBytes(hash[:])
	defer C.free(hashC)

	go C.executor_fetch_block_height(ptr, (*C.uint8_t)(hashC), fptr2)
	return <-fetchBlockHeightChannel
}

// --------------------------------
// ExecutorFetchBlockHeader
// --------------------------------

var fetchBlockHeaderChannel1 chan unsafe.Pointer
var fetchBlockHeaderChannel2 chan int

//export fetchBlockHeaderGoCallBack
func fetchBlockHeaderGoCallBack(header unsafe.Pointer, height int) {
	fmt.Printf("Go.fetchBlockHeaderGoCallBack(): height = %d\n", height)
	fmt.Printf("Go.fetchBlockHeaderGoCallBack(): header = %p\n", header)

	fetchBlockHeaderChannel1 <- header
	fetchBlockHeaderChannel2 <- height
}

func ExecutorFetchBlockHeader(exec unsafe.Pointer, height int) (unsafe.Pointer, int) {
	ptr := (*C.struct_executor)(exec)

	fptr := unsafe.Pointer(C.fetchBlockHeaderGoCallBack_cgo)
	fptr2 := (C.block_header_fetch_handler_t)(fptr)

	go C.executor_fetch_block_header(ptr, (C.size_t)(height), fptr2)
	return <-fetchBlockHeaderChannel1, <-fetchBlockHeaderChannel2
}

// --------------------------------

// --------------------------------------------------------------------------------

type Executor struct {
	exec_native unsafe.Pointer
}

/*
func (e Executor) Construct() *Executor {
	m := new(matrix)
	m.rows = rows
	m.cols = cols
	m.elems = make([]float, rows*cols)
	return m
}
*/

func NewExecutorWithStd(path string, sin_fd int, sout_fd int, serr_fd int) *Executor {
	e := new(Executor)
	e.exec_native = ExecutorConstruct(path, sin_fd, sout_fd, serr_fd)
	return e
}

func NewExecutor(path string) *Executor {
	return NewExecutorWithStd(path, syscall.Stdin, syscall.Stdout, syscall.Stderr)
}

func (e Executor) Close() {
	ExecutorDestruct(e.exec_native)
}

func (e Executor) Run() int {
	return ExecutorRun(e.exec_native)
}

func (e Executor) Initchain() int {
	return ExecutorInitchain(e.exec_native)
}

func (e Executor) FetchLastHeight() int {
	return ExecutorFetchLastHeight(e.exec_native)
}

func (e Executor) FetchBlockHeight(hash hashT) int {
	return ExecutorFetchBlockHeight(e.exec_native, hash)
}

func (e Executor) FetchBlockHeader(height int) (unsafe.Pointer, int) {
	return ExecutorFetchBlockHeader(e.exec_native, height)
}

/*
func main() {

	e := NewExecutor("/pepe")
	defer e.Close()

	// res := e.Initchain()
	res := e.Run()

	for {
	}

	fmt.Printf("%d\n", res)
}
*/

func cleanup() {
	fmt.Println("cleanup")
}

func reverseHash(h hashT) hashT {
	for i, j := 0, len(h)-1; i < j; i, j = i+1, j-1 {
		h[i], h[j] = h[j], h[i]
	}
	return h
}

func main() {
	running := true
	fetchLastHeightChannel = make(chan int)
	fetchBlockHeightChannel = make(chan int)
	fetchBlockHeaderChannel1 = make(chan unsafe.Pointer)
	fetchBlockHeaderChannel2 = make(chan int)

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
		fmt.Println("running: ", running)
		if running {
			height := e.FetchLastHeight()
			fmt.Printf("height: %d\n", height)

			block_hash := reverseHash([32]byte{0x00, 0x00, 0x00, 0x00, 0x7d, 0x07, 0x68, 0x1a, 0x95, 0x5b, 0x7b, 0xb9, 0xd9, 0x6c, 0x47, 0x3e, 0x84, 0x73, 0x95, 0xb5, 0x92, 0xb6, 0xe9, 0xe5, 0xa7, 0x3b, 0x15, 0xb5, 0x94, 0xbd, 0x40, 0x13})
			fmt.Println(block_hash)

			block_height := e.FetchBlockHeight(block_hash)
			fmt.Printf("block_height: %d\n", block_height)

			block_header_1500, temp := e.FetchBlockHeader(1500)
			fmt.Printf("block_header_1500: %p\n", block_header_1500)
			fmt.Println("temp:             ", temp)
			//TODO: Fer: header object must be copied in C++,
			//			then, the "client language" is responsible for its
			//          release

		} else {
			//runtime.Gosched()
			fmt.Println("wait...")
		}
		time.Sleep(5 * time.Second) // or runtime.Gosched() or similar per @misterbee
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
