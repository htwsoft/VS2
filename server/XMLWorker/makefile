# Makefile Übung 3

# Makros
CFLAGS = -O2 -Wall -g -std=c++11 -pedantic -Wall
CXX = g++
CC = gcc
LDXX = g++
LDFLAGS = 
LOESCHLISTE = *.o *.exe
SOURCEPATH = ./source/

all: test01

clean:
	@echo "Folgende Dateien werden geloescht"
	@echo $(LOESCHLISTE)
	rm -f $(LOESCHLISTE)

#Abhaengigkeiten

test01: FileWorker.o XMLWorker.o XMLWorkerTest.o main.cpp
	$(CXX) $(CFLAGS) -o test01 XMLWorkerTest.o  XMLWorker.o FileWorker.o main.cpp
	
XMLWorkerTest.o: $(SOURCEPATH)XMLWorkerTest.cpp $(SOURCEPATH)XMLWorkerTest.h $(SOURCEPATH)XMLWorker.h
	$(CXX) $(CFLAGS) -c $(SOURCEPATH)XMLWorkerTest.cpp 
	
XMLWorker.o: $(SOURCEPATH)XMLWorker.cpp $(SOURCEPATH)XMLWorker.h
	$(CXX) $(CFLAGS) -c $(SOURCEPATH)XMLWorker.cpp 
 
FileWorker.o: $(SOURCEPATH)FileWorker.cpp $(SOURCEPATH)FileWorker.h
	$(CXX) $(CFLAGS) -c $(SOURCEPATH)FileWorker.cpp
