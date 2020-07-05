#include "simdjson.h"

bool is_ok(const char * filename) {
    simdjson::dom::element doc;
    simdjson::dom::parser parser;
    auto error = parser.load(filename).get(doc);
    if (error) { std::cerr << error << std::endl; return false;}
    return true;
}

extern "C" {

#include <Python.h>

static PyObject *check_if_valid(PyObject *self, PyObject *args) {
    char *char_values;
    if (!PyArg_ParseTuple(args, "s", &char_values)) {
        Py_RETURN_NONE;
    }
    if(is_ok(char_values)) {
      Py_RETURN_TRUE;
    } else {
      Py_RETURN_FALSE;  
    }
}

static PyMethodDef simdjson_methods[] = {
     {"is_valid", check_if_valid, METH_VARARGS, "is valid"},
     {NULL, NULL, 0, NULL}
};



#if PY_MAJOR_VERSION >= 3

static struct PyModuleDef cModsimdjson =
{
    PyModuleDef_HEAD_INIT,
    "simdjson",
    "",
    -1,
    simdjson_methods
};


PyMODINIT_FUNC
PyInit_simdjson(void)
{
     return PyModule_Create(&cModsimdjson);
}

#else

PyMODINIT_FUNC
initsimdjson(void)
{
     (void) Py_InitModule("simdjson", simdjson_methods);
}

#endif

}