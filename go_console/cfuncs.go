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

package bitprim

// Gateway functions

/*
#include <stdio.h>

void fetchLastHeightGoCallBack_cgo(int error, size_t height) {
	// printf("C.fetchLastHeightGoCallBack_cgo(): height = %lu\n", height);
	void FetchLastHeightGoCallBack(int, size_t);
	FetchLastHeightGoCallBack(error, height);
}

void fetchBlockHeightGoCallBack_cgo(int error, size_t height) {
	// printf("C.fetchBlockHeightGoCallBack_cgo(): height = %lu\n", height);
	void FetchBlockHeightGoCallBack(int, size_t);
	FetchBlockHeightGoCallBack(error, height);
}

void fetchBlockHeaderGoCallBack_cgo(int error, void* header, size_t height) {
	// printf("C.fetchBlockHeaderGoCallBack_cgo(): header = ?, height = %lu\n", height);
	void FetchBlockHeaderGoCallBack(int, void*, int);
	FetchBlockHeaderGoCallBack(error, header, height);
}

void fetchBlockHeaderByHashGoCallBack_cgo(int error, void* header, size_t height) {
	// printf("C.fetchBlockHeaderByHashGoCallBack_cgo(): header = ?, height = %lu\n", height);
	void FetchBlockHeaderByHashGoCallBack(int, void*, int);
	FetchBlockHeaderByHashGoCallBack(error, header, height);
}

void fetchBlockGoCallBack_cgo(int error, void* block, size_t height) {
	// printf("C.fetchBlockGoCallBack_cgo(): block = ?, height = %lu\n", height);
	void FetchBlockGoCallBack(int, void*, int);
	FetchBlockGoCallBack(error, block, height);
}

void fetchBlockByHashGoCallBack_cgo(int error, void* block, size_t height) {
	// printf("C.fetchBlockByHashGoCallBack_cgo(): block = ?, height = %lu\n", height);
	void FetchBlockByHashGoCallBack(int, void*, int);
	FetchBlockByHashGoCallBack(error, block, height);
}

void fetchTransactionGoCallBack_cgo(int error, void* transaction, size_t height, size_t index) {
	// printf("C.fetchTransactionGoCallBack_cgo(): transaction = ?, height = %lu, index = %lu\n", height, index);
	void FetchTransactionGoCallBack(int, void*, int, int);
	FetchTransactionGoCallBack(error, transaction, height, index);
}

void fetchOutputGoCallBack_cgo(int error, void* output) {
	// printf("C.fetchTransactionGoCallBack_cgo(): output = ?\n");
	void FetchOutputGoCallBack(int, void*);
	FetchOutputGoCallBack(error, output);
}

*/
import "C"
