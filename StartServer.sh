#!/bin/bash
#Benoetigt zum Starten zwei werte: IP des ORB Servers und Port
./server/StartServer -ORBInitRef NameService=corbaloc::$1:$2/NameService -ORBtraceLevel 5
