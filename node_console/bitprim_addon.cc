#include <node.h>

#include <bitprim/nodecint/executor_c.h>

#include <inttypes.h>   //TODO: Remove, it is for the printf (printing pointer addresses)

namespace bitprim_ns {

using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Value;
using v8::External;
using v8::Exception;
using v8::Number;

//void Method(FunctionCallbackInfo<Value> const& args) {
//    Isolate* isolate = args.GetIsolate();
//    args.GetReturnValue().Set(String::NewFromUtf8(isolate, "world"));
//}


void bitprim_executor_construct(FunctionCallbackInfo<Value> const& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 4) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }

//    printf("args[0]->IsString(): %d\n", args[0]->IsString());
//    printf("args[1]->IsObject(): %d\n", args[1]->IsObject());
//    printf("args[2]->IsObject(): %d\n", args[2]->IsObject());
//    printf("args[3]->IsObject(): %d\n", args[3]->IsObject());

    if ( ! args[0]->IsString() ||
         ! args[1]->IsObject() ||
         ! args[2]->IsObject() ||
         ! args[3]->IsObject()
       ) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
        return;
    }

    v8::String::Utf8Value path(args[0]->ToString());

    auto sin_obj = args[1]->ToObject();
    auto sout_obj = args[2]->ToObject();
    auto serr_obj = args[3]->ToObject();

    auto sin_fd = sin_obj->Get(String::NewFromUtf8(isolate, "fd"))->Int32Value();
    auto sout_fd = sout_obj->Get(String::NewFromUtf8(isolate, "fd"))->Int32Value();
    auto serr_fd = serr_obj->Get(String::NewFromUtf8(isolate, "fd"))->Int32Value();


//    printf("path:    %s\n", *path);
//    printf("sin_fd:  %d\n", sin_fd);
//    printf("sout_fd: %d\n", sout_fd);
//    printf("serr_fd: %d\n", serr_fd);

    executor_t exec = executor_construct_fd(*path, sin_fd, sout_fd, serr_fd);
    printf("bitprim_executor_construct - exec: 0x%" PRIXPTR "\n", (uintptr_t)exec);

    Local<External> ext = External::New(isolate, exec);
    args.GetReturnValue().Set(ext);
}


void bitprim_executor_destruct(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();

    // Check the number of arguments passed.
    if (args.Length() != 1) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }

    if (!args[0]->IsExternal()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
        return;
    }

    void* vptr = v8::External::Cast(*args[0])->Value();
    executor_t exec = (executor_t)vptr;
    executor_destruct(exec);
}



void bitprim_executor_initchain(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();

    // Check the number of arguments passed.
    if (args.Length() != 1) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }

    if (!args[0]->IsExternal()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
        return;
    }

    void* vptr = v8::External::Cast(*args[0])->Value();
    executor_t exec = (executor_t)vptr;
    int res = executor_initchain(exec);

    Local<Number> num = Number::New(isolate, res);
    args.GetReturnValue().Set(num);
}

void bitprim_executor_run(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();

    // Check the number of arguments passed.
    if (args.Length() != 1) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }

    if (!args[0]->IsExternal()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
        return;
    }

    void* vptr = v8::External::Cast(*args[0])->Value();
    executor_t exec = (executor_t)vptr;
    int res = executor_run(exec);

    Local<Number> num = Number::New(isolate, res);
    args.GetReturnValue().Set(num);
}


void init(Local<Object> exports) {
    NODE_SET_METHOD(exports, "construct", bitprim_executor_construct);
    NODE_SET_METHOD(exports, "destruct", bitprim_executor_destruct);
    NODE_SET_METHOD(exports, "initchain", bitprim_executor_initchain);
    NODE_SET_METHOD(exports, "run", bitprim_executor_run);
}

NODE_MODULE(bitprim, init)

}  // namespace bitprim_ns
