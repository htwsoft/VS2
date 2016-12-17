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

test01: FileWorker.o main.cpp
	$(CXX) $(CFLAGS) -o test01 FileWorker.o main.cpp
 
FileWorker.o: .\source\FileWorker.cpp .\source\FileWorker.h
	$(CXX) $(CFLAGS) -c $(SOURCEPATH)FileWorker.cpp
