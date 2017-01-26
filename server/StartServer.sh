#!/bin/bash
#
./StartServer -ORBInitRef NameService=corbaloc::$1:$2/NameService -ORBtraceLevel 20
