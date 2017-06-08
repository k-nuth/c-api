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
	"fmt" // or "runtime"
	"unsafe"
)

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

// -----------------------------------

func (x Transaction) Locktime() uint32 {
	return transactionLocktime(x.native_ptr)
}

func (x Transaction) SerializedSize(wire bool /*= true*/) uint64 /*size_t*/ {
	return transactionSerializedSize(x.native_ptr, wire)
}

func (x Transaction) Fees() uint64 {
	return transactionFees(x.native_ptr)
}

func (x Transaction) SignatureOperations() uint64 /*size_t*/ {
	return transactionSignatureOperations(x.native_ptr)
}

func (x Transaction) SignatureOperationsBip16Active(bip16Active bool) uint64 /*size_t*/ {
	return transactionSignatureOperationsBip16Active(x.native_ptr, bip16Active)
}

func (x Transaction) TotalInputValue() uint64 {
	return transactionTotalInputValue(x.native_ptr)
}

func (x Transaction) TotalOutputValue() uint64 {
	return transactionTotalOutputValue(x.native_ptr)
}

func (x Transaction) IsCoinbase() bool {
	return transactionIsCoinbase(x.native_ptr)
}

func (x Transaction) IsNullNonCoinbase() bool {
	return transactionIsNullNonCoinbase(x.native_ptr)
}

func (x Transaction) IsOversizedCoinbase() bool {
	return transactionIsOversizedCoinbase(x.native_ptr)
}

func (x Transaction) IsImmature(targetHeight uint64 /*size_t*/) bool {
	return transactionIsImmature(x.native_ptr, targetHeight)
}

func (x Transaction) IsOverspent() bool {
	return transactionIsOverspent(x.native_ptr)
}

func (x Transaction) IsDoubleSpend(includeUnconfirmed bool) bool {
	return transactionIsDoubleSpend(x.native_ptr, includeUnconfirmed)
}

func (x Transaction) IsMissingPreviousOutputs() bool {
	return transactionIsMissingPreviousOutputs(x.native_ptr)
}

func (x Transaction) IsFinal(blockHeight uint64 /*size_t*/, blockTime uint32) bool {
	return transactionIsFinal(x.native_ptr, blockHeight, blockTime)
}

func (x Transaction) IsLocktimeConflict() bool {
	return transactionIsLocktimeConflict(x.native_ptr)
}
