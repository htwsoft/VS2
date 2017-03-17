#!/bin/bash
#Benoetigt zum Starten zwei werte: IP des ORB Servers und Port 
java ./client/Dialog -ORBInitialHost $1 -ORBInitialPort $2
