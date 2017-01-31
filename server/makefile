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
OMNI_HOME     = /home/marco/Documents/HTW/Entwicklung/omniORB-4.2.1/
OMNI_INCLUDES = -I$(OMNI_HOME)/include
OMNI_LIB_DIR  = $(OMNI_HOME)/lib
OMNIIDL       = $(OMNI_HOME)/bin/omniidl
INCLUDES      = $(OMNI_INCLUDES)
LIBS          = -lomniORB4 -lomnithread -lomniDynamic4



all: server01

clean:
	@echo "Folgende Dateien werden geloescht"
	@echo $(LOESCHLISTE)
	rm -f $(LOESCHLISTE)

#Abhaengigkeiten



server01: Message.o Messageboard.o FileWorker.o XMLWorker.o MessageboardServer.o ServerClient.o StartServer.cpp
	$(CXX) $(CFLAGS) -o StartServer Message.o Messageboard.o XMLWorker.o FileWorker.o ServerClient.o MessageboardServer.o $(LIBS) StartServer.cpp
	

#Files fuer MessageBoard

MessageboardServer.o: $(SERVERSOURCEPATH)MessageboardServer.cpp $(SERVERSOURCEPATH)MessageboardServer.h $(SERVERSOURCEPATH)VS2.hh
	$(CXX) $(CFLAGS) -c $(SERVERSOURCEPATH)MessageboardServer.cpp

ServerClient.o: $(SERVERSOURCEPATH)ServerClient.cpp $(SERVERSOURCEPATH)ServerClient.h $(SERVERSOURCEPATH)VS2.hh
	$(CXX) $(CFLAGS) -c $(SERVERSOURCEPATH)ServerClient.cpp

FileWorker.o: $(XMLSOURCEPATH)FileWorker.cpp $(XMLSOURCEPATH)FileWorker.h
	$(CXX) $(CFLAGS) -c $(XMLSOURCEPATH)FileWorker.cpp 
	
Messageboard.o: $(SERVERSOURCEPATH)Messageboard.cpp $(SERVERSOURCEPATH)Messageboard.h $(SERVERSOURCEPATH)ConnectInformation.h $(SERVERSOURCEPATH)BoardInformation.h
	$(CXX) $(CFLAGS) -c $(SERVERSOURCEPATH)Messageboard.cpp
	
Message.o: $(SERVERSOURCEPATH)Message.cpp $(SERVERSOURCEPATH)Message.h
	$(CXX) $(CFLAGS) -c $(SERVERSOURCEPATH)Message.cpp 
	
#Files fuer XML
	
XMLWorker.o: $(XMLSOURCEPATH)XMLWorker.cpp $(XMLSOURCEPATH)XMLWorker.h $(XMLSOURCEPATH)FileWorker.h
	$(CXX) $(CFLAGS) -c $(XMLSOURCEPATH)XMLWorker.cpp
