from setuptools import setup, Extension

module = Extension('TadRoadForest', sources=['src/TADRoadForest.cpp'], language='c++')

setup(name='TadRoadForest',
      version='1.0',
      description='Módulo de cálculo da função objetivo para o pátio.',
      ext_modules=[module])