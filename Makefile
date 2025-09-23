CXX = g++        
CXXFLAGS = -Wall -g  
TARGET = Projeto
SRC = main.cpp agendar_sjf.h agendar_mlq.h

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)
