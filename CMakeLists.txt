cmake_minimum_required(VERSION 3.12)
project(meu_modulo)

# Defina o executável do Python
set(PYTHON_EXECUTABLE "C:/Users/NOTE155/AppData/Local/Programs/Python/Python310/python.exe")

# Adicione o subdiretório do Pybind11
add_subdirectory(pybind11)

# Criação do módulo
pybind11_add_module(meu_modulo src/meu_modulo.cpp)
