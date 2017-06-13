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
// Transaction Golang idiomatic Interface
// --------------------------------

package bitprim

import (
	"unsafe"
)

type Transaction struct {
	ptr     unsafe.Pointer
	height  int
	index   int
	outputs []Output
	inputs  []Input
}

func NewTransaction(ptr unsafe.Pointer, height int, index int) *Transaction {
	x := new(Transaction)
	x.ptr = ptr
	x.height = height
	x.index = index

	n := transactionOutputCount(ptr)
	i := 0
	for i != n {
		ptr := transactionOutputNth(ptr, i)
		out := NewOutput(ptr)
		x.outputs = append(x.outputs, *out)
		i++
	}

	n = transactionInputCount(ptr)
	i = 0
	for i != n {
		ptr := transactionInputNth(ptr, i)
		in := NewInput(ptr)
		x.inputs = append(x.inputs, *in)
		i++
	}

	return x
}

func (x *Transaction) Close() {
	// fmt.Printf("Go.Transaction.Close() - ptr: %p\n", x.ptr)
	transactionDestruct(x.ptr)
	x.ptr = nil
}

func (x Transaction) IsValid() bool {
	return transactionIsValid(x.ptr)
}

func (x Transaction) Version() int {
	return transactionVersion(x.ptr)
}

func (x *Transaction) SetVersion(version int) {
	transactionSetVersion(x.ptr, version)
}

func (x Transaction) Hash() HashT {
	return transactionHash(x.ptr)
}

func (x Transaction) HashSighashType(sighash_type uint32) HashT {
	return transactionHashSighashType(x.ptr, sighash_type)
}

// -----------------------------------

func (x Transaction) Locktime() uint32 {
	return transactionLocktime(x.ptr)
}

func (x Transaction) SerializedSize(wire bool /*= true*/) uint64 /*size_t*/ {
	return transactionSerializedSize(x.ptr, wire)
}

func (x Transaction) Fees() uint64 {
	return transactionFees(x.ptr)
}

func (x Transaction) SignatureOperations() uint64 /*size_t*/ {
	return transactionSignatureOperations(x.ptr)
}

func (x Transaction) SignatureOperationsBip16Active(bip16Active bool) uint64 /*size_t*/ {
	return transactionSignatureOperationsBip16Active(x.ptr, bip16Active)
}

func (x Transaction) TotalInputValue() uint64 {
	return transactionTotalInputValue(x.ptr)
}

func (x Transaction) TotalOutputValue() uint64 {
	return transactionTotalOutputValue(x.ptr)
}

func (x Transaction) IsCoinbase() bool {
	return transactionIsCoinbase(x.ptr)
}

func (x Transaction) IsNullNonCoinbase() bool {
	return transactionIsNullNonCoinbase(x.ptr)
}

func (x Transaction) IsOversizedCoinbase() bool {
	return transactionIsOversizedCoinbase(x.ptr)
}

func (x Transaction) IsImmature(targetHeight uint64 /*size_t*/) bool {
	return transactionIsImmature(x.ptr, targetHeight)
}

func (x Transaction) IsOverspent() bool {
	return transactionIsOverspent(x.ptr)
}

func (x Transaction) IsDoubleSpend(includeUnconfirmed bool) bool {
	return transactionIsDoubleSpend(x.ptr, includeUnconfirmed)
}

func (x Transaction) IsMissingPreviousOutputs() bool {
	return transactionIsMissingPreviousOutputs(x.ptr)
}

func (x Transaction) IsFinal(blockHeight uint64 /*size_t*/, blockTime uint32) bool {
	return transactionIsFinal(x.ptr, blockHeight, blockTime)
}

func (x Transaction) IsLocktimeConflict() bool {
	return transactionIsLocktimeConflict(x.ptr)
}

func (x Transaction) Inputs() []Input {
	return x.inputs
}

func (x Transaction) Outputs() []Output {
	return x.outputs
}
