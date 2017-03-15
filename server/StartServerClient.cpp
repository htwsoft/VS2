#include <iostream>
#include "./src/ServerClient.h"
#include "./src/ConnectInformation.h"

using namespace std;

int main(int argc, char ** argv)
{
    cout << "ServerClient-Test gestartet" << endl;
    cout << "Create Objects..." << endl;
    ConnectInformation * ci = new ConnectInformation("127.0.0.1", 6000);
    ConnectInformation * ci2 = new ConnectInformation("127.0.0.1", 65001);
    ServerClient * sc = new ServerClient(ci);
    cout << "-----------------------------------------------" << endl;
    ConnectInformation ciFather = sc->connectToFather();    
    cout << "Father: " << ciFather.getIp() << " ("<< ciFather.getPort() << ")"<< endl;
    sc->saveChildInformation(2, "Child 1", ci2); 
    ConnectInformation ciChild  = sc->connectToChild("Child 1");
    cout << "Child: " << ciChild.getIp() << " ("<< ciChild.getPort() << ")"<< endl; 
    cout << "-----------------------------------------------" << endl;    
    cout << "Delete Objects..." << endl;
    delete sc;    
    delete ci;
    delete ci2;
    cout << "ServerClient-Test beendet" << endl;
    return 0;
}
