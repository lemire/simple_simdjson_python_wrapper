#include "simdjson.h"
#include <chrono>


// simdjson is designed so that you reuse the same parser.
simdjson::dom::parser parser;

bool is_ok(const char *filename) {
  std::chrono::steady_clock::time_point begin, end;
  std::chrono::duration<double> elapsed;
  
  simdjson::padded_string docdata;
  begin = std::chrono::steady_clock::now();
  auto error = simdjson::padded_string::load(filename).get(docdata);
  if (error) {
    std::cerr << "could not parse " << filename << ":" << error << std::endl;
    return false;
  }
  end = std::chrono::steady_clock::now();
  elapsed = end - begin;
  double gb = double(docdata.size()) / 1000000000.;

  std::cout << "loading at " << gb / elapsed.count() << " GB/s" << std::endl;

  for (size_t i = 0; i < 3; i++) {
    std::cout << "trial one : " << i << std::endl;
    begin = std::chrono::steady_clock::now();
    simdjson::dom::element doc;
    if ((error = parser.parse(docdata).get(doc))) {
      std::cerr << "could not parse " << filename << ":" << error << std::endl;
      return false;
    }
    end = std::chrono::steady_clock::now();
    elapsed = end - begin;

    std::cout << "parsing at " << gb / elapsed.count() << " GB/s" << std::endl;
  }
  return true;
}

extern "C" {

#include <Python.h>

static PyObject *check_if_valid(PyObject *self, PyObject *args) {
  char *char_values;
  if (!PyArg_ParseTuple(args, "s", &char_values)) {
    Py_RETURN_NONE;
  }
  if (is_ok(char_values)) {
    Py_RETURN_TRUE;
  } else {
    Py_RETURN_FALSE;
  }
}

static PyMethodDef simdjson_methods[] = {
    {"is_valid", check_if_valid, METH_VARARGS, "is valid"},
    {NULL, NULL, 0, NULL}};

#if PY_MAJOR_VERSION >= 3

static struct PyModuleDef cModsimdjson = {PyModuleDef_HEAD_INIT, "simdjson", "",
                                          -1, simdjson_methods};

PyMODINIT_FUNC PyInit_simdjson(void) { return PyModule_Create(&cModsimdjson); }

#else

PyMODINIT_FUNC initsimdjson(void) {
  (void)Py_InitModule("simdjson", simdjson_methods);
}

#endif
}