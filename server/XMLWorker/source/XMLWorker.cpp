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
	this->indexWorkNode = 0;
}

XMLWorker::~XMLWorker()
{
	if(!this->rootNode)
	{
		delete this->rootNode;
	}	
}

/*
* erstellt ein ChildNode fuer die aktuelle Work-Node
*/
XMLNode * XMLWorker::createChildNode(string name, string value)
{
	XMLNode * newChild;
	newChild = this->workNode->addChild(name, value, false);
	return newChild;
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
		delete this->rootNode;
		this->rootNode = NULL;
	}
	this->rootNode = new XMLNode(rootName, "", true, NULL);
	this->workNode = this->rootNode;
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
	XMLNode * newChild;
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
	XMLAttribut * newAttribut;
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
	XMLNode * childNode = 0;
	//Pruefen ib gueltiger Index
	if(index < vChildNodes.size())
	{
		childNode = vChildNodes[index];
	}
	return childNode;
}

/* Liefert das Attribut an der Stelle Index */
XMLAttribut * XMLNode::getAttribut(unsigned int index)
{
	XMLAttribut * attribut = 0;
	//Pruefen ib gueltiger Index
	if(index < vAttributes.size())
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