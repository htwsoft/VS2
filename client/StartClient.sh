#!/bin/bash
#Benoetigt zum Starten zwei werte: IP des ORB Servers und Port 
java StartClient -ORBInitRef NameService=corbaloc::$1:$2/NameService
