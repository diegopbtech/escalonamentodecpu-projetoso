#ifndef ESCALONADOR_MLFQ_H
#define ESCALONADOR_MLFQ_H

#include <iostream>
#include <list>
#include "tarefa.h"
#include "EscalonadorRR.h"

using namespace std;

inline double tempoEspera = 0.0;
inline double tempoEsperaMedio = 0.0;

// ESTRUTURA DE DADOS PARA FILA DE PRIORIDADE
struct FilaPrioridadeQuantum {
    int prioridade;
    int quantum;
    list<Tarefa> processos;
};

inline double calcularTempoTotalEsperaMLFQ(const std::list<Tarefa>& filaEntrada, int quantum) {
    if (filaEntrada.empty()) return 0.0;
    if (quantum <= 0) quantum = 1;

    std::vector<int> duracao;                          
    std::vector<int> prioridade;                     
    for (const auto& t : filaEntrada) {
        duracao.push_back(t.duracao);
        prioridade.push_back(t.prioridade);
    }

    const int n = (int)duracao.size();
    std::vector<int> restante = duracao;
    std::vector<int> completion(n, -1);
    std::deque<int> fila;
    for (int i = 0; i < n; ++i) fila.push_back(i);

    int tempo = 0;                                   

    while (!fila.empty()) {
        int i = fila.front(); fila.pop_front();
        if (restante[i] <= 0) continue;

        int exec = std::min(quantum, restante[i]);
        tempo += exec;                               
        restante[i] -= exec;

        if (restante[i] > 0) fila.push_back(i);
        else completion[i] = tempo;                  
    }

    double somaEspera = 0.0;
    for (int i = 0; i < n; ++i) {
        somaEspera += (completion[i] - duracao[i]);
    }

    // SE FOR O ÚLTIMO PROCESSO A SER ENCERRADO NÃO SOMAR A DURAÇÃO
    if (n > 0) {
        // PEGAR O ÍNDICE DO PROCESSO QUE TERMINOU POR ÚLTIMO
        int ultimoIdx = std::distance(
            completion.begin(), 
            std::max_element(completion.begin(), completion.end())
        );

        if (prioridade[ultimoIdx] == 1) {
            somaEspera -= (completion[ultimoIdx] - duracao[ultimoIdx]);
        }
    }

    return somaEspera;
}

list<Tarefa> escalonadorMultilevelFeedbackQueue(const list<Tarefa>& dados) {
    list<FilaPrioridadeQuantum> filas;

    // PEGAR O NÍVEL DE PRIORIDADE MÁXIMA
    int maxPrioridade = 0;
    for (const auto& t : dados) {
        if (t.prioridade > maxPrioridade)
            maxPrioridade = t.prioridade;
    }

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
            FilaPrioridadeQuantum nova;
            nova.prioridade = t.prioridade;
            nova.processos.push_back(t);
            filas.push_back(nova);
        }
    }

    // ORDENAR FILAS POR PRIORIDADE
    filas.sort([](const FilaPrioridadeQuantum& a, const FilaPrioridadeQuantum& b) {
        return a.prioridade > b.prioridade;
    });

    // ATRIBUINDO UM QUANTUM PARA CADA FILA DE PRIORIDADE
    for (auto& f : filas) {
        // ATRIBUINDO UM QUANTUM A CADA FILA DE ACORDO COM SUA PRIORIDADE
        // QUANTO MAIOR A PRIORIDADE, MENOR O QUANTUM
        f.quantum = (maxPrioridade - f.prioridade + 1) * 2;
    }

    // APLICANDO O ROUND ROBIN EM CADA FILA DE ACORDO COM SEU QUANTUM
    for (auto& f : filas) {
        f.processos = EscalonadorRR(f.processos, f.quantum);
        tempoEsperaMedio = calcularTempoTotalEsperaMLFQ(f.processos, f.quantum);
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

#endif