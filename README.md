# Projeto final da disciplina Sistemas Operacionais UFPB

Projeto desenvolvido para a disciplina de Sistemas Operacionais, com o objetivo de implementar e comparar diferentes algoritmos de escalonamento de CPU.
O simulador lê uma lista de processos a partir de um arquivo .txt contendo: nome do processo, prioridade e duração, e permite escolher qual algoritmo aplicar para reordenar a fila.

## Algoritmos implementados:

1. SJF
2. Multilevel Queue (MLQ)
3. Multilevel Feedback Queue (MLFQ)
4. FCFS
5. Round Robin (RR)
6. Prioridade

## Equipe
- Diego Araújo dos Santos | Matrícula: 20220024992
  
  Implementação dos algoritmos SJF, Multilevel Queue e Multilevel Feedback Queue

- Gustavo Caminha da Silva Júnior | Matrícula: 20210114817
  
  Implementação dos algoritmos FCFS, Round Robin e Prioridade

## Instruções de USO

 Basta selecionar no menu principal o algoritmo desejado e observar o comportamento. A lista carregada inicialmente dos processos está no arquivo schedule.txt.
  
## Compilação
Executar os seguintes comandos:
 
  make
  
  ./Projeto


## Tempo Médio de Espera

| Algoritmo                              | Tempo médio de espera (ms) |
| -------------------------------------- | -------------------------- |
| SJF                                    | 76.6                       |
| Multilevel Queue                       | 91.8667                    |
| Multilevel Feedback Queue              | 120                        |
| Escalonador FCFS                       | 110.467                    |
| Escalonador Round Robin (quantum 10ms) | 132.6                      |
| Prioridade                             | 93.3333                    |
