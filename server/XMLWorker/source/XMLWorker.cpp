#include ".\XMLWorker.h"
#include ".\FileWorker.h"
#include <String>
#include <cstdlib>
#include <sstream>

/*********************************************
* Methoden der XMLWorker-Klasse              *
*********************************************/
XMLWorker::XMLWorker()
{
	this->rootNode = NULL;
	this->workNode = NULL;
	this->indexChildNode = -1;
	this->indexAttribut = -1;
}

XMLWorker::~XMLWorker()
{
	if(!this->rootNode)
	{
		this->clearXML();
	}	
}

/* 
* Funktion wertet die Nodes einer XML aus 
*/
void  XMLWorker::parseXML(FileReader * fileReader)
{
	string zeile;
	XMLNode * newNode = NULL;
	//Schleife da nodes auch child nodes besitzen koennen
	do
	{
		//Lesen einer Zeile der XML Datei
		zeile = fileReader->readLine();
		newNode = parseNode(zeile);		
	}while(!fileReader->isEof());
}

/*
* entfernen aller lerrzeichen am Anfang eines Strings
*/
XMLNode * XMLWorker::parseNode(string zeile)
{
	XMLNode * newNode = NULL;
	zeile = this->trim(zeile);
	cout << zeile << endl;
	return newNode;
}

/*
* entfernen aller lerrzeichen am Anfang eines Strings
*/
string XMLWorker::trim(string text)
{
	string worker;
	worker = text;
	while(worker.substr(0,1) == " ")
	{
		worker.erase(0, 1);
	}
	return worker;
}

/*
* prueft die zeile einer XML und liefert true zurueck wenn 
* eine Node in dieser geschlossen wird
*/
bool XMLWorker::isEndeTag(string name)
{
	return false;
}
string XMLWorker::readNodeName(string node)
{
	return "";
}

/* 
* Methode liest den Inhalt einer XML und soeichert diesen in
* XMLWorker. Liefert true zurueck wenn die Datei geladen werden 
* konnte
*/
bool XMLWorker::loadXML(string fileName)
{
	FileReader * fileReader = NULL; //eigene Klasse zum lesen der Datei
	bool dateiGeladen = false; 
	//Vorherige gespeicherter XMLleeren
	this->clearXML();
	try
	{
		//laden der XML in FileReader
		fileReader = new FileReader(fileName);
		//Pruefen ob die Datei einen Inhakt besitzt und ob sie
		//geoeffnet werden konnte
		if(!fileReader->isEof() && fileReader->isFileOpen())
		{
			parseXML(fileReader);
		}	
	}
	catch(const char * c)
	{
		cout << "Achtung: " << c << endl;
	}
	if(fileReader != NULL)
	{
		//schliessen der Datei
		delete fileReader;
	}
	return dateiGeladen;
}

/* 
* Funktion sucht nach einem Attribut mit einem Bestimmten Namen
* und liefert diese zurueck
*/
XMLAttribut * XMLWorker::getAttributWithName(string name)
{
	int attributIndex = 0;
	int anzAttributes = 0;
	string nameAttribut = "";
	XMLAttribut * searchedAttr = NULL;
	XMLAttribut * workAttr = NULL; 
	//Anzahl der Childs ermitteln
	anzAttributes = this->workNode->getAttributCount();
	if(anzAttributes > 0)
	{
		//suchen der ChildNode
		while(attributIndex < anzAttributes && searchedAttr == NULL)
		{
			workAttr = this->workNode->getAttribut(attributIndex);
			nameAttribut = workAttr->getName();
			//Prüfen ob Namen uebereinstimmen
			if(name.compare(nameAttribut) == 0)
			{
				searchedAttr = workAttr;
			}
			attributIndex++;
		}
	}
	return searchedAttr;
}

/* 
* Funktion sucht nach einer Node mit einem Bestimmten Namen
* und liefert diese zurueck
*/
XMLNode * XMLWorker::getChildNodeWithName(string name)
{
	int childIndex = 0;
	int anzChilds = 0;
	string nameNode = "";
	XMLNode * searchedNode = NULL;
	XMLNode * workNode = NULL; //Nicht workNode der Work-Klasse. Lediglich fuer diese Funktion
	//Anzahl der Childs ermitteln
	anzChilds = this->workNode->getChildCount();
	if(anzChilds > 0)
	{
		//suchen der ChildNode
		while(childIndex < anzChilds && searchedNode == NULL)
		{
			workNode = this->workNode->getChild(childIndex);
			nameNode = workNode->getName();
			//Prüfen ob Namen uebereinstimmen
			if(name.compare(nameNode) == 0)
			{
				searchedNode = workNode;
			}
			childIndex++;
		}
	}
	return searchedNode;
}

/* 
   Funktion wechselt zum naechsten Attribut ausgehend vom
   zuletzt aktiven Attribut 
*/
XMLAttribut * XMLWorker::getNextAttribut()
{
	XMLAttribut * attr = NULL;
	int newIndexAttribut = 0;
	if(this->workNode != NULL)
	{
		newIndexAttribut = this->indexAttribut + 1; //Neuer Index fuer das naechste Child
		attr = this->workNode->getAttribut(newIndexAttribut);
		if(attr != NULL)
		{
			this->indexAttribut = newIndexAttribut;
		}
	}
	return attr;	
}

/* Funktion liefert das erste Attribut der workNode */
XMLAttribut * XMLWorker::getFirstAttribut()
{
	XMLAttribut * attr = NULL;
	if(this->workNode != NULL)
	{
		attr = this->workNode->getAttribut(0);
		if(attr != NULL)
		{
			this->indexAttribut = 0;
		}
	}
	return attr;
}


/*
* erstellt ein neues Attribut fuer die workNode
*/
XMLAttribut * XMLWorker::createAttribut(string name, string value)
{
	XMLAttribut * newAttribut = NULL;
	if(this->workNode != NULL)
	{
		newAttribut = this->workNode->addAttribut(name, value);
	}
	return newAttribut;
}

/* neue WorkNode setzen */
void XMLWorker::setWorkNode(XMLNode * newWorkNode)
{
	if(newWorkNode != NULL)
	{
		this->workNode = newWorkNode;
		this->indexChildNode = -1;
		this->indexAttribut = -1;
	}
}

/*
* erstellt ein ChildNode fuer die aktuelle Work-Node
*/
XMLNode * XMLWorker::createChildNode(string name, string value)
{
	XMLNode * newChild = NULL;
	if(this->workNode != NULL)
	{
		newChild = this->workNode->addChild(name, value, false);
	}
	return newChild;
}

/* 
   Funktion wechselt zum naechsten Child ausgehend vom
   zuletzt aktiven child 
*/
XMLNode * XMLWorker::getNextChildNode()
{
	XMLNode * childNode = NULL;
	int newIndexChildNode = 0;
	if(this->workNode != NULL)
	{
		newIndexChildNode = this->indexChildNode + 1; //Neuer Index fuer das naechste Child
		childNode = this->workNode->getChild(newIndexChildNode);
		if(childNode != NULL)
		{
			this->indexChildNode = newIndexChildNode;
		}
	}
	return childNode;	
}

/* Funktion liefert die erste ChildNode der workNode */
XMLNode * XMLWorker::getFirstChildNode()
{
	XMLNode * childNode = NULL;
	if(this->workNode != NULL)
	{
		childNode = this->workNode->getChild(0);
		if(childNode != NULL)
		{
			this->indexChildNode = 0;
		}
	}
	return childNode;
}

/*
* Funktion liefert die FatherNode der workNode zurueck
* bsp: 	<test>
*		  <test2></test2>
*		</test>
* FatherNode von test2 = test
*/
XMLNode * XMLWorker::getFatherNode()
{
	XMLNode * fatherNode = NULL;
	//Pruefen ob workNode zugewiesen ist
	if(this->workNode != NULL)
	{
		 fatherNode = this->workNode->getFatherNode();
	}
	return fatherNode;
}

/*
* Methode erstellt eine neue XML.
* Falls eine XML bisher geladen wurde, wird
* diese vollstaendig verworfen
*/
void XMLWorker::createRootNode(string rootName)
{
	//Pruefen ob mit einer XML gearbietet wurde
	if(this->rootNode != NULL)
	{
		this->clearXML();
	}
	this->rootNode = new XMLNode(rootName, "", true, NULL);
	this->workNode = this->rootNode;
}

/* Loeschen der zuvor gespeicherten XML */
void XMLWorker::clearXML()
{
	if(this->rootNode != NULL)
	{
		delete this->rootNode;
		this->indexChildNode = -1;
		this->indexAttribut = -1;
		this->rootNode = NULL;	
	}
}

/*
* Methode speichert die im XMLWorker gespeicherte XML
* liefert true zurueck wenn die Datei gespeichert werden konnt
* sonst false
*/
bool XMLWorker::saveXML(string fileName)
{
	FileWriter * fileWriter;
	string xmlText = "";
	bool dateiGespeichert = false;
	try
	{
		
		fileWriter = new FileWriter(fileName);
		//XML als Text erstellen
		xmlText = this->rootNode->toString(true);
		//XML in Datei uebergeben
		fileWriter->writeLine(xmlText, false);
		//Datei schliessen und speichern
		delete fileWriter;	
		//isGood ist false falls ein Fehler aufgetreten ist
		dateiGespeichert = fileWriter->isGood();
	}
	catch(const char * c)
	{
		cout << "Achtung: " << c << endl;
	}
	return dateiGespeichert;
}


/* Liefert die Referenz auf die zuletzt angesprochene Node */
XMLNode * XMLWorker::getWorkNode()
{
	return this->workNode;
}

/* Liefert die Referenz auf die RootNode zurueck */
XMLNode * XMLWorker::getRootNode()
{
	this->workNode = this->rootNode;
	return this->rootNode;
}

/*********************************************
* Methoden der XMLNode-Klasse                *
*********************************************/
/*
* Konstruktor der XMLNode-Klasse
*/
XMLNode::XMLNode(string name, string value, bool isRoot, XMLNode * fatherNode):XMLElement(name, value)
{
	this->isRoot = isRoot;
	this->fatherNode = fatherNode;
	if(isRoot)
	{
		//nur root Node hat Ebene 0
		this->ebene = 0;
		this->value = "";
	}
	else
	{
		//alle anderen Ebenene FatherEbene+1
		this->ebene = this->fatherNode->getEbene()+1;
		this->value = value;
	}
}

/*
* Destruktor der XMLNode-Klasse
*/
XMLNode::~XMLNode()
{
	//Leeren der Child- und Attribut-Liste
	this->clearChilds();
	this->clearAttributes();
}

/*
* legt eine neue Child-Node für die Vater-Node an
* liefert den Index in der Child-liste zurueck
* asFirst gibt an ob das neue Child am Anfang oder
* am Ende eingefuegt werden soll
*/
XMLNode * XMLNode::addChild(string name, string value, bool asFirst)
{
	XMLNode * newChild = NULL;
	newChild = new XMLNode(name, value, false, this);
	/*Pruefen ob neue Node am Anfang oder ende eingefuegt werden soll */
	if(asFirst)
	{
		iterChilds = vChildNodes.begin();
		vChildNodes.insert(iterChilds, newChild);
	}
	else
	{
		vChildNodes.push_back(newChild);
	}
	return newChild;
}

XMLAttribut *  XMLNode::addAttribut(string name, string value)
{
	XMLAttribut * newAttribut = NULL;
	newAttribut = new XMLAttribut(name, value, this);
	vAttributes.push_back(newAttribut);
	return newAttribut;
}

/*  
* liefert die Node als String zurueck
* withChilds ist true wenn auch die childNodes gezeigt werden sollen
*/
string XMLNode::toString(bool withChilds)
{
	string node;
	node = node + "<" + this->name + this->attributesToString() + ">";
	//Pruefen ob ChildNodes vorhanden sind
	if(this->vChildNodes.size() > 0)
	{
		if(withChilds)
		{
			node = node + "\n" + this->childeNodesToString(true);
		}
		else
		{
			//wenn child node vorhanden sind ... zur verdeutlichung anzeigen
			node = node + "\n" + " ... " + "\n";
		}
	}
	else
	{
		//wenn keine ChildNodes vorhanden sind den value wert eintragen
		node = node + " " + this->value + " "; 
	}
	node = node +  "</" + this->name + ">";
	return node;
}

/*
* liefert alle ChildNodes als String zurueck
* withChilds ist true wenn die childs der ChildeNodes mitgeliefert werden sollen
*/
string XMLNode::childeNodesToString(bool withChilds)
{
	string nodes = "";
	int iAnzLeerzeichen = 0; //Anzahl Leerzeichen fuer Bessere Darstellung
	iAnzLeerzeichen = (this->ebene + 1) * 2;
	if(vChildNodes.size() > 0)
	{
		//alle Child-Nodes suchen und im Speicher freigeben
		for(iterChilds=vChildNodes.begin(); iterChilds<vChildNodes.end(); iterChilds++)
		{
			//generieren der LeerZeichen
			for(int i=0; i<iAnzLeerzeichen; i++)
			{
				nodes = nodes + " ";
			}
			nodes = nodes + (*iterChilds)->toString(withChilds) + "\n";
		}
	}	
	return nodes;
}

/*
* Liefert alle Attribute als String zurueck
*/
string XMLNode::attributesToString()
{
	string attribute = "";
	//prüfen ob attribute vorhanden sind
	if(vAttributes.size() > 0)
	{
		//alle Attribute suchen und die toString()-Methode aufrufen
		for(iterAttributes=vAttributes.begin(); iterAttributes<vAttributes.end(); iterAttributes++)
		{
			attribute = attribute + " " + (*iterAttributes)->toString();
		}
	}
	return attribute;	
}

/* Liefert die Child-Node an der Stelle Index */
XMLNode * XMLNode::getChild(unsigned int index)
{
	XMLNode * childNode = NULL;
	//Pruefen ib gueltiger Index
	if(index >= 0 && index < vChildNodes.size())
	{
		childNode = vChildNodes[index];
	}
	return childNode;
}

/* Liefert das Attribut an der Stelle Index */
XMLAttribut * XMLNode::getAttribut(unsigned int index)
{
	XMLAttribut * attribut = NULL;
	//Pruefen ib gueltiger Index
	if( index >= 0 && index < vAttributes.size())
	{
		attribut = vAttributes[index];
	}
	return attribut;
}
/* Funktion liefert die Ebene der Node zurueck */
int XMLNode::getEbene()
{
	return this->ebene;
}


/* Funktion liefert die Vater-Node der Node zurueck */
XMLNode * XMLNode::getFatherNode()
{
	return this->fatherNode;
}

/*
* Liefert den Wert isRoot der XMLNode zurueck
*/
bool XMLNode::getIsRoot()
{
	return this->isRoot;
}

/*
* Methode leert die Child-Liste der Node
*/
void XMLNode::clearChilds()
{
	//Prüfen ob Child-Nodes vorhanden sind
	if(vChildNodes.size() > 0)
	{
		//alle Child-Nodes suchen und im Speicher freigeben
		for(iterChilds=vChildNodes.begin(); iterChilds<vChildNodes.end(); iterChilds++)
		{
			delete *iterChilds;
		}
		vChildNodes.clear();	
	}
}

/*
* Methode liefert die Anzahl der Child-Nodes zurueck
*/
int XMLNode::getChildCount()
{
	return vChildNodes.size();
}

/*
* Methode liefert die Anzahl der Attribute zurueck
*/
int XMLNode::getAttributCount()
{
	return vAttributes.size();
}

/*
* Methode leert die Attribut-Liste der Node
*/
void XMLNode::clearAttributes()
{
	//prüfen ob attribute vorhanden sind
	if(vAttributes.size() > 0)
	{
		//alle Attribute suchen und im Speicher freigeben
		for(iterAttributes=vAttributes.begin(); iterAttributes<vAttributes.end(); iterAttributes++)
		{
			delete *iterAttributes;
		}
		vAttributes.clear();	
	}
}

/*********************************************
* Methoden der XMLAttribut-Klasse            *
*********************************************/

/* Konstruktor der XMLAttribut-Klasse */
XMLAttribut::XMLAttribut(string name, string value, XMLNode * fatherNode):XMLElement(name, value)
{
	this->fatherNode = fatherNode;
}

/* Funktion liefert die Vater-Node des Attributes zurueck */
XMLNode * XMLAttribut::getFatherNode()
{
	return this->fatherNode;
}

/* Funktion liefert das Attribut als String zurück zurueck 
* name="value"
*/
string XMLAttribut::toString()
{
	string text;
	text = this->name + "=\"" + this->value + "\"" ;
	return text;
}