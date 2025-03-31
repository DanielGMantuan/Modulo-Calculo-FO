#include <pybind11/pybind11.h>

int add(int a, int b) {
    return a + b;
}

PYBIND11_MODULE(meu_modulo, m) {
    m.def("add", &add, "Uma função que soma dois números");
}
