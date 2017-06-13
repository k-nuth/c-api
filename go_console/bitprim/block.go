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

func (x Block) Hash() HashT {
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

func (x Block) SerializedSize(version uint32) uint64 /*size_t*/ {
	return blockSerializedSize(x.native_ptr, version)
}

/*static*/
func (x Block) Subsidy(height uint64 /*size_t*/) uint64 {
	return blockSubsidy(height)
}

func (x Block) Fees(block unsafe.Pointer) uint64 {
	return blockFees(x.native_ptr)
}

func (x Block) Claim(block unsafe.Pointer) uint64 {
	return blockClaim(x.native_ptr)
}

func (x Block) Reward(height uint64) uint64 {
	return blockReward(x.native_ptr, height)
}

func (x Block) GenerateMerkleRoot(block unsafe.Pointer) HashT {
	return blockGenerateMerkleRoot(x.native_ptr)
}

func (x Block) SignatureOperations() uint64 /*size_t*/ {
	return blockSignatureOperations(x.native_ptr)
}

func (x Block) SignatureOperationsBip16Active(bip16_active bool) uint64 /*size_t*/ {
	return blockSignatureOperationsBip16Active(x.native_ptr, bip16_active)
}

func (x Block) TotalInputs(with_coinbase bool) uint64 /*size_t*/ {
	return blockTotalInputs(x.native_ptr, with_coinbase)
}

func (x Block) IsExtraCoinbases(block unsafe.Pointer) bool {
	return blockIsExtraCoinbases(x.native_ptr)
}

func (x Block) IsFinal(height uint64 /*size_t*/) bool {
	return blockIsFinal(x.native_ptr, height)
}

func (x Block) IsDistinctTransactionSet(block unsafe.Pointer) bool {
	return blockIsDistinctTransactionSet(x.native_ptr)
}

func (x Block) IsValidCoinbaseClaim(height uint64 /*size_t*/) bool {
	return blockIsValidCoinbaseClaim(x.native_ptr, height)
}

func (x Block) IsValidCoinbaseScript(height uint64 /*size_t*/) bool {
	return blockIsValidCoinbaseScript(x.native_ptr, height)
}

func (x Block) IsInternalDoubleSpend(block unsafe.Pointer) bool {
	return blockIsInternalDoubleSpend(x.native_ptr)
}

func (x Block) IsValidMerkleRoot(block unsafe.Pointer) bool {
	return blockIsValidMerkleRoot(x.native_ptr)
}
