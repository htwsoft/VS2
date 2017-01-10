#include <iostream>
#include "./src/Messageboard.h"

using namespace std;

int main(int argc, char ** args)
{
	
	Messageboard * mb = 0;
	Message * message = 0;
	cout << "Server gestartet..." << endl;
	mb = new Messageboard("./new2.xml");
	message = mb->getHighlightedMessage();
	cout << "Message: " << message->toString() << endl;
	delete mb;
	cout << "Server beendet" << endl;
} 