/*
 * XMLWorker.h
 *  Created on: 15.12.2016
 *  Author: Marco Palumbo
 *  Klasse zum Testen und demonstrieren der XMLWorkerKlasse
 */
 
#ifndef XMLWORKERTEST_H_
#define XMLWORKERTEST_H_

#include "XMLWorker.h"

enum Menueauswahl {AUSGEBEN = 1, NEUE_XML, ANZAHL_CHILDS_ROOT, CREATE_CHILD, NODE_WITH_CHILD, 
					NODE_WITHOUT_CHILD, GET_FIRST_CHILD, GET_NEXT_CHILD, SEARCH_CHILD,
					CREATE_ATTRIBUT, SEARCH_ATTRIBUT, SET_WORK_NODE, LOAD_XML, SAVE_XML, ENDE};

class XMLWorkerTest
{
	private:
		XMLWorker * xmlWorker;
		Menueauswahl zeigeMenue();
		void testeAnzeigeRootNode();
		void testeNeueRoot();
		void testeSetWorkNode();
		void testeCreateAttribut();
		void testeGetFirstChild();
		void testeGetNextChild();
		void testeAnzahlChildsRoot();
		void testeCreateChildNode();
		void testeAusgabeWorkNodeOhneChild();
		void testeAusgabeWorkNodeMitChild();
		void testeXMLspeichern();
		void testeSearchChild();
		void testeSearchAttribut();
		void testeLadeXML();
		void starteBenutzersteuerung();
	public:
		XMLWorkerTest();
		~XMLWorkerTest();
		void starteTest();	
};

#endif