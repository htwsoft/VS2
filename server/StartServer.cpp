#include <iostream>
#include "./src/Messageboard.h"

using namespace std;

int main(int argc, char ** args)
{
	
	Messageboard * mb = 0;
	cout << "Server gestartet..." << endl;
	mb = new Messageboard("./messageboard.xml");
	cout << "Create New Message..." << endl;
	//createNewMessage(string message, string mid, int uid, string uName, bool withSave)
	mb->createNewMessage("Eine neue Message", 1000, "User XY");
	cout << "New Message Created" << endl;
	delete mb;
	cout << "Server beendet" << endl;
} 