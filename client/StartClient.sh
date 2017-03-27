#!/bin/bash
echo IP und Port
echo IDL - client/* und Dialog comp.
idlj -fall VS2.idl
javac client/*.java
javac Dialog.java

ordb -ORBDInitialHost $1

echo Starte Dialog mit IP $1 port $2

java Dialog $1 $2