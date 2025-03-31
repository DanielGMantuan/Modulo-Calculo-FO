// python setup.py build_ext --inplace

#include <Python.h>
#include <iostream>
#include <vector>
#include <limits>

class Arvore {
public:
    int id;
    int numero;

    Arvore(int f, int s) : id(f), numero(s) {}
};

// Definições das estruturas
struct SolucaoStorageYard {
    std::vector<int> patios;
    std::vector<std::vector<Arvore>> arvores;
    std::vector<double> volumes;
    double distanciaTotal;
    double FO;
    double tempoSol;
    double tempo;
    double t;
    int numIteracoes;
    int numViaveis;
    int numInviaveis;
    bool viavel;
};

struct ArvoreExploravel {
    int id;
    int numero;
    double DAP;
    double H;
    double areaBasal;
    double volume;
    double x;
    double y;
    double z;
};

// Definindo variáveis globais
std::vector<ArvoreExploravel> florestaGlobal;
std::vector<std::vector<double>> distanciasGlobal;
double distanciaMaximaGlobal;
int penalizacaoVolumeGlobal;
int numArvoresExploraveisGlobal;
int numPatiosGlobal;
int numVerticesPatiosGlobal;

// Função para calcular a FO
void calculaFOPatio(SolucaoStorageYard& solAtual, double restVolSup) {
    double distanciaMenor, distancia;
    double diferencaVolume = 0, diferencaDistancia = 0;
    double distanciaTotal = 0;
    int i, j, k, patio;

    for (i = 0; i < numPatiosGlobal; i++) {
        solAtual.volumes[i] = 0;
        solAtual.arvores[i].clear();
    }

    for (j = 0; j < numArvoresExploraveisGlobal; j++) {
        distanciaMenor = std::numeric_limits<double>::infinity();
        patio = 0;
        for (k = 0; k < numPatiosGlobal; k++) {
            distancia = distanciasGlobal[j][solAtual.patios[k] - 1];
            if (distancia < distanciaMenor) {
                distanciaMenor = distancia;
                patio = k;
            }
        }
        if (distanciaMenor > distanciaMaximaGlobal)
            diferencaDistancia += distanciaMenor - distanciaMaximaGlobal;
        distanciaTotal += distanciaMenor;

        solAtual.arvores[patio].push_back(Arvore(florestaGlobal[j].id, florestaGlobal[j].numero));
        solAtual.volumes[patio] += florestaGlobal[j].volume;
    }

    for (i = 0; i < numPatiosGlobal; i++) {
        diferencaVolume += (solAtual.volumes[i] > restVolSup) ? solAtual.volumes[i] - restVolSup : 0;
    }

    solAtual.distanciaTotal = distanciaTotal;
    distanciaTotal += penalizacaoVolumeGlobal * (diferencaVolume + diferencaDistancia);

    solAtual.FO = distanciaTotal;
    solAtual.viavel = (diferencaVolume + diferencaDistancia) == 0;
}

// Função wrapper para armazenar as informações de floresta e distâncias em variáveis globais
static PyObject* py_definicaoVariaveisGlobais(PyObject* self, PyObject* args) {
    PyObject *py_floresta, *py_distancias;

    // Parsing dos argumentos
    if (!PyArg_ParseTuple(args, "OOiiiid", &py_floresta, &py_distancias, &numPatiosGlobal, &numArvoresExploraveisGlobal, &numVerticesPatiosGlobal, &penalizacaoVolumeGlobal, &distanciaMaximaGlobal)) {
        PyErr_Print(); // Imprime erro de parsing
        return NULL;
    }

    // Limpar variáveis globais anteriores
    florestaGlobal.clear();
    distanciasGlobal.clear();

    // Processar floresta
    for (int i = 0; i < PyList_Size(py_floresta); i++) {
        PyObject* py_arvore = PyList_GetItem(py_floresta, i);
        if (py_arvore == NULL) {
            PyErr_Print();
            return NULL;
        }

        ArvoreExploravel arvore;
        arvore.id = PyLong_AsLong(PyObject_GetAttrString(py_arvore, "id"));
        if (PyErr_Occurred()) {
            PyErr_Print();
            return NULL;
        }

        arvore.numero = PyLong_AsLong(PyObject_GetAttrString(py_arvore, "numero"));
        if (PyErr_Occurred()) {
            PyErr_Print();
            return NULL;
        }

        arvore.DAP = PyFloat_AsDouble(PyObject_GetAttrString(py_arvore, "DAP"));
        if (PyErr_Occurred()) {
            PyErr_Print();
            return NULL;
        }

        arvore.H = PyFloat_AsDouble(PyObject_GetAttrString(py_arvore, "H"));
        if (PyErr_Occurred()) {
            PyErr_Print();
            return NULL;
        }

        arvore.areaBasal = PyFloat_AsDouble(PyObject_GetAttrString(py_arvore, "areaBasal"));
        if (PyErr_Occurred()) {
            PyErr_Print();
            return NULL;
        }

        arvore.volume = PyFloat_AsDouble(PyObject_GetAttrString(py_arvore, "volume"));
        if (PyErr_Occurred()) {
            PyErr_Print();
            return NULL;
        }

        arvore.x = PyFloat_AsDouble(PyObject_GetAttrString(py_arvore, "x"));
        if (PyErr_Occurred()) {
            PyErr_Print();
            return NULL;
        }

        arvore.y = PyFloat_AsDouble(PyObject_GetAttrString(py_arvore, "y"));
        if (PyErr_Occurred()) {
            PyErr_Print();
            return NULL;
        }

        arvore.z = PyFloat_AsDouble(PyObject_GetAttrString(py_arvore, "z"));
        if (PyErr_Occurred()) {
            PyErr_Print();
            return NULL;
        }

        // Adicionar árvore à floresta
        florestaGlobal.push_back(arvore);
    }

    // Processar distâncias
    for (int i = 0; i < PyList_Size(py_distancias); i++) {
        PyObject* py_distancia_row = PyList_GetItem(py_distancias, i);
        if (py_distancia_row == NULL) {
            PyErr_Print();
            return NULL;
        }

        std::vector<double> distanciasRow;
        for (int j = 0; j < PyList_Size(py_distancia_row); j++) {
            PyObject* py_distancia = PyList_GetItem(py_distancia_row, j);
            if (py_distancia == NULL) {
                PyErr_Print();
                return NULL;
            }

            distanciasRow.push_back(PyFloat_AsDouble(py_distancia));
            if (PyErr_Occurred()) {
                PyErr_Print();
                return NULL;
            }
        }

        // Adicionar linha de distâncias
        distanciasGlobal.push_back(distanciasRow);
    }

    // Retornar um valor para indicar que a operação foi bem-sucedida
    Py_RETURN_NONE;
}

// Função wrapper para calculo da FO
static PyObject* py_calculaFOPatio(PyObject* self, PyObject* args) {
    PyObject* py_solucao = nullptr;
    PyObject* py_patios = nullptr;
    PyObject* py_volumes = nullptr;
    PyObject* py_arvores = nullptr;
    PyObject* py_item_patio = nullptr;
    PyObject* py_item_volume = nullptr;
    PyObject* py_sublista = nullptr;
    PyObject* py_dict = nullptr;
    PyObject* py_id = nullptr;
    PyObject* py_numero = nullptr;
    PyObject* py_viavel = nullptr;

    double restVolSup;
    SolucaoStorageYard solucaoAtual;

    if (!PyArg_ParseTuple(args, "Od", &py_solucao, &restVolSup)) {
        PyErr_SetString(PyExc_ValueError, "Argumentos inválidos: Esperado um objeto de solução e um número de tipo double.");
        return NULL;
    }

    py_patios = PyObject_GetAttrString(py_solucao, "patios");
    py_volumes = PyObject_GetAttrString(py_solucao, "volumes");
    py_arvores = PyObject_GetAttrString(py_solucao, "arvores");

    if (!py_patios || !py_volumes || !py_arvores) {
        PyErr_SetString(PyExc_AttributeError, "A solução fornecida não contém os atributos 'patios', 'volumes' ou 'arvores'.");
        Py_XDECREF(py_patios);
        Py_XDECREF(py_volumes);
        Py_XDECREF(py_arvores);
        return NULL;
    }

    solucaoAtual.patios.resize(PyList_Size(py_patios));
    solucaoAtual.volumes.resize(PyList_Size(py_volumes));
    solucaoAtual.arvores.resize(PyList_Size(py_arvores));

    for (int i = 0; i < numPatiosGlobal; i++) {
        py_item_patio = PyList_GetItem(py_patios, i);
        if (!py_item_patio || !PyLong_Check(py_item_patio)) {
            PyErr_SetString(PyExc_TypeError, "Cada item da lista de 'patios' deve ser um inteiro.");
            Py_XDECREF(py_patios);
            Py_XDECREF(py_volumes);
            Py_XDECREF(py_arvores);
            return NULL;
        }
        solucaoAtual.patios[i] = PyLong_AsLong(py_item_patio);

        if(PyList_Size(py_volumes) > 0){
            py_item_volume = PyList_GetItem(py_volumes, i);
            if (!py_item_volume || !PyFloat_Check(py_item_volume)) {
                PyErr_SetString(PyExc_TypeError, "Cada item da lista de 'volumes' deve ser um número de ponto flutuante.");
                Py_XDECREF(py_patios);
                Py_XDECREF(py_volumes);
                Py_XDECREF(py_arvores);
                return NULL;
            }
            solucaoAtual.volumes[i] = PyFloat_AsDouble(py_item_volume);
        }

        py_sublista = PyList_GetItem(py_arvores, i);
        if (!py_sublista) {
            PyErr_SetString(PyExc_TypeError, "Lista de árvores não encontrada para o índice de patio.");
            Py_XDECREF(py_patios);
            Py_XDECREF(py_volumes);
            Py_XDECREF(py_arvores);
            return NULL;
        }

        // if(PyList_Size(py_sublista) > 0){

        //     for (int j = 0; j < PyList_Size(py_sublista); j++) {
        //         py_dict = PyList_GetItem(py_sublista, j);
        //         if (!py_dict || !PyDict_Check(py_dict)) {
        //             PyErr_SetString(PyExc_TypeError, "Cada item da lista de 'arvores' deve ser um dicionário.");
        //             Py_XDECREF(py_patios);
        //             Py_XDECREF(py_volumes);
        //             Py_XDECREF(py_arvores);
        //             return NULL;
        //         }
    
        //         py_id = PyDict_GetItemString(py_dict, "id");
        //         py_numero = PyDict_GetItemString(py_dict, "numero");
    
        //         if (!py_id || !py_numero || !PyLong_Check(py_id) || !PyLong_Check(py_numero)) {
        //             PyErr_SetString(PyExc_TypeError, "O dicionário da árvore deve conter as chaves 'id' e 'numero', com valores inteiros.");
        //             Py_XDECREF(py_patios);
        //             Py_XDECREF(py_volumes);
        //             Py_XDECREF(py_arvores);
        //             return NULL;
        //         }
    
        //         int id = PyLong_AsLong(py_id);
        //         int numero = PyLong_AsLong(py_numero);
    
        //         solucaoAtual.arvores[i].push_back(Arvore(id, numero));
        //     }
        // }

    }

    Py_XDECREF(py_sublista);

    // Atribuição dos valores diretamente, verificando se o atributo existe
    solucaoAtual.distanciaTotal = PyFloat_AsDouble(PyObject_GetAttrString(py_solucao, "distanciaTotal"));
    solucaoAtual.FO = PyFloat_AsDouble(PyObject_GetAttrString(py_solucao, "FO"));
    solucaoAtual.tempoSol = PyFloat_AsDouble(PyObject_GetAttrString(py_solucao, "tempoSol"));
    solucaoAtual.t = PyFloat_AsDouble(PyObject_GetAttrString(py_solucao, "t"));
    solucaoAtual.tempo = PyFloat_AsDouble(PyObject_GetAttrString(py_solucao, "tempo"));
    solucaoAtual.numIteracoes = PyLong_AsLong(PyObject_GetAttrString(py_solucao, "numIteracoes"));
    solucaoAtual.numViaveis = PyLong_AsLong(PyObject_GetAttrString(py_solucao, "numViaveis"));
    solucaoAtual.numInviaveis = PyLong_AsLong(PyObject_GetAttrString(py_solucao, "numInviaveis"));

    py_viavel = PyObject_GetAttrString(py_solucao, "viavel");
    if (!py_viavel) {
        PyErr_SetString(PyExc_AttributeError, "A solução não contém o atributo 'viavel'.");
        Py_XDECREF(py_patios);
        Py_XDECREF(py_volumes);
        Py_XDECREF(py_arvores);
        return NULL;
    }
    solucaoAtual.viavel = PyObject_IsTrue(py_viavel);
    Py_XDECREF(py_viavel);

    // Modificando diretamente o py_solucao
    calculaFOPatio(solucaoAtual, restVolSup);

    // Atualiza diretamente os atributos de py_solucao
    py_patios = PyList_New(solucaoAtual.patios.size());
    for (size_t i = 0; i < solucaoAtual.patios.size(); i++) {
        PyList_SetItem(py_patios, i, PyLong_FromLong(solucaoAtual.patios[i]));
    }
    PyObject_SetAttrString(py_solucao, "patios", py_patios);

    py_volumes = PyList_New(solucaoAtual.volumes.size());
    for (size_t i = 0; i < solucaoAtual.volumes.size(); i++) {
        PyList_SetItem(py_volumes, i, PyFloat_FromDouble(solucaoAtual.volumes[i]));
    }
    PyObject_SetAttrString(py_solucao, "volumes", py_volumes);

    PyObject_SetAttrString(py_solucao, "distanciaTotal", PyFloat_FromDouble(solucaoAtual.distanciaTotal));
    PyObject_SetAttrString(py_solucao, "FO", PyFloat_FromDouble(solucaoAtual.FO));
    PyObject_SetAttrString(py_solucao, "tempoSol", PyFloat_FromDouble(solucaoAtual.tempoSol));
    PyObject_SetAttrString(py_solucao, "tempo", PyFloat_FromDouble(solucaoAtual.tempo));
    PyObject_SetAttrString(py_solucao, "t", PyFloat_FromDouble(solucaoAtual.t));
    PyObject_SetAttrString(py_solucao, "numIteracoes", PyLong_FromLong(solucaoAtual.numIteracoes));
    PyObject_SetAttrString(py_solucao, "numViaveis", PyLong_FromLong(solucaoAtual.numViaveis));
    PyObject_SetAttrString(py_solucao, "numInviaveis", PyLong_FromLong(solucaoAtual.numInviaveis));
    PyObject_SetAttrString(py_solucao, "viavel", solucaoAtual.viavel ? Py_True : Py_False);

    py_arvores = PyList_New(numPatiosGlobal);  // Criação da lista principal para os patios

    for (size_t i = 0; i < numPatiosGlobal; i++) {
        // Verifica se o vetor de arvores[i] não está vazio antes de criar a sublista
        // if (solucaoAtual.arvores[i].empty()) {
            // Se estiver vazio, criamos uma lista vazia para essa posição
            py_sublista = PyList_New(0);
        // } else {
        //     // Caso contrário, criamos a sublista com o tamanho apropriado
        //     py_sublista = PyList_New(solucaoAtual.arvores[i].size());
        //     for (size_t j = 0; j < solucaoAtual.arvores[i].size(); j++) {
        //         py_dict = PyDict_New();
        //         PyDict_SetItemString(py_dict, "id", PyLong_FromLong(solucaoAtual.arvores[i][j].id));
        //         PyDict_SetItemString(py_dict, "numero", PyLong_FromLong(solucaoAtual.arvores[i][j].numero));
        //         PyList_SetItem(py_sublista, j, py_dict);
        //     }
        // }

        // Atribui a sublista à lista principal
        PyList_SetItem(py_arvores, i, py_sublista);
    }
    PyObject_SetAttrString(py_solucao, "arvores", py_arvores);

    // Limpeza dos objetos temporários
    Py_XDECREF(py_patios);
    Py_XDECREF(py_volumes);
    Py_XDECREF(py_arvores);
    Py_XDECREF(py_item_patio);
    Py_XDECREF(py_item_volume);
    Py_XDECREF(py_dict);
    Py_XDECREF(py_id);
    Py_XDECREF(py_numero);
    Py_XDECREF(py_viavel);
    Py_XDECREF(py_sublista);

    // Retorna None, pois não precisamos retornar nenhum valor
    Py_RETURN_NONE;
}


// Definição do módulo Python
static PyMethodDef TadRoadForestMethods[] = {
    {"calculaFOPatio", py_calculaFOPatio, METH_VARARGS, "Calcula a função objetivo para a solução do pátio."},
    {"definicaoVariaveisGlobais", py_definicaoVariaveisGlobais, METH_VARARGS, "Recebe as informações de floresta e distâncias."},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef TadRoadForestModule = {
    PyModuleDef_HEAD_INIT,
    "TadRoadForest",   // Nome do módulo
    "Módulo de cálculo da função objetivo",  // Descrição
    -1,  // Tamanho do estado do módulo
    TadRoadForestMethods
};

PyMODINIT_FUNC PyInit_TadRoadForest(void) {
    return PyModule_Create(&TadRoadForestModule);
}
