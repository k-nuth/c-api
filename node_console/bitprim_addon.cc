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

    if (args.Length() != 3) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }

//    printf("args[0]->IsString(): %d\n", args[0]->IsString());
//    printf("args[1]->IsObject(): %d\n", args[1]->IsObject());
//    printf("args[2]->IsObject(): %d\n", args[2]->IsObject());

    if ( ! args[0]->IsString() ||
         ! args[1]->IsObject() ||
         ! args[2]->IsObject()
       ) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
        return;
    }

    v8::String::Utf8Value path(args[0]->ToString());

//    printf("xxxxx 1\n");

    auto sout_obj = args[1]->ToObject();
    auto serr_obj = args[2]->ToObject();


//    printf("sout_obj->IsUndefined():    %d\n", sout_obj->IsUndefined());
//    printf("sout_obj->IsNull():         %d\n", sout_obj->IsNull());
//    printf("sout_obj->IsTrue():         %d\n", sout_obj->IsTrue());
//    printf("sout_obj->IsFalse():        %d\n", sout_obj->IsFalse());
//    printf("sout_obj->IsString():       %d\n", sout_obj->IsString());
//    printf("sout_obj->IsFunction():     %d\n", sout_obj->IsFunction());
//    printf("sout_obj->IsArray():        %d\n", sout_obj->IsArray());
//    printf("sout_obj->IsObject():       %d\n", sout_obj->IsObject());
//    printf("sout_obj->IsBoolean():      %d\n", sout_obj->IsBoolean());
//    printf("sout_obj->IsNumber():       %d\n", sout_obj->IsNumber());
//    printf("sout_obj->IsExternal():     %d\n", sout_obj->IsExternal());
//    printf("sout_obj->IsInt32():        %d\n", sout_obj->IsInt32());
//    printf("sout_obj->IsUint32():       %d\n", sout_obj->IsUint32());
//    printf("sout_obj->IsDate():         %d\n", sout_obj->IsDate());
//    printf("sout_obj->IsBooleanObject():%d\n", sout_obj->IsBooleanObject());
//    printf("sout_obj->IsNumberObject(): %d\n", sout_obj->IsNumberObject());
//    printf("sout_obj->IsStringObject(): %d\n", sout_obj->IsStringObject());
//    printf("sout_obj->IsNativeError():  %d\n", sout_obj->IsNativeError());
//    printf("sout_obj->IsRegExp():       %d\n", sout_obj->IsRegExp());


//    printf("xxxxx 2\n");

    auto yyyy = sout_obj->Get(String::NewFromUtf8(isolate, "fd"));

//    printf("yyyy->IsUndefined():    %d\n", yyyy->IsUndefined());
//    printf("yyyy->IsNull():         %d\n", yyyy->IsNull());
//    printf("yyyy->IsTrue():         %d\n", yyyy->IsTrue());
//    printf("yyyy->IsFalse():        %d\n", yyyy->IsFalse());
//    printf("yyyy->IsString():       %d\n", yyyy->IsString());
//    printf("yyyy->IsFunction():     %d\n", yyyy->IsFunction());
//    printf("yyyy->IsArray():        %d\n", yyyy->IsArray());
//    printf("yyyy->IsObject():       %d\n", yyyy->IsObject());
//    printf("yyyy->IsBoolean():      %d\n", yyyy->IsBoolean());
//    printf("yyyy->IsNumber():       %d\n", yyyy->IsNumber());
//    printf("yyyy->IsExternal():     %d\n", yyyy->IsExternal());
//    printf("yyyy->IsInt32():        %d\n", yyyy->IsInt32());
//    printf("yyyy->IsUint32():       %d\n", yyyy->IsUint32());
//    printf("yyyy->IsDate():         %d\n", yyyy->IsDate());
//    printf("yyyy->IsBooleanObject():%d\n", yyyy->IsBooleanObject());
//    printf("yyyy->IsNumberObject(): %d\n", yyyy->IsNumberObject());
//    printf("yyyy->IsStringObject(): %d\n", yyyy->IsStringObject());
//    printf("yyyy->IsNativeError():  %d\n", yyyy->IsNativeError());
//    printf("yyyy->IsRegExp():       %d\n", yyyy->IsRegExp());


//    printf("xxxxx 3\n");

//    printf("yyyy: %d\n", yyyy);

    auto sout_fd = sout_obj->Get(String::NewFromUtf8(isolate, "fd"))->Int32Value();
    auto serr_fd = serr_obj->Get(String::NewFromUtf8(isolate, "fd"))->Int32Value();

//    printf("path:    %s\n", *path);
//    printf("sout_fd: %d\n", sout_fd);
//    printf("serr_fd: %d\n", serr_fd);

    executor_t exec = executor_construct_fd(*path, sout_fd, serr_fd);
//    printf("bitprim_executor_construct - exec: 0x%" PRIXPTR "\n", (uintptr_t)exec);

    Local<External> ext = External::New(isolate, exec);
//    printf("xxxxx 4\n");
    args.GetReturnValue().Set(ext);
//    printf("xxxxx 5\n");
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

//void bitprim_executor_run(const FunctionCallbackInfo<Value>& args) {
//    Isolate* isolate = args.GetIsolate();
//
//    // Check the number of arguments passed.
//    if (args.Length() != 1) {
//        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
//        return;
//    }
//
//    if (!args[0]->IsExternal()) {
//        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
//        return;
//    }
//
//    void* vptr = v8::External::Cast(*args[0])->Value();
//    executor_t exec = (executor_t)vptr;
//    int res = executor_run(exec);
//
//    Local<Number> num = Number::New(isolate, res);
//    args.GetReturnValue().Set(num);
//}

void bitprim_executor_run_wait(const FunctionCallbackInfo<Value>& args) {
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
    int res = executor_run_wait(exec);

    Local<Number> num = Number::New(isolate, res);
    args.GetReturnValue().Set(num);
}


void init(Local<Object> exports) {
    NODE_SET_METHOD(exports, "construct", bitprim_executor_construct);
    NODE_SET_METHOD(exports, "destruct", bitprim_executor_destruct);
    NODE_SET_METHOD(exports, "initchain", bitprim_executor_initchain);
//    NODE_SET_METHOD(exports, "run", bitprim_executor_run);
    NODE_SET_METHOD(exports, "run_wait", bitprim_executor_run_wait);


}

NODE_MODULE(bitprim, init)

}  // namespace bitprim_ns
