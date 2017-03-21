#!/bin/bash
#Benoetigt zum Starten zwei werte: IP des ORB Servers und Port 
java -cp client.VS2 client.Dialog -ORBInitialHost $1 -ORBInitialPort $2
