// --------------------------------
// Block Golang idiomatic Interface
// --------------------------------

package bitprim

import (
	"fmt" // or "runtime"
	"unsafe"
)

type Block struct {
	native_ptr   unsafe.Pointer
	height       int
	transactions []Transaction
}

func NewBlock(native_ptr unsafe.Pointer, height int) *Block {
	x := new(Block)
	x.native_ptr = native_ptr
	x.height = height

	n := blockTransactionCount(native_ptr)
	i := 0
	for i != n {
		ptr := blockTransactionNth(native_ptr, i)
		tx := NewTransaction(ptr, height, i)
		x.transactions = append(x.transactions, *tx)
		i++
	}

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
	return x.transactions
	//var res []Transaction
	//return res
}
