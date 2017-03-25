# Makefile Übung 3

# Makros
CFLAGS = -O2 -Wall -g -std=c++11 -pedantic -Wall
CXX = g++
CC = gcc
LDXX = g++
LDFLAGS = 
LOESCHLISTE = *.o *.exe
SOURCEPATH = ./
REQUESTPATH = requests/
SERVERCOMPATH=serverCom/
OMNI_HOME     = /home/marco/Documents/HTW/Entwicklung/omniORB-4.2.1/
OMNI_INCLUDES = -I/request
OMNI_LIB_DIR  = $(OMNI_HOME)/lib
OMNIIDL       = $(OMNI_HOME)/bin/omniidl
INCLUDES      = $(OMNI_INCLUDES)
LIBS          = #-lomniORB4 -lomnithread -lomniDynamic4



all: soap01

clean:
	@echo "Folgende Dateien werden geloescht"
	@echo $(LOESCHLISTE)
	rm -f $(LOESCHLISTE)

#Abhaengigkeiten



soap01: SoapException.o RequestException.o ModifyRequest.o DeleteRequest.o stdsoap2.o soapC.o soapServerComWebserviceImplPortBindingProxy.o SendRequest.o SoapRequest.o SoapDeliverer.o RunClient.cpp
	$(CXX) $(CFLAGS) -o RunClient SoapException.o RequestException.o ModifyRequest.o DeleteRequest.o stdsoap2.o soapC.o soapServerComWebserviceImplPortBindingProxy.o SendRequest.o SoapRequest.o SoapDeliverer.o RunClient.cpp

#Files fuer MessageBoard
SoapException.o: $(REQUESTPATH)SoapException.cpp $(REQUESTPATH)SoapException.h
	$(CXX) $(CFLAGS) -c $(REQUESTPATH)SoapException.cpp

SoapDeliverer.o: $(SOURCEPATH)SoapDeliverer.cpp $(SOURCEPATH)SoapDeliverer.h
	$(CXX) $(CFLAGS) -c $(SOURCEPATH)SoapDeliverer.cpp

RequestException.o: $(REQUESTPATH)RequestException.cpp $(REQUESTPATH)RequestException.h
	$(CXX) $(CFLAGS) -c $(REQUESTPATH)RequestException.cpp

SoapRequest.o: $(REQUESTPATH)SoapRequest.cpp $(REQUESTPATH)SoapRequest.h
	$(CXX) $(CFLAGS) -c $(REQUESTPATH)SoapRequest.cpp

DeleteRequest.o: $(REQUESTPATH)DeleteRequest.cpp $(REQUESTPATH)DeleteRequest.h
	$(CXX) $(CFLAGS) -c $(REQUESTPATH)DeleteRequest.cpp

ModifyRequest.o: $(REQUESTPATH)ModifyRequest.cpp $(REQUESTPATH)ModifyRequest.h
	$(CXX) $(CFLAGS) -c $(REQUESTPATH)ModifyRequest.cpp

SendRequest.o: $(REQUESTPATH)SendRequest.cpp $(REQUESTPATH)SendRequest.h
	$(CXX) $(CFLAGS) -c $(REQUESTPATH)SendRequest.cpp

soapC.o: $(SERVERCOMPATH)soapC.cpp $(SERVERCOMPATH)soapH.h
	$(CXX) $(CFLAGS) -c $(SERVERCOMPATH)soapC.cpp

soapServerComWebserviceImplPortBindingProxy.o: $(SERVERCOMPATH)soapServerComWebserviceImplPortBindingProxy.cpp $(SERVERCOMPATH)serverCom.h $(SERVERCOMPATH)soapServerComWebserviceImplPortBindingProxy.h
	$(CXX) $(CFLAGS) -c $(SERVERCOMPATH)soapServerComWebserviceImplPortBindingProxy.cpp 

stdsoap2.o: $(SERVERCOMPATH)stdsoap2.cpp $(SERVERCOMPATH)stdsoap2.h
	$(CXX) $(CFLAGS) -c $(SERVERCOMPATH)stdsoap2.cpp

