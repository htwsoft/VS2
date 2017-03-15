#include <iostream>
#include "./src/ServerClient.h"
#include "./src/ConnectInformation.h"

using namespace std;

int main(int argc, char ** argv)
{
    cout << "ServerClient-Test gestartet" << endl;
    cout << "Create Objects..." << endl;
    ConnectInformation * ci = new ConnectInformation("127.0.0.1", 6000);
    ServerClient * sc = new ServerClient(ci);
    cout << "-----------------------------------------------" << endl;
    sc->notifyFather(); 
    cout << "-----------------------------------------------" << endl;    
    cout << "Delete Objects..." << endl;
    delete sc;    
    delete ci;
    cout << "ServerClient-Test beendet" << endl;
    return 0;
}
