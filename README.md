@Marco

OmniORB_4.2.1/
	READMEfirst.txt
	READMEunix.txt
	sample.reg

1) zuerst den OmniORB Dienst starten!

sudo orbd -ORBInitialPort 6000 -ORBInitialHost 127.0.0.1

(gleiche Funktion wie orbd --> fuer java)
sudo omniNames -ORBendPointPublish giop:tcp:127.0.0.1:6000 -ORBsupportBootstrapAgent 1

sudo ./StartServer.sh 127.0.0.1 6000




# VS2
Verteilte Anzeigetafeln - CORBA
------------------------------------------------------------------------------------------------------------------------
Wiki zum CORBA Projekt:
------------------------------------------------------------------------------------------------------------------------
!!!Hier bitte eintragen fuer was die einzelnen Dateien sind!!!


VS2/server/src
--------------

Message.cpp --> Enthält Methoden/Funktionen zum erstellen/bearbeiten von Nachrichten

Message.h --> Klasse definiert Aufbau/Struktur einer Nachricht

MessageBoard.cpp --> Funktionen zum erstellen eines Knoten als Anzeigetafel

MessageBoard.h --> Klasse definiert Aufbau/Struktur einer Anzeigetafeln

ConnectInformation.h --> Verbindungsinformationen eines Knotens / Methoden definieren Umgang mit IP-Adresse und Port

========================================================================================================================

VS2/server/XMLWorker/src
------------------------

XMLWorker.cpp ---> Methoden der XMLWorker Klasse

XMLWorker.h ---> Klasse zum Lesen/Bearbeiten von XML Dateien

FileWorker.cpp ---> enthält Methoden der FileWorker Klasse

FileWorker.h ---> Klasse zum Lesen einer Datei

XMLWorkerTest.cpp --->

XMLWorkerTest.h --->
