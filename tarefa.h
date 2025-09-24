#ifndef TAREFA_H
#define TAREFA_H

#include <fstream>
#include <iostream>
#include <string>
#include <list>
#include <iomanip>
using namespace std;

// ESTRUTURA PARA GUARDAR AS TAREFAS/PROCESSOS DO ARQUIVO
struct Tarefa {
    string nome;
    int prioridade;
    int duracao;

    Tarefa(string n, int p, int d) : nome(n), prioridade(p), duracao(d) {}
};

// CARREGAR AS TAREFAS DO ARQUIVO
list<Tarefa> carregarTarefas(const string &nome_do_arquivo) {
    ifstream arquivo(nome_do_arquivo);
    
    list<Tarefa> tarefas;
    string linha;
  
    while (getline(arquivo, linha)) {
        stringstream ss(linha);
        string nome, prioridade_str, duracao_str;
  
        getline(ss, nome, ',');
        getline(ss, prioridade_str, ',');
        getline(ss, duracao_str, ',');
      
        int prioridade = stoi(prioridade_str);
        int duracao = stoi(duracao_str);
  
          tarefas.emplace_back(nome, prioridade, duracao);
    }
  
    arquivo.close();
    return tarefas;
  }
  
  // EXIBIR TABELA COM TAREFAS PRESENTES NA LISTA
  void exibirTarefas(const list<Tarefa> &tarefas, string nome_escalonamento) {
    cout << "|-----------" << nome_escalonamento << "-----------|" << endl;
    cout << left
         << "| " << setw(10) << "NOME"
         << "| " << setw(12) << "PRIORIDADE"
         << "| " << setw(10) << "DURACAO"
         << "|" << endl;
    cout << "|-------------------------------------|" << endl;
  
    for (const auto &t : tarefas) {
        cout << "| " << setw(10) << t.nome
             << "| " << setw(12) << t.prioridade
             << "| " << setw(10) << to_string(t.duracao) + " ms"
             << "|" << endl;
    }
    cout << "---------------------------------------" << endl;
  }

void exibirTarefasComparacao(const list<Tarefa> &lista1, 
    const list<Tarefa> &lista2,
    string nome1, string nome2) {
    cout << "|-----------" << nome1 << "-----------|   "
    << "|-----------" << nome2 << "-----------|" << endl;

    cout << left
    << "| " << setw(10) << "NOME"
    << "| " << setw(12) << "PRIORIDADE"
    << "| " << setw(10) << "DURACAO"
    << "|   "
    << "| " << setw(10) << "NOME"
    << "| " << setw(12) << "PRIORIDADE"
    << "| " << setw(10) << "DURACAO"
    << "|" << endl;

    cout << "|-------------------------------------|   "
    << "|-------------------------------------|" << endl;

    // iteradores para percorrer as duas listas
    auto it1 = lista1.begin();
    auto it2 = lista2.begin();

    while (it1 != lista1.end() || it2 != lista2.end()) {
    // coluna da lista1
    if (it1 != lista1.end()) {
    cout << "| " << setw(10) << it1->nome
    << "| " << setw(12) << it1->prioridade
    << "| " << setw(10) << to_string(it1->duracao) + " ms"
    << "|   ";
    ++it1;
    } else {
    cout << "| " << setw(10) << ""
    << "| " << setw(12) << ""
    << "| " << setw(10) << ""
    << "|   ";
    }

    // coluna da lista2
    if (it2 != lista2.end()) {
    cout << "| " << setw(10) << it2->nome
    << "| " << setw(12) << it2->prioridade
    << "| " << setw(10) << to_string(it2->duracao) + " ms"
    << "|" << endl;
    ++it2;
    } else {
    cout << "| " << setw(10) << ""
    << "| " << setw(12) << ""
    << "| " << setw(10) << ""
    << "|" << endl;
    }
    }

    cout << "---------------------------------------   "
    << "---------------------------------------" << endl;
}

// FUNÇÃO PARA CALCULAR O TEMPO MÉDIO DE ESPERA DOS ALGORITMOS
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
