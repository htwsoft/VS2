#include "./XMLWorker.h"
#include "./FileWorker.h"
#include <string>
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
	string zeile = "";
	//Schleife da nodes auch child nodes besitzen koennen
	do
	{
		//Lesen einer Zeile der XML Datei
		zeile = fileReader->readLine();
		parseNode(fileReader, zeile, NULL);
        //Bei linux benötigt da sonst kein EOF gefunden wird
        fileReader->readLine();
	}while(!fileReader->isEof());
}

/*
* entfernen aller lerrzeichen am Anfang eines Strings
*/
XMLNode * XMLWorker::parseNode(FileReader * fileReader, string zeile, XMLNode * fatherNode)
{
	XMLNode * newNode = NULL; //Neue Node die zurueckgeliefert wird
	string nodeName = ""; //Name der Node
	string value = ""; //Wert der Node
	bool isRootNode = false; //true falls es die RootNode ist (fatherNode = NULL)
	isRootNode = (fatherNode == NULL);
	//Alle leerzeichen am Anfang der Zeile loeschen
	zeile = this->trim(zeile);
	//Name der Node erstellen / parsen
	nodeName = this->readNodeName(zeile);
	if(isRootNode)
	{
		this->createRootNode(nodeName);
		newNode = this->rootNode;
	}
	else
	{
		newNode = new XMLNode(nodeName, "", false, fatherNode);
	}
	//Pruefen ob es eine Node mit Child-Nodes ist
	/*
	* <father>
	*   <child1></child1>
	*   <child2></child2>
	* </father>
	*/
	if(!this->isEndeTag(zeile))
	{
		parseChilds(fileReader, newNode);
		this->parseAttributes(zeile, newNode);
	}
	else
	{
		value = this->parseNodeValue(zeile);
		newNode->setValue(value);
		this->parseAttributes(zeile, newNode);
	}
	return newNode;
}

/*
* Methode parst alle Attribute einer Node
*/
void XMLWorker::parseAttributes(string nodeText, XMLNode * node)
{
	size_t posGleich; //Position von "=" zum ermitteln eines Attributes. id = "12"
	size_t posEndFirstTag; //Position ">" das Attribute nur im Anfangs Tag <test id="1">
	size_t posHochkomma1;
	size_t posHochkomma2;
	string nodeWorker = ""; //arbeiter Variable
	string nodeName = ""; //Name der node die barbeitet wird
	string attributName = "";
	string attributValue = "";
	
	nodeWorker = nodeText;
	nodeName = 	node->getName();
	posEndFirstTag = nodeWorker.find(">");
	//Alles ab posEndFirstTag trennen
	//Bsp. <test id="2"> value </test> => <test id="2">
	nodeWorker.erase(posEndFirstTag+1, nodeWorker.length()- posEndFirstTag);
	//Alles bis zum nodeNamen trennen <test id="2"> => id="2">
	//+1 wg. "<"
	nodeWorker.erase(0, nodeName.length()+1);
	do
	{
		posGleich = nodeWorker.find("=");
		//Pruefen ob Attribute vorhanden sind
		if(posGleich != std::string::npos)
		{		
			//min. ein Attribut ist noch vorhanden
			//Leerzeichen am Anfang und am Ende entfernen
			nodeWorker = this->trim(nodeWorker);
			attributName = "";
			attributValue = "";
			//Position der beiden hockomma fuer den wert des Attributs
			//bsp. id="2" => 2
			posHochkomma1 = nodeWorker.find("\"");
			posHochkomma2 = nodeWorker.find("\"", posHochkomma1+1);
			//Kopieren des Attribut-Namens
			attributName = this->trim( nodeWorker.substr(0, posGleich-1) );
			//Kopieren des Attribut Wertes
			attributValue = this->trim( nodeWorker.substr(posHochkomma1+1, posHochkomma2-posHochkomma1-1) );
			nodeWorker.erase(0, posHochkomma2+1);	
			//erstellen eines neuen Attributes fuer die uebergeben node
			node->addAttribut(attributName, attributValue);
		}
	}
	while(posGleich != std::string::npos);
}

/*
* Funktion sucht die Kinder einer Vater-Node
*/
void XMLWorker::parseChilds(FileReader * fileReader, XMLNode * fatherNode)
{
	string fatherNodeName = "";
	string zeile = "";
	bool endOfFather = false;
	XMLNode * childNode = NULL;
	fatherNodeName = fatherNode->getName();
	do
	{
		zeile = fileReader->readLine();
		//Pruefen ob das ende der Vater-Node erreicht ist
		childNode = this->parseNode(fileReader, zeile, fatherNode);
		if(fatherNode->getName() != childNode->getName())
		{
			//Child-Node fuer FatherNode parsen
			fatherNode->addChild(childNode, false);
		}
		else
		{
			//Ende-Node der aktuellen FatherNode ist erreicht
			delete childNode;
			endOfFather = true;
		}
	}
	while(!fileReader->isEof() && (!endOfFather));
}

/* Funktion pars den Wert einer Node und liefert diesen zureuck */
string XMLWorker::parseNodeValue(string node)
{
	string value = "";
	size_t endFirtsNodeTag; //Position Ende des ersten Node Tags <test>
	size_t beginLastNodeTag; //Position beginn des Node-Tags </test>
	endFirtsNodeTag = node.find(">");
	beginLastNodeTag = node.find("</");
	//prüfen ob endFirtsNodeTag < beginLastNodeTag da bei </ende> anders rum
	if(endFirtsNodeTag < beginLastNodeTag)
	{
		//Kopieren des Node-Values
		value = node.substr(endFirtsNodeTag+1, (beginLastNodeTag-endFirtsNodeTag-1));
		//entfernen der leerzeichen am Anfang
		value = this->trim(value);
	}
	return value;
}

/*
* Funktion liefert den Namen einer Node zurueck
*/
string XMLWorker::readNodeName(string node)
{
	string name = "";
	size_t pos_leerzeichen; //Position fuer das erste leerzeichen
	size_t pos_GreaterThan; //Position fuer das erste ">";
	size_t pos_Slash; //Position des "/" wichtig wenn ende tag gefunden
	//Wenn Position fuer erstes Leerzeichen. Trennt name von attribut wert
	//<test id="">
	name = node;
	pos_leerzeichen = name.find(" ");
	//Position fuer ">" beendet den ersten teil der Node <test>value</test>
	pos_GreaterThan = name.find(">");
	//Position des Slah ermitteln. Muss bei Ende Tag auch entfernt werden
	pos_Slash = name.find("/");
	if(pos_leerzeichen != std::string::npos)
	{
		//leerzeichen gefunden <test id=""> oder <test> value </test>
		//Pruefen ob leerzeichen vor ">"
		if(pos_leerzeichen < pos_GreaterThan)
		{
			//Kopieren des Namens. Starten ab 2ter stelle um "<" nicht
			//mit zu kopieren
			name = name.substr(1, pos_leerzeichen-1);
			
		}
		else
		{
			//bsp. <test> value
			name = name.substr(1, pos_GreaterThan-1);
		}
	}
	else
	if(pos_GreaterThan != std::string::npos)
	{
		//Pruefen ob ">" gefunden wurde
		//Kopieren des Namens
		name = name.substr(1, pos_GreaterThan-1);
	}
	
	// wenn slash an erster stelle gefunden, "/" entfernen
	if(pos_Slash != std::string::npos && pos_Slash < pos_GreaterThan)
	{
		name = name.erase(0, 1);
	}
	return name;
}

/*
* prueft ob das Ende Tag in der aktuellen Node vorhanden ist
*/
bool XMLWorker::isEndeNode(string node, string name)
{
	size_t pos_name;
	bool endeTag = false;
	endeTag = this->isEndeTag(node); 
	//suchen des uebergebene Namens fuer die Node, derren Ende geprueft werden soll
	pos_name = node.find(name);
 	//npos gibt an das keine uebereinstimmung gefunden wurde mit find
	//Wenn das EndeTag und der NodeName gefunden wurden wird true zurueckgeliefert
	return endeTag && (pos_name != std::string::npos);
}

/*
* prueft ob das Ende Tag in der aktuellen Node vorhanden ist
*/
bool XMLWorker::isEndeTag(string node)
{
	size_t pos_endeTag;
	//Bsp: <test>value</test>
	pos_endeTag = node.find("</");
	//npos gibt an das keine uebereinstimmung gefunden wurde mit find
	return (pos_endeTag != std::string::npos);
}

/*
* entfernen alle lerrzeichen am Anfang und am Ende eines Strings
*/
string XMLWorker::trim(string text)
{
	string worker;
	worker = text;
	//Solange ein zeichen loeschen bis kein leerzeichen
	//mehr gefunden wird. 9 = Tabluator
    if(worker.size() > 0)
    {
	    while(worker.at(0) == ' ' || worker.at(0) == 9)
	    {
		    worker.erase(0, 1);
	    }
	    //entfernen der leerzeichen am Ende
	    while(worker.at(worker.length()-1) == ' ' || worker.at(worker.length()-1) == 9)
	    {	
			worker.pop_back();
	    }
    }
	return worker;
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
			dateiGeladen = true;
		}	
	}
	catch(const char * c)
	{
		cout << endl << "Achtung: " << c << endl;
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
		cout << endl << "Achtung: " << c << endl;
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
XMLNode::XMLNode():XMLElement("", "")
{
	this->isRoot = true;
	this->fatherNode = NULL;
	this->ebene = 0;
	this->value = "";
}

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

XMLNode * XMLNode::addChild(XMLNode * newChild, bool asFirst)
{
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

XMLAttribut * XMLNode::addAttribut(XMLAttribut * newAttribut)
{
	vAttributes.push_back(newAttribut);
	return newAttribut;	
}

/*  
* liefert die Node als String zurueck
* withChilds ist true wenn auch die childNodes gezeigt werden sollen
*/
string XMLNode::toString(bool withChilds)
{
	string node = "";
	string endeTag = "";
	int iAnzLeerzeichen = 0; //Anzahl Leerzeichen fuer Bessere Darstellung
	iAnzLeerzeichen = (this->ebene) * 2;
	node = node + "<" + this->name + this->attributesToString() + ">";
	endeTag = "</" + this->name + ">";
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
		endeTag = this->addLeerzeichen(iAnzLeerzeichen, endeTag);
	}
	else
	{
		//wenn keine ChildNodes vorhanden sind den value wert eintragen
		if(this->value != "")
		{
			node = node + " " + this->value + " "; 
		}
	}
	node = node + endeTag;
	return node;
}

/*
* liefert alle ChildNodes als String zurueck
* withChilds ist true wenn die childs der ChildeNodes mitgeliefert werden sollen
*/
string XMLNode::childeNodesToString(bool withChilds)
{
	string nodes = "";
	string node = "";
	int iAnzLeerzeichen = 0; //Anzahl Leerzeichen fuer Bessere Darstellung
	iAnzLeerzeichen = (this->ebene + 1) * 2;
	if(vChildNodes.size() > 0)
	{
		//alle Child-Nodes suchen und im Speicher freigeben
		for(iterChilds=vChildNodes.begin(); iterChilds<vChildNodes.end(); iterChilds++)
		{
			//generieren der LeerZeichen
			node = (*iterChilds)->toString(withChilds) + "\n";
			nodes = nodes + this->addLeerzeichen(iAnzLeerzeichen, node);
		}
	}	
	return nodes;
}

/* Fuegt am einfang eines Strings leerzeiche ein */
string XMLNode::addLeerzeichen(int count, string text)
{
	string newText = "";
	for(int i=0; i<count; i++)
	{
		newText = newText + " ";
	}	
	newText = newText + text;
	return newText;
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
XMLAttribut::XMLAttribut():XMLElement("", "")
{
	this->fatherNode = NULL;
}

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
