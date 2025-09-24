#ifndef ESCALONADOR_FCFS_H
#define ESCALONADOR_FCFS_H

#include <list>
#include "tarefa.h"

// FCFS: mantém a ordem de chegada (ordem do arquivo/lista).
inline std::list<Tarefa> EscalonadorFCFS(const std::list<Tarefa>& filaEntrada) {
    return std::list<Tarefa>(filaEntrada.begin(), filaEntrada.end()); // cópia direta
}

#endif
