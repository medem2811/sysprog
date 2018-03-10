/*
 * Symboltable.h
 *
 * The Symboltable is a way to store and look up token that are
 * identifiers and to keep track on the values they store
 * To quickly access the data it uses a hashmap
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */

#ifndef SYMBOLTABLE_H_
#define SYMBOLTABLE_H_

#include "StringTab.h"
#include "Key.h"

class Symboltable {
public:
	/**
	 * constructor for symboltable
	 * initializes size for hashtable
	 */
	Symboltable();
	virtual ~Symboltable();

	/**
	 * initializes Table with keywords
	 */
	void initSymbols();

	/**
	 * a function to add a new lexem to the table or
	 * save new information about said lexem
	 * @return: Key
	 */
	Key* insert (char* lexem);

	/**
	 * returns the information bound to the key
	 * @return: lexem
	 */
	char* lookup (char* key);

private:

	StringTab strTab;

	int HASH_SIZE = 1024;
	/**
	 * hashfunction to make a new key
	 */
	char* hash (char* lexem);

};

#endif /* SYMBOLTABLE_H_ */
