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
#cgo CFLAGS: -I/home/fernando/dev/bitprim/bitprim-node-cint/include
#cgo LDFLAGS: -L/home/fernando/dev/bitprim/bitprim-node-cint/cmake-build-debug -lbitprim-node-cint

#include <stdio.h>
#include <stdlib.h>
#include <bitprim/nodecint/executor_c.h>

typedef void (*fetch_last_height_handler)(int);

void fetchLastHeightGoCallBack_cgo(int in); // Forward declaration.

static inline void fetch_last_height(fetch_last_height_handler handler) {
	printf("C.fetch_last_height()\n");
	handler(999);
}
*/
import "C"

// --------------------------------------------------------------------------------

import (
	"fmt"
	"os"
	"os/signal"
	"runtime"
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
	//C.executor_fetch_last_height(ptr, ...)

	fptr := unsafe.Pointer(C.fetchLastHeightGoCallBack_cgo)
	fptr2 := (C.last_height_fetch_handler_t)(fptr)

	go C.executor_fetch_last_height(ptr, fptr2)
	return <-fetchLastHeightChannel
}

/*
 *
 *
// typedef void (*last_height_fetch_handler_t)(void* client_data, const char* name, int32_t votes, const char* html);
typedef void (*last_height_fetch_handler_t)(size_t h);


BITPRIM_EXPORT
void executor_fetch_last_height(executor_t exec, last_height_fetch_handler_t handler) {
//    exec->actual.node().chain().fetch_last_height(handler);
//    exec->actual.node().chain().fetch_last_height([handler](size_t h){ handler(h);});
    exec->actual.node().chain().fetch_last_height([handler](std::error_code const& ec, size_t h) {
        handler(h);
    });
}

*/

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

func main() {
	running := true
	fetchLastHeightChannel = make(chan int)

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
			fmt.Printf("captured %v\n", sig)
			//pprof.StopCPUProfile()

			if running {
				fmt.Println("cleanup")
				e.Close()
				fmt.Println("exiting..")
				os.Exit(1)
			}
			running = false
			// signal.Notify(c, os.Interrupt, syscall.SIGTERM)
		}
	}()

	for {
		if running {
			height := e.FetchLastHeight()
			fmt.Printf("height: %d\n", height)
		}

		runtime.Gosched()
		fmt.Println("sleeping...")
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
