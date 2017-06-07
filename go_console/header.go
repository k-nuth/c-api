// --------------------------------
// Header Golang idiomatic Interface
// --------------------------------

package bitprim

import (
	"fmt" // or "runtime"
	"unsafe"
)

type Header struct {
	native_ptr unsafe.Pointer
	height     int
}

func NewHeader(native_ptr unsafe.Pointer, height int) *Header {
	x := new(Header)
	x.native_ptr = native_ptr
	x.height = height
	return x
}

func (x *Header) Close() {
	fmt.Printf("Go.Header.Close() - native_ptr: %p\n", x.native_ptr)
	headerDestruct(x.native_ptr)
	x.native_ptr = nil
}

func (x Header) IsValid() bool {
	return headerIsValid(x.native_ptr)
}

func (x Header) Version() int {
	return headerVersion(x.native_ptr)
}

func (x *Header) SetVersion(version int) {
	headerSetVersion(x.native_ptr, version)
}

func (x Header) Timestamp() int {
	return headerTimestamp(x.native_ptr)
}

func (x *Header) SetTimestamp(timestamp int) {
	headerSetTimestamp(x.native_ptr, timestamp)
}

func (x Header) Bits() int {
	return headerBits(x.native_ptr)
}

func (x *Header) SetBits(bits int) {
	headerSetBits(x.native_ptr, bits)
}

func (x Header) Nonce() int {
	return headerNonce(x.native_ptr)
}

func (x *Header) SetNonce(nonce int) {
	headerSetNonce(x.native_ptr, nonce)
}

func (x Header) PreviousBlockHash() hashT {
	return headerPreviousBlockHash(x.native_ptr)
}

func (x Header) Merkle() hashT {
	return headerMerkle(x.native_ptr)
}

func (x Header) Hash() hashT {
	return headerHash(x.native_ptr)
}
