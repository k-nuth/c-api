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
// Transaction
// --------------------------------

package bitprim

// #include <bitprim/nodecint/transaction.h>
import "C"

import (
	"unsafe"
)

func transactionDestruct(tx unsafe.Pointer) {
	ptr := C.transaction_t(tx)
	C.transaction_destruct(ptr)
}

func transactionIsValid(tx unsafe.Pointer) bool {
	ptr := C.transaction_t(tx)
	res := C.transaction_is_valid(ptr)
	return res == 0
}

func transactionVersion(tx unsafe.Pointer) int {
	ptr := C.transaction_t(tx)
	return (int)(C.transaction_version(ptr))
}

func transactionSetVersion(tx unsafe.Pointer, version int) {
	ptr := C.transaction_t(tx)
	C.transaction_set_version(ptr, (C.uint32_t)(version))
}

func transactionHash(tx unsafe.Pointer) HashT {
	ptr := C.transaction_t(tx)
	return CHashToGo(C.transaction_hash(ptr))
}

func transactionHashSighashType(tx unsafe.Pointer, sighash_type uint32) HashT {
	ptr := C.transaction_t(tx)
	return CHashToGo(C.transaction_hash_sighash_type(ptr, C.uint32_t(sighash_type)))
}

// ------------------------------

func transactionLocktime(tx unsafe.Pointer) uint32 {
	return uint32(C.transaction_locktime(C.transaction_t(tx)))
}

func transactionSerializedSize(tx unsafe.Pointer, wire bool /*= true*/) uint64 /*size_t*/ {
	return uint64(C.transaction_serialized_size(C.transaction_t(tx), boolToC(wire)))
}

func transactionFees(tx unsafe.Pointer) uint64 {
	return uint64(C.transaction_fees(C.transaction_t(tx)))
}

func transactionSignatureOperations(tx unsafe.Pointer) uint64 /*size_t*/ {
	return uint64(C.transaction_signature_operations(C.transaction_t(tx)))
}

func transactionSignatureOperationsBip16Active(tx unsafe.Pointer, bip16Active bool) uint64 /*size_t*/ {
	return uint64(C.transaction_signature_operations_bip16_active(C.transaction_t(tx), boolToC(bip16Active)))
}

func transactionTotalInputValue(tx unsafe.Pointer) uint64 {
	return uint64(C.transaction_total_input_value(C.transaction_t(tx)))
}

func transactionTotalOutputValue(tx unsafe.Pointer) uint64 {
	return uint64(C.transaction_total_output_value(C.transaction_t(tx)))
}

func transactionIsCoinbase(tx unsafe.Pointer) bool {
	return CToBool(C.transaction_is_coinbase(C.transaction_t(tx)))
}

func transactionIsNullNonCoinbase(tx unsafe.Pointer) bool {
	return CToBool(C.transaction_is_null_non_coinbase(C.transaction_t(tx)))
}

func transactionIsOversizedCoinbase(tx unsafe.Pointer) bool {
	return CToBool(C.transaction_is_oversized_coinbase(C.transaction_t(tx)))
}

func transactionIsImmature(tx unsafe.Pointer, targetHeight uint64 /*size_t*/) bool {
	return CToBool(C.transaction_is_immature(C.transaction_t(tx), C.size_t(targetHeight)))
}

func transactionIsOverspent(tx unsafe.Pointer) bool {
	return CToBool(C.transaction_is_overspent(C.transaction_t(tx)))
}

func transactionIsDoubleSpend(tx unsafe.Pointer, includeUnconfirmed bool) bool {
	return CToBool(C.transaction_is_double_spend(C.transaction_t(tx), boolToC(includeUnconfirmed)))
}

func transactionIsMissingPreviousOutputs(tx unsafe.Pointer) bool {
	return CToBool(C.transaction_is_missing_previous_outputs(C.transaction_t(tx)))
}

func transactionIsFinal(tx unsafe.Pointer, blockHeight uint64 /*size_t*/, blockTime uint32) bool {
	return CToBool(C.transaction_is_final(C.transaction_t(tx), C.size_t(blockHeight), C.uint32_t(blockTime)))
}

func transactionIsLocktimeConflict(tx unsafe.Pointer) bool {
	return CToBool(C.transaction_is_locktime_conflict(C.transaction_t(tx)))
}

// --------------------------------------

func transactionOutputCount(transaction unsafe.Pointer) int {
	return (int)(C.transaction_output_count(C.transaction_t(transaction)))
}

func transactionOutputNth(transaction unsafe.Pointer, n int) unsafe.Pointer {
	res := C.transaction_output_nth(C.transaction_t(transaction), C.size_t(n))
	return unsafe.Pointer(res)
}

func transactionInputCount(transaction unsafe.Pointer) int {
	return (int)(C.transaction_input_count(C.transaction_t(transaction)))
}

func transactionInputNth(transaction unsafe.Pointer, n int) unsafe.Pointer {
	res := C.transaction_input_nth(C.transaction_t(transaction), C.size_t(n))
	return unsafe.Pointer(res)
}
