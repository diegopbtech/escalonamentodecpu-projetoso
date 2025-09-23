#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <list>
#include <iomanip>
#include <cstdlib>
using namespace std;

#include "tarefa.h"
#include "agendar_sjf.h"
#include "agendar_mlq.h"

// CARREGAR DO ARQUIVO
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

int main() {
  // CARREGAR TAREFAS DO ARQUIVO E COLOCÁ-LAS EM UMA LISTA
  list<Tarefa> Tarefas = carregarTarefas("schedule.txt");
  list<Tarefa> Tarefas_escalonamento;
  int opcao;
  // EXIBIR TAREFAS DA LISTA CARREGADA
  exibirTarefas(Tarefas, "FILA DE ENTRADA");

  while(true){
    cout << "\nSistemas Operacionais\n";
    cout << "\n1 - Escalonador SJF\n";
    cout << "\n2 - Escalonador Multilevel Queue\n";
    cout << "\n3 - Escalonador Multilevel Feedback Queue\n";
    cout << "\n4 - Escalonador FCFS\n";
    cout << "\n5 - Escalonador Round Robin\n";
    cout << "\n6 - Escalonador Prioridade\n";
    cout << "\nQual escalonador deseja executar? ";
    cin >> opcao;
    
    // EXECUTAR O SJF
    if(opcao == 1){
        Tarefas_escalonamento = escalonadorSJF(Tarefas);
        exibirTarefas(Tarefas_escalonamento, " FILA POR SJF ");
        cout << "\nTempo de espera total: " << calcularTempoMedioEspera(Tarefas_escalonamento) << " ms" << endl;
    }else if (opcao == 2){
        Tarefas_escalonamento = escalonadorMultilevelQueue(Tarefas);
        exibirTarefas(Tarefas_escalonamento, " FILA POR MLQ ");
        cout << "\nTempo de espera total: " << calcularTempoMedioEspera(Tarefas_escalonamento) << " ms" << endl;
    }
  }

  return 0;
}