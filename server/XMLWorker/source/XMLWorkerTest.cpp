
#include "XMLWorkerTest.h"
#include <iostream>

using namespace std;

XMLWorkerTest::XMLWorkerTest()
{
	this->xmlWorker = new XMLWorker();
}

XMLWorkerTest::~XMLWorkerTest()
{
	delete this->xmlWorker;
}

void XMLWorkerTest::starteTest()
{
	this->starteBenutzersteuerung();
}

/*
 * Methode Startet die Benutzersteuerung für den Test
 */
void XMLWorkerTest::starteBenutzersteuerung()
{
	Menueauswahl benutzerEingabe;
	do
	{
		benutzerEingabe = zeigeMenue();
		cout << endl;
		try
		{
			switch(benutzerEingabe)
			{
				case AUSGEBEN:
					cout << "ausgabe" << endl;
					break;
				case NEUE_XML:
				    this->testeNeueRoot();
					break;
				case ANZAHL_CHILDS_ROOT:
					this->testeAnzahlChildsRoot();
					cout  << endl;
					break;
				case CREATE_CHILD:
					this->testeCreateChildNode();
					cout  << endl;
					break;
				case NODE_WITHOUT_CHILD:
					this->testeAusgabeWorkNodeOhneChild();
					cout  << endl;
					break;
				case NODE_WITH_CHILD:
					this->testeAusgabeWorkNodeMitChild();
					cout  << endl;
					break;
				case SAVE_XML:
					this->testeXMLspeichern();
					cout  << endl;
					break;					
				case ENDE:
					cout << "Test beendet!" << endl;
					break;
				default:
					cout << "Ungueltige Eingabe!" << endl;
					break;
			}
		}
		catch(const char * c)
		{
			cout << "Achtung: " << c << endl;
		}
		catch(...)
		{
			cout << "Achtung: Unbekannter Fehler!" << endl;
		}
	}
	while(benutzerEingabe != ENDE);
}

void XMLWorkerTest::testeXMLspeichern()
{
	string fileName;
	bool speicherErfolgreich;
	cout << "Name der XML-Datei: ";
	cin >> fileName;
	speicherErfolgreich = this->xmlWorker->saveXML(fileName);
	if(speicherErfolgreich)
	{
		cout << "Datei wurde gespeichert" << endl;
	}
	else
	{
		cout << "Fehler beim Speichern der Datei!" << endl;
	}
	
}


/*
* teste Ausgabe der WorkNode ohne Childs
*/
void XMLWorkerTest::testeAusgabeWorkNodeOhneChild()
{
	XMLNode * workNode;
	workNode = this->xmlWorker->getWorkNode();
	cout << workNode->toString() << endl;
}

/*
* teste Ausgabe der WorkNode mit den Childs
*/
void XMLWorkerTest::testeAusgabeWorkNodeMitChild()
{
	XMLNode * workNode;
	workNode = this->xmlWorker->getWorkNode();
	cout << workNode->toString(true) << endl;
}

void XMLWorkerTest::testeCreateChildNode()
{
	string name = "";
	string value = "";
	XMLNode * workNode; //zuletzt angesprochene Node
	XMLNode * newChild; //Referenz auf neues Child
	workNode = this->xmlWorker->getWorkNode();
	cout << "neue Child-Node fuer Node: " << workNode->getName() << endl;
	cout << "Name: ";
	cin >> name;
	cout << "Value: ";
	cin >> value;
	//erstellen einer neuen Child-Node fuer die zuletzt
	//angesprochene Node
	newChild = this->xmlWorker->createChildNode(name, value);
	cout << "neue Node erstellt: " << newChild->toString() << endl;
}

/*
* Test ob anzahl der Root-ChildNodes richtig ausgegeben wird
*/
void XMLWorkerTest::testeAnzahlChildsRoot()
{
	XMLNode * rootNode;
	rootNode = this->xmlWorker->getRootNode();
	cout << "Anzahl Chids der Root: " << rootNode->getChildCount() << endl; 
}

/*
* testen ob anlegen der RoorNode funktioniert
*/
void XMLWorkerTest::testeNeueRoot()
{
	string name = "";
	cout<<"Name der RoorNode: ";
	cin >> name;
	this->xmlWorker->createRootNode(name);
}

Menueauswahl XMLWorkerTest::zeigeMenue()
{
	int benutzerEingabe = 0;
	do
	{
		cout << "Menueauswahl" << endl
			<< "---------------" << endl
			<< AUSGEBEN << ": Anzeigen der XML" << endl
			<< NEUE_XML << ": Neue Root erstellen" << endl
			<< ANZAHL_CHILDS_ROOT << ": Anz. Childs Root" << endl
			<< CREATE_CHILD << ": erstelle neue Child-Node" << endl
			<< NODE_WITH_CHILD << ": zeige Work-Node mit Child" << endl
			<< NODE_WITHOUT_CHILD << ": zeige Work-Node ohne Child" << endl
			<< SAVE_XML << ": XML speichern" << endl
			<< ENDE << ": Ende" << endl;

		cout << "Ihre Eingabe: ";
		cin >> benutzerEingabe;
		cout << endl;
	}
	while(benutzerEingabe < AUSGEBEN && benutzerEingabe > ENDE);
	return static_cast<Menueauswahl>(benutzerEingabe);	
} 