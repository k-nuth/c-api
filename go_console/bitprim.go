/*
export PATH=$PATH:$(/usr/lib/go-1.8/bin/go env GOPATH)/bin
export GOPATH=$(go env GOPATH)
*/

// 1. 	go install github.com/fpelliccioni/bitprim
// 2.	cd $GOPATH/src/github.com/fpelliccioni/bitprim
// 		go install

// export LD_LIBRARY_PATH=/home/fernando/dev/bitprim/bitprim-node-cint/cmake-build-debug:$LD_LIBRARY_PATH
// $GOPATH/bin/bitprim

// package bitprim
package main


// #cgo CFLAGS: -I/home/fernando/dev/bitprim/bitprim-node-cint/include
// #cgo LDFLAGS: -L/home/fernando/dev/bitprim/bitprim-node-cint/cmake-build-debug -lbitprim-node-cint
// #include <bitprim/nodecint/executor_c.h>
import "C"


import "fmt"
import "unsafe"
//import "os"
import "syscall"


func ExecutorConstruct(path string, sin_fd int, sout_fd int, serr_fd int) unsafe.Pointer {
    exec := C.executor_construct_fd(C.CString(path), C.int(sin_fd), C.int(sout_fd), C.int(serr_fd))
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

func main() {
	
	// ptrFromSystem := (*uint64)(unsafe.Pointer(os.Stdout.Fd))
	// uint64FromSystem = uint64(valFromSystem)
	// fmt.Printf("os.Stdout.Fd = %d\n", uint64FromSystem)
	
	//fmt.Printf("os.Stdout.Fd = %d\n", *(os.Stdout.Fd))
	

	e := NewExecutor("/pepe")
	//e := NewExecutor("/pepe", 5, 6, 7)
	defer e.Close()

	// res := e.Initchain()
	res := e.Run()
	
	fmt.Printf("%d\n", res)
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
