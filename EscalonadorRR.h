#ifndef ESCALONADOR_RR_H
#define ESCALONADOR_RR_H

#include <list>
#include <vector>
#include <deque>
#include <algorithm>
#include "tarefa.h"
#include "EscalonadorRR.h"

// RR: timeline por fatias; arrival=0; ordem de chegada preservada.
inline std::list<Tarefa> EscalonadorRR(const std::list<Tarefa>& filaEntrada, int quantum) {
    if (quantum <= 0) quantum = 1;                  // quantum mínimo

    std::vector<Tarefa> base(filaEntrada.begin(), filaEntrada.end());
    const int n = (int)base.size();

    std::deque<int> fila;                            // fila circular (índices)
    std::vector<int> restante(n, 0);                 // burst restante
    for (int i = 0; i < n; ++i) {
        restante[i] = base[i].duracao;
        fila.push_back(i);
    }

    std::list<Tarefa> timeline;                      // saída: fatias executadas

    while (!fila.empty()) {
        int i = fila.front(); fila.pop_front();
        if (restante[i] <= 0) continue;

        int exec = std::min(quantum, restante[i]);   // fatia = min(q, restante)
        timeline.emplace_back(base[i].nome, base[i].prioridade, exec);
        restante[i] -= exec;

        if (restante[i] > 0) fila.push_back(i);      // não terminou → volta ao fim
    }
    return timeline;
}

// Tempo médio de espera no RR (arrival=0): wait_i = completion_i - burst_i
inline double calcularTempoMedioEsperaRR(const std::list<Tarefa>& filaEntrada, int quantum) {
    if (filaEntrada.empty()) return 0.0;
    if (quantum <= 0) quantum = 1;

    std::vector<int> burst;                          // burst original
    for (const auto& t : filaEntrada) burst.push_back(t.duracao);

    const int n = (int)burst.size();
    std::vector<int> restante = burst;
    std::vector<int> completion(n, -1);
    std::deque<int> fila;
    for (int i = 0; i < n; ++i) fila.push_back(i);

    int tempo = 0;                                   // relógio global

    while (!fila.empty()) {
        int i = fila.front(); fila.pop_front();
        if (restante[i] <= 0) continue;

        int exec = std::min(quantum, restante[i]);
        tempo += exec;                               // avança o relógio
        restante[i] -= exec;

        if (restante[i] > 0) fila.push_back(i);
        else completion[i] = tempo;                  // terminou → fixa completion
    }

    double somaEspera = 0.0;
    for (int i = 0; i < n; ++i) somaEspera += (completion[i] - burst[i]);
    return somaEspera / n;
}

#endif