/*
 * XMLWorker.h
 *  Created on: 15.12.2016
 *  Author: Marco Palumbo
 *  Klasse zum Lesen und bearbeiten einer XML
 */

#ifndef XMLWORKER_H_
#define XMLWORKER_H_

/**
* TO-DO:
* + Fehlermeldung fuer XML-Worker implementieren
* + parsen einer XML
* + speichern der Daten der geparsten XML
**/


#include <string>
#include <vector>
#include "./FileWorker.h"

using namespace std;

/*
* class stellt den Inhalt eines xml-elemnts dar
* z.B. <test id="100" > 2 </test>
*/
class XMLElement
{
	protected:
		string name; //Name des Elements
		string value; //Wert des Elements
	public:
		XMLElement(string name, string value){this->name = name; this->value = value;};
		~XMLElement(){};
		string getName(){return this->name=name;};
		string getValue(){return this->value;};
		void setValue(string value){this->value = value;};
};

class XMLNode;

/*
* Klasse stellt den Inhalt eines Attributes dar
* z.B. <test id="5"> 1 </test>
* name = id
* value = 5
* fatherNode = test
*/
class XMLAttribut: public XMLElement
{
	private:
		XMLNode * fatherNode; //Vater-Node des Attributes bzw. Node bei dem das Attribut steht
	public:
		XMLAttribut();
		XMLAttribut(string name, string value, XMLNode * fatherNode);
		~XMLAttribut(){};
		XMLNode * getFatherNode();
		string toString();
};

/*
* Klasse stellt den Inhakt einer XML-Node dar
* bsp: <test id="5"> Text </test>
* name = text
* value = text
* attribut = id="5"
*/
class XMLNode: public XMLElement
{
	private:
		int ebene; //gibt die Ebene der Node an. Root hat Ebene 0. Child der Root haben Ebene 1
		bool isRoot; //ist true wenn es sich um die RootNode handelt, also die erste Node der XML
		XMLNode * fatherNode; //alle bis auf die RootNode haben eine FatherNode
		vector<XMLNode *> vChildNodes; //Liste mit allen Kinder-Elementen einer Node
		vector<XMLNode *>::iterator iterChilds; //Iterator zum durchlaufen der Child-Nodes
		vector<XMLAttribut *> vAttributes; //Liste mit allen Attributen einer node
		vector<XMLAttribut *>::iterator iterAttributes; //Iterator zum durchlaufen der Attribute
		void clearChilds();
		void clearAttributes();
		string addLeerzeichen(int count, string text);
	public:
		XMLNode();
		XMLNode(string name, string value, bool isRoot, XMLNode * fatherNode);
		~XMLNode();
		XMLNode * addChild(string name, string value, bool asFirst); //Anlegen eines neuen Kind-Elements
		XMLNode * addChild(XMLNode * newChild, bool asFirst); //Anlegen eines neuen Kind-Elements
		XMLAttribut * addAttribut(string name, string value); //Anlegen eines neuen Attributes
		XMLAttribut * addAttribut(XMLAttribut * newAttribut); //Anlegen eines neuen Attributes
		XMLNode * getFatherNode();
		bool getIsRoot(); 
		XMLNode * getChild(unsigned int index);
		XMLAttribut * getAttribut(unsigned int index);
		int getChildCount();
		int getAttributCount();
		int getEbene();
		string attributesToString();
		string childeNodesToString(bool withChilds = false);
		string toString(bool withChilds = false); //erstellt den XML-Text fuer die Node
};

/*
* Klasse XMLWorker. Dient zum lesen und bearbeiten einer XML
* Nutzt die oben definierten Klassen
*/
class XMLWorker
{
	private:
		/* Hier noch File-Reader und -Writer */
		XMLNode * rootNode; //Pointer auf RootNode der XML
		XMLNode * workNode; // zuletzt gewaehlte / angesprochene Node
		int indexChildNode; //Index der aktuellen Node in der Childe-Node-Liste
							//der aktuellen Node
		int indexAttribut; //Index des aktuellen Attributes
		void parseXML(FileReader * fileReader);
		XMLNode * parseNode(FileReader * fileReader, string zeile, XMLNode * fatherNode); //Parst eine Zeile / eine Node einer XML und speichert dessen Werte
		void parseChilds(FileReader * fileReader, XMLNode * fatherNode);
		string parseNodeValue(string node);
		void parseAttributes(string nodeText, XMLNode * node);
		string readNodeName(string node);
		string trim(string text); //enfernt alle Leerzeichen am Anfang eines Strings
		bool isEndeTag(string node); //Prueft ob ein EndeTag fuer die Node gefunden wurde
		bool isEndeNode(string node, string name); //Prueft ob die Node zu ende ist. Wenn ohne Childs dann immer in der selben Zeile
		bool isNodeWithChilds(string node); //Liefert true zurueck falls es eine Node mit Child-Elementen ist
	public:
		XMLWorker();
		~XMLWorker();	
		bool saveXML(string fileName); //Speichert die in XMLWorker hinterlegte XML
		bool loadXML(string fileName); //laedt eine XML und speichert diese in XMLWorker
		void clearXML();
		void createRootNode(string rootName); //Erstellt eine neue Root-Node und damit eine neue XML
		XMLNode * createChildNode(string name, string value); //Erstellt ein neues Child fuer die aktuelle workNode
		XMLAttribut * createAttribut(string name, string value); //erstellt ein neues Attribut fuer die workNode
		XMLNode * getChildNodeWithName(string name); //Funktion sucht nach einer Node mit bestimmten Namen
		XMLAttribut * getAttributWithName(string name); //Funktion sucht nach einem Attribut mit bestimmten Namen
		XMLNode * getFatherNode(); //liefert die FathereNode der workNode
		XMLNode * getFirstChildNode(); //Liefert die erste ChildNode zurueck sofern vorhanden
		XMLNode * getNextChildNode(); //Liefert das naechste Child ausgehend vom letzten aktiven Child
		XMLAttribut * getFirstAttribut(); //Liefert das erste Attribut zurueck sofern vorhanden
		XMLAttribut * getNextAttribut(); //Liefert das naechste Attribut ausgehend vom letzten aktiven Attribut
		XMLNode * getRootNode(); //Liefert die RootNode der XML
		void setWorkNode(XMLNode * newWorkNode); //setzen einer neuen WorkNode
		XMLNode * getWorkNode(); //Referenz auf aktuelle workNode
};


#endif