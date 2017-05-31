#include <Python.h>

#include <bitprim/nodecint/executor_c.h>

static
PyObject* module_executor_construct(PyObject* self, PyObject* args) {
    char const* path;
    PyObject* py_in;
    PyObject* py_out;
    PyObject* py_err;

    if ( ! PyArg_ParseTuple(args, "sOOO", &path, &py_in, &py_out, &py_err))
        return NULL;

    FILE* sin = PyFile_AsFile(py_in);
    FILE* sout = PyFile_AsFile(py_out);
    FILE* serr = PyFile_AsFile(py_err);

//    PyFile_IncUseCount(p);
///* ... */
//    Py_BEGIN_ALLOW_THREADS
//        do_something(fp);
//    Py_END_ALLOW_THREADS
///* ... */
//        PyFile_DecUseCount(p);



    executor_t exec = executor_construct(path, sin, sout, serr);

    return PyCObject_FromVoidPtr(exec, NULL);
}

static
PyObject* module_executor_destruct(PyObject* self, PyObject* args) {
    PyObject* py_exec;

    if ( ! PyArg_ParseTuple(args, "O", &py_exec))
        return NULL;

    executor_t exec = (executor_t)PyCObject_AsVoidPtr(py_exec);
    executor_destruct(exec);
    return Py_BuildValue("");
}

static
PyObject* module_executor_initchain(PyObject* self, PyObject* args) {
    PyObject* py_exec;

    if ( ! PyArg_ParseTuple(args, "O", &py_exec))
        return NULL;

    executor_t exec = (executor_t)PyCObject_AsVoidPtr(py_exec);
    int res = executor_initchain(exec);
    return Py_BuildValue("i", res);
}


static
PyMethodDef BitprimMethods[] = {

    {"construct",  module_executor_construct, METH_VARARGS, "Construct the executor object."},
    {"destruct",  module_executor_destruct, METH_VARARGS, "Destruct the executor object."},
    {"initchain",  module_executor_initchain, METH_VARARGS, "Directory Initialization."},

    {NULL, NULL, 0, NULL}        /* Sentinel */
};

PyMODINIT_FUNC
initbitprim(void) {
    (void) Py_InitModule("bitprim", BitprimMethods);
}