/*
 * Key.h
 *
 * Stores the address in the string table aka the actual key
 *
 *  Created on: 10.03.2018
 *      Author: deme1013
 */

#ifndef SYMBOLTABLE_INCLUDES_KEY_H_
#define SYMBOLTABLE_INCLUDES_KEY_H_

#include "StringTab.h"

class Key {
public:

	/**
	 * Constructor
	 */
	Key (char* myPos, char* type);

	virtual ~Key();

	/**
	 * returns address
	 */
	char* getPos();

	/**
	 * returns type
	 */
	char* getType();

	/**
	 * checks if two keys are the same
	 */
	bool compareKeys(char* key);

private:
	char* key;
	char* type;

};



#endif /* SYMBOLTABLE_INCLUDES_KEY_H_ */
