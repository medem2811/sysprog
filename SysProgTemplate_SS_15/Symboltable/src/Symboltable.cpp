/*
 * Symboltable.cpp
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */

#include "../includes/Symboltable.h"

Symboltable::Symboltable() {

	StringTab* hashTable = new StringTab[HASH_SIZE];

	initSymbols();
}

Symboltable::~Symboltable() {
}

void Symboltable::initSymbols() {


}

Key* Symboltable::insert(char* lexem) {
	/**
	 * if lookup == 0
	 * 	make new Key
	 */
	return 0;
}

char* Symboltable::lookup (char* key) {
	/**
	 * if key not found
	 * return 0
	 */

	return '\0';
}

char* Symboltable::hash(char* lexem) {



	return '\0';
}


