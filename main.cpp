#include <iostream>
#include <sstream>
#include <string>
#include <list>
#include <iomanip>
#include <cstdlib>
using namespace std;

#include "tarefa.h"
#include "EscalonadorSJF.h"
#include "EscalonadorMLQ.h"
#include "EscalonadorMLFQ.h"
#include "EscalonadorFCFS.h"
#include "EscalonadorPrioridade.h"
#include "EscalonadorRR.h"

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
    cout << "\n7 - Finalizar\n";
    cout << "\nQual escalonador deseja executar? ";
    cin >> opcao;
    
    // EXECUTAR O SJF
    if(opcao == 1){
        system("clear");
        Tarefas_escalonamento = escalonadorSJF(Tarefas);
        exibirTarefasComparacao(Tarefas, Tarefas_escalonamento, "FILA DE ENTRADA", " FILA POR SJF ");
        cout << "\nTempo de espera medio: " << calcularTempoMedioEspera(Tarefas_escalonamento) << " ms" << endl;
    }else if (opcao == 2){
        system("clear");
        Tarefas_escalonamento = escalonadorMultilevelQueue(Tarefas);
        exibirTarefasComparacao(Tarefas_escalonamento, Tarefas, " FILA POR MLQ ", "FILA DE ENTRADA");
        cout << "\nTempo de espera medio: " << calcularTempoMedioEspera(Tarefas_escalonamento) << " ms" << endl;
    }else if (opcao == 3){
      system("clear");
      Tarefas_escalonamento = escalonadorMultilevelFeedbackQueue(Tarefas);
      exibirTarefasComparacao(Tarefas_escalonamento, Tarefas, " FILA POR MLFQ ", "FILA DE ENTRADA");
      cout << "\nTempo de espera medio: " << tempoEsperaMedio << " ms" << endl;
    }else if (opcao == 4) {
      system("clear");
      Tarefas_escalonamento = EscalonadorFCFS(Tarefas);
      exibirTarefasComparacao(Tarefas_escalonamento, Tarefas, " FILA POR FCFS ", "FILA DE ENTRADA");
      cout << "\nTempo de espera medio: "
          << calcularTempoMedioEspera(Tarefas_escalonamento) << " ms" << endl;
    }else if (opcao == 5) {
      system("clear");
      int quantum;
      cout << "Informe o quantum (ms): ";
      cin >> quantum;

      Tarefas_escalonamento = EscalonadorRR(Tarefas, quantum);
      exibirTarefasComparacao(Tarefas_escalonamento, Tarefas, " FILA POR RR ", "FILA DE ENTRADA");

      cout << "\nTempo de espera medio (RR): "
          << calcularTempoMedioEsperaRR(Tarefas, quantum) << " ms" << endl;
    }else if (opcao == 6) {
      system("clear");
      Tarefas_escalonamento = EscalonadorPrioridade(Tarefas);
      exibirTarefasComparacao(Tarefas_escalonamento, Tarefas, " FILA POR PRIORIDADE ", "FILA DE ENTRADA");

      cout << "\nTempo de espera medio: "
          << calcularTempoMedioEspera(Tarefas_escalonamento) << " ms" << endl;
    }else if (opcao == 7) {
      break;
    }
    
  }

  return 0;
}