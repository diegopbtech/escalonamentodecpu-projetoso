#ifndef TAREFA_H
#define TAREFA_H

#include <string>
#include <list>
using namespace std;

struct Tarefa {
    string nome;
    int prioridade;
    int duracao;

    Tarefa(string n, int p, int d) : nome(n), prioridade(p), duracao(d) {}
};

double calcularTempoMedioEspera(const list<Tarefa>& processos) {
    if (processos.empty()) return 0.0;

    double soma = 0;
    double processoAtual = 0;

    for (const auto& t : processos) {
        soma += processoAtual;
        processoAtual += t.duracao;
    }

    return soma / processos.size();
}

#endif
