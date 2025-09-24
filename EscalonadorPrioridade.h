#ifndef ESCALONADOR_PRIORIDADE_H
#define ESCALONADOR_PRIORIDADE_H

#include <list>
#include <vector>
#include <algorithm>
#include "tarefa.h"

// Prioridade: maior número = maior prioridade; estável em empates (ordem de chegada).
inline std::list<Tarefa> EscalonadorPrioridade(const std::list<Tarefa>& filaEntrada) {
    std::list<Tarefa> out = filaEntrada; // cópia
    out.sort([](const Tarefa& a, const Tarefa& b){
        return a.prioridade > b.prioridade; // maior primeiro
    });
    return out;
}


#endif
