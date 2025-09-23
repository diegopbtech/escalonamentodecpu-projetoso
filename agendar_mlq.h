#include <iostream>
#include <list>
#include "tarefa.h"

using namespace std;

// ESTRUTURA DE DADOS PARA FILA DE PRIORIDADE
struct FilaPrioridade {
    int prioridade;
    list<Tarefa> processos;
};

list<Tarefa> escalonadorMultilevelQueue(const list<Tarefa>& dados) {
    list<FilaPrioridade> filas;

    // PERCORRE A LISTA DE TAREFAS RECEBIDA
    for (const auto& t : dados) {
        // VERIFICA SE HÁ UMA FILA COM A MESMA PRIORIDADE E ADICIONA A TAREFA NESSA FILA
        bool encontrei = false;
        for (auto& f : filas) {
            if (f.prioridade == t.prioridade) {
                f.processos.push_back(t);
                encontrei = true;
                break;
            }
        }
        // SE NÃO HOUVER, CRIA UMA FILA NOVA COM A PRIORIDADE DA TAREFA
        if (!encontrei) {
            FilaPrioridade nova;
            nova.prioridade = t.prioridade;
            nova.processos.push_back(t);
            filas.push_back(nova);
        }
    }

    // ORDENAR FILAS POR PRIORIDADE
    filas.sort([](const FilaPrioridade& a, const FilaPrioridade& b) {
        return a.prioridade < b.prioridade;
    });

    // APLICANDO ALGORITMOS DE ESCALONAMENTO ESPECÍFICOS PARA CADA FILA

    // APLICANDO SJF PARA CADA FILA DE PRIORIDADE PAR
    for (auto& f : filas) {
        if (f.prioridade % 2 == 0) {
            f.processos = escalonadorSJF(f.processos);
        }
    }

    // APLICANDO FCFS PARA CADA FILA DE PRIORIDADE IMPAR
    for (auto& f : filas) {
        if (f.prioridade % 2 != 0) {
            f.processos.sort([](const Tarefa& a, const Tarefa& b) {
                return a.nome < b.nome;
            });
        }
    }

    // RETORNA A LISTA ORDENADA COM AS FILAS JUNTAS
    list<Tarefa> resultado;
    for (const auto& f : filas) {
        for (const auto& t : f.processos) {
            resultado.push_back(t);
        }
    }

    return resultado;
}