CXX = g++        
CXXFLAGS = -Wall -g  
TARGET = Projeto
SRC = main.cpp tarefa.h EscalonadorFCFS.h EscalonadorMLQ.h EscalonadorMLFQ.h EscalonadorPrioridade.h EscalonadorRR.h EscalonadorSJF.h

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)

