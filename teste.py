import sys
import os
import pybind11

import platform
print(platform.architecture())

try:
    import TadRoadForest
    TadRoadForest.calculaFOPatio()
    print("Módulo importado com sucesso!")
except ImportError as e:
    print(f"Erro ao importar o módulo: {e}")