package main

// Gateway functions

/*
#include <stdio.h>

void fetchLastHeightGoCallBack_cgo(int error, size_t height) {
	// printf("C.fetchLastHeightGoCallBack_cgo(): height = %lu\n", height);
	void fetchLastHeightGoCallBack(int, size_t);
	fetchLastHeightGoCallBack(error, height);
}

void fetchBlockHeightGoCallBack_cgo(int error, size_t height) {
	// printf("C.fetchBlockHeightGoCallBack_cgo(): height = %lu\n", height);
	void fetchBlockHeightGoCallBack(int, size_t);
	fetchBlockHeightGoCallBack(error, height);
}

void fetchBlockHeaderGoCallBack_cgo(int error, void* header, size_t height) {
	// printf("C.fetchBlockHeaderGoCallBack_cgo(): header = ?, height = %lu\n", height);
	void fetchBlockHeaderGoCallBack(int, void*, int);
	fetchBlockHeaderGoCallBack(error, header, height);
}

void fetchBlockHeaderByHashGoCallBack_cgo(int error, void* header, size_t height) {
	// printf("C.fetchBlockHeaderByHashGoCallBack_cgo(): header = ?, height = %lu\n", height);
	void fetchBlockHeaderByHashGoCallBack(int, void*, int);
	fetchBlockHeaderByHashGoCallBack(error, header, height);
}

void fetchBlockGoCallBack_cgo(int error, void* block, size_t height) {
	// printf("C.fetchBlockGoCallBack_cgo(): block = ?, height = %lu\n", height);
	void fetchBlockGoCallBack(int, void*, int);
	fetchBlockGoCallBack(error, block, height);
}

void fetchBlockByHashGoCallBack_cgo(int error, void* block, size_t height) {
	// printf("C.fetchBlockByHashGoCallBack_cgo(): block = ?, height = %lu\n", height);
	void fetchBlockByHashGoCallBack(int, void*, int);
	fetchBlockByHashGoCallBack(error, block, height);
}

void fetchTransactionGoCallBack_cgo(int error, void* transaction, size_t height, size_t index) {
	// printf("C.fetchTransactionGoCallBack_cgo(): transaction = ?, height = %lu, index = %lu\n", height, index);
	void fetchTransactionGoCallBack(int, void*, int, int);
	fetchTransactionGoCallBack(error, transaction, height, index);
}
*/
import "C"
