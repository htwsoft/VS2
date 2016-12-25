
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
				    this->testeAnzeigeRootNode();
					cout << endl;
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
				case GET_FIRST_CHILD:
					this->testeGetFirstChild();
					cout << endl;
					break;
				case GET_NEXT_CHILD:
					this->testeGetNextChild();
					break;
				case SEARCH_CHILD:
					this->testeSearchChild();
					cout  << endl;
					break;
				case CREATE_ATTRIBUT:
					this->testeCreateAttribut();
					break;
				case SEARCH_ATTRIBUT:
					this->testeSearchAttribut();
					cout  << endl;
					break;
				case SET_WORK_NODE:
					this->testeSetWorkNode();
					cout  << endl;
					break;
				case LOAD_XML:
					this->testeLadeXML();
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


void XMLWorkerTest::testeAnzeigeRootNode()
{
	XMLNode * rootNode = NULL;
	rootNode = this->xmlWorker->getRootNode();
	cout << rootNode->toString(true) << endl;
}

void XMLWorkerTest::testeLadeXML()
{
	string fileName;
	cout << "Welche XML soll geladen werden?: ";
	cin >> fileName;
	if(this->xmlWorker->loadXML(fileName))
	{
		cout << endl << "Datei erfolgreich geladen" << endl;	
	}
	else
	{
		cout << endl << "Datei konnte nicht geladen werden!" << endl;
	}
}

void XMLWorkerTest::testeSearchAttribut()
{
	XMLAttribut * searchedAttr = NULL;
	string name;
	cout << "Name des gesuchten Attributes: ";
	cin >> name;
	searchedAttr = this->xmlWorker->getAttributWithName(name);
	if(searchedAttr == NULL)	
	{
		cout << "keine Node gefunden!" << endl;
	}
	else
	{
		cout << searchedAttr->toString() << endl;
	}
	
}

void XMLWorkerTest::testeSearchChild()
{
	XMLNode * searchedNode = NULL;
	string name;
	cout << "Name der gesuchten Node: ";
	cin >> name;
	searchedNode = this->xmlWorker->getChildNodeWithName(name);
	if(searchedNode == NULL)	
	{
		cout << "keine Node gefunden!" << endl;
	}
	else
	{
		cout << searchedNode->toString() << endl;
	}
	
}

void XMLWorkerTest::testeSetWorkNode()
{
	XMLNode * newWorkNode = NULL;
	newWorkNode = this->xmlWorker->getFirstChildNode();
	this->xmlWorker->setWorkNode(newWorkNode);
	cout << "neue WorkNode: " << newWorkNode->toString() << endl;
}

void XMLWorkerTest::testeCreateAttribut()
{
	XMLAttribut * attr = NULL;
	string name;
	string value;
	cout << "neues Attribut fuer Node: " << this->xmlWorker->getWorkNode()->getName() << endl;
	cout << "Name: ";
	cin >> name;
	cout << "Value: ";
	cin >> value;
	attr = this->xmlWorker->createAttribut(name, value);
	cout << "neues Attribut: " << attr->toString() << endl;
}

void XMLWorkerTest::testeGetNextChild()
{
	XMLNode * child;
	child = this->xmlWorker->getNextChildNode();
	cout << "First Child: " << child->toString() << endl;
	cout << "Father Node: " << child->getFatherNode()->toString() << endl;
	
}

void XMLWorkerTest::testeGetFirstChild()
{
	XMLNode * child;
	child = this->xmlWorker->getFirstChildNode();
	cout << "First Child: " << child->toString() << endl;
	cout << "Father Node: " << child->getFatherNode()->toString() << endl;
	
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
			<< GET_FIRST_CHILD << ": Wechsel zum ersten Child" << endl
			<< GET_NEXT_CHILD << ": Wechsel zum naechsten Child" << endl
			<< SEARCH_CHILD << ": suchen eines Childs" << endl
			<< CREATE_ATTRIBUT << ": Neues Attribut erstellen" << endl
			<< SEARCH_ATTRIBUT << ": suchen eines Attributes" << endl
			<< SET_WORK_NODE << ": Neue Work Node setzen" << endl
			<< LOAD_XML << ": XML laden" << endl
			<< SAVE_XML << ": XML speichern" << endl
			<< ENDE << ": Ende" << endl;

		cout << "Ihre Eingabe: ";
		cin >> benutzerEingabe;
		cout << endl;
	}
	while(benutzerEingabe < AUSGEBEN && benutzerEingabe > ENDE);
	return static_cast<Menueauswahl>(benutzerEingabe);	
} 