package main

// Gateway functions

/*
#include <stdio.h>

void fetchLastHeightGoCallBack_cgo(int height) {
	printf("C.fetchLastHeightGoCallBack_cgo(): height = %d\n", height);
	void fetchLastHeightGoCallBack(int);
	fetchLastHeightGoCallBack(height);
}

void fetchBlockHeightGoCallBack_cgo(int height) {
	printf("C.fetchBlockHeightGoCallBack_cgo(): height = %d\n", height);
	void fetchBlockHeightGoCallBack(int);
	fetchBlockHeightGoCallBack(height);
}

*/
import "C"
