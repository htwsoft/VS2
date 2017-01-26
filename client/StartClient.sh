#!/bin/bash
#
java StartClient -ORBInitRef NameService=corbaloc::$1:$2/NameService
