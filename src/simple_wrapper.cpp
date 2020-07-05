#include "simdjson.h"
#include <chrono>


// simdjson is designed so that you reuse the same parser.
simdjson::dom::parser parser;
simdjson::padded_string docdata;
bool load_file(const char *filename) {
  auto error = simdjson::padded_string::load(filename).get(docdata);
  if (error) {
    std::cerr << "could not load " << filename << ":" << error << std::endl;
    return false;
  }
  return true;
}

bool is_valid() {
  simdjson::dom::element doc;
  simdjson::error_code error;
  if ((error = parser.parse(docdata).get(doc))) {
    return false;
  }
  return true;
}



bool load_and_check_if_valid_simdjson(const char *filename) {
  
  simdjson::padded_string docdata;
  auto error = simdjson::padded_string::load(filename).get(docdata);
  if (error) {
    std::cerr << "could not parse " << filename << ":" << error << std::endl;
    return false;
  }
  simdjson::dom::element doc;
  if ((error = parser.parse(docdata).get(doc))) {
      return false;
  }
  return true;
}

extern "C" {

#include <Python.h>

static PyObject *load_and_check_if_valid(PyObject *self, PyObject *args) {
  char *char_values;
  if (!PyArg_ParseTuple(args, "s", &char_values)) {
    Py_RETURN_NONE;
  }
  if (load_and_check_if_valid_simdjson(char_values)) {
    Py_RETURN_TRUE;
  } else {
    Py_RETURN_FALSE;
  }
}
static PyObject *load_file(PyObject *self, PyObject *args) {
  char *char_values;
  if (!PyArg_ParseTuple(args, "s", &char_values)) {
    Py_RETURN_NONE;
  }
  if (load_file(char_values)) {
    Py_RETURN_TRUE;
  } else {
    Py_RETURN_FALSE;
  }
}

static PyObject *is_ok(PyObject *self, PyObject *args) {

  if (is_valid()) {
    Py_RETURN_TRUE;
  } else {
    Py_RETURN_FALSE;
  }
}

static PyMethodDef simdjson_methods[] = {
    {"load_and_check_if_valid", load_and_check_if_valid, METH_VARARGS, "is valid"},
    {"load_file", load_file, METH_VARARGS, "load the file"},
    {"is_ok", is_ok, METH_NOARGS, "parse the loaded file and check if it is valid"},
    {NULL, NULL, 0, NULL}};

#if PY_MAJOR_VERSION >= 3

static struct PyModuleDef cModsimdjson = {PyModuleDef_HEAD_INIT, "simdjson_demo", "",
                                          -1, simdjson_methods};

PyMODINIT_FUNC PyInit_simdjson_demo(void) { return PyModule_Create(&cModsimdjson); }

#else

PyMODINIT_FUNC initsimdjson_demo(void) {
  (void)Py_InitModule("simdjson_demo", simdjson_methods);
}

#endif
}