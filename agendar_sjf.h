#include <iostream>
#include <list>
using namespace std;

#include "tarefa.h"

list<Tarefa> escalonadorSJF(const list<Tarefa>& dados) {
    list<Tarefa> processos = dados;

    // SELECT SORT EMBUTIDO NA BIBLIOTECA LIST PARA ORDENAR A FILA DE PROCESSOS PELA DURAÇÃO
    processos.sort([](const Tarefa& a, const Tarefa& b) {
        return a.duracao < b.duracao;
    });

    return processos;
}