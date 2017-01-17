# Makefile Übung 3

# Makros
CFLAGS = -O2 -Wall -g -std=c++11 -pedantic -Wall
CXX = g++
CC = gcc
LDXX = g++
LDFLAGS = 
LOESCHLISTE = *.o *.exe
XMLSOURCEPATH = ./XMLWorker/source/
SERVERSOURCEPATH = ./src/


all: server01

clean:
	@echo "Folgende Dateien werden geloescht"
	@echo $(LOESCHLISTE)
	rm -f $(LOESCHLISTE)

#Abhaengigkeiten



server01: Message.o Messageboard.o FileWorker.o XMLWorker.o StartServer.cpp
	$(CXX) $(CFLAGS) -o server01 Message.o Messageboard.o XMLWorker.o FileWorker.o StartServer.cpp
	

#Files fuer MessageBoard

FileWorker.o: $(XMLSOURCEPATH)FileWorker.cpp $(XMLSOURCEPATH)FileWorker.h
	$(CXX) $(CFLAGS) -c $(XMLSOURCEPATH)FileWorker.cpp 
	
Messageboard.o: $(SERVERSOURCEPATH)Messageboard.cpp $(SERVERSOURCEPATH)Messageboard.h $(SERVERSOURCEPATH)ConnectInformation.h $(SERVERSOURCEPATH)BoardInformation.h
	$(CXX) $(CFLAGS) -c $(SERVERSOURCEPATH)Messageboard.cpp
	
Message.o: $(SERVERSOURCEPATH)Message.cpp $(SERVERSOURCEPATH)Message.h
	$(CXX) $(CFLAGS) -c $(SERVERSOURCEPATH)Message.cpp 
	
#Files fuer XML
	
XMLWorker.o: $(XMLSOURCEPATH)XMLWorker.cpp $(XMLSOURCEPATH)XMLWorker.h $(XMLSOURCEPATH)FileWorker.h
	$(CXX) $(CFLAGS) -c $(XMLSOURCEPATH)XMLWorker.cpp
