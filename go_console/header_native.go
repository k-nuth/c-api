// --------------------------------
// Header
// --------------------------------

package bitprim

// #include <bitprim/nodecint/header.h>
import "C"

import (
	"unsafe"
)

func headerDestruct(header unsafe.Pointer) {
	ptr := (C.header_t)(header)
	C.header_destruct(ptr)
}

func headerIsValid(header unsafe.Pointer) bool {
	ptr := (C.header_t)(header)
	res := C.header_is_valid(ptr)
	return res == 0
}

func headerVersion(header unsafe.Pointer) int {
	ptr := (C.header_t)(header)
	return (int)(C.header_version(ptr))
}

func headerSetVersion(header unsafe.Pointer, version int) {
	ptr := (C.header_t)(header)
	C.header_set_version(ptr, (C.uint32_t)(version))
}

func headerTimestamp(header unsafe.Pointer) int {
	ptr := (C.header_t)(header)
	return (int)(C.header_timestamp(ptr))
}

func headerSetTimestamp(header unsafe.Pointer, timestamp int) {
	ptr := (C.header_t)(header)
	C.header_set_timestamp(ptr, (C.uint32_t)(timestamp))
}

func headerBits(header unsafe.Pointer) int {
	ptr := (C.header_t)(header)
	return (int)(C.header_bits(ptr))
}

func headerSetBits(header unsafe.Pointer, bits int) {
	ptr := (C.header_t)(header)
	C.header_set_bits(ptr, (C.uint32_t)(bits))
}

func headerNonce(header unsafe.Pointer) int {
	ptr := (C.header_t)(header)
	return (int)(C.header_nonce(ptr))
}

func headerSetNonce(header unsafe.Pointer, nonce int) {
	ptr := (C.header_t)(header)
	C.header_set_nonce(ptr, (C.uint32_t)(nonce))
}

func headerPreviousBlockHash(header unsafe.Pointer) hashT {
	ptr := (C.header_t)(header)
	return CHashToGo(C.header_previous_block_hash(ptr))
}

func headerMerkle(header unsafe.Pointer) hashT {
	ptr := (C.header_t)(header)
	return CHashToGo(C.header_merkle(ptr))
}

func headerHash(header unsafe.Pointer) hashT {
	ptr := (C.header_t)(header)
	return CHashToGo(C.header_hash(ptr))
}
