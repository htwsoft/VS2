# Makefile Übung 3

# Makros
CFLAGS = -O2 -Wall -g -std=c++11 -pedantic -Wall
CXX = g++
CC = gcc
LDXX = g++
LDFLAGS = 
LOESCHLISTE = *.o *.exe
XMLSOURCEPATH = XMLWorker/source/
SERVERSOURCEPATH = src/
SOAPSOURCEPATH = src/SOAP-Client/src/
SOAPREQUESTSPATH = src/SOAP-Client/src/requests/
SOAPSERVERCOMPATH = src/SOAP-Client/src/serverCom/
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



server01: SoapException.o RequestException.o ModifyRequest.o DeleteRequest.o stdsoap2.o soapC.o soapServerComWebserviceImplPortBindingProxy.o SendRequest.o SoapRequest.o SoapDeliverer.o SoapServerClient.o Message.o Messageboard.o FileWorker.o XMLWorker.o MessageboardServer.o ServerClient.o StartServer.cpp
	$(CXX) $(CFLAGS) -o StartServer SoapException.o RequestException.o ModifyRequest.o DeleteRequest.o stdsoap2.o soapC.o soapServerComWebserviceImplPortBindingProxy.o SendRequest.o SoapRequest.o SoapDeliverer.o SoapServerClient.o Message.o Messageboard.o XMLWorker.o FileWorker.o ServerClient.o MessageboardServer.o $(LIBS) StartServer.cpp
	
server02: Message.o Messageboard.o FileWorker.o XMLWorker.o MessageboardServer.o ServerClient.o StartServerClient.cpp
	$(CXX) $(CFLAGS) -o StartServerClient Message.o Messageboard.o XMLWorker.o FileWorker.o ServerClient.o MessageboardServer.o $(LIBS) StartServerClient.cpp

soap01: SoapException.o RequestException.o ModifyRequest.o DeleteRequest.o stdsoap2.o soapC.o soapServerComWebserviceImplPortBindingProxy.o SendRequest.o SoapRequest.o SoapDeliverer.o RunClient.cpp
	$(CXX) $(CFLAGS) -o RunClient SoapException.o RequestException.o ModifyRequest.o DeleteRequest.o stdsoap2.o soapC.o soapServerComWebserviceImplPortBindingProxy.o SendRequest.o SoapRequest.o SoapDeliverer.o RunClient.cpp

#Files fuer MessageBoard

SoapServerClient.o: $(SERVERSOURCEPATH)SoapServerClient.cpp $(SERVERSOURCEPATH)SoapServerClient.h
	$(CXX) $(CFLAGS) -c $(SERVERSOURCEPATH)SoapServerClient.cpp

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

#Files fuer SoapClient
SoapException.o: $(SOAPREQUESTSPATH)SoapException.cpp $(SOAPREQUESTSPATH)SoapException.h
	$(CXX) $(CFLAGS) -c $(SOAPREQUESTSPATH)SoapException.cpp

SoapDeliverer.o: $(SOAPSOURCEPATH)SoapDeliverer.cpp $(SOAPSOURCEPATH)SoapDeliverer.h
	$(CXX) $(CFLAGS) -c $(SOAPSOURCEPATH)SoapDeliverer.cpp

RequestException.o: $(SOAPREQUESTSPATH)RequestException.cpp $(SOAPREQUESTSPATH)RequestException.h
	$(CXX) $(CFLAGS) -c $(SOAPREQUESTSPATH)RequestException.cpp

SoapRequest.o: $(SOAPREQUESTSPATH)SoapRequest.cpp $(SOAPREQUESTSPATH)SoapRequest.h
	$(CXX) $(CFLAGS) -c $(SOAPREQUESTSPATH)SoapRequest.cpp

DeleteRequest.o: $(SOAPREQUESTSPATH)DeleteRequest.cpp $(SOAPREQUESTSPATH)DeleteRequest.h
	$(CXX) $(CFLAGS) -c $(SOAPREQUESTSPATH)DeleteRequest.cpp

ModifyRequest.o: $(SOAPREQUESTSPATH)ModifyRequest.cpp $(SOAPREQUESTSPATH)ModifyRequest.h
	$(CXX) $(CFLAGS) -c $(SOAPREQUESTSPATH)ModifyRequest.cpp

SendRequest.o: $(SOAPREQUESTSPATH)SendRequest.cpp $(SOAPREQUESTSPATH)SendRequest.h
	$(CXX) $(CFLAGS) -c $(SOAPREQUESTSPATH)SendRequest.cpp

soapC.o: $(SOAPSERVERCOMPATH)soapC.cpp $(SOAPSERVERCOMPATH)soapH.h
	$(CXX) $(CFLAGS) -c $(SOAPSERVERCOMPATH)soapC.cpp

soapServerComWebserviceImplPortBindingProxy.o: $(SOAPSERVERCOMPATH)soapServerComWebserviceImplPortBindingProxy.cpp $(SOAPSERVERCOMPATH)serverCom.h $(SOAPSERVERCOMPATH)soapServerComWebserviceImplPortBindingProxy.h
	$(CXX) $(CFLAGS) -c $(SOAPSERVERCOMPATH)soapServerComWebserviceImplPortBindingProxy.cpp 

stdsoap2.o: $(SOAPSERVERCOMPATH)stdsoap2.cpp $(SOAPSERVERCOMPATH)stdsoap2.h
	$(CXX) $(CFLAGS) -c $(SOAPSERVERCOMPATH)stdsoap2.cpp