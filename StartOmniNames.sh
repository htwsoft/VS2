#!/bin/bash
#Benoetigt zum Starten zwei werte: IP und Port 
sudo omniNames -ORBendPointPublish giop:tcp:$1:$2 -ORBsupportBootstrapAgent 1
