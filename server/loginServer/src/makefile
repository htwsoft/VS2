# Autor: Christian Patzek(03.02.15)
# Aufruf: make oder make all
#
RULES=make-rules
CXXFLAGS=-Wall -pedantic

all:	LoginServer

LoginServer: LoginServer.o
	$(CXX) $(CXXFLAGS) -o $@ $^ -l sqlite3

		
include ./$(RULES)

