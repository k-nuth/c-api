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

package bitprim

// package main

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

// ----------------------------------------------------------------
// Test code
// ----------------------------------------------------------------

// func cleanup() {
// 	fmt.Println("cleanup")
// }

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

	//TODO: Fer: ver donde ubicamos todos estos channels.
	//TODO: Fer: consular con expertos en Golang a ver si es la forma correcta de pasar de un esquema asincronico a uno sincronico
	// ----------------------------------------------------------

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

	fetchOutputChannel = make(chan unsafe.Pointer)

	// ----------------------------------------------------------

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
