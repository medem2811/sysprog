/*
 * Symboltable.cpp
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */

#include "../includes/Symboltable.h"

Symboltable::Symboltable() {

	hashSize = 1024;

	StringTab* hashTable = new StringTab[hashSize];

	initSymbols();
}

Symboltable::~Symboltable() {
}

void Symboltable::initSymbols() {

	this->insert("while", 5, "while");
	this->insert("WHILE", 5, "while");
	this->insert("if", 2, "if");
	this->insert("IF", 2, "if");

}

Key* Symboltable::insert(char* lexem, int size, char* type) {


	return 0;
}

char* Symboltable::lookup (char* key) {
	/**
	 * if key not found
	 * return 0
	 */

	return '\0';
}

int Symboltable::hash(char* lexem) {

	int hash = 0;

	while(*lexem) {

		hash = (hash << 7) + (int)*lexem;

		lexem++;
	}

	hash = hash % hashSize;

	return hash;
}


