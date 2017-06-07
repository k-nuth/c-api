// --------------------------------
// Executor Golang idiomatic Interface
// --------------------------------

package bitprim

// --------------------------------------------------------------------------------

import (
	"syscall" // or "runtime"
	"unsafe"
)

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
