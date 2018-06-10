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
#include "../../Parser/includes/TypeCheck.h"

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
	bool compareLexem(char* lexem);

	/**
	 * sets the new typeCheck
	 */
	void setTypeCheck(TypeCheck::Type type);
	/**
	 * returns typeCheck type
	 */
	TypeCheck::Type getTypeCheck();

private:
	char* key;
	char* type;
	TypeCheck::Type typeCheck;

};



#endif /* SYMBOLTABLE_INCLUDES_KEY_H_ */
