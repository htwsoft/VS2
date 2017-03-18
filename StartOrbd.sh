#!/bin/bash
#Benoetigt zum Starten zwei werte: IP des ORB Servers und Port
sudo orbd -ORBInitialPort $2 -ORBInitialHost $1
