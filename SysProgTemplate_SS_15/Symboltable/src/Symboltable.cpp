/*
 * Symboltable.cpp
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */

#include "../includes/Symboltable.h"
#include <iostream>
using namespace std;

Symboltable::Symboltable() {

	hashSize = 1024;

	this->hashTable = new LinkedList[hashSize];
	strTab = new StringTab();

	initSymbols();
}

Symboltable::~Symboltable() {
}

void Symboltable::initSymbols() {


	//initializes Symboltable with keywords
	this->insert((char*)"while", 5,(char*) "while");
	this->insert((char*)"WHILE", 5,(char*) "while");
	this->insert((char*)"if", 2,(char*) "if");
	this->insert((char*)"IF", 2,(char*) "if");

}

Key* Symboltable::insert(char* lexem, int size, char* type) {

	Key* key = lookup(lexem);

	//if key doesn't already exist
	if (key == NULL) {

		//creates a new key
		key = new Key(strTab->insert(lexem, size), type);

		//checks whether a hash value already has a list or not
		if (this->hashTable[hash(lexem)].isEmpty()) {
			this->hashTable[hash(lexem)].initList(key);
		} else {
			this->hashTable[hash(lexem)].insert(key);
		}
	}


	return key;
}

Key* Symboltable::lookup (char* lexem) {

	Key* key;

	if (!this->hashTable[hash(lexem)].isEmpty()) {

		//uses Linked List to see if key is already stored there
		key = this->hashTable[hash(lexem)].contains(lexem);

		return key;
	}

	return NULL;
}

int Symboltable::hash(char* lexem) {

	unsigned int hash = 0;

	//this one is basically from wikipedia
	//works though
	while(*lexem) {

		hash = (hash << 7) + (int)*lexem;

		lexem++;
	}

	hash = hash % hashSize;

	return hash;
}


